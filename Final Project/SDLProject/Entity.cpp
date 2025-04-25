int animCols = 10;
int animRows = 8;

#include "Entity.h"
#include <iostream>
using namespace std;

Entity::Entity()
{
    position = glm::vec3(0);
    movement = glm::vec3(0);
    acceleration = glm::vec3(0);
    velocity = glm::vec3(0);
    speed = 0;

    modelMatrix = glm::mat4(1.0f);

    animCols = 10;
    animRows = 8;

    // Animation arrays will be assigned externally
    animRight = nullptr;
    animLeft = nullptr;
    animIdle = nullptr;
    animIdleLeft = nullptr;
    animAttackRight = nullptr;
    animAttackLeft = nullptr;

    animIndices = nullptr;
    animFrames = 0;
    animIndex = 0;
    animTime = 0.0f;

}

bool Entity::CheckCollision(Entity *other) {
    if (isActive == false || other->isActive == false) return false;
    float xdist = fabs(position.x - other->position.x) - ((width + other->width) / 2.0f);
    float ydist = fabs(position.y - other->position.y) - ((height + other->height) / 2.0f);
    
    if (xdist < 0 && ydist < 0) return true;
    return false;
}

void Entity::CheckCollisionsY(Entity *objects, int objectCount)
{
   for (int i = 0; i < objectCount; i++)
   {
       Entity *object = &objects[i];
       if (CheckCollision(object))
       {
           float ydist = fabs(position.y - object->position.y);
           float penetrationY = fabs(ydist - (height / 2.0f) - (object->height / 2.0f));
           if (velocity.y > 0) {
               position.y -= penetrationY;
               velocity.y = 0;
               collidedTop = true;
               object->collidedBottom = true;
           }
           else if (velocity.y < 0) {
               position.y += penetrationY;
               velocity.y = 0;
               collidedBottom = true;
               object->collidedTop = true;
} }
} }

void Entity::CheckCollisionsX(Entity *objects, int objectCount)
{
   for (int i = 0; i < objectCount; i++)
   {
       Entity *object = &objects[i];
       if (CheckCollision(object))
       {
           float xdist = fabs(position.x - object->position.x);
           float penetrationX = fabs(xdist - (width / 2.0f) - (object->width / 2.0f));
           if (velocity.x > 0) {
               position.x -= penetrationX;
               velocity.x = 0;
               collidedRight = true;
               object->collidedLeft = true;
           }
           else if (velocity.x < 0) {
               position.x += penetrationX;
               velocity.x = 0;
               collidedLeft = true;
               object->collidedRight = true;
} }
} }

void Entity::CheckEnemyCollided(Entity *enemies, int enemyCount) {
    collidedLeft = false;
    collidedRight = false;
    collidedTop = false;
    // Prevent collision glitches by skipping actual resolution with enemies
    if (collidedBottom == true) {
        for (int i = 0; i < enemyCount; ++i) {
            if (enemies[i].collidedTop == true) {
                enemies[i].isActive = false;
            }
        }
    }
    
    // Legacy collision logic removed for clarity
}

void Entity::CheckCollisionsY(Map *map)
{
    // Probes for tiles
    glm::vec3 top = glm::vec3(position.x, position.y + (height / 2), position.z);
    glm::vec3 top_left = glm::vec3(position.x - (width / 2), position.y + (height / 2), position.z);
    glm::vec3 top_right = glm::vec3(position.x + (width / 2), position.y + (height / 2), position.z);
    glm::vec3 bottom = glm::vec3(position.x, position.y - (height / 2), position.z);
    glm::vec3 bottom_left = glm::vec3(position.x - (width / 2), position.y - (height / 2), position.z);
    glm::vec3 bottom_right = glm::vec3(position.x + (width / 2), position.y - (height / 2), position.z);
    float penetration_x = 0;
    float penetration_y = 0;
    if (map->IsSolid(top, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    else if (map->IsSolid(top_left, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    else if (map->IsSolid(top_right, &penetration_x, &penetration_y) && velocity.y > 0) {
        position.y -= penetration_y;
        velocity.y = 0;
        collidedTop = true;
    }
    if (map->IsSolid(bottom, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
    else if (map->IsSolid(bottom_left, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
    else if (map->IsSolid(bottom_right, &penetration_x, &penetration_y) && velocity.y < 0) {
        position.y += penetration_y;
        velocity.y = 0;
        collidedBottom = true;
    }
}

void Entity::CheckCollisionsX(Map *map)
{

    glm::vec3 left = glm::vec3(position.x - (width / 2), position.y, position.z);
    glm::vec3 right = glm::vec3(position.x + (width / 2), position.y, position.z);
    float penetration_x = 0;
    float penetration_y = 0;
    if (map->IsSolid(left, &penetration_x, &penetration_y) && velocity.x < 0) {
        position.x += penetration_x;
        velocity.x = 0;
        collidedLeft = true;
}
    if (map->IsSolid(right, &penetration_x, &penetration_y) && velocity.x > 0) {
        position.x -= penetration_x;
        velocity.x = 0;
        collidedRight = true;
} }

void Entity::CheckPit(Entity *platforms, int platformCount) {
    int leftLocation = -1;
    int rightLocation = -1;
    glm::vec3 sensorRight = glm::vec3(position.x + 0.6f, position.y - 0.6f, 0);
    glm::vec3 sensorLeft = glm::vec3(position.x - 0.6f, position.y - 0.6f, 0);
    for (int i = 0; i < platformCount; ++i) {
        float leftDistX = fabs(sensorLeft.x - platforms[i].position.x) - ((width + platforms[i].width) / 2.0f);
        float rightDistX = fabs(sensorRight.x - platforms[i].position.x) - ((width + platforms[i].width) / 2.0f);
        float leftDistY = fabs(sensorLeft.y - platforms[i].position.y) - ((height + platforms[i].height) / 2.0f);
        float rightDistY = fabs(sensorRight.y - platforms[i].position.y) - ((height + platforms[i].height) / 2.0f);
        
        if (leftDistX < 0 && leftDistY < 0) leftLocation = i;
        if (rightDistX < 0 && rightDistY < 0) rightLocation = i;
    }
    if (leftLocation == -1) pitLeft = true;
    if (rightLocation == -1) pitRight = true;
}

void Entity::AI(Entity *player) {
    switch(aiType) {
        case SUIT_AI:
            AISuit(player);
            break;
    }
}

void Entity::AISuit(Entity *player) {
    float distance = glm::distance(position, player->position);

    if (isAttacking) {
        // Do not update movement or animation while attack is playing
        movement = glm::vec3(0);
        return;
    }


    if (distance < 0.5f) {
        // In attack range
        movement = glm::vec3(0);
        if (!isAttacking) {
            isAttacking = true;
            animIndex = 0;
            animTime = 0.0f;
            attackStartTime = -1.0f;
            hasAttacked = false;
            animIndices = facingLeft ? animAttackLeft : animAttackRight;
            animFrames = 5;
            
        }

        if (!hasAttacked && player->isActive) {
            attackFrameCounter++;
//            cout << attackFrameCounter << endl;
            if (attackFrameCounter >= 3) {
                player->isActive = false;
                hasAttacked = true;
                attackFrameCounter = 0;
            }
        }

    } else if (distance < 4.0f) {
        // Chase the player
        isAttacking = false;
        hasAttacked = false;
        attackStartTime = -1.0f;
        attackFrameCounter = 0;

        if (player->position.x < position.x) {
            movement = glm::vec3(-1, 0, 0);
            animIndices = animLeft;
            animFrames = 10;
            facingLeft = true;
        } else {
            movement = glm::vec3(1, 0, 0);
            animIndices = animRight;
            animFrames = 10;
            facingLeft = false;
        }

    } else {
        // Idle if far
        isAttacking = false;
        hasAttacked = false;
        attackStartTime = -1.0f;
        attackFrameCounter = 0;
        movement = glm::vec3(0);
        animIndices = facingLeft ? animIdleLeft : animIdle;
        animFrames = 8;
    }
}

void Entity::Update(float deltaTime, Entity *player, Entity *objects, int objectCount, Map *map)
{
    if (isActive == false) {
        return;
    }
    collidedTop = false;
    collidedBottom = false;
    collidedLeft = false;
    collidedRight = false;

    pitLeft = false;
    pitRight = false;

    // Let SUIT AI handle all movement and animation logic
    if (entityType == SUIT) {
        AI(player);
    }

    if (animIndices != NULL) {
        animTime += deltaTime;
    

        if (animTime >= 0.1f) {
            animTime = 0.0f;
            animIndex++;
          

            if (animIndex >= animFrames) {
                if (isAttacking) {
               
                    isAttacking = false;
                }
                if (isUsingItem) {
           
                    isUsingItem = false;
                }
                animIndex = 0;
            }
        }
    }

    if (!isAttacking &&!isUsingItem && movement.x == 0 && movement.y == 0) {
        if (facingLeft && animIndices != animIdleLeft) {
            animIndices = animIdleLeft;
            animFrames = 8;
            animIndex = 0;
            animTime = 0.0f;
        } else if (!facingLeft && animIndices != animIdle) {
            animIndices = animIdle;
            animFrames = 8;
            animIndex = 0;
            animTime = 0.0f;
        }
    }

    if (jump) {
        jump = false;
        velocity.y += jumpPower;
    }

    velocity.x = movement.x * speed;
    velocity.y = movement.y * speed;
    velocity += acceleration * deltaTime;

    position.y += velocity.y * deltaTime;
    CheckCollisionsY(map);

    position.x += velocity.x * deltaTime;
    CheckCollisionsX(map);

    if(entityType == PLAYER) {
        //CheckCollisionsY(objects, objectCount);
        //CheckCollisionsX(objects, objectCount);
        CheckEnemyCollided(objects, objectCount);
    }

    // Removed: player deactivation on hitCounter >= 3

    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
}

void Entity::DrawSpriteFromTextureAtlas(ShaderProgram *program, GLuint textureID, int index)
{
    float u = (float)(index % animCols) / (float)animCols;
    float v = (float)(index / animCols) / (float)animRows;
    
    float width = 1.0f / (float)animCols;
    float height = 1.0f / (float)animRows;
    
    float texCoords[] = { u, v + height, u + width, v + height, u + width, v,
        u, v + height, u + width, v, u, v};
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}

void Entity::Render(ShaderProgram *program) {
    if (isActive == false) {
        return;
    }
    
    modelMatrix = glm::mat4(1.0f);
    modelMatrix = glm::translate(modelMatrix, position);
    modelMatrix = glm::scale(modelMatrix, glm::vec3(width, height, 1.0f));
    program->SetModelMatrix(modelMatrix);
    
    if (animIndices != NULL) {
        
        DrawSpriteFromTextureAtlas(program, textureID, animIndices[animIndex]);
        return;
    }
    
    float vertices[]  = { -0.5, -0.5, 0.5, -0.5, 0.5, 0.5, -0.5, -0.5, 0.5, 0.5, -0.5, 0.5 };
    float texCoords[] = { 0.0, 1.0, 1.0, 1.0, 1.0, 0.0, 0.0, 1.0, 1.0, 0.0, 0.0, 0.0 };
    
    glBindTexture(GL_TEXTURE_2D, textureID);
    
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    
    glDrawArrays(GL_TRIANGLES, 0, 6);
    
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);
}
