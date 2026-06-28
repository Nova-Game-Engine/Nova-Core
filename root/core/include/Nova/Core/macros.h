#pragma once

#include <nova/logger/logger.hpp>

#ifdef NOVA_CORE_LOGGING_DISABLE

    #define NOVA_INFO(logger, fmt, ...)   ((void)0)
    #define NOVA_WARN(logger, fmt, ...)   ((void)0)
    #define NOVA_ERROR(logger, fmt, ...)  ((void)0)
    #define NOVA_DEBUG(logger, fmt, ...)  ((void)0)

    #define NINFO(fmt, ...)    ((void)0)
    #define NWARN(fmt, ...)    ((void)0)
    #define NERROR(fmt, ...)   ((void)0)
    #define NDEBUG(fmt, ...)   ((void)0)

#else

    #define NOVA_INFO(logger, fmt, ...)   (logger).Info((fmt), __FILE__, __LINE__, ##__VA_ARGS__)
    #define NOVA_WARN(logger, fmt, ...)   (logger).Warn((fmt), __FILE__, __LINE__, ##__VA_ARGS__)
    #define NOVA_ERROR(logger, fmt, ...)  (logger).Error((fmt), __FILE__, __LINE__, ##__VA_ARGS__)
    #define NOVA_DEBUG(logger, fmt, ...)  (logger).Debug((fmt), __FILE__, __LINE__, ##__VA_ARGS__)

        #define NINFO(fmt, ...)  oLogger().Info(fmt, __FILE__, __LINE__, ##__VA_ARGS__)
        #define NWARN(fmt, ...)  oLogger().Warn(fmt, __FILE__, __LINE__, ##__VA_ARGS__)
        #define NERROR(fmt, ...) oLogger().Error(fmt, __FILE__, __LINE__, ##__VA_ARGS__)
        #define NDEBUG(fmt, ...) oLogger().Debug(fmt, __FILE__, __LINE__, ##__VA_ARGS__)

#endif

#if defined(__clang__) || defined(__GNUC__)
    #define NOVA_INTERNAL_LOW [[deprecated("Internal use only")]]
#elif defined(_MSC_VER)
    #define NOVA_INTERNAL_LOW __declspec(deprecated("Internal use only"))
#else
    #define NOVA_INTERNAL_LOW
#endif
    
#ifndef NINTERNAL
    #define NINTERNAL NOVA_INTERNAL_LOW
#endif


// In your common header
#if defined(__clang__) || defined(__GNUC__)
    #define NOVA_SUPPRESS_INTERNAL_BEGIN \
        _Pragma("GCC diagnostic push") \
        _Pragma("GCC diagnostic ignored \"-Wdeprecated-declarations\"")
    #define NOVA_SUPPRESS_INTERNAL_END \
        _Pragma("GCC diagnostic pop")
#elif defined(_MSC_VER)
    #define NOVA_SUPPRESS_INTERNAL_BEGIN \
        __pragma(warning(push)) \
        __pragma(warning(disable: 4996))
    #define NOVA_SUPPRESS_INTERNAL_END \
        __pragma(warning(pop))
#else
    #define NOVA_SUPPRESS_INTERNAL_BEGIN
    #define NOVA_SUPPRESS_INTERNAL_END
#endif


#define NOVA_LOG_DEF(name) \
    inline static Nova::Core::Logger& oLogger() { \
        static Nova::Core::Logger logger{name}; \
        return logger; \
    }



#define NOVA_ASSERT(expr) \
    do { if (!(expr)) ::Nova::Core::assertFail(#expr, nullptr); } while(0)


#define NOVA_ASSERT_MSG(expr, msg) \
    do { if (!(expr)) ::Nova::Core::assertFail(#expr, msg); } while(0)


#define NOVA_PANIC(msg) \
    ::Nova::Core::assertFail("PANIC", msg)

#ifdef N_DEBUG
    #define NOVA_DASSERT(expr)          do {} while(0)
    #define NOVA_DASSERT_MSG(expr, msg) do {} while(0)
#else
    #define NOVA_DASSERT(expr)          NOVA_ASSERT(expr)
    #define NOVA_DASSERT_MSG(expr, msg) NOVA_ASSERT_MSG(expr, msg)
#endif
