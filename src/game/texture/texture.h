#pragma once

namespace texture {
    extern Texture2D flowerTexture;
    extern Texture2D bg;
    extern Texture2D ball;
    extern Texture2D chest;
    extern Texture2D chest_open;
    void drawBackground(Texture2D tex);
    void loadTexture();
    void loadBg();
    void unloadBg();
    void unloadTexture();
} // namespace
