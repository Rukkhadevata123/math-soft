#include <array>
#include <cstdlib>
#include <ctime>
#include <iostream>
#include <ncurses.h>
#include <unistd.h>

using namespace std;

bool gameOver;                   // 游戏结束标志
constexpr int width = 40;        // 游戏区域宽度
constexpr int height = 20;       // 游戏区域高度
int x, y, fruitX, fruitY, score; // 蛇头坐标，水果坐标，得分
array<int, 100> tailX, tailY;    // 蛇尾坐标
int nTail;                       // 蛇尾长度
enum class eDirecton { STOP = 0, LEFT, RIGHT, UP, DOWN }; // 方向枚举
eDirecton dir;                                            // 当前方向
bool specialFood = false;        // 是否有特殊食物
int specialFoodTimer = 0;        // 特殊食物存在时间
int specialFoodCount = 0;        // 吃到特殊食物的次数
int timer = 0;                   // 游戏运行时间
bool canPassThroughWall = false; // 是否可以穿墙

void Setup() {
  initscr();             // 初始化屏幕
  clear();               // 清屏
  noecho();              // 关闭回显
  cbreak();              // 关闭行缓冲
  curs_set(0);           // 隐藏光标
  gameOver = false;      // 游戏未结束
  dir = eDirecton::STOP; // 初始方向为停止
  x = width / 2;         // 蛇头初始位置
  y = height / 2;
  fruitX = rand() % width; // 随机生成水果位置
  fruitY = rand() % height;
  score = 0;      // 初始得分为0
  srand(time(0)); // 初始化随机数种子

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
      else if (i == y && j == x)
        mvprintw(i, j, "*");
      else if (i == fruitY && j == fruitX)
        if (specialFood)
          mvprintw(i, j, "@");
        else
          mvprintw(i, j, "&");
      else {
        bool print = false;
        for (int k = 0; k < nTail; k++) {
          if (tailX[k] == j && tailY[k] == i) {
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
    if (dir != eDirecton::RIGHT)
      dir = eDirecton::LEFT;
    break;
  case KEY_RIGHT:
    if (dir != eDirecton::LEFT)
      dir = eDirecton::RIGHT;
    break;
  case KEY_UP:
    if (dir != eDirecton::DOWN)
      dir = eDirecton::UP;
    break;
  case KEY_DOWN:
    if (dir != eDirecton::UP)
      dir = eDirecton::DOWN;
    break;
  case 113:
    gameOver = true;
    break;
  }
}

bool isTail(int x, int y) {
  for (int i = 0; i < nTail; i++)
    if (tailX[i] == x && tailY[i] == y)
      return true;
  return false;
}

void algorithm() {
  // 更新蛇尾坐标
  int prevX = tailX[0];
  int prevY = tailY[0];
  int prev2X, prev2Y;
  tailX[0] = x;
  tailY[0] = y;

  for (int i = 1; i < nTail; i++) {
    prev2X = tailX[i];
    prev2Y = tailY[i];
    tailX[i] = prevX;
    tailY[i] = prevY;
    prevX = prev2X;
    prevY = prev2Y;
  }

  // 根据方向移动蛇头
  switch (dir) {
  case eDirecton::LEFT:
    x--;
    break;
  case eDirecton::RIGHT:
    x++;
    break;
  case eDirecton::UP:
    y--;
    break;
  case eDirecton::DOWN:
    y++;
    break;
  default:
    break;
  }
  // 检查是否撞墙或撞到自己
  if (x > width || x < 1 || y > height || y < 1) {
    if (canPassThroughWall) { // 如果可以穿墙
      if (x > width)
        x = 1;
      if (x < 1)
        x = width;
      if (y > height)
        y = 1;
      if (y < 1)
        y = height;
    } else {
      gameOver = true;
    }
  }

  for (int i = 0; i < nTail; i++)
    if (tailX[i] == x && tailY[i] == y)
      gameOver = true;

  // 检查是否吃到食物
  if (x == fruitX && y == fruitY) {
    if (specialFood) {     // 如果吃到的是特殊食物
      score += 20;         // 分数增加20
      specialFoodCount++;  // 吃到特殊食物的次数增加1
      specialFood = false; // 特殊食物消失
    } else {
      score += 10; // 否则分数增加10
    }
    do {
      fruitX = (rand() % width) + 1;
      fruitY = (rand() % height) + 1;
    } while (isTail(fruitX, fruitY)); // 重新生成食物位置，直到它不再与蛇身重合
    nTail++;
  }
  timer++;               // 游戏运行时间增加1
  if (timer % 50 == 0) { // 每50个时间单位，有可能出现一个特殊食物
    if (rand() % 2 == 0) { // 有50%的概率出现特殊食物
      specialFood = true;
      specialFoodTimer =
          rand() % 20 + 1; // 特殊食物存在的时间单位随机，范围在1到20之间
    }
  }
  if (specialFood) {    // 如果有特殊食物
    specialFoodTimer--; // 特殊食物的存在时间减1
    if (specialFoodTimer == 0) // 如果特殊食物的存在时间到了，就让它消失
      specialFood = false;
  }
}

int main() {
  Setup();            // 游戏设置
  while (!gameOver) { // 游戏主循环
    Draw();           // 绘制游戏界面
    Input();          // 获取用户输入
    algorithm();      // 游戏逻辑
  }

  cout << endl;
  cout << "Game Over!" << endl; // 输出游戏结束信息
  sleep(3);                     // 等待3秒

  getch();  // 游戏结束后等待用户输入
  endwin(); // 结束窗口模式

  return 0;
}