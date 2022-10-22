#pragma once

struct Location
{
  int y, x;
};

class Snake
{
public:
  int x, y;
  SDirection *sDir;
  std::vector<Location> body;

  Snake();
  void move(WIN *win, void m_SpawnFruit(WIN *win, int &height, int &width), int &height, int &width, int &score, bool &gameLoop);
};
