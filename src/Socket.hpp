/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Socket
*/

#ifndef SOCKET_HPP_
#define SOCKET_HPP_
#ifdef _WIN32
    #include <winsock2.h>
    #pragma comment(lib, "ws2_32.lib")
#else
    #include <sys/socket.h>
    #include <netinet/in.h>
    #include <unistd.h>
    #include <arpa/inet.h>
#endif
#include <iostream>
#include <string>
#include <cstring>

class Socket {
    public:
        Socket();
        ~Socket();
        void connect_to(char *ip, int port);
        void receiveData(int socket){};
    protected:
    private:
        int sockfd;
        char buffer[4096];
};

#endif /* !SOCKET_HPP_ */
