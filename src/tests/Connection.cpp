/*
** EPITECH PROJECT, 2023
** Connection.cpp
** File description:
** Connection
*/

#include <criterion/criterion.h>
#include "../server/Server.hpp"
#include "../client/Game.hpp"

// Test: Check if the game client can connect to the TCP Server
Test(Connection, tcpConnection)
{
    Game gameClient;
    ServerClass server;
    bool checkIsConnected = gameClient.connectToServer("127.0.0.1", 4242);
    cr_assert_eq(checkIsConnected, true);
}
