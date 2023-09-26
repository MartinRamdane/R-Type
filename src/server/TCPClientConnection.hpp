/*
** EPITECH PROJECT, 2023
** B-CPP-500-MAR-5-1-rtype-martin.ramdane
** File description:
** TCPClientConnection
*/

#ifndef TCPCLIENTCONNECTION_HPP_
#define TCPCLIENTCONNECTION_HPP_
#include <iostream>
#include <boost/system/error_code.hpp>
#include <boost/bind.hpp>
#include <boost/asio.hpp>
#include <boost/shared_ptr.hpp>
#include <boost/enable_shared_from_this.hpp>
#include "EventHandler.hpp"

using boost::asio::ip::tcp;

class TCPClientConnection : public boost::enable_shared_from_this<TCPClientConnection> {
    public:
    typedef boost::shared_ptr<TCPClientConnection> pointer;
    static pointer create(boost::asio::io_service &ios)
    {
      return pointer(new TCPClientConnection(ios));
    }
    tcp::socket &socket()
    {
      return _socket;
    }
    void start();
    protected:
    private:
        TCPClientConnection(boost::asio::io_service &io_service);
        tcp::socket _socket;
        void handleWrite(const boost::system::error_code &error);
        std::string _message;
        void handleRead(const boost::system::error_code &error);
};

#endif /* !TCPCLIENTCONNECTION_HPP_ */
