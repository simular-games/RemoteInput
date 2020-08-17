/* Copyright (c) 2020 Simular Games, LLC.
 * -------------------------------------------------------------------------------------------------
 *
 * MIT License
 * -------------------------------------------------------------------------------------------------
 * Permission is hereby granted, free of charge, to any person obtaining a copy of this software and
 * associated documentation files (the "Software"), to deal in the Software without restriction,
 * including without limitation the rights to use, copy, modify, merge, publish, distribute,
 * sublicense, and/or sell copies of the Software, and to permit persons to whom the Software is
 * furnished to do so, subject to the following conditions:
 *
 * The above copyright notice and this permission notice shall be included in all copies or
 * substantial portions of the Software.
 * -------------------------------------------------------------------------------------------------
 *
 * THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR IMPLIED, INCLUDING BUT
 * NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY, FITNESS FOR A PARTICULAR PURPOSE AND
 * NONINFRINGEMENT. IN NO EVENT SHALL THE AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM,
 * DAMAGES OR OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
 * OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE SOFTWARE.
 */
/**
 * \file
 * \brief
 * \details
 */
#pragma once
#include <cstdint>

namespace simular::reminput {
  /**
   * \brief   Represents a keyboard key.
   * \details
   */
  enum class InputKey {
    Undefined,
    A, B, C, D, E, F, G, H, I, J, K, L, M, N, O, P, Q, R, S, T, U, V, W, X, Y, Z,
    NumBar0, NumBar1, NumBar2, NumBar3, NumBar4, NumBar5, NumBar6, NumBar7, NumBar8, NumBar9,
    NumPad0, NumPad1, NumPad2, NumPad3, NumPad4, NumPad5, NumPad6, NumPad7, NumPad8, NumPad9,
    NumLock, NumPadSlash, NumPadMul, NumPadAdd, NumPadSub, NumPadDot, NumPadEnter,
    LeftShift, LeftControl, LeftAlt, LeftSuper, RightShift, RightControl, RightAlt, RightSuper, ArrowUp, ArrowRight, ArrowDown, ArrowLeft,
    Enter, Backspace, Insert, Home, PageUp, PageDown, Delete, End, PrintScreen, ScrollLock, Pause, CapsLock, Tab, Escape, Space,
    Grave, Minus, Equal, LBracket, RBracket, Backslash, Semicolon, Apostrophe, Comma, Period, ForwardSlash,
    F1, F2, F3, F4, F5, F6, F7, F8, F9, F10, F11, F12, F13, F14, F15, F16, F17, F18, F19, F20, F21, F22, F23, F24,
  };

  /**
   * \brief   Represents the state of a given input.
   * \return
   */
  enum class InputState {
    Press,
    Release
  };

  /**
   * \brief   Represents a mouse button.
   * \return
   */
  enum class MouseButton {
    Undefined,
    Button0,
    Button1,
    Button2,
    Button3,
    Button4,
    LeftButton = Button0,
    RightButton = Button1,
    MiddleButton = Button2,
  };

  /**
   * \brief   Represents a platform agnostic handle to windows, or even other objects.
   * \details This should never contain anything inside of this.
   */
  struct tagHandleID {};

  /**
   * \brief   A typedef of the tag object pointer for casting and aliasing operations.
   * \details Since each platform type has a different type of data that it stores for it's handles
   *          to windows, we must alias it and then cast back before operations.
   */
  using HandleID = tagHandleID*;

  /**
   * \brief   Represents keyboard key event data to be sent to the injectee.
   * \details This contains the key and the state of the key.
   */
  struct KeyEventData final {
    /**
     * \brief   The key whose state changed.
     * \details The state of the key should be placed in `state` property of this object.
     */
    InputKey key;

    /**
     * \brief   The state of the button.
     * \details To tell the injectee whether or not the key was pressed and released.
     */
    InputState state;
  };

  /**
   * \brief     Injects a key event into the event stream of the given injectee.
   * \details   On most systems, the native platform window object processes events that are sent to
   *            it. Applications can send events themselves to trigger things within the application.
   * \param[in] injectee The object that will receive the key event injection.
   * \param[in] data The data for the key event.
   * \throws    std::runtime_error If the injectee is not a valid window object on a given platform.
   */
  void injectKeyboardEvent(HandleID injectee, const KeyEventData& data);

  /**
   * \brief   Represents mouse event data to be sent to the injectee.
   * \details This contains the scroll delta, the move delta, the button, and the state of the
   *          button.
   */
  struct MouseEventData final {
    /**
     * \brief   The absolute location of the mouse on the x-axis.
     * \details This value is the absolute location of the cursor x-position on the desktop virtual
     *          space. **This should be in screen space**.
     */
    int32_t xpos;

    /**
     * \brief   The absolute location of the mouse on the y-axis.
     * \details This value is the absolute location of the cursor y-position on the desktop virtual
     *          space. **This should be in screen space**.
     */
    int32_t ypos;

    /**
     * \brief   The amount of times the scroll wheel moved on the y-axis.
     * \details This value will be multiplied by the wheel delta for the platform to provide the
     *          final scroll delta on this axis. Positive values means the wheel was scrolled
     *          forward, away from the user; while negative values means the wheel was scrolled
     *          backward, toward the user.
     */
    int8_t scrolldy;

    /**
     * \brief   A button whose state should be changed.
     * \details The state of the button should be set in the `state` property of this struct.
     */
    MouseButton button;

    /**
     * \brief   The state of the button.
     * \details To tell the injectee whether or not the button was pressed or released.
     */
    InputState state;
  };

  /**
   * \brief     Injects a mouse event into the event stream of the given injectee.
   * \details   On most systems, the native platform window object processes events that are sent to
   *            it. Applications can send events themselves to trigger things within the application.
   * \param[in] injectee The object that will receive the mouse event injection.
   * \param[in] data The mouse event data to send to the injectee event stream.
   * \throws    std::runtime_error If the injectee is not a valid window object on a given platform.
   */
  void injectMouseEvent(HandleID injectee, const MouseEventData& data);
}
