#ifndef SERVER_H
#define SERVER_H

// #include "publisher.h"
// #include <zmq.hpp>
// #include <mutex>
// #include <tuple>
// #include <string>
// #include <memory>
// #include <map>
// #include <functional>
// #include <chrono>

// class Server
// {
// protected:
    // std::string router_addr;
    // std::map<std::string, std::weak_ptr<Publisher>> publishers;
    // std::function<void(ReceivedRequest)> message_handler;

// public:
//     Server()
        // : router_addr(addr)
        // , message_handler(NULL)
    // {
    // }

    // void run();
    // void stop();

    // void register_handler(std::function<void(const ReceivedRequest)> handler);
    // std::shared_ptr<Publisher> get_publisher(std::string address);
// };
#endif // !SERVER_H
