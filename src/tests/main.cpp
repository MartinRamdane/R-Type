/*
** EPITECH PROJECT, 2023
** main.cpp
** File description:
** main
*/

#include <gtest/gtest.h>

int main(int argc, char **argv) {
    ::testing::InitGoogleTest(&argc, argv);
    int ret = RUN_ALL_TESTS();

    return ret;
}
