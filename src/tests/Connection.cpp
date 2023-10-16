/*
** EPITECH PROJECT, 2023
** Connection.cpp
** File description:
** Connection
*/

#include <gtest/gtest.h>
#include "../client/TCPClientImpl.hpp"
#include "../global/EventHandler.hpp"

// Test: Check if the game client can connect to the TCP Server
TEST(TCPConnection, can_connect_to_server) {
    TCPClientImpl client;
    bool checkIsConnected = client.Connect("127.0.0.1", 4242, nullptr);
    ASSERT_EQ(checkIsConnected, true);
}
