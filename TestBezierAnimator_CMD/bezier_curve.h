#pragma once

struct BezierEase
{
  BezierEase(double x1, double y1, double x2, double y2)
  {
    init(x1, y1, x2, y2);
    for (int i = 0; i < size; ++i) {
      sample_[i] = PointF(calcX(i * 1.0 / size), calcY(i * 1.0 / size));
    }
  }

  double value(double t)
  {
    return GetYAtX(t);
  }

  double GetYAtX(double x)
  {
    int head = 0;
    int tail = size - 1;
    int center;
    while (head <= tail) {
      center = (head + tail) / 2;
      if (sample_[center].x < x) {
        head = center + 1;
      } else if (sample_[center].x > x) {
        tail = center - 1;
      } else {
        break;
      }
    }

    if (head < size - 1) {
      double x0 = sample_[head].x;
      double x1 = sample_[head + 1].x;
      double y0 = sample_[head].y;
      double y1 = sample_[head + 1].y;
      return (x - x0) / (x1 - x0) * (y1 - y0) + y0; // 线性插值计算
    } else {
      return 1;
    }
  }
private:
  struct PointF
  {
    PointF() : x(0), y(0) {}
    PointF(double x, double y) : x(x), y(y) {}
    double x;
    double y;
  };

  double calcX(double t)
  {
    return ((pa.x * t + pb.x) * t + pc.x) * t;
  }

  double calcY(double t)
  {
    return ((pa.y * t + pb.y) * t + pc.y) * t;
  }

  void init(double x1, double y1, double x2, double y2)
  {
    pc.x = 3.0 * x1;
    pb.x = 3.0 * (x2 - x1) - pc.x;
    pa.x = 1.0 - pc.x - pb.x;

    pc.y = 3.0 * y1;
    pb.y = 3.0 * (y2 - y1) - pc.y;
    pa.y = 1.0 - pc.y - pb.y;
  }
  PointF pa;
  PointF pb;
  PointF pc;
  const static int size = 1001;
  PointF sample_[size];
};