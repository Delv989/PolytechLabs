#ifndef SUBJECT_HPP
#define SUBJECT_HPP

#include <unordered_map>
#include <string>
#include <any>


class Subject {
public:
    std::string replace_words(const std::unordered_map<std::string, std::any>& args);
    std::string find_phrase(const std::unordered_map<std::string, std::any>& args);
    std::string capitalize_words(const std::unordered_map<std::string, std::any>& args);
    std::string capitalize_sentences(const std::unordered_map<std::string, std::any>& args);
    std::string number_sentences(const std::unordered_map<std::string, std::any>& args);
};

#endif