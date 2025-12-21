#include <iostream>
#include <string>

#include "impl/peerconnection.hpp"
#include "rtc/peerconnection.hpp"

namespace rtc {

PeerConnection::PeerConnection() : PeerConnection(std::string()) {}

PeerConnection::PeerConnection(std::string config) : CheshireCat<impl::PeerConnection>(std::move(config))
{
    std::cout << "PeerConnection constructor called" << std::endl;
}

PeerConnection::~PeerConnection()
{
    std::cout << "PeerConnection destructor called" << std::endl;
}

void PeerConnection::close()
{
    std::cout << "PeerConnection close called" << std::endl;
    impl()->close();
}

} // namespace rtc
