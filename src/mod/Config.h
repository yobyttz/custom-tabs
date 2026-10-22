#pragma once

#include <string>
#include <string_view>

#include <pl/Config.hpp>

namespace tabs {

struct ModConfig {
    int version = 1;
    bool enabled = true;
    std::string message = "Hello from tabs";
};

nlohmann::json makeDefaultConfigJson();
nlohmann::json makeConfigSchemaJson();

} // namespace clange_me

template <> struct pl::config::Schema<clange_me::ModConfig> {
    static constexpr std::string_view title = "tabs Config";
    static constexpr std::string_view description = {};

    static constexpr FieldSchema field(std::string_view name) {
        if (name == "version")
            return {.title = "Version", .readOnly = true};
        if (name == "enabled")
            return {.title = "Enabled", .description = "Turns tabs behavior on or off."};
        if (name == "message")
            return {.title = "Message", .description = "Message written when the mod is enabled."};
        return {};
    }
};
