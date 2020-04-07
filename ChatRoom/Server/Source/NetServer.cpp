#include <thread>
#include <Printer.h>
#include "NetServer.h"

NetServer::~NetServer()
{

}

void NetServer::start()
{
    server.Start(8888);
}

void NetServer::run()
{
    using namespace netlib;
    // while server should not terminate
    static bool terminate = false;
    while (!terminate)
    {
        std::queue<NetworkEvent> all_events = server.GetNetworkEvents();
        while(!all_events.empty())
        {
            NetworkEvent& event = all_events.front();
            switch (event.eventType)
            {
                case NetworkEvent::EventType::ON_CONNECT:
                {
                    ClientInfo info = server.GetClientInfo(event.senderId);
                    Printer() << "New client " << info.name
                              << " connected on ip: " << info.ipv4
                              << " - ID:[" << info.uid << "]" << std::endl;
                    break;
                }
                case NetworkEvent::EventType::ON_DISCONNECT:
                {
                    Printer() << "Client " << event.senderId << " has disconnected." << std::endl;
                    break;
                }
                case NetworkEvent::EventType::MESSAGE:
                {
                    server.SendMessageToAllExcluding(event.data, event.senderId);
                    break;
                }
            }
            all_events.pop();
        }
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
    }
}
