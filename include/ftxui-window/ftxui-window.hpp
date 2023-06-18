#pragma once
#ifndef FTXUI_WINDOW_FTXUI_WINDOW_HPP
#define FTXUI_WINDOW_FTXUI_WINDOW_HPP

#include <ftxui/component/component.hpp>
#include <ftxui/util/ref.hpp>

namespace ftxuiwindow {

using namespace ftxui;

struct WindowOptions {
  Component inner;
  ConstStringRef title;

  Ref<int> left = 0;
  Ref<int> top = 0;
  Ref<int> width = 20;
  Ref<int> height = 10;
};

Component Window(WindowOptions option);
Component WindowContainer(Components children);

};  // namespace ftxuiwindow

#endif  // FTXUI_WINDOW_FTXUI_WINDOW_HPP
