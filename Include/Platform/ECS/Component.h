#pragma once
namespace HC {
    class Entity;

    class Component {
    public:
        virtual ~Component() = default;
        void Initialize() {}
        virtual void BeginPlay() {}
        virtual void EndPlay() {}
        [[nodiscard]] Entity* GetEntity() const { return entity; }
        virtual void Update(float deltaTime) {}

        void RegisterEntity(Entity* owner) { entity = owner; }

    private:
        Entity* entity = nullptr;
    };
}
