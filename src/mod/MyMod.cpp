#include "mod/MyMod.h"

#include <dlfcn.h>
#include <filesystem>

#include <pl/Mod.hpp>

namespace custom_tabs {

CustomTabsMod &CustomTabsMod::instance() {
    static CustomTabsMod instance;
    return instance;
}

CustomTabsMod::CustomTabsMod() : mSelf(*ll::mod::NativeMod::current()) {}

void CustomTabsMod::probeMinecraft() {
    auto &log = getSelf().getLogger();

    // Offsets de strings en libminecraftpe.so 1.26.52.3 (solo referencia; NO son hooks)
    // construction_tab  0x2758437
    // equipment_tab     0x2527807
    // nature_tab        0x2527815
    // items_tab         0x25bdc36
    // search_tab        0x2492a88
    // CreativeItemGroupCategory  0x33349e7

    void *mc = dlopen("libminecraftpe.so", RTLD_NOLOAD | RTLD_LAZY);
    if (mc) {
        log.info("libminecraftpe.so ya está cargada");
        // TODO: cuando tengas signature de fill creativo:
        // auto addr = pl::memory::resolveSignature("XX XX ?? ...", "libminecraftpe.so");
        // pl::memory::hook(...);
    } else {
        log.warn("libminecraftpe.so aún no cargada (normal en load/enable temprano)");
    }
}

bool CustomTabsMod::load() {
    auto &self = getSelf();
    self.getLogger().info("CustomTabs: load()");

    std::error_code ec;
    std::filesystem::create_directories(self.getDataDir(), ec);
    std::filesystem::create_directories(self.getConfigDir(), ec);

    mConfigFile.emplace();
    if (!mConfigFile->load()) {
        self.getLogger().warn("No se pudo cargar config");
        return false;
    }
    mConfig = mConfigFile->value();
    return true;
}

bool CustomTabsMod::enable() {
    auto &self = getSelf();
    self.getLogger().info("CustomTabs: enable()");
    probeMinecraft();
    // Las tabs visuales van en resource pack / JSON UI.
    // Aquí irá el hook de ítems cuando haya signature.
    return true;
}

bool CustomTabsMod::disable() {
    getSelf().getLogger().info("CustomTabs: disable()");
    return true;
}

bool CustomTabsMod::unload() {
    getSelf().getLogger().info("CustomTabs: unload()");
    mConfigFile.reset();
    return true;
}

} // namespace custom_tabs
