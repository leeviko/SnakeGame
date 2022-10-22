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
  int score;

  Game();
  ~Game();
  void InitWindow(WIN *win, int height, int width);
  void Start();
  void End();
  void Input(bool &gameLoop, SDirection &keyPressed);
  static void SpawnFruit(WIN *win, int &height, int &width);
};

#include "Snake.h"
