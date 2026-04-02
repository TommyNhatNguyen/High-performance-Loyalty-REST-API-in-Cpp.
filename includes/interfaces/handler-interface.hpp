#pragma once
#include "httplib.h"

class IHandler {
public:
  virtual ~IHandler() = default;
  virtual void setup(httplib::Server &app) = 0;
};