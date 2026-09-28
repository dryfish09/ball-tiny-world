#include "raylib.h"
#include "chest.h"
#include "game/var.h"
#include "game/texture/texture.h"
Vector2 chestPos = {0, 0};
const float chestRange = 30.0f;
void spawnChest() {
    chestPos.x = static_cast<float>(GetRandomValue(windowX - chestRange, windowX + chestRange));
    chestPos.y = static_cast<float>(GetRandomValue(windowY - chestRange, windowY + chestRange));
}
void drawChest() {
    DrawTextureV(chest, chestPos, WHITE);
}
void drawOpenedChest() {
    DrawTextureV(chest_open, chestPos, WHITE);
}
