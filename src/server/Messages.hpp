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
struct message {
    std::vector<uint8_t> data;
    size_t size() const {
        return data.size();
    }
};
template <typename T>
class TCPConnection;
struct owned_message {
    std::shared_ptr<TCPConnection<T>> remote = nullptr;
    message<T> msg;
};

#endif /* !MESSAGES_HPP_ */
