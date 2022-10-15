#include <iostream>
#include <unistd.h>
#include "includes/Types.h"
#include "includes/Snake.h"
#include <ncurses.h>
#include <chrono>
#include <thread>

Snake::Snake()
{
  x = 0;
  y = 0;
  length = 1;
  sDir;
}

void Snake::move()
{
  switch (*sDir)
  {
  case UP:
    this->y--;
    break;
  case DOWN:
    this->y++;
    break;
  case LEFT:
    this->x--;
    break;
  case RIGHT:
    this->x++;
    break;
  default:
    break;
  }
  std::this_thread::sleep_for(std::chrono::milliseconds(250));
  mvprintw(this->y, this->x, "%c", 'O');
  refresh();
}
