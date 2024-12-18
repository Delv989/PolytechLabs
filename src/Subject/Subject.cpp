#include "Subject.hpp"
#include <cctype>
#include <sstream>
#include <algorithm>

static std::string fetch_argument(const std::unordered_map<std::string, std::any>& args, const std::string& key) {
    try {
        return std::any_cast<std::string>(args.at(key));
    } catch (const std::exception& e) {
        throw std::invalid_argument("Argument missing or invalid: " + key + " - " + e.what());
    }
}

std::string Subject::find_phrase(const std::unordered_map<std::string, std::any>& args) {
    const auto& input_text = fetch_argument(args, "text");
    const auto& target_phrase = fetch_argument(args, "phrase");

    return (input_text.find(target_phrase) != std::string::npos) ? "Found" : "Not Found";
}

std::string Subject::replace_words(const std::unordered_map<std::string, std::any>& args) {
    auto input_text = fetch_argument(args, "text");
    const auto& search_term = fetch_argument(args, "word");
    const auto& replacement = fetch_argument(args, "replacement");

    size_t position = 0;
    while ((position = input_text.find(search_term, position)) != std::string::npos) {
        input_text.replace(position, search_term.length(), replacement);
        position += replacement.length();
    }
    return input_text;
}

std::string Subject::capitalize_words(const std::unordered_map<std::string, std::any>& args) {
    auto input_text = fetch_argument(args, "text");
    bool should_capitalize = true;
    for (char& character : input_text) {
        if (std::isspace(character)) {
            should_capitalize = true;
        } else if (should_capitalize) {
            character = std::toupper(character);
            should_capitalize = false;
        }
    }
    return input_text;
}

std::string Subject::capitalize_sentences(const std::unordered_map<std::string, std::any>& args) {
    auto input_text = fetch_argument(args, "text");
    bool should_capitalize = true;
    for (char& character : input_text) {
        if (should_capitalize && std::isalpha(character)) {
            character = std::toupper(character);
            should_capitalize = false;
        }
        if (character == '.' || character == '!' || character == '?') {
            should_capitalize = true;
        }
    }
    return input_text;
}

std::string Subject::number_sentences(const std::unordered_map<std::string, std::any>& args) {
    const auto& input_text = fetch_argument(args, "text");
    std::stringstream output;

    size_t sentence_start = 0;
    size_t sentence_end = 0;
    int sentence_counter = 1;

    while ((sentence_end = input_text.find_first_of(".!?", sentence_start)) != std::string::npos) {
        output << sentence_counter++ << ". " << input_text.substr(sentence_start, sentence_end - sentence_start + 1) << "\n";
        sentence_start = sentence_end + 1;
    }

    if (sentence_start < input_text.size()) {
        output << sentence_counter++ << ". " << input_text.substr(sentence_start) << "\n";
    }
    return output.str();
}
