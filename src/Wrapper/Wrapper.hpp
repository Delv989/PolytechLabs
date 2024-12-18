#pragma once

#include <functional>
#include <string>
#include <unordered_map>
#include <any>
#include <stdexcept>
#include "../Subject/Subject.hpp"

class Wrapper {
public:
    Wrapper(Subject* subject, const std::function<std::string(const std::unordered_map<std::string, std::any>&)> func);
    std::string execute(const std::unordered_map<std::string, std::any>& args);

private:
    Subject* subject_;
    std::function<std::string(const std::unordered_map<std::string, std::any>&)> function_;
};
