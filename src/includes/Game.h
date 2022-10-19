#pragma once
#include <iostream>
#include <future>
#include <unistd.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>
#include <functional>
#include <random>

#include "Types.h"
#include "Snake.h"

typedef struct _WIN_BORDER_struct
{
  chtype ls, rs, ts, bs,
      tl, tr, bl, br;
} WIN_BORDER;

typedef struct _WIN_struct
{
  int startx, starty;
  int height, width;
  WIN_BORDER border;
} WIN;

class Game
{
public:
  WIN win;
  SDirection keyPressed;
  bool gameLoop;

  Game();
  void m_InitWindow(WIN *win, int height, int width);
  void m_Start();
  void m_End();
  void m_Input(bool &gameLoop, SDirection &keyPressed);
  void m_SpawnFruit(WIN *win, int &height, int &width);
};
