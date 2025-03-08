#include "Reflection/IReflectable.h"
#include "Reflection/Property.h"
HC::Property HC::IReflectable::GetProperty(const char *propertyName) {
    return GetMutableMembers().at(propertyName);
}
