#include <chrono>
#include <thread>
#include "includes/Game.h"

Snake::Snake()
{
  x = 0;
  y = 0;
  length = 1;
  sDir;
}

void Snake::move(WIN *win, void m_SpawnFruit(WIN *win, int &height, int &width), int &height, int &width, int &score)
{
  int prevX = this->x;
  int prevY = this->y;

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

  if ('X' == mvinch(this->y, this->x))
  {
    score++;
    length++;

    m_SpawnFruit(win, height, width);
  }

  mvprintw(prevY, prevX, "%c", ' '); // Clear previous position
  mvprintw(this->y, this->x, "%c", 'O');
  refresh();
}
