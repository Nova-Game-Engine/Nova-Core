#pragma once

#include <fmt/color.h>
#include <fmt/chrono.h>
#include <chrono>
#include <mutex>
#include <string>
#include <string_view>

namespace Nova::Core {

enum class LogLevel { Info, Warn, Error, Debug };

inline std::mutex& log_mutex() {
    static std::mutex m;
    return m;
}

inline fmt::text_style level_style(LogLevel level) {
    switch (level) {
        case LogLevel::Info:  return fmt::bg(fmt::color::green)  | fmt::fg(fmt::color::black);
        case LogLevel::Warn:  return fmt::bg(fmt::color::yellow) | fmt::fg(fmt::color::black);
        case LogLevel::Error: return fmt::bg(fmt::color::red)    | fmt::fg(fmt::color::white);
        case LogLevel::Debug: return fmt::bg(fmt::color::cyan)   | fmt::fg(fmt::color::black);
    }
    return {};
}

inline std::string_view level_str(LogLevel level) {
    switch (level) {
        case LogLevel::Info:  return "INFO";
        case LogLevel::Warn:  return "WARN";
        case LogLevel::Error: return "ERRO";
        case LogLevel::Debug: return "DEBG";
    }
    return "????";
}

inline void nova_log(LogLevel level, std::string_view logger_name, std::string_view msg, std::string_view file, int line) {
    auto now = std::chrono::system_clock::now();

    std::string name(logger_name.substr(0, 8));
    int padding = 8 - (int)name.size();
    int pad_l   = padding / 2;
    int pad_r   = padding - pad_l;
    std::string name_padded = std::string(pad_l, ' ') + name + std::string(pad_r, ' ');

    std::string_view fname = file;
    auto slash = fname.find_last_of("/\\");
    if (slash != std::string_view::npos) fname = fname.substr(slash + 1);

    std::lock_guard<std::mutex> lock(log_mutex());

    fmt::print(fmt::fg(fmt::color::gray),  "[");
    fmt::print(fmt::fg(fmt::color::white), "{:%H:%M:%S}", now);
    fmt::print(fmt::fg(fmt::color::gray),  "] ");
    fmt::print(level_style(level),         " {} ", level_str(level));
    fmt::print(" ");
    fmt::print(level_style(level),         " {} ", name_padded);
    fmt::print(" ");
    fmt::print(fmt::fg(fmt::color::white), "{}", msg);
    fmt::print(fmt::fg(fmt::color::gray),  " [{}:{}]\n", fname, line);
}

struct Logger {
    std::string name;

    explicit Logger(std::string_view n) : name(n) {}

    void info (std::string_view msg, std::string_view file = "", int line = 0) const { nova_log(LogLevel::Info,  name, msg, file, line); }
    void warn (std::string_view msg, std::string_view file = "", int line = 0) const { nova_log(LogLevel::Warn,  name, msg, file, line); }
    void error(std::string_view msg, std::string_view file = "", int line = 0) const { nova_log(LogLevel::Error, name, msg, file, line); }
    void debug(std::string_view msg, std::string_view file = "", int line = 0) const { nova_log(LogLevel::Debug, name, msg, file, line); }
};


#ifdef NOVA_LOGGING_DISABLE
    #define NOVA_INFO(logger, fmt, ...)  ((void)0)
    #define NOVA_WARN(logger, fmt, ...)  ((void)0)
    #define NOVA_ERROR(logger, fmt, ...) ((void)0)
    #define NOVA_DEBUG(logger, fmt, ...) ((void)0)
    #define NINFO(fmt, ...)  ((void)0)
    #define NWARN(fmt, ...)  ((void)0)
    #define NERROR(fmt, ...) ((void)0)
    #define NDEBUG(fmt, ...) ((void)0)
#else
    #define NOVA_INFO(logger, fmt, ...)  (logger).info(fmt::format(fmt, ##__VA_ARGS__), __FILE__, __LINE__)
    #define NOVA_WARN(logger, fmt, ...)  (logger).warn(fmt::format(fmt, ##__VA_ARGS__), __FILE__, __LINE__)
    #define NOVA_ERROR(logger, fmt, ...) (logger).error(fmt::format(fmt, ##__VA_ARGS__), __FILE__, __LINE__)
    #define NOVA_DEBUG(logger, fmt, ...) (logger).debug(fmt::format(fmt, ##__VA_ARGS__), __FILE__, __LINE__)
    #define NINFO(fmt, ...)  oLogger().info(fmt::format(fmt,  ##__VA_ARGS__), __FILE__, __LINE__)
    #define NWARN(fmt, ...)  oLogger().warn(fmt::format(fmt,  ##__VA_ARGS__), __FILE__, __LINE__)
    #define NERROR(fmt, ...) oLogger().error(fmt::format(fmt, ##__VA_ARGS__), __FILE__, __LINE__)
    #define NDEBUG(fmt, ...) oLogger().debug(fmt::format(fmt, ##__VA_ARGS__), __FILE__, __LINE__)
#endif

#define NOVA_LOG_DEF(name) \
    inline static Nova::Core::Logger& oLogger() { \
        static Nova::Core::Logger logger{name}; \
        return logger; \
}

} // namespace Nova::Core