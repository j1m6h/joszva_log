#ifndef LOG_H
#define LOG_H

#include <fstream>
#include <string>

namespace joszva
{
    enum class log_level
    {
        TRACE,
        WARNING,
        ERROR,
        FATAL
    };

    class log
    {
    public:
        log(const std::string& log_file_path = "");
        ~log();

        void write_log(log_level lvl, std::string&& str);
        void set_console_output(bool enabled);
        static void set_default_log_file_for_all_instances(const std::string& file_path);

    private:
        void write_to_console(const std::string& level_txt, const std::string& str);

        std::ofstream output_file;
        bool console_output_enabled;
        std::string log_file_path;
    };
}
#endif