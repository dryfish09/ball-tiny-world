#include <cstdlib>
#include "raylib.h"
#include "texture.h"
namespace texture {
    Texture2D flowerTexture;
    Texture2D ball;
    Texture2D bg;
    Texture2D chest;
    Texture2D chest_open;
    void drawBackground(Texture2D tex) {
    DrawTexturePro(tex,
        (Rectangle){ 0, 0, (float)tex.width, (float)tex.height },
        (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
        (Vector2){ 0, 0 }, 0.0f, WHITE);
    }
    void loadTexture() {
        flowerTexture = LoadTexture("src/assets/texture/flower.png");
        ball = LoadTexture("src/assets/texture/ball.png");
        chest = LoadTexture("src/assets/texture/chest.png");
        chest_open = LoadTexture("src/assets/texture/chest_open.png");
        // make sure texture loaded by check it
        if (flowerTexture.id == 0) {
            TraceLog(LOG_ERROR, "texture is not available or can't be loaded: flower texture.");
            std::abort();
        }
        if (ball.id == 0) {
            TraceLog(LOG_ERROR, "texture is not available or can't be loaded: ball texture.");
            std::abort();
        }
    }
    void loadBg() {
        bg = LoadTexture("src/assets/texture/bg.png");
        if (bg.id == 0) {
            TraceLog(LOG_ERROR, "texture is not available or can't be loaded: background.");
        }
    }
    void unloadBg() {
        UnloadTexture(bg);
    }
    void unloadTexture() {
        UnloadTexture(flowerTexture);
        UnloadTexture(ball);
        UnloadTexture(chest);
        UnloadTexture(chest_open);
    }
} // namespace
