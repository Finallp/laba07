// Copyright 2021 Your Name <your_email>

#ifndef INCLUDE_JSONSTORAGE_HPP_
#define INCLUDE_JSONSTORAGE_HPP_

#include <iostream>
#include <string>
#include "nlohmann/json.hpp"

using json = nlohmann::json;

// json хранилище
class JsonStorage{
public:
    // предотвращает неявное преобразование типов
    explicit JsonStorage(const std::string filename);
    json get_storage() const;
    void load();

private:
    json _storage; // Место хранения
    std::string _filename; // Имя файла
};

#endif  // INCLUDE_JSONSTORAGE_HPP_
