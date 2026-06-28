#pragma once

#include "log.h"
#include "base.h"
#include "macros.h"
#include "structs.hpp"

#ifndef NOVA_LOGGING
    #define NOVA_LOGGING 1
#endif

#ifndef NOVA_DEBUGGING
    #define NOVA_DEBUGGING 1
    #define NOVA_CORE_INTERNAL_DEBUGGING_DEFAULT_OVERRIDE_NOTICE 0 // used for internal debugging override notice - long for a reason
#endif

namespace N = Nova;