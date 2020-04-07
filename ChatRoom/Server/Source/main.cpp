#include <memory>
#include "NetServer.h"

int main()
{
  NetServer server;
  server.start();
  server.run();
  return 0;
}
