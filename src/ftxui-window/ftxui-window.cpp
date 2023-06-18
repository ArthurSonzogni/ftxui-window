#include <ftxui-window/ftxui-window.hpp>
#include <ftxui/component/component_base.hpp>
#include <cassert>

namespace ftxuiwindow {

using namespace ftxui;

Component Window(WindowOptions option) {
  class Impl : public ComponentBase, WindowOptions {
   public:
    Impl(WindowOptions option) : WindowOptions(std::move(option)) {
      Add(inner);
    }

   private:
    Element Render() final {
      auto element = window(text(" " + title() + " "), inner->Render())  //
                     | size(WIDTH, EQUAL, width())           //
                     | size(HEIGHT, EQUAL, height())         //
                     | clear_under                           //
                     | reflect(box_);                        //

      auto padding_left = emptyElement() | size(WIDTH, EQUAL, left());
      auto padding_top = emptyElement() | size(HEIGHT, EQUAL, top());

      return vbox({
          padding_top,
          hbox({
              padding_left,
              element,
          }),
      });
    }

    bool OnEvent(Event event) final {
      bool handled = inner->OnEvent(event);

      if (!event.is_mouse()) {
        return handled;
      }

      if (captured_mouse_) {
        if (event.mouse().motion == Mouse::Released) {
          captured_mouse_ = nullptr;
          return true;
        }

        if (resize_right) {
          width() = event.mouse().x - resize_start_x;
        }

        if (resize_down) {
          height() = event.mouse().y - resize_start_y;
        }

        if (drag) {
          left() = event.mouse().x - drag_start_x;
          top() = event.mouse().y - drag_start_y;
        }
        return true;
      }

      mouse_hover_ =
          box_.Contain(event.mouse().x, event.mouse().y) && CaptureMouse(event);

      if (!mouse_hover_) {
        return handled;
      }

      if (event.mouse().button == Mouse::Left &&
          event.mouse().motion == Mouse::Pressed) {
        TakeFocus();

        captured_mouse_ = CaptureMouse(event);
        if (!captured_mouse_) {
          return true;
        }

        resize_right = event.mouse().x == left() + width() - 1;
        resize_down = event.mouse().y == top() + height() - 1;
        resize_start_x = event.mouse().x - width();
        resize_start_y = event.mouse().y - height();
        drag_start_x = event.mouse().x - left();
        drag_start_y = event.mouse().y - top();
        drag = !resize_right && !resize_down;
        return true;
      }

      return handled;
    }

    Box box_;
    bool mouse_hover_ = false;

    CapturedMouse captured_mouse_;
    int drag_start_x = 0;
    int drag_start_y = 0;
    int resize_start_x = 0;
    int resize_start_y = 0;

    bool drag = false;
    bool resize_down = false;
    bool resize_right = false;
  };
  return Make<Impl>(std::move(option));
}

Component WindowContainer(Components children) {
  class Impl : public ComponentBase {
   public:
    Impl(Components children) {
      for (Component& child : children) {
        Add(std::move(child));
      }
    }

   private:
    Element Render() final {
      Elements elements;
      for (auto& child : children_) {
        elements.push_back(child->Render());
      }
      // Reverse the order of the elements.
      std::reverse(elements.begin(), elements.end());
      return dbox(std::move(elements));
    }

    bool Focusable() const final {
      if (children_.size() == 0)
        return false;
      return children_[0]->Focusable();
    }

    Component ActiveChild() final {
      if (children_.size() == 0)
        return nullptr;
      return children_[0];
    }

    void SetActiveChild(ComponentBase* child) final {
      if (children_.size() == 0) {
        return;
      }

      int previous_index = 0;
      for (int i = 0; i < children_.size(); ++i) {
        if (children_[i].get() == child) {
          previous_index = i;
          break;
        }
      }

      // Rotate to make the `previous_index` become the first element.
      std::rotate(children_.begin(), children_.begin() + previous_index,
                  children_.end());

      assert(ActiveChild().get() == child);
    }

    bool OnEvent(Event event) final {
      for (auto& child : children_) {
        if (child->OnEvent(event)) {
          return true;
        }
      }
      return false;
    }

    int selected_tab_ = 0;
    Component tab_ = Container::Tab(children_, &selected_tab_);
  };
  return Make<Impl>(std::move(children));
}

};  // namespace ftxuiwindow
