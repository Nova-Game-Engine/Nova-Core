#pragma once

#include <cstdio>
#include <memory>
#include <source_location>
#include <string>
namespace Nova::Core {
    using byte = unsigned char;
    using u8 = unsigned char;
    using u16 = unsigned short;
    using u32 = unsigned int;
    using u64 = unsigned long long;
    using i8 = signed char;
    using i16 = short;
    using i32 = int;
    using i64 = long long;

    using f32 = float;
    using f64 = double;

    using bool8 = unsigned char;
    using bool16 = unsigned short;
    using bool32 = unsigned int;
    using bool64 = unsigned long long;

    using s8 = signed char;
    using s16 = short;
    using s32 = int;
    using s64 = long long;

    using string = std::string;

    template<typename T>
    using ref = std::shared_ptr<T>;
    template<typename T>
    using weakRef = std::weak_ptr<T>;

    template<typename T>
    using unique = std::unique_ptr<T>;

    template<typename T, typename... Args>
    constexpr auto makeUnique(Args&&... args) {
        return std::make_unique<T>(std::forward<Args>(args)...);
    }

    template<typename T, typename... Args>
    constexpr auto makeRef(Args&&... args) {
        return std::make_shared<T>(std::forward<Args>(args)...);
    }

    template<typename T, typename U>
    constexpr ref<T> staticRef(const ref<U>& ptr) {
        return std::static_pointer_cast<T>(ptr);
    }
    template<typename T, typename U>
    constexpr ref<T> dynamicRef(const ref<U>& ptr) {
        return std::dynamic_pointer_cast<T>(ptr);
    }


    template<typename F>
    struct ScopeExit {
        F fn;
        ~ScopeExit() { fn(); }
    };
    template<typename F>
    auto makeScopeExit(F&& fn) { return ScopeExit<F>{std::forward<F>(fn)}; }

    template<typename T>
    using ref_nn = T&;

    enum class Result {
        Success,
        Failure,
        NotFound,
        InvalidArgument,
        OutOfMemory,
        UnknownError
    };

    inline void assertFail(const char* expr, const char* msg, std::source_location loc = std::source_location::current()) {
        std::fprintf(
            stderr, "[Nova Assert] %s:%u - '%s' failed%s%s\n",
            loc.file_name(),
            loc.line(),
            expr,
            msg ? " | " : "",
            msg ? msg : ""
        );
        std::abort();
    }
};