#pragma once

#include <iostream>
#define Assertion(expression, message) if(expression == false)  {\
    std::cout << "ASSERTION FAILED: \n" << \
    "Message: " << message << "\n" << \
    "Line: " << __LINE__ << "\n" << \
    "Function: " << __func__ << "\n" << \
    "File: " << __FILE__ << "\n";   \
    exit(1);    \
    }

