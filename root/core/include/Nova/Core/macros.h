#pragma once




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
