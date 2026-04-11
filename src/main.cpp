#include <iostream>

#include <glad/glad.h>

#include "core/Settings.h"
#include "core/Application.h"

auto& settings = Settings::Get();

int main() {
    Application app;
    app.Run();
    return 0;
}
