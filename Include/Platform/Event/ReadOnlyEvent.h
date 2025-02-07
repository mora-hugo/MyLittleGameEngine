#pragma once
#include <Event/Event.h>
#include <Event/IEvent.h>

namespace HC {
    template <typename ...Args>
    class ReadOnlyEvent : public IEvent<Args...> {
    public:
        explicit ReadOnlyEvent(Event<Args...>& event) : event(event) {}
        ReadOnlyEvent(const ReadOnlyEvent&) = delete;
        ReadOnlyEvent& operator=(const ReadOnlyEvent&) = delete;

        void AddListener(const void* ownerPtr, std::function<void(Args...)> func) override{
            event.AddListener(ownerPtr, std::move(func));
        }

        void RemoveListener(const void* ownerPtr) override{
            event.RemoveListener(ownerPtr);
        }

        void ClearListeners() override{
            event.ClearListeners();
        }

    private:
        Event<Args...>& event;
    };

}