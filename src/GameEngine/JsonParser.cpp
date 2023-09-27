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

nlohmann::json JsonParser::readFile(std::string const &fileName)
{
    std::string directory = ".";
    for (const auto &entry : std::filesystem::recursive_directory_iterator(directory))
    {
        if (entry.is_regular_file())
        {
            std::string filePath = entry.path().string();
            std::string key = entry.path().stem().string();
            key = key + ".json";
            if (key == fileName)
            {
                std::ifstream inputFile(filePath);
                if (inputFile.is_open())
                {
                    // std::cout << "JSON contenu : " << inputFile.rdbuf() << std::endl;
                    return nlohmann::json::parse(inputFile);
                }
                else
                {
                    std::cerr << "Impossible de trouver le JSON : " << key << std::endl;
                    // Handle the case where the file couldn't be opened
                    // You might want to throw an exception or return a default JSON object.
                }
            }
        }
    }

    // Handle the case where the JSON file was not found
    std::cerr << "Here Impossible de trouver le JSON : " << fileName << std::endl;
    // You might want to throw an exception or return a default JSON object.
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
