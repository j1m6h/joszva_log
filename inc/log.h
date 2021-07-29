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
        log();
        ~log();

        void write_log(log_level lvl, const std::string& str);
        void set_log_path(const std::string& path);
        void set_console_output(bool enabled);
        /* will set the default output path for all instances of log */
        static void set_default_output_path(const std::string& path);

    private:
        void write_to_console(const std::string& level_txt, const std::string& str);

        std::ifstream input_file;
        std::ofstream output_file;
        bool console_output_enabled;
    };
}
#endif