#include <iostream>
#include <fstream>
#include <sstream>
#include <unordered_map>
#include <any>
#include "Engine/Engine.hpp"
#include "Subject/Subject.hpp"
#include "Wrapper/Wrapper.hpp"

// Функция для записи текста в файл
void save_text_to_file(const std::string& file_path, const std::string& content) {
    std::ofstream output_file(file_path);
    if (!output_file.is_open()) {
        throw std::runtime_error("Failed to create file: " + file_path);
    }
    output_file << content;
}

// Функция для чтения текста из файла
std::string load_text_from_file(const std::string& file_path) {
    std::ifstream input_file(file_path);
    if (!input_file.is_open()) {
        throw std::runtime_error("Failed to open file: " + file_path);
    }
    std::ostringstream buffer;
    buffer << input_file.rdbuf();
    return buffer.str();
}

// Функция для выполнения тестов
void execute_tests() {
    const std::string test_file = "test_text.txt";
    const std::string sample_text = "the cat jumped. he smiled brightly";

    try {
        save_text_to_file(test_file, sample_text);

        Subject subject;

        Wrapper replace_wrapper(&subject, [&](const auto& arguments) { return subject.replace_words(arguments); });
        Wrapper find_wrapper(&subject, [&](const auto& arguments) { return subject.find_phrase(arguments); });
        Wrapper capitalize_words_wrapper(&subject, [&](const auto& arguments) { return subject.capitalize_words(arguments); });
        Wrapper capitalize_sentences_wrapper(&subject, [&](const auto& arguments) { return subject.capitalize_sentences(arguments); });
        Wrapper number_sentences_wrapper(&subject, [&](const auto& arguments) { return subject.number_sentences(arguments); });

        Engine command_engine;
        command_engine.register_command(&replace_wrapper, "replace_words");
        command_engine.register_command(&find_wrapper, "find_phrase");
        command_engine.register_command(&capitalize_words_wrapper, "capitalize_words");
        command_engine.register_command(&capitalize_sentences_wrapper, "capitalize_sentences");
        command_engine.register_command(&number_sentences_wrapper, "number_sentences");

        std::unordered_map<std::string, std::any> arguments;

        arguments = { {"text", load_text_from_file(test_file)}, {"word", std::string("cat")}, {"replacement", std::string("dog")} };
        std::cout << "replace_words: " << std::any_cast<std::string>(command_engine.execute("replace_words", arguments)) << "\n";

        arguments = { {"text", load_text_from_file(test_file)}, {"phrase", std::string("smiled")} };
        std::cout << "find_phrase: " << std::any_cast<std::string>(command_engine.execute("find_phrase", arguments)) << "\n";

        arguments = { {"text", load_text_from_file(test_file)} };
        std::cout << "capitalize_words: " << std::any_cast<std::string>(command_engine.execute("capitalize_words", arguments)) << "\n";

        arguments = { {"text", load_text_from_file(test_file)} };
        std::cout << "capitalize_sentences: " << std::any_cast<std::string>(command_engine.execute("capitalize_sentences", arguments)) << "\n";

        arguments = { {"text", load_text_from_file(test_file)} };
        std::cout << "number_sentences: " << std::any_cast<std::string>(command_engine.execute("number_sentences", arguments)) << "\n";
    }
    catch (const std::exception& e) {
        std::cerr << "Error during testing: " << e.what() << "\n";
    }

    if (std::remove(test_file.c_str()) != 0) {
        std::cerr << "Warning: Failed to delete test file." << "\n";
    }
}

int main() {
    execute_tests();
    return 0;
}
