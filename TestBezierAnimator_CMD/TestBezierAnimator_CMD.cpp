#include "pch.h"
#include <iostream>
#include "animator.h"
#include "console.h"
#include "rectangle.h"

int main()
{
  std::getc(stdin);

  std::thread thread(
    []()
    {

      draw::Rectangle r(10, 2);
      int fps = 70;
      int64_t interval = 1000 / fps;
      Animator animator(0, 150, 1,
                        [&](int v)
                        {
                          r.SetPos(40 + v, 10);
                          r.Draw();
                        }
      , EasingCurve::Type::InOutBounceBezier);
      auto last_time = std::chrono::steady_clock::now();
      bool forward = true;
      while (true) {
        while (!animator.Step(1.0 / fps, forward)) {
          auto now = std::chrono::steady_clock::now();
          auto delay = (interval - std::chrono::duration_cast<std::chrono::milliseconds>((now - last_time)).count());
          std::this_thread::sleep_for(std::chrono::milliseconds(delay > 0 ? delay : 1)); // 最低1ms免得卡
          last_time = std::chrono::steady_clock::now();
        }
        forward = !forward;
      }

    }
  );

  thread.join();
  std::cout << std::endl;
}
