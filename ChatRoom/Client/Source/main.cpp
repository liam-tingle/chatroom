#include "NetClient.h"

int main()
{
	NetClient client;
	client.connect();
	client.run();
	return 0;
}