
#include "raylib.h"
#include "game/var.h"
#include "game/sound/sound.h"
#include "game/texture/texture.h"
#include "game/spawn/flower/flower_spawner.h"
#include "game/spawn/player/ball_spawner.h"
#include "game/spawn/chest/chest.h"
#include "logic.h"
void insertLogic() {
    spawn::spawnBall();
    spawn::spawnFlower();
    spawnChest();
    // speed: 
    float speed = 300.5f;
    float runSpeed = 240.5f;
    float dashSpeed = 360.0f;
    bool chestOpened = false;
    float spawnTimer = 3.0f;
    float despawnTimer = 5.0f;
    float despawnCooldown = 0;
    float spawnCooldown = 0;
    // play background music 
    sound::playBgm();
    while (!WindowShouldClose()) {
        float dt = GetFrameTime();
        UpdateMusicStream(sound::bgm);
        // check is bgm are playing and replay it
        if(!IsMusicStreamPlaying(sound::bgm)) {
            sound::playBgm();
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
        
        // easter egg for who knows some code
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
        // player pos must = chest pos to open, because player doesn't have hands :)
        if (IsKeyPressed(KEY_E) && spawn::ballPos.x == chestPos.x) {
            chestOpened = true;
            despawnCooldown = despawnTimer;
            spawnCooldown = spawnTimer;
        }
        
        if (IsKeyPressed(KEY_E) && spawn::ballPos.y == chestPos.y) {
            chestOpened = true;
            despawnCooldown = despawnTimer;
            spawnCooldown = spawnTimer;
        }
        // prevent player go out of screen
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
        if (chestOpened) {
            despawnCooldown -= dt;
            drawOpenedChest();
            if (despawnCooldown <= 0) {
                spawnCooldown = 0;
                // do nothing, skip
            }
            spawnChest();
            spawnCooldown -= dt;
            if (spawnCooldown <= 0) {
                spawnCooldown = 0;
                chestOpened = false;
            }
        } else {
            drawChest();
        }
        DrawText("Use arrow keys or WASD to move!", 20, 20, 20, BLACK);
        EndDrawing();
    }
}
