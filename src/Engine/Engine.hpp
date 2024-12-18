#pragma once

#include <unordered_map>
#include <string>
#include <functional>
#include "../Wrapper/Wrapper.hpp"

class Engine {
public:
    void register_command(Wrapper* wrapper, const std::string& command_name);
    std::string execute(const std::string& command_name, const std::unordered_map<std::string, std::any>& args);

private:
    std::unordered_map<std::string, Wrapper*> commands_;
};
