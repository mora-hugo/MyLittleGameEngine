#pragma once

#include <glm/vec2.hpp>
#include <Event/ReadOnlyEvent.h>
namespace HC {
    class Viewport {
    public:

       static glm::vec2 GetGameViewportSize() { return gameViewportSize; }
       static glm::vec2 GetEditorViewportSize() { return { 0, 0 }; }

       static  void SetGameViewportSize(const glm::vec2& size) {
           gameViewportSize = size;
           OnViewportResize.Invoke(size);
       }


    public:
        static inline Event<glm::vec2> OnViewportResize;
    private:

    static inline glm::vec2 gameViewportSize = { 0, 0 };
    };
}