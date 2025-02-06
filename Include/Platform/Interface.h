#pragma once

#include <type_traits>

class Interface {
public:
    virtual ~Interface() = default;

    template<typename TO, typename FROM>
    static TO* GetInterface(FROM* object) {
        return dynamic_cast<TO*>(object);
    }
};