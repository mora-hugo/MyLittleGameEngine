#pragma once

#include "Reflection/IReflectable.h"

namespace HC {
    class HCObject: public IReflectable {
        virtual class HCClass * Class() = 0;


    };
}