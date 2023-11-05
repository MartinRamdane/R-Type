/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** Messages
*/

#ifndef MESSAGES_HPP_
#define MESSAGES_HPP_
#include "TCPServerConnection.hpp"

template <typename T>
struct message_header {
    T id{};
    uint32_t size = 0;
};
template <typename T>
struct message {
    message_header<T> header{};
    std::vector<uint8_t> body;
    size_t size() const { return body.size(); }
};
template <typename T>
class TCPConnection;
template <typename T>
struct owned_message {
    std::shared_ptr<TCPConnection<T>> remote = nullptr;
    message<T> msg;
};

#endif /* !MESSAGES_HPP_ */
