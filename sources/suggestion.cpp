// Copyright 2021 Your Name <your_email>

#include <stdexcept>
#include "suggestion.hpp"

CallSuggestions::CallSuggestions() {
    _suggestions = { };
}

// подготовка предложений (сортировка)
void CallSuggestions::update(json storage) {
    std::sort(storage.begin(), storage.end(),
            // компаратор используется для "обучения" сортировки
            // сортируем по "стоимости"
            // чем ниже стоимость, тем выше вариант
              [](const json& a, const json& b) -> bool {
                  return a.at("cost") < b.at("cost");
              });
    _suggestions = storage;
}

// формируем ответ
json CallSuggestions::suggest(const std::string& input) {
    json res;
    for (size_t i = 0, m = 0; i < _suggestions.size(); ++i) {
        if (input == _suggestions[i].at("id")) {
            //формируем одно предложение
            json sug;
            sug["text"] = _suggestions[i].at("name");
            sug["position"] = m++;
            //кладём в объект - ответ все предложения
            res["suggestions"].push_back(sug);
        }
    }
    return res;
}
