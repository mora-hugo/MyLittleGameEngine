#pragma once

#include "Reflection/Property.h"
#include "Event/ReadOnlyEvent.h"
#include "Reflection/HCObject.h"
#include "Reflection/ReflexionMacro.h"
#include "typeindex"
#include <iostream>
#define INSPECTOR_PROPERTY_OF(type, inspectorClass) \
    static inline bool registered = (InspectorProperty::RegisterInspector<type>(StaticClass()), true);

namespace HC::Editor {


    class InspectorProperty : public HCObject {

    public:
        InspectorProperty() : HCObject(), OnValueChanged(InternalOnValueChanged)  {

        }

        void SetProperty(Property& property) {
            this->property = property;

        }


        virtual ~InspectorProperty() = default;

        virtual void Draw() = 0;
    public:
        ReadOnlyEvent<> OnValueChanged;

        template<typename T>
        static void RegisterInspector(HCClass* inspectorClass) {
            using PointerType = std::add_pointer_t<T>;
            auto type = std::type_index(typeid(PointerType));

            inspectorClasses[type] = inspectorClass;
        }


        static HCClass* GetInspectorPropertyClass(const Property& property) {
            if(inspectorClasses.contains(property.propertyValue.type())) {
                return inspectorClasses[property.propertyValue.type()];
            }

            return nullptr;
        }



        // <HCClass*, HCClass*> : <default class, inspector property class>
        // we use typeindex because i can't reflect primitive types
        // TODO: Find a way to use HCClass reflection for primitive types
        static inline std::unordered_map<std::type_index, HCClass*> inspectorClasses;
    protected:
        Event<> InternalOnValueChanged;

    protected:
        Property property { "Property", nullptr };

        START_REFLECTION(InspectorProperty)
        STOP_REFLECTION()
    };
}