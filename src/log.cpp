#include <chrono>
#include <iostream>
#include <map>

#include "../inc/log.h"

using joszva::log;

namespace 
{
    std::string default_path("joszva_log.txt");
}

log::log()
    : input_file(""),
    output_file(""),
    console_output_enabled(true)
{
}

log::~log()
{
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

void log::write_log(log_level lvl, const std::string& str)
{
    std::string level_txt;
    switch (lvl)
    {
        case log_level::TRACE: level_txt = "[TRACE]"; break;
        case log_level::WARNING: level_txt = "[WARNING]"; break;
        case log_level::ERROR: level_txt = "[ERROR]"; break;
        case log_level::FATAL: level_txt = "[FATAL]"; break;
    }

    if (console_output_enabled)
    {
        write_to_console(level_txt, str);
    }

    output_file.open(default_path);
}

void log::set_console_output(bool enabled)
{
    if (enabled)
    {
        console_output_enabled = true;
        return;
    }

    console_output_enabled = false;
}

void log::set_default_output_path(const std::string& path)
{
    default_path = path;
}

void log::write_to_console(const std::string& level_txt, const std::string& str)
{
    std::cout << stamp_to_time(get_timestamp()) << " " << level_txt << " " << str << std::endl;
}

int main()
{
    log::set_default_output_path("/home/joshua/Desktop/example_log1.txt");
    log _log;
    _log.write_log(joszva::log_level::ERROR, "This is a test error message");
    _log.write_log(joszva::log_level::TRACE, "Tracing now");

    return 0;
}
