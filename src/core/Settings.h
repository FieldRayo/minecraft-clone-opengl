#pragma once

#include <string>

struct RuntimeSettings {
    int windowWidth = 1080;
    int windowHeight = 720;
    bool fullscreen = false;
    std::string windowTitle = "Minecraft Clone";
};

class Settings {
public:
    static RuntimeSettings& Get() {
        static RuntimeSettings instance;
        return instance;
    }
};
