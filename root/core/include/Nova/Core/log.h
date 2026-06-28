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
}


namespace N = Nova;

#endif
