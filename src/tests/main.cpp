/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include <gtest/gtest.h>
#include "../server/Server.hpp"

int main(int argc, char **argv) {
    ServerClass server("r-type");
    std::thread([&server]()
                { server.loop(); }).detach();
    server.createInstance();
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();

    return ret;
}
