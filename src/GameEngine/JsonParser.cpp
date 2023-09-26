/*
** EPITECH PROJECT, 2023
** r-type
** File description:
** JsonParser
*/

#include "JsonParser.hpp"

JsonParser::JsonParser()
{
}

JsonParser::~JsonParser()
{
}

nlohmann::json JsonParser::readFile(std::string const &path)
{
    std::ifstream inputFile(path);
    return nlohmann::json::parse(inputFile);
}

std::vector<std::string> JsonParser::split(std::string const &str, char const delim) noexcept
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

