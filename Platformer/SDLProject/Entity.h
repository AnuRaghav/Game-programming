#pragma once
#define GL_SILENCE_DEPRECATION

#ifdef _WINDOWS
#include <GL/glew.h>
#endif

#define GL_GLEXT_PROTOTYPES 1
#include <SDL.h>
#include <SDL_opengl.h>
#include "glm/mat4x4.hpp"
#include "glm/gtc/matrix_transform.hpp"
#include "ShaderProgram.h"
#include "Map.h"

enum EntityType {PLAYER, PLATFORM, ENEMY, BAT};

enum AIType {WALKER, WAITANDGO, JUMPER};
enum AIState {IDLE, WALKING, ATTACKING, JUMPING};

class Entity {
public:
    EntityType entityType;
    AIType aiType;
    AIState aiState;
    glm::vec3 position;
    glm::vec3 movement;
    glm::vec3 acceleration;
    glm::vec3 velocity;
    
    float width = 1;
    float height = 1;
    
    bool jump = false;
    float jumpPower = 0;
    
    float speed;
    
    GLuint textureID;
    
    glm::mat4 modelMatrix;
    
    int *animRight = NULL;
    int *animLeft = NULL;
    int *animUp = NULL;
    int *animDown = NULL;

    int *animIndices = NULL;
    int animFrames = 0;
    int animIndex = 0;
    float animTime = 0;
    int animCols = 0;
    int animRows = 0;
    
    int numLives;
    bool isActive = true;
    
    bool collidedTop = false;
    bool collidedBottom = false;
    bool collidedLeft = false;
    bool collidedRight = false;
    
    bool pitRight = false;
    bool pitLeft = false;

    glm::vec3 batOrigin;
    float batRadius = 2.0f; // Radius of circular area
    float batAngle = 0.0f; // Angle for circular motion
    float batSpeed = 2.0f; // Speed of circular motion
    
    Entity();
    
    bool CheckCollision(Entity *other);
    void CheckCollisionsY(Entity *objects, int objectCount);
    void CheckCollisionsX(Entity *objects, int objectCount);
    void CheckEnemyCollided(Entity *enemies, int enemyCount);
    void CheckPit(Entity *platforms, int platformCount);
    void CheckCollisionsX(Map *map);
    void CheckCollisionsY(Map *map);
    
    void Update(float deltaTime, Entity *player, Entity *objects, int objectCount, Map *map);
    void Render(ShaderProgram *program);
    void DrawSpriteFromTextureAtlas(ShaderProgram *program, GLuint textureID, int index);
    
    void AI(Entity *player);
    void AIWalker(Entity *platforms, int platformCount);
    void AIWaitAndGo(Entity *player);
    void AIJumper();
};
