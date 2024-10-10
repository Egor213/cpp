#include <iostream>
#include <mpi.h>
#include <vector>
#include <random>
#include <algorithm>
#include <numeric> 
#define TEXT_SIZE 10

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
    std::uniform_int_distribution<> distrib(1, size);
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
    for (int i = 0; i < 9; ++i) {
        int random_char = gen() % 62;
        if (random_char < 26) {
            text[i] = 'A' + random_char;
        } else if (random_char < 52) {
            text[i] = 'a' + (random_char - 26);
        } else {
            text[i] = '0' + (random_char - 52);
        }
    }
    text[9] = '\0';
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
    MPI_Unpack(recv_buf.data(), sizeof(recv_buf), &recv_buf_size, package.data, 10, MPI_CHAR, MPI_COMM_WORLD); 
    return package;
}

//  tag 0 - отправка
//  tag 1 - принятие пакета

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


    // std::cout << "Process " << rank << " received order: ";
    // for (auto per : order_process)
    // {
    //     std::cout << per << ' ';
    // }
    // std::cout << '\n';

    // for (auto order : order_process)
    // {
        if (rank == order_process[0])
        {
            // создаем пакет и заполняем его данными
            Package package;
            package.from_process = rank;
            package.to_process = gen_number_process(size, rank);
            fill_random_chars(package.data);

            // упаковка данных
            auto temp = pack_data(package);
            std::vector<char> buf = temp.first;
            int buf_size = temp.second;

            // буфер для принятых данных
            int recv_buf_size = 0;
            std::vector<char> recv_buf(sizeof(package));

            // принятие и отправка данных
            MPI_Sendrecv(buf.data(), buf_size, MPI_BYTE, 0, 0, recv_buf.data(), sizeof(recv_buf), MPI_BYTE, 0, 1, MPI_COMM_WORLD, MPI_STATUS_IGNORE);

            // распаковка данных
            Package recv_package = unpack_data(recv_buf, recv_buf_size);
            std::cout << "Process " << rank << ":"
                      << " recv FROM: " << recv_package.from_process
                      << " TO: " << recv_package.to_process 
                      << " DATA: " << recv_package.data 
                      << '\n';

        }
        else if (rank == 0)
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

            std::cout << "Process 0:"
                      << " recv FROM: " << recv_package.from_process
                      << " TO: " << recv_package.to_process 
                      << " DATA: " << recv_package.data 
                      << '\n';


            MPI_Send(recv_buf.data(), sizeof(recv_buf), MPI_BYTE, recv_package.to_process, 0, MPI_COMM_WORLD);
            

            // package.from_process = rank;
            // package.to_process = order_process[0];
            // for (int i = 0; i < 9; i++)
            //     package.data[i] = 'A';

            // int send_buf_size = 0;
            // char send_buf[sizeof(package)];
            // MPI_Pack(&package.from_process, 1, MPI_INT, send_buf, sizeof(send_buf), &send_buf_size, MPI_COMM_WORLD);
            // MPI_Pack(&package.to_process, 1, MPI_INT, send_buf, sizeof(send_buf), &send_buf_size, MPI_COMM_WORLD);
            // MPI_Pack(package.data, TEXT_SIZE, MPI_CHAR, send_buf, sizeof(send_buf), &send_buf_size, MPI_COMM_WORLD); 
            


        }
        else
        {
            Package package;
            int recv_buf_size = 0;
            std::vector<char> recv_buf(sizeof(package));
            MPI_Status recv_status;

            // принятие пакета
            MPI_Recv(recv_buf.data(), sizeof(recv_buf), MPI_BYTE, MPI_ANY_SOURCE, MPI_ANY_TAG, MPI_COMM_WORLD, &recv_status);

            // распаковка пакета
            Package recv_package = unpack_data(recv_buf, recv_buf_size);

            std::cout << "Process " << rank << ":"
                      << " recv FROM: " << recv_package.from_process
                      << " TO: " << recv_package.to_process 
                      << " DATA: " << recv_package.data 
                      << '\n';
            
        }

        MPI_Barrier(MPI_COMM_WORLD);
    // }

    MPI_Finalize(); 
    return 0;
}
