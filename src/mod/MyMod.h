#pragma once

#include <optional>

#include "mod/Config.h"
#include <pl/Mod.hpp>

namespace custom_tabs {

class CustomTabsMod {
  public:
    static CustomTabsMod &instance();

    CustomTabsMod();

    [[nodiscard]] ll::mod::NativeMod &getSelf() const { return mSelf; }

    bool load();
    bool enable();
    bool disable();
    bool unload();

  private:
    ll::mod::NativeMod &mSelf;
    ModConfig mConfig;
    std::optional<pl::config::ConfigFile<ModConfig>> mConfigFile;

    void probeMinecraft();
};

} // namespace custom_tabs
