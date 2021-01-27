#pragma once

#include "bezier_curve.h"

class EasingCurve
{
public:
  enum Type
  {
    InOutBezier, InOutBounceBezier
  };

  EasingCurve(Type t)
  {
    switch (t) {
      case InOutBounceBezier:
        curve_.reset(new BezierEase(.56, -0.48, .46, 1.5));
        break;
      case InOutBezier:
        curve_.reset(new BezierEase(.63, 0, .37, 1));
      default:
        break;
    }
  }

  // [0 - 1]
  double valueForProgress(double t)
  {
    t = max(0, min(t, 1));
    return curve_->value(t);
  }
private:
  std::unique_ptr<BezierEase> curve_;
};

template<typename T = int>
class Animator_
{
public:
  Animator_(T from, T to, double duration/*单位秒*/, std::function<void(T)> fn = nullptr, EasingCurve::Type type = EasingCurve::InOutBezier)
    : ec_(type), from_(from), to_(to), duration_(duration), fn_(fn)
  {
  }
  Animator_() : ec_(EasingCurve::InOutBezier) {}
  bool Step(double interval/*单位秒*/, bool forward = true)
  {
    assert(interval > 0);
    double time_now = current_time_ + (forward ? interval : (-interval));
    bool isFinished = forward ? time_now >= duration_ : time_now <= 0;
    time_now = forward ? min(time_now, duration_) : max(time_now, 0);
    T val = duration_ == 0 ? (forward ? to_ : from_) : from_ + T((to_ - from_) *ec_.valueForProgress(time_now / duration_));
    current_time_ = time_now;
    if (fn_) fn_(val);
    return isFinished;
  }
public:
  void SetRange(T from_val, T to_value) { from_ = from_val; to_ = to_value; }
  void SetDuration(double val) { duration_ = val; }
  void SetFn(std::function<void(T)> val) { fn_ = val; }
  void ResetCurrentTime() { current_time_ = 0; }
  void SetCurrentTime(double current_time) { current_time_ = current_time; }
  void Complete(bool state_forward) { SetCurrentTime(state_forward ? duration_ : 0); }
private:
  T from_ = {};
  T to_ = {};
  double duration_ = 0;
  double current_time_ = 0;	//当前时间
  std::function<void(T)> fn_ = nullptr;
  EasingCurve ec_;
};

using Animator = Animator_<>;
