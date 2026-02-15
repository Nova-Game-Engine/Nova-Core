#pragma once

#include "core.h"



namespace Nova::Core {
    namespace Base {
        // This act's as a builder class template for the Base class
        template<typename T>
        class Builder {
            private: T info{};
            public: Builder() = default;
            
            template<typename... Args>
            Builder& set(Args&&... args) {
                info.set(std::forward<Args>(args)...);
                return *this;
            }
            T build() && {
                return std::move(info);
            };

            T build() const & {
                return info;
            }
        };
    };
};