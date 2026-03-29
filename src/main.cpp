#include "server.hpp"
#include <iostream>
#include <sodium.h>

using namespace std;

int main() {
  if (sodium_init() < 0) {
    std::cerr << "Failed to init sodium\n";
    return 1;
  }

  try {
    Server server;
    server.start();
  } catch (const std::exception &e) {
    std::cerr << e.what() << '\n';
  }
  return 0;
}