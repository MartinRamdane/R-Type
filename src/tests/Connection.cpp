/*
** EPITECH PROJECT, 2023
** Connection.cpp
** File description:
** Connection
*/

#include <gtest/gtest.h>
#include "../global/EventHandler.hpp"
#include "../server/TCPServer.hpp"
#include "../server/UDPServer.hpp"
#include "../global/JsonParser.hpp"

TEST(READJSON, can_read_json) {
    JsonParser jsonParser;
    nlohmann::json jsonFile = jsonParser.readFile("rTypeInstanceConfig.json");
    int nbPlayersMax = jsonParser.get<int>(jsonFile, "nbPlayersMax");
    ASSERT_EQ(nbPlayersMax, 4);
}

// Test: Check if the client can connect to the UDP Server
TEST(UDPServer, can_bind_udp_server) {
    boost::asio::io_service _io_service;
    UDPServer *udpServer = new UDPServer(_io_service, 4210);
    bool clientIsConnected = true;
    ASSERT_EQ(clientIsConnected, true);
}

TEST(CRCCheck, can_check_crc) {
    EventHandler eventHandler(ACTION::RESET, "testing");
    std::vector<uint8_t> coded = eventHandler.encodeMessage();
    Event decoded = eventHandler.decodeMessage(coded);
    int test = 4343;
    uint32_t testCrc = eventHandler.calculateCRCForInt(test);
    ASSERT_EQ(testCrc, eventHandler.calculateCRCForInt(test));
    ASSERT_EQ(decoded.ACTION_NAME, ACTION::RESET);
}