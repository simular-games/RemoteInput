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
#include <chrono>
#include <iostream>
#include <string>
#include <thread>
#include <reminput/reminput.hpp>
#define UNICODE 1
#define _UNICODE 1
#define WIN32_LEAN_AND_MEAN 1
#define VC_EXTRALEAN 1
#include <windows.h>

HWND         vscodeHWND = nullptr;
std::wstring windowTitle;
BOOL CALLBACK EnumWindowProc(HWND hwnd, LPARAM lParam) {
  // Get title size.
  int titleSize = GetWindowTextLengthW(hwnd) + 1;

  // Reserve space.
  windowTitle.clear();
  windowTitle.reserve(titleSize);

  // Grab title.
  wchar_t title[titleSize];
  GetWindowTextW(hwnd, title, titleSize);
  windowTitle.insert(windowTitle.begin(), title, title + titleSize);

  // Print the name for testing.
  auto index = windowTitle.find(L"Visual Studio Code");
  if (index != std::wstring::npos) {
    std::wcout << windowTitle << std::endl;
    vscodeHWND = hwnd;
    return FALSE;
  }

  return TRUE;
}

int main(void) {
  // enumerate windows and get handle.
  EnumWindows(&EnumWindowProc, 0);

  // Give keyboard focus to the application.
  BringWindowToTop(vscodeHWND);
  SetForegroundWindow(vscodeHWND);
  SetFocus(vscodeHWND);

  // For explicitness.
  using namespace simular::reminput;

  // Convert handle and send keyboard injection.
  auto id = reinterpret_cast<HandleID>(vscodeHWND);

  // Keyboard info.
  const KeyEventData keydata {
    .key   = InputKey::A,
    .state = InputState::Press,
  };

  // Inject 5 times.
  for (std::size_t count = 0; count < 5; count++) {
    injectKeyboardEvent(id, keydata);
    std::this_thread::sleep_for(std::chrono::milliseconds(100));
  }
}
