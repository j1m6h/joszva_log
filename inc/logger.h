#ifndef LOGGER_H
#define LOGGER_H

#include <fstream>
#include <string>

namespace joszva
{
    class logger
    {
    public:
        logger(const std::string& log_file_path = "");
        ~logger();

        void info(const std::string& str);
        void warning(const std::string& str);
        void error(const std::string& str);
        void fatal(const std::string& str);
        static void set_default_log_path(const std::string& file_path);
        const std::string& get_log_path() const;
        static const std::string& get_default_log_path();

    private:
        enum text_color
        {
            RED,
            GREEN,
            YELLOW,
            DEFAULT
        };

        enum class log_level
        {
            INFO,
            WARNING,
            ERROR,
            FATAL
        };

        void write_to_console(const std::string& txt, int col = DEFAULT);
        void write_log(log_level lvl, std::string& str);

        std::ofstream output_file;
        bool console_output_enabled;
        std::string log_path;
        static std::string default_log_path;
    };
}
#endif