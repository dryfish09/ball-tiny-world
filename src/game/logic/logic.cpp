#include "raylib.h"
#include "game/var.h"
#include "game/sound/sound.h"
#include "game/texture/texture.h"
#include "game/spawn/flower/flower_spawner.h"
#include "game/spawn/player/ball_spawner.h"
#include "game/spawn/chest/chest_spawner.h"
#include "logic.h"
#include <string>
// keep this, do not modify :)
Font font;
float dt;
int trapped = GetRandomValue(0, 1);
int score = 0;
bool scoreAdded = false;
bool chestOpened = false;
float spawnTimer = 3.0f;
float spawnCooldown = 0;
int highScore = 0;

void DrawTextF(const std::string text, int x, int y, int size, Color color) {
    DrawTextEx(font, text.c_str(),
        (Vector2){ static_cast<float>(x), static_cast<float>(y) },
        static_cast<float>(size), 1.0f, color);
}

void insertLogic() {
    font = LoadFont("src/assets/font/font.ttf");

    spawn::spawnBall();
    spawn::spawnFlower();
    spawnChest();

    float speed = 300.5f;
    float runSpeed = 240.5f;
    float dashSpeed = 360.0f;

    sound::playBgm();

    while (!WindowShouldClose()) {
        dt = GetFrameTime();
        UpdateMusicStream(sound::bgm);

        if (!IsMusicStreamPlaying(sound::bgm)) {
            sound::playBgm();
        }

        if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
            spawn::ballPos.x += runSpeed * dt;
            sound::playRunSound();
        }
        else if (IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) {
            spawn::ballPos.x -= runSpeed * dt;
            sound::playRunSound();
        }
        else if (IsKeyDown(KEY_DOWN) || IsKeyDown(KEY_S)) {
            spawn::ballPos.y += runSpeed * dt;
            sound::playRunSound();
        }
        else if (IsKeyDown(KEY_UP) || IsKeyDown(KEY_W)) {
            spawn::ballPos.y -= runSpeed * dt;
            sound::playRunSound();
        }

        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            spawn::ballPos.x += speed * dt;
            sound::playFootstepSound();
        }
        else if (IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) {
            spawn::ballPos.x -= speed * dt;
            sound::playFootstepSound();
        }
        else if (IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) {
            spawn::ballPos.y += speed * dt;
            sound::playFootstepSound();
        }
        else if (IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) {
            spawn::ballPos.y -= speed * dt;
            sound::playFootstepSound();
        }
        else if (IsKeyDown(KEY_X) && IsKeyDown(KEY_LEFT_SHIFT)) {
            spawn::ballPos.x -= dashSpeed * dt;
        }
        else if (IsKeyDown(KEY_Y) && IsKeyDown(KEY_LEFT_SHIFT)) {
            spawn::ballPos.y -= dashSpeed * dt;
        }
        else if (IsKeyDown(KEY_Y)) {
            spawn::ballPos.y += dashSpeed * dt;
        }
        else if (IsKeyDown(KEY_X)) {
            spawn::ballPos.x += dashSpeed * dt;
        }

        if (IsKeyPressed(KEY_E) &&
            (spawn::ballPos.x - chestPos.x) * (spawn::ballPos.x - chestPos.x) +
            (spawn::ballPos.y - chestPos.y) * (spawn::ballPos.y - chestPos.y) < 2500) {
            chestOpened = true;
            spawnCooldown = spawnTimer;
        }

        if (spawn::ballPos.x - spawn::ballRadius <= 0) {
            spawn::ballPos.x = spawn::ballRadius;
        }
        if (spawn::ballPos.x + spawn::ballRadius >= windowX) {
            spawn::ballPos.x = windowX - spawn::ballRadius;
        }
        if (spawn::ballPos.y - spawn::ballRadius <= 0) {
            spawn::ballPos.y = spawn::ballRadius;
        }
        if (spawn::ballPos.y + spawn::ballRadius >= windowY) {
            spawn::ballPos.y = windowY - spawn::ballRadius;
        }

        draw();
    }

    UnloadFont(font);
}

void draw() {
    BeginDrawing();
    ClearBackground(GREEN);

    texture::drawBackground(texture::bg);

    DrawTextureV(texture::ball, spawn::ballPos, WHITE);
    DrawTextureV(texture::flowerTexture, spawn::flowerPos, WHITE);
    DrawTextureV(texture::flowerTexture, spawn::flowerPos2, WHITE);
    DrawTextureV(texture::flowerTexture, spawn::flowerPos3, WHITE);
    DrawTextureV(texture::flowerTexture, spawn::flowerPos4, WHITE);
    DrawTextureV(texture::flowerTexture, spawn::flowerPos5, WHITE);
    DrawTextureV(texture::flowerTexture, spawn::flowerPos6, WHITE);

    if (chestOpened) {
        trapped = GetRandomValue(0, 1);
        drawOpenedChest();
        spawnCooldown -= dt;

        if (spawnCooldown <= 0 && !scoreAdded && trapped == 0) {
            spawnCooldown = 0;
            chestOpened = false;
            score += 2;
            scoreAdded = true;
            spawnChest();
        }
        if (highScore < score) {
            highScore = score;
        }
        if (trapped == 1) {
            score -= score / 2;
        }
    } else {
        scoreAdded = false;
        drawChest();
    }

    DrawTextF("Use arrow keys or WASD to move!", 20, 20, 20, BLACK);
    DrawTextF(TextFormat("Score: %i", score), 20, 50, 20, BLACK);
    DrawTextF(TextFormat("High score: %i", highScore), 20, 80, 20, BLACK);

    EndDrawing();
}
