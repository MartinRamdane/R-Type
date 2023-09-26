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

    nlohmann::json readFile(std::string const &path)
    {
        std::ifstream inputFile(path);
        return nlohmann::json::parse(inputFile);
    }

    std::vector<std::string> split(std::string const &str, char const delim) noexcept
    {
        std::vector<std::string> res = {};
        std::size_t start{0};
        std::size_t end{0};
        while ((start = str.find_first_not_of(delim, end)) != std::string::npos)
        {
            end = str.find(delim, start);
            res.push_back(str.substr(start, end - start));
        }
        return res;
    }

    template <typename T>
    T get(nlohmann::json const jsonData, std::string const key)
    {
        int cou = count(key.begin(), key.end(), '.');
        std::vector<std::string> keys = split(key, '.');

        nlohmann::json const *leaf = &jsonData;

        if (cou > 0)
        {
            for (int i = 0; i <= cou; i++)
            {
                if (leaf->contains(keys[i]))
                {
                    leaf = &leaf->at(keys[i]);
                }
                else
                {
                    std::cerr << "Key '" << keys[i] << "' not found!" << std::endl;
                    return T();
                }
            }
        }
        return leaf->get<T>();
    }
};