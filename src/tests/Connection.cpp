/*
** EPITECH PROJECT, 2023
** Connection.cpp
** File description:
** Connection
*/

#include <gtest/gtest.h>
#include "../client/Game.hpp"
#include "../global/EventHandler.hpp"

// Test: Check if the game client can connect to the TCP Server
TEST(TCPConnection, can_connect_to_server) {
    Game *game = new Game();
    bool clientIsConnected = game->connectToServer("127.0.0.1", 4242);
    ASSERT_EQ(clientIsConnected, true);
}

// Test: Check if the client can connect to the UDP Server
TEST(UDPConnection, can_connect_to_server) {
    Game *game = new Game();
    bool clientIsConnected = game->connectToUdpServer("127.0.0.1", 4210);
    ASSERT_EQ(clientIsConnected, true);
}