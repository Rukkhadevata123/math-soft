#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

constexpr int width = 40;  // 游戏区域宽度
constexpr int height = 20; // 游戏区域高度

enum class eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN }; // 方向枚举

struct Snake {
  int x, y;                     // 蛇头坐标
  array<int, 100> tailX, tailY; // 蛇尾坐标
  int nTail;                    // 蛇尾长度
  eDirecton dir;                // 当前方向

  Snake() {
    dir = eDirecton::STOP; // 初始方向为停止
    x = width / 2;         // 蛇头初始位置
    y = height / 2;
    nTail = 0;
  }
};

struct Food {
  int fruitX, fruitY;       // 水果坐标
  bool specialFood = false; // 是否有特殊食物
  int specialFoodTimer = 0; // 特殊食物存在时间

  Food() {
    fruitX = rand() % (width - 1); // 随机生成水果位置
    fruitY = rand() % (height - 1);
  }
};

struct Game {
  bool gameOver;                   // 游戏结束标志
  int score;                       // 得分
  int specialFoodCount = 0;        // 吃到特殊食物的次数
  int timer = 0;                   // 游戏运行时间
  bool canPassThroughWall = false; // 是否可以穿墙
  Snake snake;
  Food food;

  Game() {
    initscr();            // 初始化屏幕
    clear();              // 清屏
    noecho();             // 关闭回显
    cbreak();             // 关闭行缓冲
    curs_set(0);          // 隐藏光标
    gameOver = false;     // 游戏未结束
    score = 0;            // 初始得分为0
    srand(time(nullptr)); // 初始化随机数种子
  }

  void Setup() {
    initscr();                   // 初始化屏幕
    clear();                     // 清屏
    noecho();                    // 关闭回显
    cbreak();                    // 关闭行缓冲
    curs_set(0);                 // 隐藏光标
    gameOver = false;            // 游戏未结束
    snake.dir = eDirecton::STOP; // 初始方向为停止
    snake.x = width / 2;         // 蛇头初始位置
    snake.y = height / 2;
    food.fruitX = rand() % width; // 随机生成水果位置
    food.fruitY = rand() % height;
    score = 0;            // 初始得分为0
    srand(time(nullptr)); // 初始化随机数种子

    // 询问用户是否可以穿墙
    mvprintw(0, 0, "Can pass through wall? (y/n)");
    refresh();
    char c = getch();
    if (c == 'y' || c == 'Y') {
      canPassThroughWall = true;
      mvprintw(1, 0, "Mode: Can pass through wall");
    } else {
      mvprintw(1, 0, "Mode: Cannot pass through wall");
    }
    refresh();
    getch(); // 等待用户按键开始游戏
    clear(); // 清屏
  }

  void Draw() {
    clear(); // 清屏
    // 绘制游戏区域边界
    for (int i = 0; i < width + 2; i++)
      mvprintw(0, i, "#");
    for (int i = 0; i < height + 2; i++) {
      for (int j = 0; j < width + 2; j++) {
        // 绘制蛇头、蛇尾、水果
        if (i == 0 | i == 21)
          mvprintw(i, j, "#");
        else if (j == 0 | j == 41)
          mvprintw(i, j, "#");
        else if (i == snake.y && j == snake.x)
          mvprintw(i, j, "*");
        else if (i == food.fruitY && j == food.fruitX)
          if (food.specialFood)
            mvprintw(i, j, "@");
          else
            mvprintw(i, j, "&");
        else {
          bool print = false;
          for (int k = 0; k < snake.nTail; k++) {
            if (snake.tailX[k] == j && snake.tailY[k] == i) {
              mvprintw(i, j, "*");
              print = true;
            }
          }
          if (!print)
            mvprintw(i, j, " ");
        }
      }
    }
    // 显示得分和吃到特殊食物的次数
    mvprintw(23, 0, "Score %d", score);
    mvprintw(24, 0, "Special Food Count %d", specialFoodCount);

    if (canPassThroughWall) {
      mvprintw(25, 0, "Mode: Can pass through wall");
    } else {
      mvprintw(25, 0, "Mode: Cannot pass through wall");
    }

    refresh(); // 刷新屏幕
  }

  void Input() {
    keypad(stdscr, TRUE); // 开启键盘输入
    halfdelay(1);         // 设置输入延迟

    int c = getch(); // 获取输入

    // 根据输入改变方向或结束游戏
    switch (c) {
    case KEY_LEFT:
      if (snake.dir != eDirecton::RIGHT)
        snake.dir = eDirecton::LEFT;
      break;
    case KEY_RIGHT:
      if (snake.dir != eDirecton::LEFT)
        snake.dir = eDirecton::RIGHT;
      break;
    case KEY_UP:
      if (snake.dir != eDirecton::DOWN)
        snake.dir = eDirecton::UP;
      break;
    case KEY_DOWN:
      if (snake.dir != eDirecton::UP)
        snake.dir = eDirecton::DOWN;
      break;
    case 113:
      gameOver = true;
      break;
    }
  }

  bool isTail(int x, int y) {
    for (int i = 0; i < snake.nTail; i++)
      if (snake.tailX[i] == x && snake.tailY[i] == y)
        return true;
    return false;
  }

  void algorithm() {
    // 更新蛇尾坐标
    int prevX = snake.tailX[0];
    int prevY = snake.tailY[0];
    int prev2X, prev2Y;
    snake.tailX[0] = snake.x;
    snake.tailY[0] = snake.y;

    for (int i = 1; i < snake.nTail; i++) {
      prev2X = snake.tailX[i];
      prev2Y = snake.tailY[i];
      snake.tailX[i] = prevX;
      snake.tailY[i] = prevY;
      prevX = prev2X;
      prevY = prev2Y;
    }

    // 根据方向移动蛇头
    switch (snake.dir) {
    case eDirecton::LEFT:
      snake.x--;
      break;
    case eDirecton::RIGHT:
      snake.x++;
      break;
    case eDirecton::UP:
      snake.y--;
      break;
    case eDirecton::DOWN:
      snake.y++;
      break;
    default:
      break;
    }
    // 检查是否撞墙或撞到自己
    if (snake.x > width || snake.x < 1 || snake.y > height || snake.y < 1) {
      if (canPassThroughWall) { // 如果可以穿墙
        if (snake.x > width)
          snake.x = 1;
        if (snake.x < 1)
          snake.x = width;
        if (snake.y > height)
          snake.y = 1;
        if (snake.y < 1)
          snake.y = height;
      } else {
        gameOver = true;
      }
    }

    for (int i = 0; i < snake.nTail; i++)
      if (snake.tailX[i] == snake.x && snake.tailY[i] == snake.y)
        gameOver = true;

    // 检查是否吃到食物
    if (snake.x == food.fruitX && snake.y == food.fruitY) {
      if (food.specialFood) {     // 如果吃到的是特殊食物
        score += 20;              // 分数增加20
        specialFoodCount++;       // 吃到特殊食物的次数增加1
        food.specialFood = false; // 特殊食物消失
      } else {
        score += 10; // 否则分数增加10
      }
      do {
        food.fruitX = (rand() % width) + 1;
        food.fruitY = (rand() % height) + 1;
      } while (isTail(food.fruitX,
                      food.fruitY)); // 重新生成食物位置，直到它不再与蛇身重合
      snake.nTail++;
    }
    timer++;               // 游戏运行时间增加1
    if (timer % 50 == 0) { // 每50个时间单位，有可能出现一个特殊食物
      if (rand() % 2 == 0) { // 有50%的概率出现特殊食物
        food.specialFood = true;
        food.specialFoodTimer =
            rand() % 20 + 1; // 特殊食物存在的时间单位随机，范围在1到20之间
      }
    }
    if (food.specialFood) {    // 如果有特殊食物
      food.specialFoodTimer--; // 特殊食物的存在时间减1
      if (food.specialFoodTimer == 0) // 如果特殊食物的存在时间到了，就让它消失
        food.specialFood = false;
    }
  }
};

int main() {
  Game game;
  game.Setup();            // 游戏设置
  while (!game.gameOver) { // 游戏主循环
    game.Draw();           // 绘制游戏界面
    game.Input();          // 获取用户输入
    game.algorithm();      // 游戏逻辑
  }

  cout << endl;
  cout << "Game Over!" << endl; // 输出游戏结束信息
  sleep(3);                     // 等待3秒

  getch();  // 游戏结束后等待用户输入
  endwin(); // 结束窗口模式

  return 0;
}