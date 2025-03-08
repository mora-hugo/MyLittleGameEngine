#pragma once

#include "EditorCommands/EditorCommand.h"
#include "Utils/CircularBuffer.h"
#include <queue>
namespace HC::Editor {
    class EditorCommandManager {
    public:

        static void EnqueueCommand(std::unique_ptr<EditorCommand> command);
        static EditorCommand* DequeueCommand();

        static bool Undo();
    private:
        static inline std::queue<std::unique_ptr<EditorCommand>> commandQueue;
        static inline CircularBuffer<std::unique_ptr<EditorCommand>*> undoBuffer{10};
    };
}