#include <iostream>
#include <array>
#include <string>
#include <vector>
#include <fstream>
namespace Logs
{

    

class FileSink
{
public:
    FileSink(const std::string& file_name, std::size_t buffer_size = 4096u)
        : m_buffer(buffer_size), m_output(file_name), m_offset(0u)
    {
        if (!m_output.is_open())
        {
            throw std::runtime_error("File was not created");
        }
    }

    ~FileSink()
    {
        flush();
    }

    void write(const std::string& data)
    {
        const std::size_t data_size = data.size();
        if (data_size + m_offset >= m_buffer.size())
        {
            flush();
        }
        std::copy(begin(data), end(data), begin(m_buffer) + m_offset);
        m_offset += data_size;
    }

private:
    void flush()
    {
        if (m_offset != 0u)
        {
            m_output.write(m_buffer.data(), m_offset);
            m_offset = 0u;
        }
    }

private:
    std::vector<char> m_buffer;
    std::ofstream     m_output;
    std::size_t       m_offset;

};

class Logger
{
public:
    enum Level
    {
        TRACE_LEVEL,
        DEBUG_LEVEL,
        INFO_LEVEL,
        WARN_LEVEL,
        ERROR_LEVEL,
        FATAL_LEVEL
    };

    static inline std::array<std::string, Level::FATAL_LEVEL + 1u> LevelStr = {
        "TRACE", "DEBUG", "INFO", "WARN", "ERROR", "FATAL"
    };

public:
    Logger(const std::string& file_name)
        : m_sink(file_name)
    {

    }

    void log(Level level, const char* source, const std::string& message)
    {
        const std::string formate_message = "[" + LevelStr[level] + "] - " + source + " - " + message + '\n';
        m_sink.write(formate_message);
    }

private:
    FileSink m_sink;

};



}

inline Logs::Logger& getGlobalLogger()
{
    static Logs::Logger logger{"/home/egor/C++/data.log"};
    return logger;
}

#define STR_(x) #x
#define STR(x) STR_(x)

#define LOG_DEBUG(message) getGlobalLogger().log(Logs::Logger::DEBUG_LEVEL, __FILE__ ":" STR(__LINE__), (message))
#define LOG_TRACE(message) getGlobalLogger().log(Logs::Logger::TRACE_LEVEL, __FILE__ ":" STR(__LINE__), (message))
#define LOG_INFO(message) getGlobalLogger().log(Logs::Logger::INFO_LEVEL, __FILE__ ":" STR(__LINE__), (message))
#define LOG_WARN(message) getGlobalLogger().log(Logs::Logger::WARN_LEVEL, __FILE__ ":" STR(__LINE__), (message))
#define LOG_ERROR(message) getGlobalLogger().log(Logs::Logger::ERROR_LEVEL, __FILE__ ":" STR(__LINE__), (message))
#define LOG_FATAL(message) getGlobalLogger().log(Logs::Logger::FATAL_LEVEL, __FILE__ ":" STR(__LINE__), (message))


int main() {
    
    for (auto i = 0; i < 100; ++i)
    {
        LOG_DEBUG("testing.");
    }

    


    return 0;
}
