#pragma once
#include "Reflection/IReflectable.h"
#include "Reflection/ReflexionMacro.h"
#include "Reflection/HCObject.h"
#include <functional>
#include <memory>
#include <type_traits>
namespace HC {

    /* Not very memory optimized implementation but its a good start */
    /* Bc we create an entry for each class and add their derived classes */
    /* We can do a tree to optimize this */
    class HCClass  {
        using CreateFunc = std::function<std::unique_ptr<HCObject>()>;
    private:
    public:
        [[nodiscard]] const char* GetClassName() const {
            return name;
        }

        explicit HCClass(const char* className, HCClass* parent, CreateFunc func) : name(className), createFunc(func) {

        }

        std::unique_ptr<HCObject> CreateInstance() {
            return createFunc();
        }

        template<typename T>
        static std::unique_ptr<HCClass> RegisterClass(const char* className, HCClass* parent) {
            /* We add current class to available classes */
            CreateFunc func;

            if constexpr(std::is_abstract<T>::value) {
                func = []() -> std::unique_ptr<HCObject> {
                    return nullptr;
                };
            } else {
                func = []() -> std::unique_ptr<HCObject> {
                    return std::make_unique<T>();
                };
            }

            auto classPtr = std::make_unique<HCClass>(className, parent, func);

            derivedClasses.insert({classPtr.get(), std::vector<HCClass*>()});

            if(IsClassRegistered(parent)) {
                derivedClasses[parent].push_back(classPtr.get());
            }

            return std::move(classPtr);
    }

        [[nodiscard]] static std::vector<HCClass*> GetDerivedClasses(HCClass* parent) {
            if(derivedClasses.contains(parent)) {
                return derivedClasses[parent];
            }
            return {};
        }

        static HCClass* GetClassFromName(const char* className) {
            for(auto& [key, value] : derivedClasses) {
                if(strcmp(key->GetClassName(), className) == 0) {
                    return key;
                }
            }
        }
    protected:
        static bool IsClassRegistered(HCClass* hcClass) {
            return derivedClasses.contains(hcClass);
        }
        static inline std::unordered_map<HCClass*, std::vector<HCClass*>> derivedClasses;

    private:
        const char* name;
        CreateFunc createFunc{};
    };
}