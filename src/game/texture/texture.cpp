
#include "raylib.h"
#include "texture.h"
namespace texture {
    Texture2D flowerTexture;
    Texture2D ball;
    Texture2D bg;
    void drawBackground(Texture2D tex) {
    DrawTexturePro(tex,
        (Rectangle){ 0, 0, (float)tex.width, (float)tex.height },
        (Rectangle){ 0, 0, (float)GetScreenWidth(), (float)GetScreenHeight() },
        (Vector2){ 0, 0 }, 0.0f, WHITE);
    }
    void loadTexture() {
        flowerTexture = LoadTexture("src/assets/texture/flower.png");
        ball = LoadTexture("src/assets/texture/ball.png");
        // make sure texture loaded by check it
        if (flowerTexture.id == 0) {
            TraceLog(LOG_ERROR, "texture is not available or can't be loaded: flower texture.");
        }
        if (ball.id == 0) {
            TraceLog(LOG_ERROR, "texture is not available or can't be loaded: ball texture.");
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
    }
} // namespace
