#pragma once

#include <nova/logger/logger.hpp>

#if NOVA_CORE_LOGGING

    #define NOVA_INFO(logger, fmt, ...)  (logger).Info((fmt), ##__VA_ARGS__)
    #define NOVA_WARN(logger, fmt, ...)   (logger).Warn((fmt), ##__VA_ARGS__)
    #define NOVA_ERROR(logger, fmt, ...)  (logger).Error((fmt), ##__VA_ARGS__)
    #define NOVA_DEBUG(logger, fmt, ...)  (logger).Debug((fmt), ##__VA_ARGS__)

    #define NINFO(fmt, ...)   NOVA_INFO(oLogger, fmt, ##__VA_ARGS__)
    #define NWARN(fmt, ...)   NOVA_WARN(oLogger, fmt, ##__VA_ARGS__)
    #define NERROR(fmt, ...)  NOVA_ERROR(oLogger, fmt, ##__VA_ARGS__)
    #define NDEBUG(fmt, ...)  NOVA_DEBUG(oLogger, fmt, ##__VA_ARGS__)

#else

    #define NOVA_INFO(logger, fmt, ...)   ((void)0)
    #define NOVA_WARN(logger, fmt, ...)   ((void)0)
    #define NOVA_ERROR(logger, fmt, ...)  ((void)0)
    #define NOVA_DEBUG(logger, fmt, ...)  ((void)0)

    #define NINFO(fmt, ...)    ((void)0)
    #define NWARN(fmt, ...)    ((void)0)
    #define NERROR(fmt, ...)   ((void)0)
    #define NDEBUG(fmt, ...)   ((void)0)

#endif

#define NOVA_LOG_DEF(name) ::Nova::Core::Logger oLogger{(name)}
