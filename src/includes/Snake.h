#pragma once

class Snake
{
public:
  int x, y, length;
  SDirection *sDir;

  Snake();
  void move(WIN *win, void m_SpawnFruit(WIN *win, int &height, int &width), int &height, int &width, int &score);
};
