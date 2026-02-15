#ifndef CORE_HPP
#define CORE_HPP

// Patch i did in Nova Desktop (since it isn't Nova desktop dependant it's okay)

#include <nova/logger/logger.hpp>
#include <fmt/format.h>
#include <spdlog/common.h>
#include <string_view>
#include <utility>



namespace Nova::Core {
    #ifndef NOVA_LOGGING
    class Logger {
        Nova::Logger log;
    public:
        explicit Logger(std::string_view name) : log(name.data()) {}

        template<typename... Args>
        inline void Info(fmt::format_string<Args...> fmtStr, const std::string& file, int line, Args&&... args) {
            // log.info(fmt::format(fmtStr, std::forward<Args>(args)...));;;
            log.log_with_location(spdlog::level::info, fmt::format(fmtStr, std::forward<Args>(args)...), file.c_str(), line, SPDLOG_FUNCTION);
        }

        template<typename... Args>
        inline void Warn(fmt::format_string<Args...> fmtStr, const std::string& file, int line, Args&&... args) {
            log.log_with_location(spdlog::level::warn, fmt::format(fmtStr, std::forward<Args>(args)...), file.c_str(), line, SPDLOG_FUNCTION);
        }

        template<typename... Args>
        inline void Error(fmt::format_string<Args...> fmtStr, const std::string& file, int line, Args&&... args) {
            log.log_with_location(spdlog::level::err, fmt::format(fmtStr, std::forward<Args>(args)...), file.c_str(), line, SPDLOG_FUNCTION);
        }

        template<typename... Args>
        inline void Debug(fmt::format_string<Args...> fmtStr, const std::string& file, int line, Args&&... args) {
            log.log_with_location(spdlog::level::debug, fmt::format(fmtStr, std::forward<Args>(args)...), file.c_str(), line, SPDLOG_FUNCTION);
        }
    };

    #else

    class Logger {
    public:
        explicit Logger(std::string_view = {}) {}

        template<typename... Args>
        inline void Info(fmt::format_string<Args...>, const std::string&, int, Args&&...) {}

        template<typename... Args>
        inline void Warn(fmt::format_string<Args...>, const std::string&, int, Args&&...) {}

        template<typename... Args>
        inline void Error(fmt::format_string<Args...>, const std::string&, int, Args&&...) {}

        template<typename... Args>
        inline void Debug(fmt::format_string<Args...>, const std::string&, int, Args&&...) {}
    };

    #endif

    #ifndef NOVA_LOGGING_DISABLE_LOW

        #define NOVA_INFO(logger, fmt, ...)  (logger).Info(fmt, __FILE__, __LINE__,##__VA_ARGS__)
        #define NOVA_WARN(logger, fmt, ...)  (logger).Warn(fmt, __FILE__, __LINE__, ##__VA_ARGS__)
        #define NOVA_ERROR(logger, fmt, ...) (logger).Error(fmt, __FILE__, __LINE__, ##__VA_ARGS__)
        #define NOVA_DEBUG(logger, fmt, ...) (logger).Debug(fmt, __FILE__, __LINE__, ##__VA_ARGS__)

        #define NOVA_LOG_DEF(name) \
            inline static Nova::Core::Logger& oLogger() { \
                static Nova::Core::Logger logger{name}; \
                return logger; \
            }

        #define NINFO(fmt, ...)  oLogger().Info(fmt, __FILE__, __LINE__, ##__VA_ARGS__)
        #define NWARN(fmt, ...)  oLogger().Warn(fmt, __FILE__, __LINE__, ##__VA_ARGS__)
        #define NERROR(fmt, ...) oLogger().Error(fmt, __FILE__, __LINE__, ##__VA_ARGS__)
        #define NDEBUG(fmt, ...) oLogger().Debug(fmt, __FILE__, __LINE__, ##__VA_ARGS__)

    #endif
}


namespace N = Nova;

#endif
