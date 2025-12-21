#include <iostream>

#include "rtc/peerconnection.hpp"

// c++ *.cpp impl/*.cpp -I. -Iimpl -Irtc

int main()
{
    std::cout << "Cheshire Cat Pattern Test" << std::endl;

    rtc::PeerConnection pc("Sample Config");
    pc.close();

    return 0;
}
