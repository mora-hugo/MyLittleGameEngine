#pragma once
#include <memory>

namespace HC {
    namespace PtrUtils {
        template<typename TO, typename FROM>
        std::unique_ptr<TO> static_unique_pointer_cast (std::unique_ptr<FROM>&& old){
            return std::unique_ptr<TO>{static_cast<TO*>(old.release())};
            // conversion: unique_ptr<FROM>->FROM*->TO*->unique_ptr<TO>
            // https://stackoverflow.com/questions/36120424/alternatives-of-static-pointer-cast-for-unique-ptr
        }
    }
}