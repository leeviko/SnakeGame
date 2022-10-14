#include <iostream>
#include <unistd.h>
#include "includes/Types.h"
#include "includes/Snake.h"

Snake::Snake()
{
  x = 0;
  y = 0;
  length = 1;
  sDir = STOP;
}

void Snake::move(SDirection dir)
{
  sDir = dir;
  sleep(1);
  std::cout << "Move to: " << sDir << std::endl;
}

int Snake::getDirection()
{
  return sDir;
};