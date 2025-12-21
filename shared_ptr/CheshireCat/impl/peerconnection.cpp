#include "peerconnection.hpp"
#include <iostream>

namespace rtc::impl {
PeerConnection::PeerConnection(std::string config_) : mConfig(std::move(config_))
{
    std::cout << "Creating impl::PeerConnection with config: " << mConfig << std::endl;
}

PeerConnection::~PeerConnection()
{
    std::cout << "Destroying impl::PeerConnection" << std::endl;
}

void PeerConnection::close()
{
    std::cout << "Closing impl::PeerConnection " << std::endl;
}
} // namespace rtc::impl
