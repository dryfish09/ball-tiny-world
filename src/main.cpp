#include "raylib.h"
#include "game/sound/sound.h"
#include "game/texture/texture.h"
#include "game/logic/logic.h"
#include "game/init/init.h"

int main() {
    init();
    // set target fps
    SetTargetFPS(60);
    // call logic
    insertLogic();
    // unload and close device sound,window,etc.
    unloadAndClose();
    return 0;
}

