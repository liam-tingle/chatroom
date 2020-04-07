#pragma once

#include <atomic>
#include <queue>
#include <NetLib/ClientConnection.h>

class NetClient
{
public: 
	NetClient() = default;
	~NetClient() = default;
	void connect();
	void run();
	void input();

private:
	netlib::ClientConnection client;
	std::atomic<bool> exiting = false;
};

