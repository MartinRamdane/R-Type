/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** TCPClientImpl
*/

#ifndef TCPCLIENTIMPL_HPP_
#define TCPCLIENTIMPL_HPP_
#include "TCPClient.hpp"
#include "Game.hpp"
class Game;
class TCPClientImpl : public TCPClient<ACTION> {
public:
    void SendEvent(Event evt) {
        message<ACTION> msg;
        std::vector<uint8_t> data = encodeEvent(evt);
        msg.header.id = evt.ACTION_NAME;
        msg.header.size = sizeof(data);
        msg.body.resize(sizeof(data));
        std::memcpy(msg.body.data(), data.data(), sizeof(data));
        Send(msg);
    }
    void setGame(Game *game) {
        _game = game;
    }
    std::vector<uint8_t> encodeEvent(Event event) {
        EventHandler evt;
        evt.addEvent(event.ACTION_NAME, event.body_size, event.body);
        return evt.encodeMessage();
    }
    void HandleMessage(message<ACTION>& msg) {
        switch (msg.header.id)
        {
        case ACTION::CONNECT:
        {
            EventHandler evt;
            evt.decodeMessage(msg.body);
            std::cout << "[BODY DATA : ]" << evt.getBody() << std::endl;
        }
        break;
        case ACTION::CREATE:
        {
            EventHandler evt;
            evt.decodeMessage(msg.body);
            std::cout << "[BODY DATA : ]" << evt.getBody() << std::endl;
            //TODO : Interepereter réponse de création d'instance -> Connecter au serveur UDP de l'instance du coup
        }
        break;
        case ACTION::LIST:
        {
        }
        break;
        case ACTION::JOIN:
        {
        }
        break;
        case ACTION::JOINED:
        {
        }
        break;
        case ACTION::READY:
        {
        }
        break;
        case ACTION::START:
        {
        }
        break;
        case ACTION::LEFT:
        {
        }
        break;
        case ACTION::RIGHT:
        {
        }
        break;
        case ACTION::UP:
        {
        }
        break;
        case ACTION::DOWN:
        {
        }
        break;
        case ACTION::SHOOT:
        {
        }
        break;
        case ACTION::QUIT:
        {
        }
        break;
    }
    }
private:
    Game *_game;
};

#endif /* !TCPCLIENTIMPL_HPP_ */
