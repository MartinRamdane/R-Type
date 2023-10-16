/*
** EPITECH PROJECT, 2023
** Connection.cpp
** File description:
** Connection
*/

#include <gtest/gtest.h>
#include "../server/TCPClient.hpp"
#include "../server/Server.hpp"
#include "../global/EventHandler.hpp"

// Test: Check if the game client can connect to the TCP Server
TEST(TCPConnection, can_connect_to_server) {
    ServerClass server;
    std::thread([&server]()
        { server.loop(); }).detach();
    TCPClient<ACTION> client;
    client.Connect("127.0.0.1", 4242);
    bool clientIsConnected = client.isConnected();
    ASSERT_EQ(clientIsConnected, true);
}

//to fix: test is not working
TEST(TCPConnection, connection_refused) {
    ServerClass server;
    std::thread([&server]()
        { server.loop(); }).detach();
    TCPClient<ACTION> client;
    client.Connect("localhost", 000);
    bool clientIsConnected = client.isConnected();
    ASSERT_EQ(clientIsConnected, false);
}
