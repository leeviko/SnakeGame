#include <chrono>
#include <thread>
#include "includes/Game.h"

Snake::Snake()
{
  x = 0;
  y = 0;
  sDir;
  body;
}

Snake::~Snake(){}

void Snake::move(WIN *win, void SpawnFruit(WIN *win, int &height, int &width), int &height, int &width, int &score, bool &gameLoop)
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

  if(*sDir != STOP)
  {
    for(Location& l : body)
    {
      if(this->x == l.x && this->y == l.y)
      {
        gameLoop = FALSE;
      }
    }
  }

  if ('X' == mvinch(this->y, this->x))
  { 
    score++;
    SpawnFruit(win, height, width);
  } else {
    mvprintw(body[body.size()-1].y,body[body.size()-1].x, "%c", ' ');
    refresh();
    body.pop_back();
  }

  body.insert(body.begin(), {this->y, this->x});
  mvprintw(body[0].y, body[0].x, "%c", 'O');

  refresh();
  std::this_thread::sleep_for(std::chrono::milliseconds(250));
}
