
#include "raylib.h"
#include "game/var.h"
#include "game/sound/sound.h"
#include "game/texture/texture.h"
void init() {
    // init windows
    InitWindow(windowX, windowY, "Ball's tiny world 2D");
    if (!IsWindowReady()) {
        TraceLog(LOG_ERROR, "FATAL: Could not open window");
    }
    // init sound:
    InitAudioDevice();
    sound::loadFootstepSound();
    sound::loadRunSound();
    sound::loadBgm();
    //load texture
    texture::loadBg();
    texture::loadTexture();
}
void unloadAndClose() {
    // close sound:
    sound::unloadDeclaredSound();
    sound::unloadBgm();
    CloseAudioDevice();
    // unload texture
    texture::unloadTexture();
    texture::unloadBg();
    // close windows
    CloseWindow();
}
