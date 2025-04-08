#include "Level1.h"
#define LEVEL1_WIDTH 14
#define LEVEL1_HEIGHT 8

#define LEVEL1_ENEMY_COUNT 2
using namespace std;

static GLuint backgroundTextureID;

unsigned int level1_data[] =
{
    4, 4, 4, 4, 4,  4,  4, 23, 24, 24, 24, 24, 24, 25,
    4, 4, 4, 4, 4,  4,  4, 23, 24, 24, 24, 24, 24, 25,
    4, 4, 4, 4, 4,  4,  4,  4, 4, 4, 4, 4,  4,  4,
    4, 4, 4, 4, 4,  4,  4,  4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4,  4,  4,  4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4,  4,  4,  4, 0, 1, 1, 2, 4, 4,
    4,20,21,21,22,  4,  4,  4, 4, 4, 4, 4, 4, 4,
    4, 4, 4, 4, 4,  4,  225,226, 227, 4, 4, 4, 4, 4
};

void Level1::Initialize(int numLives) {
    
    state.nextScene = -1;
    
    GLuint mapTextureID = Util::LoadTexture("tileset.png");
    state.map = new Map(LEVEL1_WIDTH, LEVEL1_HEIGHT, level1_data, mapTextureID, 1.0f, 16, 16);
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
    
    state.enemies = new Entity[LEVEL1_ENEMY_COUNT];
    
    GLuint enemyTextureID = Util::LoadTexture("bug.png");
    backgroundTextureID = Util::LoadTexture("exterior-parallaxBG1.png");
    glBindTexture(GL_TEXTURE_2D, backgroundTextureID);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);
    
    state.enemies[0].entityType = ENEMY;
    state.enemies[0].textureID = enemyTextureID;
    state.enemies[0].position = glm::vec3(4, -5.0f, 0);
    state.enemies[0].speed = 1;
    state.enemies[0].aiType = WALKER;
    state.enemies[0].aiState = IDLE;
    state.enemies[0].jumpPower = 5.0f;
    state.enemies[0].acceleration = glm::vec3(0, -9.81, 0);
        
    state.enemies[1].entityType = ENEMY;
    state.enemies[1].textureID = enemyTextureID;
    state.enemies[1].position = glm::vec3(10, -3.0f, 0);
    state.enemies[1].speed = 1;
    state.enemies[1].aiType = WAITANDGO;
    state.enemies[1].aiState = IDLE;
    state.enemies[1].jumpPower = 5.0f;
    state.enemies[1].acceleration = glm::vec3(0, -9.81, 0);
    
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; ++i) {
        state.enemies[i].isActive = true;
    }
}
void Level1::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; ++i) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, LEVEL1_ENEMY_COUNT, state.map);
    }
    if (state.player->numLives == 0) {
        state.nextScene = 4;
    }
    bool anyAlive = false;
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; ++i) {
        if (state.enemies[i].isActive == true) {
            anyAlive = true;
            break;
        }
    }
  
    if (state.player->position.x >= 10 && state.player->position.y <= -3) {
        state.nextScene = 2;
    }
    if (state.player->position.y <= -10 || state.player->isActive == false) {
        state.player->isActive = true;
        state.player->numLives -= 1;
        state.player->position = glm::vec3(1, 0, 0);
    }
}
void Level1::Render(ShaderProgram *program) {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glm::mat4 modelMatrix = glm::mat4(1.0f);
    float parallaxOffset = 0.0f;
    if (state.player->position.x > 5.0f) {
        parallaxOffset = (state.player->position.x - 5.0f) * 0.2f;
    }
    modelMatrix = glm::translate(modelMatrix, glm::vec3(LEVEL1_WIDTH / 2.0f + parallaxOffset, -LEVEL1_HEIGHT / 2.0f, 0.0f));
    program->SetModelMatrix(modelMatrix);

    float vertices[] = {
        -LEVEL1_WIDTH / 2.0, -LEVEL1_HEIGHT / 1.5 ,
        -LEVEL1_WIDTH / 2.0, LEVEL1_HEIGHT  / 1.5 ,
         LEVEL1_WIDTH / 2.0, LEVEL1_HEIGHT / 1.5,
         LEVEL1_WIDTH /2.0 , -LEVEL1_HEIGHT / 1.5
    };
    float texCoords[] = {
        0.0f, 1.0f,
        0.0f, 0.0f,
        LEVEL1_WIDTH / 14.0f, 0.0f,
        LEVEL1_WIDTH / 14.0f, 1.0f
    };
    glBindTexture(GL_TEXTURE_2D, backgroundTextureID);
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    glDrawArrays(GL_TRIANGLE_FAN, 0, 4);
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
    
    Util::DrawText(program, Util::LoadTexture("font1.png"), "Level 1", 0.5f, -0.1f, glm::vec3(0.2, -2, 0));
    Util::DrawText(program, Util::LoadTexture("font1.png"), "Lives " + std::to_string(state.player->numLives), 0.5f, -0.1f, glm::vec3(0.2, -2.5, 0));
    state.map->Render(program);
    state.player->Render(program);
    for (int i = 0; i < LEVEL1_ENEMY_COUNT; ++i) {
        state.enemies[i].Render(program);
    }
}
