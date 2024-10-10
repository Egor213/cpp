#include <iostream>
#include <mpi.h>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric> 
#include <cstring>
#include <thread>
#define TEXT_SIZE 10
#define COMMUTATOR 0
#define SEND_FL true
#define RECV_FL false


struct Package
{
    int from_process;
    int to_process;
    char data[TEXT_SIZE];

    Package() {
        std::fill(data, data + TEXT_SIZE, '\0'); 
    }
};

std::vector<int> gen_mass(int size)
{
    std::vector<int> mass(size - 1);
    std::iota(mass.begin(), mass.end(), 1); 
    std::random_device rd; 
    std::mt19937 engine(rd()); 
    std::shuffle(mass.begin(), mass.end(), engine);
    return mass;
}

int gen_number_process(int size, int send_proc)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<> distrib(1, size - 1);
    int number = distrib(gen);
    while (number == send_proc)
    {
        number = distrib(gen);
    }
    return number;
}

void fill_random_chars(char* text) {
    std::random_device rd;
    std::mt19937 gen(rd());
    for (int i = 0; i < TEXT_SIZE - 1; ++i) {
        int random_char = gen() % 62;
        if (random_char < 26) {
            text[i] = 'A' + random_char;
        } else if (random_char < 52) {
            text[i] = 'a' + (random_char - 26);
        } else {
            text[i] = '0' + (random_char - 52);
        }
    }
    text[TEXT_SIZE - 1] = '\0';
}

std::pair<std::vector<char>, int> pack_data(Package &package)
{
    int buf_size = 0;
    std::vector<char> buf(sizeof(package));  
    MPI_Pack(&package.from_process, 1, MPI_INT, buf.data(), buf.size(), &buf_size, MPI_COMM_WORLD);
    MPI_Pack(&package.to_process, 1, MPI_INT, buf.data(), buf.size(), &buf_size, MPI_COMM_WORLD);
    MPI_Pack(package.data, TEXT_SIZE, MPI_CHAR, buf.data(), buf.size(), &buf_size, MPI_COMM_WORLD);
    return std::make_pair(buf, buf_size);
}

Package unpack_data(std::vector<char> &recv_buf, int recv_buf_size)
{
    Package package;
    MPI_Unpack(recv_buf.data(), sizeof(recv_buf), &recv_buf_size, &package.from_process, 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Unpack(recv_buf.data(), sizeof(recv_buf), &recv_buf_size, &package.to_process, 1, MPI_INT, MPI_COMM_WORLD);
    MPI_Unpack(recv_buf.data(), sizeof(recv_buf), &recv_buf_size, package.data, TEXT_SIZE, MPI_CHAR, MPI_COMM_WORLD); 
    return package;
}

void print_info(Package &package, int rank, bool stage)
{
    std::cout << "Process " << rank << ":";
    if (stage)
        std::cout << " send FROM: " << package.from_process;
    else
        std::cout << " recv FROM: " << package.from_process;
    std::cout << " TO: " << package.to_process 
              << " DATA: " << package.data 
              << '\n';
}

void print_order_proc(std::vector<int>& order_process)
{
    std::cout << "ORDER PROC: ";
    for (auto per : order_process)
    {
        std::cout << per << ' ';
    }
    std::cout << '\n';
}

Package create_start_package(int rank, int size)
{
    Package package;
    package.from_process = rank;
    package.to_process = gen_number_process(size, rank);
    fill_random_chars(package.data);
    return package;
}


int main(int argc, char **argv) {
    MPI_Init(&argc, &argv); 

    int rank, size;
    MPI_Comm_rank(MPI_COMM_WORLD, &rank);
    MPI_Comm_size(MPI_COMM_WORLD, &size);

    std::vector<int> order_process(size - 1);

    if (rank == 0)
    {
        order_process = gen_mass(size);
    }


    MPI_Bcast(order_process.data(), order_process.size(), MPI_INT, 0, MPI_COMM_WORLD);

    if (rank == 0)
    {
        print_order_proc(order_process);
    }

    for (auto order : order_process)
    {
        if (rank == order)
        {
            // создаем пакет и заполняем его данными
            Package package = create_start_package(rank, size);

            // упаковка данных
            auto temp = pack_data(package);
            std::vector<char> buf = temp.first;
            int buf_size = temp.second;

            // буфер для принятых данных
            int recv_buf_size = 0;
            std::vector<char> recv_buf(sizeof(package));
        
            // принятие и отправка данных
            print_info(package, rank, SEND_FL);
            MPI_Sendrecv(buf.data(), buf_size, MPI_BYTE, COMMUTATOR, 0, recv_buf.data(), sizeof(recv_buf), MPI_BYTE, COMMUTATOR, 0, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // распаковка данных
            Package recv_package = unpack_data(recv_buf, recv_buf_size);
            print_info(recv_package, rank, RECV_FL);

        }
        else if (rank == 0)
        {   
            for (int j = 0; j < 2; j++)
            {
                // буфер для принятия пакета
                Package package;
                int recv_buf_size = 0;
                std::vector<char> recv_buf(sizeof(package));
                MPI_Status recv_status;

                // принятие пакета
                MPI_Recv(recv_buf.data(), sizeof(recv_buf), MPI_BYTE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &recv_status);

                // распаковка пакета
                Package recv_package = unpack_data(recv_buf, recv_buf_size);
                print_info(recv_package, rank, RECV_FL);

                        
                // отправка пакета адресату
                auto temp = pack_data(recv_package);
                recv_buf = temp.first;
                recv_buf_size = temp.second;

                print_info(recv_package, rank, SEND_FL);
                MPI_Send(recv_buf.data(), recv_buf_size, MPI_BYTE, recv_package.to_process, 0, MPI_COMM_WORLD);
            }
        }
        else 
        {
            Package package;
            int recv_buf_size = 0;
            std::vector<char> recv_buf(sizeof(package));
            MPI_Request request;
            MPI_Status status;
            int flag = false;

            // принятие пакета
            MPI_Irecv(recv_buf.data(), sizeof(recv_buf), MPI_BYTE, COMMUTATOR, 0, MPI_COMM_WORLD, &request);

            // ожидание Test
            for (int k = 0; k < 100; k++)
            {
                MPI_Test(&request, &flag, MPI_STATUS_IGNORE);
                std::this_thread::sleep_for(std::chrono::milliseconds(5));
                if (flag)
                {
                    break;
                }
                    
            }
            if (flag) {
            
            // распаковка пакета
            Package recv_package = unpack_data(recv_buf, recv_buf_size);
            print_info(recv_package, rank, RECV_FL);
            
            // заполнение пакета
            package.to_process = order;
            package.from_process = rank;
            std::strncpy(package.data, "Recv OK!", TEXT_SIZE - 1);

            // запаковка пакета
            auto temp = pack_data(package);
            std::vector<char> buf = temp.first;
            int buf_size = temp.second;


            // отправка пакета
            print_info(package, rank, SEND_FL);
            MPI_Send(buf.data(), buf_size, MPI_BYTE, COMMUTATOR, 0, MPI_COMM_WORLD);       
            }
            else
            {
                MPI_Cancel(&request);
            }
        }

        MPI_Barrier(MPI_COMM_WORLD);
    }
    MPI_Finalize(); 
    return 0;
}
