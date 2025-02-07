#pragma once

#include <functional>
#include <vector>
#include <map>
#include <Event/IEvent.h>


namespace HC {

    template <typename ...Args>
    class Event : public IEvent<Args...> {
    public:
        Event() = default;
        virtual ~Event() = default;

        Event(const Event&) = delete;
        Event& operator=(const Event&) = delete;

        void AddListener(const void* ownerPtr, std::function<void(Args...)> func) {
            listeners[reinterpret_cast<std::uintptr_t>(ownerPtr)] = std::move(func);
        }

        void RemoveListener(const void* ownerPtr) override {
            auto it = listeners.find(reinterpret_cast<std::uintptr_t>(ownerPtr));
            if (it != listeners.end()) {
                listeners.erase(it);
            }
        }

        void ClearListeners() {
            listeners.clear();
        }

        void Invoke(Args... args) const{
            for (const auto& listener : listeners) {
                listener.second(args...);
            }
        }

    private:
        struct KeyComparer {
            bool operator()(std::uintptr_t lhs, std::uintptr_t rhs) const {
                return lhs < rhs;
            }
        };

        std::map<std::uintptr_t, std::function<void(Args...)>, KeyComparer> listeners;
    };

} // namespace HC
