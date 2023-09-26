/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** JsonParser
*/

#pragma once

#include <fstream>
#include <iostream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <algorithm>

class JsonParser
{
public:
    JsonParser();
    ~JsonParser();

    nlohmann::json readFile(std::string const &path);

    std::vector<std::string> split(std::string const &str, char const delim) noexcept;

    template <typename T>
    T get(nlohmann::json const jsonData, std::string const key);
};
