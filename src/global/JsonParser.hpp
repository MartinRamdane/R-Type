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

    static nlohmann::json readFile(std::string const &path);

    std::vector<std::string> split(std::string const &str, char const delim) noexcept;

    template <typename T>
    T get(nlohmann::json const jsonData, std::string const key)
    {
        //if there is no dot in the key, we return the value
        if (key.find('.') == std::string::npos)
        {
            if (jsonData.contains(key))
            {
                return jsonData.at(key).get<T>();
            }
            else
            {
                std::cerr << "Key '" << key << "' not found!" << std::endl;
                return T();
            }
        }

        int cou = count(key.begin(), key.end(), '.');
        std::vector<std::string> keys = JsonParser::split(key, '.');

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
