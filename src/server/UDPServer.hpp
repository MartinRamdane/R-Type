/*
** EPITECH PROJECT, 2023
** UDPServer
** File description:
** UDPServer
*/

class UDPServer
{
public:
  UDPServer(asio::io_context &io_context, short port)
      : socket_(io_context, asio::ip::udp::endpoint(asio::ip::udp::v4(), port))
  {
    StartReceive();
  }

private:
  void StartReceive()
  {
    socket_.async_receive_from(asio::buffer(data_, max_length), sender_endpoint_,
                               [this](std::error_code ec, std::size_t bytes_received)
                               {
                                 if (!ec && bytes_received > 0)
                                 {
                                   std::cout << "Received from " << sender_endpoint_.address() << ": " << data_ << std::endl;
                                   StartReceive(); // Continue to receive
                                 }
                               });
  }

  asio::ip::udp::socket socket_;
  asio::ip::udp::endpoint sender_endpoint_;
  enum
  {
    max_length = 1024
  };
  char data_[max_length];
};