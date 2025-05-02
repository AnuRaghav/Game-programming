#include "Win.h"
#include <SDL_mixer.h>
static GLuint winBackground = 0;
void Win::Initialize(int numLives) {
    state.nextScene = -1;
    state.player = new Entity();
        state.player->entityType = PLAYER;
        state.player->position = glm::vec3(5, -5, 0);
        state.player->movement = glm::vec3(0);
        state.player->acceleration = glm::vec3(0, 0, 0);
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
    winBackground = Util::LoadTexture("win.jpeg");
}
void Win::Update(float deltaTime) {
    
    static float timePassed = 0.0f;
    static bool hasPlayedSamples = false;
    timePassed += deltaTime;

    
    if (!hasPlayedSamples) {
        std::vector<Mix_Chunk*> chunks;
        std::cout << "Number of collected samples: " << state.samples.size() << std::endl;
        for (const Entity& sample : state.samples) {
            int index = static_cast<int>(sample.sampleType);
            std::cout << index << std::endl;
            int fileNumber = 0;
            if (index <= 9) fileNumber = (index + 1) * 11;
            else if (index == 10) fileNumber = 110;
            else if (index == 11) fileNumber = 121;
            else if (index == 12) fileNumber = 132;
            std::string filename = std::to_string(fileNumber) + ".wav";
            Mix_Chunk* chunk = Mix_LoadWAV(filename.c_str());
            if (chunk) {
                chunks.push_back(chunk);
                std::cout << fileNumber << std::endl;
            }
        }

        
        for (Mix_Chunk* chunk : chunks) {
            Mix_PlayChannel(-1, chunk, 0);
        }
        
        hasPlayedSamples = true;
    }

    
    if (timePassed > 180.0f) {
        state.nextScene = 0;
        timePassed = 0.0f;
        hasPlayedSamples = false;
    }
}
void Win::Render(ShaderProgram *program) {
    float aspect = 4.0f / 3.0f;
    float height = 7.5f;
    float width = height * aspect;
    float vertices[] = {
        -2.0f, -7*height / 9,
        width, -7*height / 9,
        width,  7*height / 9,
        -2.0f, -7*height / 9,
        width,  7*height / 9,
        -2.0f,  7*height / 9
    };

    float texCoords[] = {
        0.0f, 1.0f,
        1.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 1.0f,
        1.0f, 0.0f,
        0.0f, 0.0f
    };

    glBindTexture(GL_TEXTURE_2D, winBackground);
    glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
    glEnableVertexAttribArray(program->positionAttribute);
    glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
    glEnableVertexAttribArray(program->texCoordAttribute);
    glDrawArrays(GL_TRIANGLES, 0, 6);
    glDisableVertexAttribArray(program->positionAttribute);
    glDisableVertexAttribArray(program->texCoordAttribute);

    Util::DrawText(program, Util::LoadTexture("font1.png"), "You Win!", 1.5, -0.5, glm::vec3(1.75f, -3.5f, 0));
}
