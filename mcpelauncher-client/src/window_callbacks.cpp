#include "window_callbacks.h"
#include "imgui.h"
#include "log.h"
#include "minecraft/std/string_linux.h"
#include "minecraft_gamepad_mapping.h"

#include "JNIBinding.h"
#include <game_window_manager.h>
#include <hybris/dlfcn.h>
#include <iostream>
#include <jni.h>
#include <mcpelauncher/minecraft_version.h>
#include <minecraft/GameControllerManager.h>
#include <minecraft/Keyboard.h>
#include <minecraft/Mouse.h>
#include <minecraft/Multitouch.h>
#include <minecraft/Options.h>
#include <minecraft/legacy/App.h>
#include <minecraft/legacy/Keyboard.h>
#include <minecraft/legacy/MinecraftGame.h>
#include <string>
#include <thread>

void WindowCallbacks::registerCallbacks() {
  using namespace std::placeholders;
  window.setWindowSizeCallback(
      std::bind(&WindowCallbacks::onWindowSizeCallback, this, _1, _2));
  window.setCloseCallback(std::bind(&WindowCallbacks::onClose, this));

  window.setMouseButtonCallback(
      std::bind(&WindowCallbacks::onMouseButton, this, _1, _2, _3, _4));
  window.setMousePositionCallback(
      std::bind(&WindowCallbacks::onMousePosition, this, _1, _2));
  window.setMouseRelativePositionCallback(
      std::bind(&WindowCallbacks::onMouseRelativePosition, this, _1, _2));
  window.setMouseScrollCallback(
      std::bind(&WindowCallbacks::onMouseScroll, this, _1, _2, _3, _4));
  window.setTouchStartCallback(
      std::bind(&WindowCallbacks::onTouchStart, this, _1, _2, _3));
  window.setTouchUpdateCallback(
      std::bind(&WindowCallbacks::onTouchUpdate, this, _1, _2, _3));
  window.setTouchEndCallback(
      std::bind(&WindowCallbacks::onTouchEnd, this, _1, _2, _3));
  window.setKeyboardCallback(
      std::bind(&WindowCallbacks::onKeyboard, this, _1, _2));
  window.setKeyboardTextCallback(
      std::bind(&WindowCallbacks::onKeyboardText, this, _1));
  window.setPasteCallback(std::bind(&WindowCallbacks::onPaste, this, _1));
  window.setGamepadStateCallback(
      std::bind(&WindowCallbacks::onGamepadState, this, _1, _2));
  window.setGamepadButtonCallback(
      std::bind(&WindowCallbacks::onGamepadButton, this, _1, _2, _3));
  window.setGamepadAxisCallback(
      std::bind(&WindowCallbacks::onGamepadAxis, this, _1, _2, _3));
  window.setFocusChangeCallback(
      std::bind(&WindowCallbacks::onFocusChange, this, _1));

  window.setOnGUIFrame(std::bind(&WindowCallbacks::onGUIFrame, this));
}

class Color {
public:
  static const Color BLACK;
  static const Color BLUE;
  static const Color CYAN;
  static const Color GREEN;
  static const Color GREY;
  static const Color NIL;
  static const Color PURPLE;
  static const Color RED;
  static const Color WHITE;
  static const Color YELLOW;
  static const Color SHADE_DOWN;
  static const Color SHADE_NORTH_SOUTH;
  static const Color SHADE_UP;
  static const Color SHADE_WEST_EAST;

  float r, g, b, a; // 0, 4, 8, 12

  Color(float r, float g, float b, float a) : r(r), g(g), b(b), a(a){};

  static Color *fromHSB(float, float, float);
};
void WindowCallbacks::onWindowSizeCallback(int w, int h) {
  auto nativeSetRenderingSize = (void (*)(void *, int, int))hybris_dlsym(
      handle, "_ZN15MinecraftClient16setRenderingSizeEii");

  auto nativeSetUI = (void (*)(void *, int, int, float))hybris_dlsym(
      handle, "_ZN15MinecraftClient17setUISizeAndScaleEiif");

  void *mc = *this->MinecraftClient;
  Log::info("Launcher", "Resizing... App is: 0x%x To: %dx%d", mc, w, h);
  nativeSetRenderingSize(mc, w, h);
  nativeSetUI(mc, w, h, 0.0f);
}

void WindowCallbacks::onClose() {
  std::thread([&]() {
    activity.callbacks->onPause(&activity);
    activity.callbacks->onStop(&activity);
    activity.callbacks->onNativeWindowDestroyed(&activity,
                                                (ANativeWindow *)&window);
    activity.callbacks->onInputQueueDestroyed(&activity, (AInputQueue *)2);
    activity.callbacks->onDestroy(&activity);
  }).detach();
}

void WindowCallbacks::onMouseButton(double x, double y, int btn,
                                    MouseButtonAction action) {
  if (btn < 1 || btn > 3)
    return;
  Mouse::feed((char)btn, (char)(action == MouseButtonAction::PRESS ? 1 : 0),
              (short)x, (short)y, 0, 0);
}
void WindowCallbacks::onMousePosition(double x, double y) {
  Mouse::feed(0, 0, (short)x, (short)y, 0, 0);
}
void WindowCallbacks::onMouseRelativePosition(double x, double y) {
  Mouse::feed(0, 0, 0, 0, (short)x, (short)y);
}
void WindowCallbacks::onMouseScroll(double x, double y, double dx, double dy) {
  char cdy = (char)std::max(std::min(dy * 127.0, 127.0), -127.0);
  Mouse::feed(4, cdy, 0, 0, (short)x, (short)y);
}
void WindowCallbacks::onTouchStart(int id, double x, double y) {
  Multitouch::feed(1, 1, (short)x, (short)y, id);
}
void WindowCallbacks::onTouchUpdate(int id, double x, double y) {
  Multitouch::feed(0, 0, (short)x, (short)y, id);
}
void WindowCallbacks::onTouchEnd(int id, double x, double y) {
  Multitouch::feed(1, 0, (short)x, (short)y, id);
}

void WindowCallbacks::onKeyboard(int key, KeyAction action) {
#ifdef __APPLE__
  if (key == 1) /* cmd */
#else
  if (key == 17)
#endif
    modCTRL = (action != KeyAction::RELEASE);
  if (key == 16)
    ((jnivm::com::mojang::minecraftpe::MainActivity *)activity.clazz)
        ->onKeyboardShiftKey(action != KeyAction::RELEASE);
  if (modCTRL && key == 'C') {
    ((jnivm::com::mojang::minecraftpe::MainActivity *)activity.clazz)
        ->copyCurrentText();
    return;
  }
  if (action == KeyAction::PRESS || action == KeyAction::REPEAT) {
    if (key == 37)
      ((jnivm::com::mojang::minecraftpe::MainActivity *)activity.clazz)
          ->onKeyboardDirectionKey(jnivm::com::mojang::minecraftpe::
                                       MainActivity::DirectionKey::LeftKey);
    else if (key == 39)
      ((jnivm::com::mojang::minecraftpe::MainActivity *)activity.clazz)
          ->onKeyboardDirectionKey(jnivm::com::mojang::minecraftpe::
                                       MainActivity::DirectionKey::RightKey);
    else if (key == 36)
      ((jnivm::com::mojang::minecraftpe::MainActivity *)activity.clazz)
          ->onKeyboardDirectionKey(jnivm::com::mojang::minecraftpe::
                                       MainActivity::DirectionKey::HomeKey);
    else if (key == 35)
      ((jnivm::com::mojang::minecraftpe::MainActivity *)activity.clazz)
          ->onKeyboardDirectionKey(jnivm::com::mojang::minecraftpe::
                                       MainActivity::DirectionKey::EndKey);
  }
  if (key == 112 + 10 && action == KeyAction::PRESS)
    window.setFullscreen(fullscreen = !fullscreen);
  if ((action == KeyAction::PRESS || action == KeyAction::RELEASE) &&
      key < 256) {
    Keyboard::InputEvent evData;
    evData.key = (unsigned int)key;
    evData.event = (action == KeyAction::PRESS ? 1 : 0);
    if (MinecraftVersion::isAtLeast(1, 2)) {
      evData.controllerId = *Keyboard::_gameControllerId;
      Keyboard::_inputs->push_back(evData);
    } else {
      Legacy::Pre_1_2::Keyboard::_inputs->push_back(evData);
    }
    Keyboard::_states[key] = evData.event;
  }
}
void WindowCallbacks::onKeyboardText(std::string const &c) {
  if ((!((jnivm::com::mojang::minecraftpe::MainActivity *)activity.clazz)
            ->isKeyboardMultiline() &&
       (c.size() == 1 && c[0] == '\n')) ||
      !((jnivm::com::mojang::minecraftpe::MainActivity *)activity.clazz)
           ->isKeyboardVisible()) {
    if (MinecraftVersion::isAtLeast(0, 17))
      Keyboard::feedText(c, false, 0);
    else
      Legacy::Pre_0_17::Keyboard::feedText(c, false);
  } else {
    ((jnivm::com::mojang::minecraftpe::MainActivity *)activity.clazz)
        ->onKeyboardText(vm->GetJNIEnv(), c);
  }
}
void WindowCallbacks::onPaste(std::string const &str) {
  ((jnivm::com::mojang::minecraftpe::MainActivity *)activity.clazz)
      ->onKeyboardText(vm->GetJNIEnv(), str);
}
void WindowCallbacks::onGamepadState(int gamepad, bool connected) {
  Log::trace("WindowCallbacks", "Gamepad %s #%i",
             connected ? "connected" : "disconnected", gamepad);
  if (connected)
    gamepads.insert({gamepad, GamepadData()});
  else
    gamepads.erase(gamepad);
  if (GameControllerManager::sGamePadManager != nullptr)
    GameControllerManager::sGamePadManager->setGameControllerConnected(
        gamepad, connected);
}

void WindowCallbacks::onGamepadButton(int gamepad, GamepadButtonId btn,
                                      bool pressed) {
  int mid = MinecraftGamepadMapping::mapButton(btn);
  auto state = pressed ? GameControllerButtonState::PRESSED
                       : GameControllerButtonState::RELEASED;
  if (GameControllerManager::sGamePadManager != nullptr && mid != -1) {
    GameControllerManager::sGamePadManager->feedButton(gamepad, mid, state,
                                                       true);
    if (btn == GamepadButtonId::START && pressed)
      GameControllerManager::sGamePadManager->feedJoinGame(gamepad, true);
  }
}

void WindowCallbacks::onGamepadAxis(int gamepad, GamepadAxisId ax,
                                    float value) {
  auto gpi = gamepads.find(gamepad);
  if (gpi == gamepads.end())
    return;
  auto &gp = gpi->second;

  if (ax == GamepadAxisId::LEFT_X || ax == GamepadAxisId::LEFT_Y) {
    gp.stickLeft[ax == GamepadAxisId::LEFT_Y ? 1 : 0] = value;
    GameControllerManager::sGamePadManager->feedStick(
        gamepad, 0, (GameControllerStickState)3, gp.stickLeft[0],
        -gp.stickLeft[1]);
  } else if (ax == GamepadAxisId::RIGHT_X || ax == GamepadAxisId::RIGHT_Y) {
    gp.stickRight[ax == GamepadAxisId::RIGHT_Y ? 1 : 0] = value;
    GameControllerManager::sGamePadManager->feedStick(
        gamepad, 1, (GameControllerStickState)3, gp.stickRight[0],
        -gp.stickRight[1]);
  } else if (ax == GamepadAxisId::LEFT_TRIGGER) {
    GameControllerManager::sGamePadManager->feedTrigger(gamepad, 0, value);
  } else if (ax == GamepadAxisId::RIGHT_TRIGGER) {
    GameControllerManager::sGamePadManager->feedTrigger(gamepad, 1, value);
  }
}

void WindowCallbacks::onFocusChange(bool hasfocus) {
  activity.callbacks->onWindowFocusChanged(&activity, hasfocus);
}

void WindowCallbacks::loadGamepadMappings() {
  auto windowManager = GameWindowManager::getManager();
  std::vector<std::string> controllerDbPaths;
  PathHelper::findAllDataFiles("gamecontrollerdb.txt",
                               [&controllerDbPaths](std::string const &path) {
                                 controllerDbPaths.push_back(path);
                               });
  for (std::string const &path : controllerDbPaths) {
    Log::trace("Launcher", "Loading gamepad mappings: %s", path.c_str());
    windowManager->addGamepadMappingFile(path);
  }
}

WindowCallbacks::GamepadData::GamepadData() {
  stickLeft[0] = stickLeft[1] = 0.f;
  stickRight[0] = stickRight[1] = 0.f;
}

void WindowCallbacks::onGUIFrame() {

  auto mc = *this->MinecraftClient;

  auto whiteColor = hybris_dlsym(handle, "_ZN5Color5WHITEE");
  Log::trace("Launcher", "white is: 0x%x", whiteColor);

  Color *white = (Color *)whiteColor;

  Log::trace("Launcher", "white is: %f %f %f %f", white->r, white->g, white->b,
             white->a);

  auto text = new mcpe::string("Lachy IS THE BEST");
  auto getFont = (void *(*)(void *mc))hybris_dlsym(
      handle, "_ZNK15MinecraftClient7getFontEv");

  auto font = getFont(mc);

  auto render =
      (void (*)(void *Font, mcpe::string *text, float x, float y, Color *color,
                bool))hybris_dlsym(handle,
                                   "_ZN4Font10drawShadowERKSsffRK5Colorb");
  render(font, text, 10.0f, 20.0f, white, false);

  // tick
  auto tick = (void (*)(void))hybris_dlsym(handle, "_ZN6Screen4tickEv");
  tick();
}