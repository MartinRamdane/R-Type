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
    std::cout << "Reading file : " << fileName << std::endl;
    std::vector<std::string> directories;
    directories.push_back("config/");
    directories.push_back("assets/");
    directories.push_back("font/");
    directories.push_back("sounds/");
    directories.push_back(".");
    for (auto directory : directories) {
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
    }
    // Handle the case where the JSON file was not found
    std::cerr << "Here Impossible de trouver le JSON : " << fileName << std::endl;
    // You might want to throw an exception or return a default JSON object.
    return {};
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

std::unordered_map<std::string, std::string> JsonParser::getJsonFile(std::string const &path) {
    std::cout << "getting json file" << std::endl;
    std::unordered_map<std::string, std::string> jsonFile;
    nlohmann::json json = JsonParser::readFile(path);
    for (auto &it : json.items()) {
        jsonFile[it.key()] = it.value();
    }
    return jsonFile;
}