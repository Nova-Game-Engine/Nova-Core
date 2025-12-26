#ifndef CORE_HPP
#define CORE_HPP

// Patch i did in Nova Desktop (since it isn't Nova desktop dependant it's okay)

#include <nova/logger/logger.hpp>
#include <fmt/format.h>
#include <spdlog/common.h>
#include <string_view>
#include <utility>

namespace Nova::Core {
    #define NOVA_CORE_LOGGING true

    #if NOVA_CORE_LOGGING

    class Logger {
        Nova::Logger log;
    public:
        explicit Logger(std::string_view name) : log(name.data()) {}

        template<typename... Args>
        inline void Info(fmt::format_string<Args...> fmtStr, Args&&... args, const std::string& file, int line) {
            // log.info(fmt::format(fmtStr, std::forward<Args>(args)...));;;
            log.log_with_location(spdlog::level::info, fmt::format(fmtStr, std::forward<Args>(args)...), file.c_str(), line, SPDLOG_FUNCTION);
        }

        template<typename... Args>
        inline void Warn(fmt::format_string<Args...> fmtStr, Args&&... args, const std::string& file, int line) {
            log.log_with_location(spdlog::level::warn, fmt::format(fmtStr, std::forward<Args>(args)...), file.c_str(), line, SPDLOG_FUNCTION);
        }

        template<typename... Args>
        inline void Error(fmt::format_string<Args...> fmtStr, Args&&... args, const std::string& file, int line) {
            log.log_with_location(spdlog::level::err, fmt::format(fmtStr, std::forward<Args>(args)...), file.c_str(), line, SPDLOG_FUNCTION);
        }

        template<typename... Args>
        inline void Debug(fmt::format_string<Args...> fmtStr, Args&&... args, const std::string& file, int line) {
            log.log_with_location(spdlog::level::debug, fmt::format(fmtStr, std::forward<Args>(args)...), file.c_str(), line, SPDLOG_FUNCTION);
        }
    };

    #else

    class Logger {
    public:
        explicit Logger(std::string_view = {}) {}

        template<typename... Args>
        inline void Info(fmt::format_string<Args...>, Args&&..., const std::string&, int) {}

        template<typename... Args>
        inline void Warn(fmt::format_string<Args...>, Args&&..., const std::string&, int) {}

        template<typename... Args>
        inline void Error(fmt::format_string<Args...>, Args&&..., const std::string&, int) {}

        template<typename... Args>
        inline void Debug(fmt::format_string<Args...>, Args&&..., const std::string&, int) {}
    };

    #endif

    #define NOVA_INFO(logger, fmt, ...)  (logger).Info(fmt, ##__VA_ARGS__)
    #define NOVA_WARN(logger, fmt, ...)  (logger).Warn(fmt, ##__VA_ARGS__)
    #define NOVA_ERROR(logger, fmt, ...) (logger).Error(fmt, ##__VA_ARGS__)
    #define NOVA_DEBUG(logger, fmt, ...) (logger).Debug(fmt, ##__VA_ARGS__)

    #define NOVA_LOG_DEF(name) \
        inline static Nova::Core::Logger& oLogger() { \
            static Nova::Core::Logger logger{name}; \
            return logger; \
        }

    #define NINFO(fmt, ...)  oLogger().Info(fmt, ##__VA_ARGS__)
    #define NWARN(fmt, ...)  oLogger().Warn(fmt, ##__VA_ARGS__)
    #define NERROR(fmt, ...) oLogger().Error(fmt, ##__VA_ARGS__)
    #define NDEBUG(fmt, ...) oLogger().Debug(fmt, ##__VA_ARGS__)

    class Object {
    public:
        virtual ~Object() = default;
    };
}

class Core {
    Nova::Logger _l;
public:
    Core();
    ~Core();

    void load();
    void unload();
};

struct ModuleContext {
    Nova::Logger logger{"Module"};
};

namespace N = Nova;

#endif
