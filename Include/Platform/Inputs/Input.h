#pragma once
#include <glm/vec2.hpp>
#include <Inputs/InputManager.h>
#include <Event/ReadOnlyEvent.h>


namespace HC {
    class InputManager;
    class Input {
        friend class App;
    public:
        static bool IsKeyPressed(int key);
        static bool IsMouseButtonPressed(int button);

        static glm::uvec2 GetMousePosition();

        static void Initialize(InputManager* InputManager);

        static void ListenKey(int key);

        static void ListenMouseKey(int key);

        static void StopListenKey(int key);

        static void StopListenMouseKey(int key);



        static ReadOnlyEvent<KeyboardInput>& GetAllKeyboardEvent();
        static ReadOnlyEvent<KeyboardInput>& GetKeyboardEventPressed();
        static ReadOnlyEvent<KeyboardInput>& GetKeyboardEventReleased();
        static ReadOnlyEvent<KeyboardInput>& GetKeyboardEventRepeat();

        static ReadOnlyEvent<MouseInput>& GetAllMouseEvent();
        static ReadOnlyEvent<MouseInput>& GetMouseEventPressed();
        static ReadOnlyEvent<MouseInput>& GetMouseEventReleased();
        static ReadOnlyEvent<MouseInput>& GetMouseEventRepeat();





    private:


        static inline std::unique_ptr<ReadOnlyEvent<KeyboardInput>> KeyboardEvent;
        static inline std::unique_ptr<ReadOnlyEvent<KeyboardInput>> KeyboardEventPressed;
        static inline std::unique_ptr<ReadOnlyEvent<KeyboardInput>> KeyboardEventReleased;
        static inline std::unique_ptr<ReadOnlyEvent<KeyboardInput>> KeyboardEventRepeat;


        static inline std::unique_ptr<ReadOnlyEvent<MouseInput>> MouseEvent;
        static inline std::unique_ptr<ReadOnlyEvent<MouseInput>> MouseEventPressed;
        static inline std::unique_ptr<ReadOnlyEvent<MouseInput>> MouseEventReleased;
        static inline std::unique_ptr<ReadOnlyEvent<MouseInput>> MouseEventRepeat;

        static inline InputManager* inputManager;
    };
}