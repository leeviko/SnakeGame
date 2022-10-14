#include <iostream>
#include <future>
#include <unistd.h>
#include <stdio.h>
#include <ncurses.h>
#include "includes/Types.h"
#include "includes/Snake.h"

void Input(int &gameLoop, SDirection &keyPressed)
{
  initscr();
  noecho();
  int ch;
  while (gameLoop == 1)
  {
    ch = getch();
    switch (ch)
    {
    case 'q':
      std::cout << "Quit" << std::endl;
      endwin();
      gameLoop = 0;
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
  int gameLoop = 1;
  SDirection keyPressed = STOP;

  std::future<void> getInput = std::async(Input, std::ref(gameLoop), std::ref(keyPressed));
  Snake snake;

  while (gameLoop == 1)
  {
    // Draw
    // Move
    snake.move(keyPressed);
    // Input
  }
}
