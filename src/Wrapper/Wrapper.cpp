#include "Wrapper.hpp"

Wrapper::Wrapper(Subject* subject, std::function<std::string(const std::unordered_map<std::string, std::any>&)> func)
    : subject_(subject), function_(std::move(func)) {
    if (!subject_) {
        throw std::invalid_argument("Subject pointer cannot be null.");
    }
}

std::string Wrapper::execute(const std::unordered_map<std::string, std::any>& args) {
    if (!function_) {
        throw std::runtime_error("Function not initialized.");
    }
    return function_(args);
}
