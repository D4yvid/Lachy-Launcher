#pragma once

#include <string>
#include <fstream>
#include <sys/stat.h>
#include <mcpelauncher/path_helper.h>
#include <properties/property_list.h>

/**
 * Configuration manager for Lachy-Launcher
 * Stores settings in ~/.config/mcpelauncher/config.properties
 */
class LauncherConfig {
private:
  properties::property_list props;
  std::string configPath;
  
  // Settings with defaults
  int windowWidth = 720;
  int windowHeight = 480;
  float pixelScale = 2.0f;
  bool disableFmod = false;
  bool disableAssetCache = false;
  int logLevel = 1; // 0=quiet, 1=normal, 2=verbose
  std::string lastGameDir;
  
  static std::string getConfigDir() {
    const char* xdgConfig = getenv("XDG_CONFIG_HOME");
    if (xdgConfig && xdgConfig[0] != '\0') {
      return std::string(xdgConfig) + "/mcpelauncher/";
    }
    const char* home = getenv("HOME");
    if (home) {
      return std::string(home) + "/.config/mcpelauncher/";
    }
    return "./";
  }
  
  static void ensureDir(const std::string& path) {
    mkdir(path.c_str(), 0755);
  }

public:
  LauncherConfig() {
    configPath = getConfigDir() + "config.properties";
    
    // Register properties
    props.register_property("window.width",
      [this](const std::string& v) { windowWidth = std::stoi(v); },
      [this]() { return std::to_string(windowWidth); });
    
    props.register_property("window.height",
      [this](const std::string& v) { windowHeight = std::stoi(v); },
      [this]() { return std::to_string(windowHeight); });
    
    props.register_property("window.scale",
      [this](const std::string& v) { pixelScale = std::stof(v); },
      [this]() { return std::to_string(pixelScale); });
    
    props.register_property("audio.disable_fmod",
      [this](const std::string& v) { disableFmod = (v == "true" || v == "1"); },
      [this]() { return disableFmod ? "true" : "false"; });
    
    props.register_property("performance.disable_cache",
      [this](const std::string& v) { disableAssetCache = (v == "true" || v == "1"); },
      [this]() { return disableAssetCache ? "true" : "false"; });
    
    props.register_property("log.level",
      [this](const std::string& v) { logLevel = std::stoi(v); },
      [this]() { return std::to_string(logLevel); });
    
    props.register_property("game.last_dir",
      [this](const std::string& v) { lastGameDir = v; },
      [this]() { return lastGameDir; });
  }
  
  bool load() {
    std::ifstream file(configPath);
    if (!file.is_open()) return false;
    props.load(file);
    return true;
  }
  
  bool save() {
    ensureDir(getConfigDir());
    std::ofstream file(configPath);
    if (!file.is_open()) return false;
    file << "# Lachy-Launcher Configuration\n";
    file << "# Generated automatically - edit with care\n\n";
    props.save(file);
    return true;
  }
  
  // Getters
  int getWindowWidth() const { return windowWidth; }
  int getWindowHeight() const { return windowHeight; }
  float getPixelScale() const { return pixelScale; }
  bool isFmodDisabled() const { return disableFmod; }
  bool isAssetCacheDisabled() const { return disableAssetCache; }
  int getLogLevel() const { return logLevel; }
  const std::string& getLastGameDir() const { return lastGameDir; }
  const std::string& getConfigPath() const { return configPath; }
  
  // Setters
  void setWindowWidth(int w) { windowWidth = w; }
  void setWindowHeight(int h) { windowHeight = h; }
  void setPixelScale(float s) { pixelScale = s; }
  void setDisableFmod(bool v) { disableFmod = v; }
  void setDisableAssetCache(bool v) { disableAssetCache = v; }
  void setLogLevel(int level) { logLevel = level; }
  void setLastGameDir(const std::string& dir) { lastGameDir = dir; }
};
