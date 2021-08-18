#include <chrono>
#include <iostream>

#include "../inc/logger.h"

using joszva::logger;

std::string logger::default_log_path = "";

logger::logger(const std::string& log_file_path)
    : output_file(""),
    console_output_enabled(true),
    log_path(log_file_path)
{
}

logger::~logger()
{
}

void logger::info(const std::string& str)
{
    write_log(log_level::INFO, const_cast<std::string&>(str));
}

void logger::warning(const std::string& str)
{
    write_log(log_level::WARNING, const_cast<std::string&>(str));
}

void logger::error(const std::string& str)
{
    write_log(log_level::ERROR, const_cast<std::string&>(str));
}

void logger::fatal(const std::string& str)
{
    write_log(log_level::FATAL, const_cast<std::string&>(str));
}

void logger::set_default_log_path(const std::string& file_path)
{
    default_log_path = file_path;
}

const std::string& logger::get_log_path() const 
{
    if (log_path.empty())
    {
        /* no custom logger path */
    }

    return log_path;
}

const std::string& logger::get_default_log_path()
{
    return default_log_path;
}

static bool is_file_empty(std::istream& file)
{
    return file.peek() == std::ifstream::traits_type::eof();
}

static unsigned long long get_timestamp()
{
    auto time = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch());
    unsigned long long timestamp = time.count();

    return timestamp;
}

static std::string stamp_to_time(long long timestamp)
{
    int ms = timestamp % 1000;
    time_t tick = static_cast<time_t>(timestamp / 1000);
    tm _tm;
    char s[40];
    _tm = *localtime(&tick);
    strftime(s, sizeof(s), "%Y-%m-%d %H:%M:%S", &_tm);
    std::string str(s);
    str = str + " " + std::to_string(ms);
    return str;
}

void logger::write_to_console(const std::string& txt, int col)
{
    std::cout << "\033[39m" << stamp_to_time(get_timestamp()) << " ";
    switch (col)
    {
        case RED:
            std::cout << "\033[31m" << txt << std::endl;
            break;
        case GREEN:
            std::cout << "\033[32m" << txt << std::endl;
            break;
        case YELLOW:     
            std::cout << "\033[33m" << txt << std::endl;
            break;
        default:   
            std::cout << "\033[0m" << txt << std::endl;
            break;
    }

    /* set back to default colors */
    std::cout << "\033[39m";
}

void logger::write_log(log_level lvl, std::string& str)
{
    /* simple check to determine whether or not logging has just started */
    static unsigned int i = 0;
    if (i == 0)
    {
        default_log_path += "-" + stamp_to_time(get_timestamp());
        ++i;
    }

    switch (lvl)
    {
        case log_level::INFO: 
            str.insert(0, "[INFO] ");
            write_to_console(str, GREEN);
            break;
        case log_level::WARNING:  
            str.insert(0, "[WARNING] ");
            write_to_console(str, YELLOW);
            break;
        case log_level::ERROR:
            str.insert(0, "[ERROR] ");
            write_to_console(str, RED);
            break;
        case log_level::FATAL:  
            str.insert(0, "[FATAL] ");
            write_to_console(str, RED);
            break;
    }

    if (log_path != default_log_path && !log_path.empty())
    {
        log_path += "-" + stamp_to_time(get_timestamp());
        output_file.open(log_path, std::ios::app);
    }
    else 
    {
        output_file.open(default_log_path, std::ios::app);
    }

    if (output_file.is_open())
    {
        output_file << stamp_to_time(get_timestamp()) << " " << str << std::endl;
        output_file.close();
    }
}