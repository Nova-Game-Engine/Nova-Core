#include "Nova/Core/core.h"
#include "Nova/Core/structs.hpp"

Core::Core(): _l("Cmake Template") {
}

Core::~Core() {}

void Core::load() {
    _l.info("Core loaded.");
}

void Core::unload() {
    _l.info("Core unloaded");
}