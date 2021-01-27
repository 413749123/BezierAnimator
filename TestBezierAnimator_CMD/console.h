#pragma once
#include <iostream>

class Console
{
private:
  struct Cursor
  {
  public:

    // up down是y变化，x不变
    void up(int n = 1)
    {
      std::cout << "\033[" << n << "A";
    }

    void down(int n = 1)
    {
      std::cout << "\033[" << n << "B";
    }

    void right(int n = 1)
    {
      std::cout << "\033[" << n << "C";
    }

    void left(int n = 1)
    {
      std::cout << "\033[" << n << "D";
    }

    void save()
    { // 保存当前位置
      std::cout << "\0337";
    }

    void restore()
    { // 回到保存的位置
      std::cout << "\0338";
    }

    void nextLine(int n = 1)
    { // 光标以当前位置为起始位置，往下到第n行开头
      std::cout << "\033[" << n << "E";
    }

    void previousLine(int n = 1)
    { // 光标以当前位置为起始位置，网上到第n行开头
      std::cout << "\033[" << n << "F";
    }

    void move(int y = 0, int x = 0)
    { // 以当前屏幕为原点(0,0)移动光标
      std::cout << "\033[" << y << ";" << x << "H";
    }

    void enableBlinking(bool enable = false)
    {
      std::cout << "\033[?12" << (enable ? "h" : "l");
    }

    void hideCursor(bool hide = true)
    {
      std::cout << "\033[?25" << (hide ? "l" : "h");
    }
  };
public:
  Console()
  {
    const auto h_out = GetStdHandle(STD_OUTPUT_HANDLE);
    DWORD mode;

    GetConsoleMode(h_out, &mode);
    SetConsoleMode(h_out, mode | ENABLE_VIRTUAL_TERMINAL_PROCESSING);
  }
  enum Color
  {
    Black = 0,
    Red,
    Green,
    Yellow,
    Blue,
    Magenta,
    Cyan,
    White
  };

  void underline()
  {
    setTextAttr(4);
  }

  void noUnderline()
  {
    setTextAttr(24);
  }

  void bright()
  { /* 设置前景颜色变亮 */
    setTextAttr(1);
  }

  void normal()
  {
    setTextAttr(0);
  }

  void negative()
  { /* 前景色和背景色交换 */
    setTextAttr(7);
  }

  void positive()
  { /* 将前景色和背景色恢复正常 */
    setTextAttr(27);
  }

  void setForeColor(Color color, bool bright = false)
  {
    setTextAttr(bright ? 90 + color : 30 + color);
  }

  void setBackColor(Color color, bool bright = false)
  {
    setTextAttr(bright ? 100 + color : 40 + color);
  }

  void setScrollRegion(int top, int bottom)
  {
    std::cout << "\033[" << top << ";" << bottom << "r";
  }

  void clearCurLine()
  {
    std::cout << "\033[K";
  }

  void setTitle(const std::string &title)
  {
    std::cout << "\033]2;" << title << "\x07";
  }

  int width()
  {
    auto info = getScreenBufferInfo();
    return info.srWindow.Right - info.srWindow.Left + 1;
  }

  int height()
  {
    auto info = getScreenBufferInfo();
    return info.srWindow.Bottom - info.srWindow.Top + 1;
  }
public:
  Cursor cursor;

private:
  void setTextAttr(int n)
  {
    std::cout << "\033[" << n << "m";
  }

  CONSOLE_SCREEN_BUFFER_INFO getScreenBufferInfo()
  {
    CONSOLE_SCREEN_BUFFER_INFO info;
    GetConsoleScreenBufferInfo(GetStdHandle(STD_OUTPUT_HANDLE), &info);
    return info;
  }

};
