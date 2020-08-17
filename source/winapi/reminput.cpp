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
#include <array>
#include <stdexcept>
#include <reminput/reminput.hpp>
#include "../config.hpp"
#if defined(SIMULAR_WINDOWS_PLATFORM)
#define UNICODE 1
#define _UNICODE 1
#define WIN32_LEAN_AND_MEAN 1
#define VC_EXTRALEAN 1
#include <windows.h>

namespace simular::reminput {
  // Maps windows VK keys to our Input keys.
  constexpr std::array<WORD, 116> kInputKeyMap {
    0, // Key undefined.
    0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47, 0x48, 0x49, 0x4A, 0x4B, 0x4C, 0x4D, 0x4E, 0x4F, 0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57, 0x58, 0x59, 0x5A,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37, 0x38, 0x39,
    VK_NUMPAD0, VK_NUMPAD1, VK_NUMPAD2, VK_NUMPAD3, VK_NUMPAD4, VK_NUMPAD5, VK_NUMPAD6, VK_NUMPAD7, VK_NUMPAD8, VK_NUMPAD9,
    VK_NUMLOCK, VK_DIVIDE, VK_MULTIPLY, VK_ADD, VK_SUBTRACT, VK_DECIMAL, VK_RETURN,
    VK_LSHIFT, VK_LCONTROL, VK_LMENU, VK_LWIN, VK_RSHIFT, VK_RCONTROL, VK_RMENU, VK_RWIN, VK_UP, VK_RIGHT, VK_DOWN, VK_LEFT,
    VK_RETURN, VK_BACK, VK_INSERT, VK_HOME, VK_NEXT, VK_PRIOR, VK_DELETE, VK_END, VK_SNAPSHOT, VK_SCROLL, VK_PAUSE, VK_CAPITAL, VK_TAB, VK_ESCAPE, VK_SPACE,
    VK_OEM_3, VK_OEM_MINUS, VK_OEM_PLUS, VK_OEM_4, VK_OEM_6, VK_OEM_5, VK_OEM_1, VK_OEM_7, VK_OEM_COMMA, VK_OEM_PERIOD, VK_OEM_2,
    VK_F1, VK_F2, VK_F3, VK_F4, VK_F5, VK_F6, VK_F7, VK_F8, VK_F9, VK_F10, VK_F11, VK_F12, VK_F13, VK_F14, VK_F15, VK_F16, VK_F17, VK_F18, VK_F19, VK_F20, VK_F21, VK_F22, VK_F23, VK_F24,
  };

  void injectKeyboardEvent(HandleID injectee, const KeyEventData& data) {
    // Convert to HWND.
    auto* hwndInjectee = reinterpret_cast<HWND>(injectee);

    // Check that HWND exists.
    if (!IsWindow(hwndInjectee))
      throw std::runtime_error("Injectee is not a valid HWND.");

    // Create necessary information to send.
    KEYBDINPUT keyboardInput{};
               keyboardInput.wVk         = kInputKeyMap[static_cast<std::size_t>(data.key)];
               keyboardInput.wScan       = 0;
               keyboardInput.dwFlags     = data.state == InputState::Release ? KEYEVENTF_KEYUP : 0;
               keyboardInput.time        = 0;
               keyboardInput.dwExtraInfo = 0;

    // Create input data.
    INPUT inputData{};
          inputData.type = INPUT_KEYBOARD;
          inputData.ki   = keyboardInput;

    // Send input data.
    SendInput(1, &inputData, sizeof(INPUT));
  }

  // Store these and use them later.
  static int ldx = 0;
  static int ldy = 0;

  // For the mouse input packs.
  std::array<INPUT, 2> mouseInputPacks;

  void injectMouseEvent(HandleID injectee, const MouseEventData& data) {
    // Convert to HWND.
    auto* hwndInjectee = reinterpret_cast<HWND>(injectee);

    // Check that HWND exists.
    if (!IsWindow(hwndInjectee))
      throw std::runtime_error("Injectee is not a valid HWND.");

    // Create necessary information to send.
    MOUSEINPUT mouseInputA{};
               mouseInputA.dx        = data.xpos;
               mouseInputA.dy        = data.ypos;
               mouseInputA.mouseData = data.scrolldy * WHEEL_DELTA;
               mouseInputA.dwFlags   = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK;
               mouseInputA.time      = 0;
    MOUSEINPUT mouseInputB{};
               mouseInputB.dx        = data.xpos;
               mouseInputB.dy        = data.ypos;
               mouseInputB.mouseData = data.button == MouseButton::Button3 ? XBUTTON1 :
                                       data.button == MouseButton::Button4 ? XBUTTON2 : 0;
               mouseInputB.dwFlags   = MOUSEEVENTF_ABSOLUTE | MOUSEEVENTF_VIRTUALDESK;
               mouseInputB.time      = 0;

    // Check if wheel was scrolled.
    if (data.scrolldy)
      mouseInputA.dwFlags |= MOUSEEVENTF_WHEEL;

    // Check if mouse moved.
    if (ldx != data.xpos || ldy != data.ypos)
      mouseInputA.dwFlags |= MOUSEEVENTF_MOVE;

    // Check for button clicks.
    switch (data.button) {
    case MouseButton::LeftButton:
      mouseInputA.dwFlags |= data.state == InputState::Press ? MOUSEEVENTF_LEFTDOWN : MOUSEEVENTF_LEFTUP;
      break;
    case MouseButton::MiddleButton:
      mouseInputA.dwFlags |= data.state == InputState::Press ? MOUSEEVENTF_MIDDLEDOWN : MOUSEEVENTF_MIDDLEUP;
      break;
    case MouseButton::RightButton:
      mouseInputA.dwFlags |= data.state == InputState::Press ? MOUSEEVENTF_RIGHTDOWN : MOUSEEVENTF_RIGHTUP;
      break;
    case MouseButton::Button3:
    case MouseButton::Button4:
      mouseInputB.dwFlags |= data.state == InputState::Press ? MOUSEEVENTF_XDOWN : MOUSEEVENTF_XUP;
      break;
    default:
      break;
    }

    // Set these.
    ldx = data.xpos;
    ldy = data.ypos;

    // Create inputs.
    INPUT inputA{};
          inputA.type = INPUT_MOUSE;
          inputA.mi   = mouseInputA;
    INPUT inputB{};
          inputB.type = INPUT_MOUSE;
          inputB.mi   = mouseInputB;

    // Fill inputs.
    auto count = 1u;
    mouseInputPacks[0] = inputA;
    if (data.button == MouseButton::Button3 || data.button == MouseButton::Button4) {
      count = 2;
      mouseInputPacks[1] = inputB;
    }

    // Send inputs.
    SendInput(count, mouseInputPacks.data(), sizeof(INPUT));
  }

}

#endif