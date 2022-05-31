// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_SUGGESTION_HPP_
#define INCLUDE_SUGGESTION_HPP_

#include <iostream>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// коллекция предложений
class CallSuggestions{
public:
    CallSuggestions();
    void update(json storage);
    json suggest(const std::string& input);

private:
    json _suggestions; // Предложения
};

#endif  // INCLUDE_SUGGESTION_HPP_
