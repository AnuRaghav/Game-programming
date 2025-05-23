#include "Level3.h"
#define Level3_WIDTH 35
#define Level3_HEIGHT 8

#define LEVEL3_ENEMY_COUNT 3
using namespace std;

unsigned int Level3_data[] =
{
    // Row 1 (top)
    4, 4, 4, 4, 4, 4, 4, 4, 23, 24, 24, 25, 4, 4, 4, 4, 4, 23, 24, 24, 25, 4, 4, 4, 4, 23, 24, 24, 25, 4, 4, 4, 4, 4, 4,
    // Row 2
    4, 4, 4, 4, 4, 4, 4, 4, 23, 24, 24, 25, 4, 4, 4, 4, 4, 23, 24, 24, 25, 4, 4, 4, 4, 23, 24, 24, 25, 4, 4, 4, 4, 4, 4,
    // Row 3 (empty sky)
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    // Row 4 (platform potential)
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,
    // Row 5 (more sky)
    4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 65, 66, 67, 68, 69,
    // Row 6 (lower platform)
    4, 4, 4, 4, 4, 4, 4, 0, 1, 1, 2, 4, 4, 0, 1, 1, 1, 1, 2, 4, 4, 0, 1, 1, 1, 1, 2, 4, 4, 0, 4, 82, 83, 84,  4,
    // Row 7 (top ground)
    4,20,21,21,22, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,20,21,21,21,21,21,22, 4, 4, 4,  4, 99,  4,  4,
    // Row 8 (bottom base)
    4, 4, 4, 4, 4,225,226,227, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4, 4,  4,4, 4, 4, 115,  4,  4
};
void Level3::Initialize(int numLives) {
    
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(Level3_WIDTH, Level3_HEIGHT, Level3_data, mapTextureID, 1.0f, 16, 16);
    // Initialize Player
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(1, -2, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, -9.81f, 0);
    state.player->speed = 3.0f;
    state.player->textureID = Util::LoadTexture("micheal.png");
    
    state.player->animRight = new int[4] {3, 7, 11, 15};
    state.player->animLeft = new int[4] {1, 5, 9, 13};
    state.player->animUp = new int[4] {2, 6, 10, 14};
    state.player->animDown = new int[4] {0, 4, 8, 12};
    
    state.player->animIndices = state.player->animRight;
    state.player->animFrames = 4;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 4;
    state.player->animRows = 4;
    
    state.player->numLives = numLives;
    
    state.player->height = 0.8f;
    state.player->width = 0.8f;
    
    state.player->jumpPower = 7.0f;
    
    state.enemies = new Entity[LEVEL3_ENEMY_COUNT];
    GLuint enemyTextureID = Util::LoadTexture("bug.png");
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(24, -2.25, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = WAITANDGO;
    state.enemies[0].aiState = IDLE;
    state.enemies[0].jumpPower = 5.0f;
    state.enemies[0].acceleration = glm::vec3(0, -9.81, 0);
    
    GLuint batTextureID = Util::LoadTexture("bat.png");
    if (batTextureID == 0) {
        batTextureID = Util::LoadTexture("fallback.png"); // optional fallback texture
    }

    state.enemies[1].entityType = BAT;
    state.enemies[1].textureID = batTextureID;
    state.enemies[1].batOrigin = glm::vec3(15, -3, 0);
    state.enemies[1].position = state.enemies[1].batOrigin;
    state.enemies[1].isActive = true;
    state.enemies[1].animRight = new int[4]{0, 1, 2, 3};
    state.enemies[1].animIndices = state.enemies[1].animRight;
    state.enemies[1].animFrames = 4;
    state.enemies[1].animIndex = 0;
    state.enemies[1].animTime = 0;
    state.enemies[1].animCols = 4;
    state.enemies[1].animRows = 4;

    state.enemies[2].entityType = BAT;
    state.enemies[2].textureID = batTextureID;
    state.enemies[2].batOrigin = glm::vec3(28, -3.5, 0);
    state.enemies[2].position = state.enemies[2].batOrigin;
    state.enemies[2].isActive = true;
    state.enemies[2].animRight = new int[4]{0, 1, 2, 3};
    state.enemies[2].animIndices = state.enemies[2].animRight;
    state.enemies[2].animFrames = 4;
    state.enemies[2].animIndex = 0;
    state.enemies[2].animTime = 0;
    state.enemies[2].animCols = 4;
    state.enemies[2].animRows = 4;

    for (int i = 0; i < LEVEL3_ENEMY_COUNT; ++i) {
        state.enemies[i].isActive = true;
    }
}
void Level3::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; ++i) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL3_ENEMY_COUNT, state.map);
    }
    if (state.player->numLives == 0) {
        state.nextScene = 4;
    }
    bool anyAlive = false;
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; ++i) {
        if (state.enemies[i].isActive == true) {
            anyAlive = true;
            break;
        }
    }
    if (state.player->position.x >= 33 && state.player->position.y <= -3) {
        state.nextScene = 5;
    }
    if (state.player->position.y <= -10 || state.player->isActive == false) {
        state.player->isActive = true;
        state.player->numLives -= 1;
        state.player->position = glm::vec3(1, -2, 0);
    }
    
}
void Level3::Render(ShaderProgram *program) {
    Util::DrawText(program, Util::LoadTexture("font1.png"), "Level 3", 0.5f, -0.1f, glm::vec3(0, -2, 0));
    Util::DrawText(program, Util::LoadTexture("font1.png"), "Lives " + std::to_string(state.player->numLives), 0.5f, -0.1f, glm::vec3(0, -2.5, 0));
    state.map->Render(program);
    state.player->Render(program);
    for (int i = 0; i < LEVEL3_ENEMY_COUNT; ++i) {
        state.enemies[i].Render(program);
    }
}
