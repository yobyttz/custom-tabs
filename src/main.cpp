#include "mod/MyMod.h"
#include <pl/Mod.hpp>

// Si el template usa clange_me::ClangeMeMod, cámbialo a:
PL_REGISTER_MOD(custom_tabs::CustomTabsMod, custom_tabs::CustomTabsMod::instance())
