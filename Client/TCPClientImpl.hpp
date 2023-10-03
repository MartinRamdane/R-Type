/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** TCPClientImpl
*/

#ifndef TCPCLIENTIMPL_HPP_
#define TCPCLIENTIMPL_HPP_
#include <sstream>
#include "TCPClient.hpp"
class Game;
class TCPClientImpl : public TCPClient<ACTION>
{
public:
    void SendEvent(Event evt)
    {
        message<ACTION> msg;
        std::vector<uint8_t> data = encodeEvent(evt);
        msg.header.id = evt.ACTION_NAME;
        msg.header.size = sizeof(data);
        msg.body.resize(sizeof(data));
        std::memcpy(msg.body.data(), data.data(), sizeof(data));
        Send(msg);
    }
    void setGame(Game *game)
    {
        _game = game;
    }
    std::vector<uint8_t> encodeEvent(Event event)
    {
        EventHandler evt;
        evt.addEvent(event.ACTION_NAME, event.body_size, event.body);
        return evt.encodeMessage();
    }
    void HandleMessage(message<ACTION> &msg);

private:
    Game *_game;
};

#endif /* !TCPCLIENTIMPL_HPP_ */
