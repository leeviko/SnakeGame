#include "includes/Game.h"

Game::Game()
{
  gameLoop = TRUE;
  keyPressed = STOP;
  score = 0;
}

void Game::m_Start()
{
  int SCREEN_HEIGHT = 16;
  int SCREEN_WIDTH = 36;

  Snake snake;
  snake.sDir = &keyPressed;

  m_InitWindow(&win, SCREEN_HEIGHT, SCREEN_WIDTH);
  snake.x = COLS / 2;
  snake.y = LINES / 2;

  snake.body.push_back({snake.y, snake.x});

  std::future<void> getInput = std::async([this]()
                                          { m_Input(std::ref(gameLoop), std::ref(keyPressed)); });

  m_SpawnFruit(&win, SCREEN_HEIGHT, SCREEN_WIDTH);
  // Main game loop
  while (gameLoop == TRUE)
  {
    if (snake.x <= win.startx || snake.x >= win.startx + SCREEN_WIDTH)
    {
      gameLoop = FALSE;
      break;
    }
    else if (snake.y <= win.starty || snake.y >= win.starty + SCREEN_HEIGHT)
    {
      gameLoop = FALSE;
      break;
    }

    // Print score
    mvprintw((LINES - SCREEN_HEIGHT) / 2 - 1, (COLS - SCREEN_WIDTH) / 2 + 1, "%s%d", "Score: ", score);
    snake.move(&win, m_SpawnFruit, SCREEN_HEIGHT, SCREEN_WIDTH, score, gameLoop);
  }

  endwin();
}

void Game::m_InitWindow(WIN *win, int height, int width)
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

void Game::m_Input(bool &gameLoop, SDirection &keyPressed)
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
      if(keyPressed != DOWN)
        keyPressed = UP;
      break;
    case 'a':
      if(keyPressed != RIGHT)
        keyPressed = LEFT;
      break;
    case 's':
      if(keyPressed != UP)
        keyPressed = DOWN;
      break;
    case 'd':
      if(keyPressed != LEFT)
        keyPressed = RIGHT;
      break;
    default:
      break;
    }
  };
}

void Game::m_SpawnFruit(WIN *win, int &height, int &width)
{
  std::random_device myRandomDevice;
  unsigned seedY = myRandomDevice();
  unsigned seedX = myRandomDevice();

  std::default_random_engine randGenY(seedY);
  std::default_random_engine randGenX(seedX);

  std::uniform_int_distribution<int> randomYPos(win->starty + 1, win->starty + height - 1);
  std::uniform_int_distribution<int> randomXPos(win->startx + 1, win->startx + width - 1);

  int xPos = randomXPos(randGenY);
  int yPos = randomYPos(randGenX);

  mvprintw(yPos, xPos, "%c", 'X');
}
