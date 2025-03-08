#pragma once

#include "Reflection/Property.h"
#include "Reflection/HCClass.h"
#include <map>



#define START_REFLECTION_2(className, parentClassName) \
    public:                                          \
    static HCClass * StaticClass() { return hcClass.get(); } \
    HCClass * Class() override { return className::StaticClass(); } \
    private:                        \
    static inline std::unique_ptr<HCClass> hcClass = HCClass::RegisterClass<className>(#className, parentClassName::StaticClass()); \
    std::map<const char*, Property> members = {

#define START_REFLECTION_1(className) \
    public:                                          \
    static HCClass * StaticClass() { return hcClass.get(); } \
    HCClass * Class() override { return className::StaticClass(); } \
    private:                        \
    static inline std::unique_ptr<HCClass> hcClass = HCClass::RegisterClass<className>(#className, nullptr); \
    std::map<const char*, Property> members = {

#define GET_MACRO(_1, _2, NAME, ...) NAME
#define START_REFLECTION(...) GET_MACRO(__VA_ARGS__, START_REFLECTION_2, START_REFLECTION_1)(__VA_ARGS__)

/* REFLEXION WITH CUSTOM FUNCTION */
#define START_REFLECTION_CUSTOM_2(className, parentClassName, customFunction) \
    public:                                                                    \
    static HCClass* StaticClass() { return hcClass.get(); }                    \
    HCClass* Class() override { return className::StaticClass(); }               \
    private:                                                                   \
    static inline std::unique_ptr<HCClass> hcClass = customFunction<className>(#className, parentClassName::StaticClass()); \
    std::map<const char*, Property> members = {

#define START_REFLECTION_CUSTOM_1(className, customFunction)                   \
    public:                                                                    \
    static HCClass* StaticClass() { return hcClass.get(); }                    \
    HCClass* Class() override { return className::StaticClass(); }               \
    private:                                                                   \
    static inline std::unique_ptr<HCClass> hcClass = customFunction<className>(#className, nullptr); \
    std::map<const char*, Property> members = {

#define GET_MACRO_CUSTOM(_1, _2, _3, NAME, ...) NAME
#define START_REFLECTION_CUSTOM(...) GET_MACRO_CUSTOM(__VA_ARGS__, START_REFLECTION_CUSTOM_2, START_REFLECTION_CUSTOM_1)(__VA_ARGS__)

#define ADD_MEMBER_PROPERTY(variable) \
    {#variable, Property(#variable, &(variable), typeid(&(variable)))},

#define ADD_OBJECT_MEMBER_PROPERTY(variable) \
    {#variable, Property(#variable, static_cast<HCObject*>(&(variable)), typeid(&(variable)))},

#define STOP_REFLECTION() \
    };                    \
public:                   \
                          \
    [[nodiscard]] std::map<const char*, Property>& GetMutableMembers() override { return members; }                     \
    [[nodiscard]] const std::map<const char*, Property>& GetMembers() const override { return members; } \


