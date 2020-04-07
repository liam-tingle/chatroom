#pragma once
#include "NetLib/ServerConnection.h"

class NetServer
{
public:
	NetServer() = default;
	~NetServer();

	void start();
	void run();
	
private:
    netlib::ServerConnection server;
};