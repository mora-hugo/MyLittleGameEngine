#include "EditorCommands/EditorCommandManager.h"
void HC::Editor::EditorCommandManager::EnqueueCommand(std::unique_ptr<EditorCommand> command) {
    commandQueue.push(std::move(command));
}

HC::Editor::EditorCommand *HC::Editor::EditorCommandManager::DequeueCommand() {
    if(commandQueue.empty()) return nullptr;
    auto command = std::move(commandQueue.front());
    commandQueue.pop();

    return command.release();
}

bool HC::Editor::EditorCommandManager::Undo() {
    if(undoBuffer.empty()) return false;

    auto command = undoBuffer[undoBuffer.size() - 1];
    command->get()->Undo();
    undoBuffer.pop_front();

    //TODO HERE
    return true;
}
