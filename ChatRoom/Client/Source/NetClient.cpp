#include <iostream>
#include <thread>
#include <Printer.h>
#include "NetClient.h"


void NetClient::connect()
{
    client.ConnectToIP("localhost", 8888);
}

void NetClient::run()
{
    using namespace netlib;
    while (client.IsRunning())
    {
        std::queue<NetworkEvent> all_events = client.GetNetworkEvents();
        while(!all_events.empty())
        {
            NetworkEvent& event = all_events.front();
            switch (event.eventType)
            {
                case NetworkEvent::EventType::ON_CONNECT:
                {
                    Printer() << "Connected to the server!" << std::endl;
                    std::thread tr(&NetClient::input, this);
                    tr.detach();
                    break;
                }
                case NetworkEvent::EventType::ON_DISCONNECT:
                {
                    break;
                }
                case NetworkEvent::EventType::MESSAGE:
                {
                    break;
                }
            }
            all_events.pop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
    exiting = true;
}

void NetClient::input()
{
    while (!exiting)
    {
        std::string input;
        std::getline(std::cin, input);
        input = std::to_string(client.GetUID()) + ": " + input;
        client.SendMessageToServer(input.c_str(), input.size() + 1);
    }
}

