#ifndef DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_TESTS_SRC_MOCK_CLASSES_H
#define DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_TESTS_SRC_MOCK_CLASSES_H

#include "client/lib/connection/include/IRequestable.h"

#include <string>

class Memorizer : public IRequestable {
 public:
    std::string request(const std::string &message) override {
        received_message = message;
        return "";
    }

    std::string received_message;
};

class FixedAnswer : public IRequestable {
 public:
    explicit FixedAnswer(std::string answer) : answer_(std::move(answer)){};

    std::string request(const std::string &message) override {
        return answer_;
    }

 private:
    std::string answer_;
};

#endif  // DICT2FLASHCARDSQT_SRC_PLUGIN_WRAPPERS_TESTS_SRC_MOCK_CLASSES_H
