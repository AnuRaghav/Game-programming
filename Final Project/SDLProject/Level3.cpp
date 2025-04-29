#include <SDL_mixer.h>
#include <cstdlib>
#include <vector>
#include "level3.h"
#define level3_WIDTH 30
#define level3_HEIGHT 20

#define MAX_ENEMIES 16
using namespace std;

static GLuint backgroundTextureID;

extern GLuint sampleIcons[10];

 extern Mix_Chunk* sampleSounds[10];


int level3_data[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 15122, 15123, 15123, 15123, 15123, 15123, 15123, 15123, 15123, 15123, 15123, 15124, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, 15122, 15123, 15123, 15661, 11367, 11367, 11367, 11367, 11367, 11367, 11367, 11367, 11367, 11367, 15660, 15123, 15123, 15124, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, 15392, 11367, 11367, 11367, 11637, 11637, 11637, 11637, 11637, 11637, 11637, 11637, 11637, 11637, 11367, 11367, 11367, 15394, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, 15392, 11637, 11637, 11637, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 11637, 11637, 11637, 15394, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, 15392, 18917, 18917, 18917, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18917, 18917, 18917, 15394, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, 15392, 18917, 18917, 18917, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18917, 18917, 18917, 15394, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, 15143, 15392, 18917, 18917, 18917, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18917, 18917, 18917, 15394, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, 15392, 18917, 18917, 18917, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18917, 18917, 18917, 15394, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, 15662, 15663, 15663, 15391, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 18914, 15390, 15663, 15663, 15664, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, 15662, 15663, 15663, 15663, 15663, 15663, 15663, 15663, 15663, 15663, 15663, 15664, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1


};

int level3_furnitureData[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 27448, 27449, 27450, -1, 26022, -1, 26097, 26098, 26099, 26100, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 27360, 27719, 27720, -1, 26832, 23060, 26367, 26368, 26369, 26370, -1, 27982, 27983, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, 26357, -1, 27630, 27989, 27990, -1, 24668, -1, -1, -1, -1, -1, -1, 28252, 28253, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, 26627, -1, -1, -1, -1, -1, -1, -1, -1, -1, 28529, 28530, -1, 28522, 28523, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21622, 21623, 21624, -1, 28799, 28800, 22258, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 30143, 30144, 30145, -1, 21892, 21893, 21894, -1, 29069, 29070, 22528, -1, 26274, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 30413, 30414, 30415, -1, -1, -1, -1, -1, 29339, 29340, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

int level3_sampleData[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  9, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 10, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  8, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

void Level3::Initialize(int numLives) {
    
    state.nextScene = -1;
    
    
    GLuint mapTextureID = Util::LoadTexture("global.png");
    
    state.map = new Map(level3_WIDTH, level3_HEIGHT, level3_data, level3_furnitureData, mapTextureID, 1.0f, 270, 215);
    
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(10, -10, 0);
    state.player->movement = glm::vec3(0);
    state.player->acceleration = glm::vec3(0, 0, 0);
    state.player->speed = 3.0f;
    state.player->textureID = Util::LoadTexture("cat.png");
    
    state.player->animRight = new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
    state.player->animLeft = new int[10]{10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
    state.player->animIdle = new int[8]{20, 21, 22, 23, 24, 25, 26, 27};
    state.player->animUseItemRight = new int[6]{30, 31, 32, 33, 34, 35};
    state.player->animUseItemLeft = new int[6]{40, 41, 42, 43, 44, 45};
    state.player->animAttackRight = new int[4]{50, 52, 54, 56};
    state.player->animAttackLeft = new int[4]{60, 62, 64, 66};
    state.player->animIdleLeft = new int[8]{70, 71, 72, 73, 74, 75, 76, 77};
    
    state.player->animIndices = state.player->animIdle;
    state.player->animFrames = 10;
    state.player->animIndex = 0;
    state.player->animTime = 0;
    state.player->animCols = 10;
    state.player->animRows = 8;
    
    state.player->numLives = numLives;
    
    state.player->height = 0.8f;
    state.player->width = 0.8f;
    
    state.player->jumpPower = 7.0f;
    
    state.enemies = new Entity[MAX_ENEMIES];

    GLuint suitTextureID = Util::LoadTexture("suit.png");

    for (int i = 0; i < MAX_ENEMIES; ++i) {
        state.enemies[i].isActive = false;
        state.enemies[i].entityType = SUIT;
        state.enemies[i].textureID = suitTextureID;
        state.enemies[i].aiType = SUIT_AI;

        
        state.enemies[i].animRight = new int[10]{0, 1, 2, 3, 4, 5, 6, 7, 8, 9};
        state.enemies[i].animLeft = new int[10]{10, 11, 12, 13, 14, 15, 16, 17, 18, 19};
        state.enemies[i].animIdle = new int[10]{20, 21, 22, 23, 24, 25, 26, 27, 28, 29};
        state.enemies[i].animIdleLeft = new int[10]{30, 31, 32, 33, 34, 35, 36, 37, 38, 39};
        state.enemies[i].animAttackRight = new int[5]{40, 41, 42, 43, 44};
        state.enemies[i].animAttackLeft = new int[5]{50, 51, 52, 53, 54};

        state.enemies[i].position = glm::vec3(15, -10, 0);
        state.enemies[i].movement = glm::vec3(0);
        state.enemies[i].acceleration = glm::vec3(0);
        state.enemies[i].speed = 1.5f;

        state.enemies[i].animFrames = 10;
        state.enemies[i].animIndex = 0;
        state.enemies[i].animTime = 0;
        state.enemies[i].animCols = 10;
        state.enemies[i].animRows = 8;

        state.enemies[i].height = 1.6f;
        state.enemies[i].width = 1.6f;
    }

    GLuint sampleTextureID = Util::LoadTexture("sample.png");
    
    sampleIcons[0] = Util::LoadTexture("tv.png");
    sampleIcons[1] = Util::LoadTexture("fireplace.png");
    sampleIcons[2] = Util::LoadTexture("tree.png");
    sampleIcons[3] = Util::LoadTexture("frog.png");
    sampleIcons[4] = Util::LoadTexture("door.png");
    sampleIcons[5] = Util::LoadTexture("microwave.png");
    sampleIcons[6] = Util::LoadTexture("balloon.png");
    sampleIcons[7] = Util::LoadTexture("piano.png");
    sampleIcons[8] = Util::LoadTexture("guitar.png");
    sampleIcons[9] = Util::LoadTexture("drums.png");

    
    sampleSounds[7] = Mix_LoadWAV("8.wav");
    sampleSounds[8] = Mix_LoadWAV("9.wav");
    sampleSounds[9] = Mix_LoadWAV("10.wav");
    
    for (int i = 0; i < level3_WIDTH * level3_HEIGHT; ++i) {
        if (level3_sampleData[i] != -1) {
            cout << "sample" << endl;
            Entity sample;
            sample.entityType = SAMPLE;
            if (sample.textureID == 0) cout << "sample texture missing!" << endl;
            int x = i % level3_WIDTH;
            int y = i / level3_WIDTH;
            if (level3_sampleData[i] == 1)
                sample.sampleType = tv1;
            else if (level3_sampleData[i] == 2)
                sample.sampleType = fireplace2;
            else if (level3_sampleData[i] == 3)
                sample.sampleType = tree3;
            float xPos = x * 1.0f;
            float yPos = -y * 1.0f;
            sample.position = glm::vec3(xPos, yPos, 0);
            sample.textureID = sampleTextureID;
            sample.width = 0.8f;
            sample.height = 0.8f;
            sample.isCollected = false;
            sample.isActive = true;
            localSamples.push_back(sample);
            cout << "Sample position: " << sample.position.x << ", " << sample.position.y << endl;
        }
    }
}
void Level3::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, MAX_ENEMIES, state.map);
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, MAX_ENEMIES, state.map);
        
        if (state.enemies[i].isActive &&
            (state.player->animIndices == state.player->animAttackRight ||
             state.player->animIndices == state.player->animAttackLeft)) {
            float dist = glm::distance(state.player->position, state.enemies[i].position);
            if (dist < 0.5f) {
                state.enemies[i].isActive = false; // Enemy dies
            }
        }
    }

    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);
    static int useCounter = 0;
    static float useCooldown = 0.0f;

    useCooldown -= deltaTime;
    if (keys[SDL_SCANCODE_E] && useCooldown <= 0.0f) {
        useCounter++;
        useCooldown = 0.2f;
    }

    for (Entity& sample : localSamples) {
        if (!sample.isCollected && sample.isActive) {
            float dist = glm::distance(state.player->position, sample.position);
            if (dist < 1.0f && useCounter >= 3) {
                sample.isCollected = true;
                Entity collected = sample;
                collected.isActive = true;
                collected.position = glm::vec3(0);
                state.samples.push_back(collected);
                std::cout << "Collected sample! Total collected: " << state.samples.size() << std::endl;
                useCounter = 0;
                
                if (sample.sampleType >= piano8 && sample.sampleType <= drums10) {
                    int soundIndex = static_cast<int>(sample.sampleType);
                    Mix_PlayChannel(-1, sampleSounds[soundIndex-8], 0);
                }
            }
        }
    }

    if (!state.player->isActive && state.player->numLives > 0) {
        state.player->numLives -= 1;

        if (state.player->numLives > 0) {
            
            
            state.player->position = glm::vec3(10, -10, 0);
            state.player->movement = glm::vec3(0);
            state.player->velocity = glm::vec3(0);
            state.player->isActive = true;

            
            for (int i = 0; i < MAX_ENEMIES; ++i) {
                state.enemies[i].isAttacking = false;
                state.enemies[i].animIndex = 0;
                state.enemies[i].animTime = 0.0f;
            }
        } else {
            
            state.nextScene = 4;
        }
    }

    
    int expectedEnemies = pow(2, currentWave - 1);
    int activeEnemies = 0;

    for (int i = 0; i < MAX_ENEMIES; ++i) {
        if (state.enemies[i].isActive) activeEnemies++;
    }

    if (activeEnemies == 0 && currentWave <= 5) {
        waveDelayTimer += deltaTime;
        if (waveDelayTimer > 2.0f) {
            for (int i = 0, spawned = 0; i < MAX_ENEMIES && spawned < expectedEnemies; ++i) {
                if (!state.enemies[i].isActive) {
                    state.enemies[i].isActive = true;
                    
                    float spawnX = 10.0f + static_cast<float>(rand() % 13);
                    float spawnY = -12.0f + static_cast<float>(rand() % 3);
                    state.enemies[i].position = glm::vec3(spawnX, spawnY, 0);
                    spawned++;
                }
            }
            currentWave++;
            waveDelayTimer = 0.0f;
        }
    } else if (activeEnemies == 0 && currentWave > 5) {
        // All waves complete and no enemies remain
        state.nextScene = 5; // Switch to Level 5 (final scene)
    }
}
void Level3::Render(ShaderProgram *program) {
    glClearColor(0.5f, 0.8f, 1.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT);
    
    Util::DrawText(program, Util::LoadTexture("font1.png"), "Level 1", 0.5f, -0.1f, glm::vec3(0.2, -2, 0));
    Util::DrawText(program, Util::LoadTexture("font1.png"), "Lives " + std::to_string(state.player->numLives), 0.5f, -0.1f, glm::vec3(0.2, -2.5, 0));
    state.map->Render(program);
    
    for (Entity& sample : localSamples) {
        sample.Render(program);
    }
    state.player->Render(program);
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        state.enemies[i].Render(program);
    }
    
    for (int i = 0; i < state.samples.size(); ++i) {
        int sampleIndex = static_cast<int>(state.samples[i].sampleType); // enum to index
        GLuint icon = sampleIcons[sampleIndex];

        float x = -4.5f + (i * 0.8f);
        float y = 3.3f;

        float width = 0.6f;
        float height = 0.6f;

        float vertices[] = {
            x - width/2, y - height/2,
            x + width/2, y - height/2,
            x + width/2, y + height/2,
            x - width/2, y - height/2,
            x + width/2, y + height/2,
            x - width/2, y + height/2
        };

        float texCoords[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        };

        glBindTexture(GL_TEXTURE_2D, icon);
        glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
        glEnableVertexAttribArray(program->positionAttribute);
        glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
        glEnableVertexAttribArray(program->texCoordAttribute);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisableVertexAttribArray(program->positionAttribute);
        glDisableVertexAttribArray(program->texCoordAttribute);
    }
}


