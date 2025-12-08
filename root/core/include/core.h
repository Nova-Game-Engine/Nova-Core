#ifndef CORE_HPP
#define CORE_HPP

#include <nova/logger/logger.hpp>


class Core {
    private:
        Nova::Logger _l;
    public:
        Core();
        ~Core();

        void load();
        void unload();
};

struct ModuleContext {
    Nova::Logger logger = Nova::Logger("Module");

};

namespace Nova::Core {
    #define NOVA_CORE_LOGGING true
    class Logger {
    private:
        Nova::Logger log;

    public:
        explicit Logger(std::string_view name) : log(name.data()) {}

        template<typename... Args>
        inline void Info(fmt::format_string<Args...> fmtStr, Args&&... args) {
            log.info(fmt::format(fmtStr, std::forward<Args>(args)...));
        }

        template<typename... Args>
        inline void Warn(fmt::format_string<Args...> fmtStr, Args&&... args) {
            log.warn(fmt::format(fmtStr, std::forward<Args>(args)...));
        }

        template<typename... Args>
        inline void Error(fmt::format_string<Args...> fmtStr, Args&&... args) {
            log.error(fmt::format(fmtStr, std::forward<Args>(args)...));
        }

        template<typename... Args>
        inline void Debug(fmt::format_string<Args...> fmtStr, Args&&... args) {
            log.debug(fmt::format(fmtStr, std::forward<Args>(args)...));
        }
    };
    #if NOVA_CORE_LOGGING
        #define NOVA_INFO(logger, fmt, ...)  (logger).Info(fmt, ##__VA_ARGS__)
        #define NOVA_WARN(logger, fmt, ...)  (logger).Warn(fmt, ##__VA_ARGS__)
        #define NOVA_ERROR(logger, fmt, ...) (logger).Error(fmt, ##__VA_ARGS__)
        #define NOVA_DEBUG(logger, fmt, ...) (logger).Debug(fmt, ##__VA_ARGS__)
    #else
        #define NOVA_INFO(logger, fmt, ...)  (void)0
        #define NOVA_WARN(logger, fmt, ...)  (void)0
        #define NOVA_ERROR(logger, fmt, ...) (void)0
        #define NOVA_DEBUG(logger, fmt, ...) (void)0
    #endif

    #if NOVA_CORE_LOGGING
        #define NOVA_LOG_DEF(name) Nova::VL::Logger oLogger{name};
    #else
        #define NOVA_LOG_DEF(name)
    #endif

    class Object {
        protected:

        public:
            virtual ~Object() = default;

        public:
    };

    
};

namespace N = Nova;

#endif