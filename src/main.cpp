#include <iostream>
#include <fstream>
#include <nlohmann/json.hpp>
#include <vector>
#include <string>
#include <algorithm>
#include "GameEngine/JsonParser.hpp"
#include "GameEngine/Core.hpp"

int main()
{
    Core core;
    core.mainLoop("test");
    return 0;
}
