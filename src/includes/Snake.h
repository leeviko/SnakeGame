#pragma once

class Snake
{
public:
  int x, y, length;
  SDirection *sDir;

  Snake();
  void move();
};
