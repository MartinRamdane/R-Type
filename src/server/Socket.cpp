/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Socket
*/

#include "Socket.hpp"

Socket::Socket()
{
    #ifdef _WIN32
        WSADATA WSAData;
        if (WSAStartup(MAKEWORD(2,0), &WSAData) != 0) {
            std::cerr << "WSAStartup failed !" << std::endl;
        } else {
            std::cout << "WSAStartup success !" << std::endl;
        }
    #endif
}

Socket::~Socket()
{
    #ifdef _WIN32
        closesocket(sockfd);
        WSACleanup();
    #else
        close(sockfd);
    #endif

}

void Socket::connect_to(char *ip, int port)
{
    struct sockaddr_in server;
    #ifdef _WIN32
        sockfd = socket(AF_INET, SOCK_STREAM, 0);
    #else
        sockfd = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    #endif
    if (sockfd == -1) {
        std::cerr << "Failed to create socket." << std::endl;
    }
    struct sockaddr_in serverAddr;
    serverAddr.sin_family = AF_INET;
    serverAddr.sin_port = htons(port);
    #ifdef _WIN32
        serverAddr.sin_addr.s_addr = inet_addr(ip);
    #else
        inet_pton(AF_INET, ip, &serverAddr.sin_addr);
    #endif
    if (connect(sockfd, (struct sockaddr *)&serverAddr, sizeof(serverAddr)) < 0) {
        std::cerr << "Failed to connect to server." << std::endl;
    } else {
        std::cout << "Connected to server." << std::endl;
    }
}

