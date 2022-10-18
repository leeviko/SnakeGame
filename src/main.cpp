#include <iostream>
#include <future>
#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>
#include <string.h>
#include "includes/Types.h"
#include "includes/Snake.h"

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

void InitScreen(WIN *win, int &height, int &width)
{
  initscr();
  cbreak();
  noecho();

  win->height = height;
  win->width = width;
  win->starty = (LINES - win->height) / 2;
  win->startx = (COLS - win->width) / 2;

  win->border.ls = '|';
  win->border.rs = '|';
  win->border.ts = '-';
  win->border.bs = '-';
  win->border.tl = '+';
  win->border.tr = '+';
  win->border.bl = '+';
  win->border.br = '+';

  int x = win->startx;
  int y = win->starty;

  // --- Box
  // Corners
  mvaddch(y, x, win->border.tl);
  mvaddch(y, x + width, win->border.tr);
  mvaddch(y + height, x, win->border.bl);
  mvaddch(y + height, x + width, win->border.br);
  // Vertical lines
  mvhline(y, x + 1, win->border.ts, width - 1);
  mvhline(y + height, x + 1, win->border.bs, width - 1);
  // Horizontal lines
  mvvline(y + 1, x, win->border.ls, height - 1);
  mvvline(y + 1, x + width, win->border.rs, height - 1);

  refresh();
}

void Input(bool &gameLoop, SDirection &keyPressed)
{
  int ch;
  while (gameLoop == 1)
  {
    ch = getch();
    switch (ch)
    {
    case 'q':
      gameLoop = FALSE;
      break;
    case 'w':
      keyPressed = UP;
      break;
    case 'a':
      keyPressed = LEFT;
      break;
    case 's':
      keyPressed = DOWN;
      break;
    case 'd':
      keyPressed = RIGHT;
      break;
    default:
      break;
    }
  };
}

int main()
{
  bool gameLoop = TRUE;
  int SCREEN_HEIGHT = 16;
  int SCREEN_WIDTH = 36;
  WIN win;

  SDirection keyPressed = STOP;
  Snake snake;
  snake.sDir = &keyPressed;

  InitScreen(&win, SCREEN_HEIGHT, SCREEN_WIDTH);
  snake.x = COLS / 2;
  snake.y = LINES / 2;

  std::future<void> getInput = std::async(Input, std::ref(gameLoop), std::ref(keyPressed));

  while (gameLoop == TRUE)
  {
    if (snake.x < win.startx || snake.x > win.startx + SCREEN_WIDTH)
    {
      gameLoop = FALSE;
      break;
    }
    else if (snake.y < win.starty || snake.y > win.starty + SCREEN_HEIGHT)
    {
      gameLoop = FALSE;
      break;
    }

    snake.move();
  }

  endwin();
}
