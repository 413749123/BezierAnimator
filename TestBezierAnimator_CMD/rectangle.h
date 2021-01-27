#pragma once
#include "shape.h"
#include "console.h"

namespace draw
{
  class Rectangle : public Shape
  {
  public:
    Rectangle(int w, int h, int x = 0, int y = 0) : width_(w), height_(h), x_(x), y_(y), last_x_(x), last_y_(y) {
      console.cursor.hideCursor();
    }

    void SetPos(int x, int y)
    {
      x_ = x;
      y_ = y;
    }

    virtual void Draw()
    {
      Console console;
      int bottom = y_ + height_;
      int right = x_ + width_;

      ClearLast();

      last_x_ = x_;
      last_y_ = y_;
      
      for (int y = y_; y < bottom; ++y) {
        console.cursor.move(y, x_);
        for (int i = 0; i < width_; ++i) {
          std::cout << "*";
        }
      }
    }

    void ClearLast()
    {
      for (int y = last_y_; y < last_y_ + height_; ++y) {
        for (int x = last_x_; x < last_x_ + width_; ++x) {
          console.cursor.move(y, x);
          std::cout << " ";
        }
      }
    }

  private:
    int width_;
    int height_;
    int x_;
    int y_;
    int last_x_;
    int last_y_;
    Console console;
  };
}
