#include <ftxui-window/ftxui-window.hpp>
#include <ftxui/component/component.hpp>
#include <ftxui/component/screen_interactive.hpp>

int main() {
  using namespace ftxui;
  using namespace ftxuiwindow;

  // Create the first window:
  bool checked_1_1 = 0;
  bool checked_1_2 = 0;
  bool checked_1_3 = 0;
  auto inner_1 = Container::Vertical({
      Checkbox("Check me", &checked_1_1),
      Checkbox("Check me", &checked_1_2),
      Checkbox("Check me", &checked_1_3),
  }) | center;
  auto window_1 = Window({
      .inner = inner_1,
      .title = "My window",
      .left = 10,
      .top = 5,
  });

  // Create the second window:
  bool checked_2_1 = 0;
  bool checked_2_2 = 0;
  float slider_2_3 = 50;
  auto inner_2 = Container::Vertical({
      Checkbox("Check me", &checked_2_1),
      Checkbox("Check me", &checked_2_2),
      Slider("Slider", &slider_2_3, 0.f, 100.f),
  });
  auto window_2 = Window({
      .inner = inner_2,
      .title = "My window",
      .left = 20,
      .top = 10,
  });

  auto container = WindowContainer({
      window_1,
      window_2,
  });

  auto screen = ScreenInteractive::Fullscreen();
  screen.Loop(container);

  return EXIT_SUCCESS;
}
