#pragma once

// This is a macro that generates a function pointer to a member function of a class without writing any placeholders.
#define HC_BIND_MEMBER_FUNCTION_ARGS(function_ptr, instance_ptr, num_args) \
    std::bind(function_ptr, instance_ptr, BIND_MEMBER_FUNCTION_PLACEHOLDERS_##num_args)

#define BIND_MEMBER_FUNCTION_PLACEHOLDERS_0
#define BIND_MEMBER_FUNCTION_PLACEHOLDERS_1 std::placeholders::_1
#define BIND_MEMBER_FUNCTION_PLACEHOLDERS_2 std::placeholders::_1, std::placeholders::_2
#define BIND_MEMBER_FUNCTION_PLACEHOLDERS_3 std::placeholders::_1, std::placeholders::_2, std::placeholders::_3
#define BIND_MEMBER_FUNCTION_PLACEHOLDERS_4 std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4
#define BIND_MEMBER_FUNCTION_PLACEHOLDERS_5 std::placeholders::_1, std::placeholders::_2, std::placeholders::_3, std::placeholders::_4, std::placeholders::_5


template <typename ...Args>
class IEvent {
    virtual void AddListener(const void* ownerPtr, std::function<void(Args...)> func) = 0;

    virtual void RemoveListener(const void* ownerPtr) = 0;

    virtual void ClearListeners() = 0;
};