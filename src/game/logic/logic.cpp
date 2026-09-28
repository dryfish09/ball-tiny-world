
#include "raylib.h"
#include "game/var.h"
#include "game/sound/sound.h"
#include "game/texture/texture.h"
#include "game/spawn/flower/flower_spawner.h"
#include "game/spawn/player/ball_spawner.h"
#include "logic.h"
void insertLogic() {
    spawnBall();
    spawnFlower();
    // speed: 
    float dt = GetFrameTime();
    float speed = 300.5f;
    float runSpeed = 240.5f;
    float dashSpeed = 360.0f;
    // play background music 
    sound::playBgm();
    while (!WindowShouldClose()) {
        UpdateMusicStream(sound::bgm);
        // check is bgm are playing and replay it
        if(!IsMusicStreamPlaying(sound::bgm)) {
            sound::playBgm();
        }
        // move ball with arrows and W, A, S, D
        if (IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) {
            spawn::ballPos.x += speed * dt;
            // play sound
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
        // player will move slower when player hold to move
        else if (IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) {
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
        // easter egg for who knows some code
        else if (IsKeyDown(KEY_Y)) {
            spawn::ballPos.y += dashSpeed * dt;
        }
        else if (IsKeyDown(KEY_X)) {
            spawn::ballPos.x += dashSpeed * dt;
        }
        else if (IsKeyDown(KEY_X) && IsKeyDown(KEY_LEFT_SHIFT)) {
            spawn::ballPos.x -= dashSpeed * dt;
        }
        else if (IsKeyDown(KEY_Y) && IsKeyDown(KEY_LEFT_SHIFT)) {
            spawn::ballPos.y -= dashSpeed * dt;
        }
        // prevent player go out of screen
        if (ballPos.x - ballRadius <= 0) {
            spawn::ballPos.x = ballRadius;
        }
        if (ballPos.x + ballRadius >= windowX) {
            spawn::ballPos.x = windowX - ballRadius;
        }
        if (spawn::ballPos.y - ballRadius <= 0) {
            spawn::ballPos.y = ballRadius;
        }
        if (ballPos.y + ballRadius >= windowY) {
            spawn::ballPos.y = windowY - ballRadius;
        }
        BeginDrawing();
        ClearBackground(GREEN);
        // draw background
        texture::drawBackground(texture::bg);
        // draw some circle
        DrawTextureV(texture::ball, spawn::ballPos, WHITE);
        DrawTextureV(texture::flowerTexture, spawn::flowerPos, WHITE);
        DrawTextureV(texture::flowerTexture, spawn::flowerPos2, WHITE);
        DrawTextureV(texture::flowerTexture, spawn::flowerPos3, WHITE);
        DrawTextureV(texture::flowerTexture, spawn::flowerPos4, WHITE);
        DrawTextureV(texture::flowerTexture, spawn::flowerPos5, WHITE);
        DrawTextureV(texture::flowerTexture, spawn::flowerPos6, WHITE);
        DrawText("Use arrow keys or WASD to move!", 20, 20, 20, BLACK);
        EndDrawing();
    }
}
