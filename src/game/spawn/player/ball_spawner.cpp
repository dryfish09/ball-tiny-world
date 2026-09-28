#include "raylib.h"
#include "game/logic/logic.h"
#include "game/var.h"
#include "ball_spawner.h"
namespace spawn {
    float ballRadius = 9.5f;
    Vector2 ballPos = {100, 100};
    void spawnBall() {
        ballPos.x = static_cast<float>(GetRandomValue(ballRadius, windowX - ballRadius));
        ballPos.y = static_cast<float>(GetRandomValue(ballRadius, windowY - ballRadius));
    }
}
