#include "Engine.hpp"

void Engine::register_command(Wrapper* wrapper, const std::string& command_name) {
    if (!wrapper) {
        throw std::invalid_argument("Cannot register a null wrapper for command: " + command_name);
    }

    if (commands_.find(command_name) != commands_.end()) {
        throw std::runtime_error("Command already exists: " + command_name);
    }

    commands_[command_name] = wrapper;
}

std::string Engine::execute(const std::string& command_name, const std::unordered_map<std::string, std::any>& args) {
    auto command_entry = commands_.find(command_name);
    if (command_entry == commands_.end()) {
        throw std::runtime_error("No such command registered: " + command_name);
    }

    Wrapper* command_wrapper = command_entry->second;
    if (!command_wrapper) {
        throw std::runtime_error("Command wrapper is uninitialized for: " + command_name);
    }

    return command_wrapper->execute(args);
}