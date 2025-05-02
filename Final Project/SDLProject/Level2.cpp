#include <iostream>
#include <SDL_mixer.h>
static Mix_Chunk* attackSound = nullptr;
#include <cstdlib>
#include <vector>
#include "Level2.h"
#define LEVEL2_WIDTH 30
#define LEVEL2_HEIGHT 20

#define MAX_ENEMIES 16
using namespace std;

static GLuint backgroundTextureID;

extern GLuint sampleIcons[12];
extern Mix_Chunk* sampleSounds[10];


int level2_data[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 20792, 20793, 20793, 20793, 20793, 20793, 20793, 20793, 20793, 20794, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21062, 16761, 16762, 16761, 16762, 16761, 16762, 16761, 16762, 21064, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21062, 17031, 17032, 17031, 17032, 17031, 17032, 17031, 17032, 21064, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21062, 20267, 20267, 20267, 20267, 20267, 20267, 20267, 20267, 21064, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21062, 20267, 20267, 20267, 20260, 20260, 20267, 20267, 20267, 21064, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21062, 20267, 20267, 20267, 20260, 20260, 20267, 20267, 20267, 21064, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21062, 20267, 20267, 20267, 20267, 20267, 20267, 20267, 20267, 21064, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21332, 21333, 21333, 21061, 19184, 19184, 21060, 21333, 21333, 21334, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, 20792, 20793, 20793, 20793, 20793, 20793, 20793, 20793, 20793, 20793, 20793, 20793, 21331, 19184, 19184, 21330, 20793, 20793, 20793, 20793, 20793, 20793, 20793, 20793, 20793, 20793, 20793, 20794, -1,
    -1, 21062, 15692, 15692, 15692, 14591, 14591, 15692, 15692, 15692, 15131, 15140, 15140, 15140, 19184, 19184, 15140, 15140, 15140, 15128, 14073, 14073, 14073, 14073, 14073, 14073, 14073, 14073, 21064, -1,
    -1, 21062, 15962, 15962, 15962, 14861, 14861, 15962, 15962, 15962, 15401, 15410, 15410, 15410, 19184, 19184, 15410, 15410, 15410, 15398, 14343, 14343, 14343, 14343, 14343, 14343, 14343, 14343, 21064, -1,
    -1, 21062, 17827, 17827, 17827, 17827, 17827, 17827, 17827, 17827, 19184, 19184, 19184, 19184, 19184, 19184, 19184, 19184, 19184, 19184, 18107, 18107, 18107, 18107, 18107, 17848, 18107, 18107, 21064, -1,
    -1, 21062, 17827, 17827, 17827, 17827, 17827, 17827, 17827, 17827, 19184, 19184, 19184, 19184, 19184, 19184, 19184, 19184, 19184, 19184, 18107, 18107, 17848, 18107, 18107, 18107, 18107, 18107, 21064, -1,
    -1, 21062, 17827, 17827, 17827, 17827, 17827, 17827, 17827, 17827, 21060, 21333, 21333, 21333, 21333, 21333, 21333, 21333, 21333, 21061, 18107, 18107, 18107, 18107, 18107, 18107, 17848, 18107, 21064, -1,
    -1, 21062, 17827, 17827, 17827, 17827, 17827, 17827, 17827, 17827, 21064, -1, -1, -1, -1, -1, -1, -1, -1, 21062, 18107, 18107, 17848, 18107, 18107, 18107, 18107, 18107, 21064, -1,
    -1, 21062, 17827, 17827, 17827, 17827, 17827, 17827, 17827, 17827, 21064, -1, -1, -1, -1, -1, -1, -1, -1, 21062, 17848, 18107, 18107, 18107, 18107, 18107, 18107, 18107, 21064, -1,
    -1, 21332, 21333, 21333, 21333, 21333, 21333, 21333, 21333, 21333, 21334, -1, -1, -1, -1, -1, -1, -1, -1, 21332, 21333, 21333, 21333, 21333, 21333, 21333, 21333, 21333, 21334, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1


};

int level2_furnitureData[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14664, 14665, 14666, 22992, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 14934, 14935, 14936, 30010, 30011, 20087, 50006, 50007, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 30280, 30281, 29742, 50276, 50277, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 27620, -1, -1, -1, -1, -1, -1, 23559, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26277, -1, -1, -1, -1, -1, 24094, 25483, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 26547, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, 23660, 23661, 23662, -1, -1, 24738, 24739, 24740, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17886, 41892, 41893, 22180, 20313, 22453, 22454, 22455, -1, -1,
    -1, -1, 21761, 21762, 21763, -1, -1, 25008, 25009, 25010, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 18156, 42162, 42163, 22720, 22722, 22723, 22724, 22725, -1, -1,
    -1, -1, 22031, 22032, 22033, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 21740, 21124, -1, -1, -1, -1,
    -1, -1, 22301, 22302, 22303, -1, 21616, 21617, 21618, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 19542, 18459, -1, 20307, 20308, 20309, -1, -1, -1,
    -1, -1, 24741, 24742, 24743, -1, 21886, 21887, 21888, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17915, 19812, 18729, -1, -1, 21670, -1, -1, -1, -1,
    -1, -1, 25011, 25012, 25013, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 18185, 27355, 17376, -1, 22208, 23555, 22209, 26819, -1, -1,
    -1, -1, 25281, 25282, 25283, 17048, -1, 18196, 18795, 18796, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, 17651, -1, 17646, 20084, -1, 22210, -1, 27089, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

int level2_sampleData[] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  4, -1, -1, -1, -1,  5, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,  3, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1,  6, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1
};

void Level2::Initialize(int numLives) {

    state.nextScene = -1;

    
    GLuint mapTextureID = Util::LoadTexture("global.png");
    
    state.map = new Map(LEVEL2_WIDTH, LEVEL2_HEIGHT, level2_data, level2_furnitureData, mapTextureID, 1.0f, 270, 215);
    
    state.player = new Entity();
    state.player->entityType = PLAYER;
    state.player->position = glm::vec3(15, -11, 0);
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

    
    attackSound = Mix_LoadWAV("attack.wav");
    if (!attackSound) {
        std::cout << "Failed to load attack.wav: " << Mix_GetError() << std::endl;
    }
    
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

    for (int i = 0; i < LEVEL2_WIDTH * LEVEL2_HEIGHT; ++i) {
        if (level2_sampleData[i] != -1) {
            cout << "sample" << endl;
            Entity sample;
            sample.entityType = SAMPLE;
            if (sample.textureID == 0) cout << "sample texture missing!" << endl;
            int x = i % LEVEL2_WIDTH;
            int y = i / LEVEL2_WIDTH;
            sample.sampleType = static_cast<SampleType>(level2_sampleData[i]);
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
void Level2::Update(float deltaTime) {
    state.player->Update(deltaTime, state.player, state.enemies, MAX_ENEMIES, state.map);
    for (int i = 0; i < MAX_ENEMIES; ++i) {
        state.enemies[i].Update(deltaTime, state.player, state.enemies, MAX_ENEMIES, state.map);
        if (state.enemies[i].isActive &&
            (state.player->animIndices == state.player->animAttackRight ||
             state.player->animIndices == state.player->animAttackLeft)) {
            float dist = glm::distance(state.player->position, state.enemies[i].position);
            if (dist < 0.5f) {
                state.enemies[i].isActive = false;
            }
        }
    }

    
    static bool attackSoundPlayed = false;
    if (!attackSoundPlayed &&
        (state.player->animIndices == state.player->animAttackRight ||
         state.player->animIndices == state.player->animAttackLeft)) {
        if (attackSound) Mix_PlayChannel(-1, attackSound, 0);
        attackSoundPlayed = true;
    }
    if (state.player->animIndices != state.player->animAttackRight &&
        state.player->animIndices != state.player->animAttackLeft) {
        attackSoundPlayed = false;
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
                state.samples.push_back(sample);

                
                Entity iconEntity;
                iconEntity.entityType = UI_ICON;
                iconEntity.textureID = sampleIcons[static_cast<int>(sample.sampleType)];
                if (iconEntity.textureID == 0) {
                    std::cout << "texture is 0 for sampleType = " << std::endl;
                }
//                cout << "texgutre id" <<iconEntity.textureID  << endl;
                iconEntity.width = 0.6f;
                iconEntity.height = 0.6f;
                iconEntity.isActive = true;
                iconEntity.position = glm::vec3(-4.5f + (state.uiIcons.size() * 0.8f), 3.3f, 0);
                
                state.uiIcons.push_back(iconEntity);

                if (sample.sampleType >= tv1 && sample.sampleType <= drums10) {
                    int soundIndex = static_cast<int>(sample.sampleType);
                    Mix_PlayChannel(-1, sampleSounds[soundIndex], 0);
                }
            
            }
        }
    }

    if (!state.player->isActive && state.player->numLives > 0) {
        state.player->numLives -= 1;

        if (state.player->numLives > 0) {
            
            state.player->position = glm::vec3(10, -11, 0);
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
                    
                    float spawnX = 10.0f + static_cast<float>(rand() % 16);
                    float spawnY = -11.0f + static_cast<float>(rand() % 2);
                    state.enemies[i].position = glm::vec3(spawnX, spawnY, 0);
                    spawned++;
                }
            }
            currentWave++;
            waveDelayTimer = 0.0f;
        }
    }
    else if (activeEnemies == 0 && currentWave > 5) {
        state.nextScene = 3;
    }
}
void Level2::Render(ShaderProgram *program) {
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
    
    
    program->SetProjectionMatrix(glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f));
    program->SetViewMatrix(glm::mat4(1.0f));
    program->SetModelMatrix(glm::mat4(1.0f));
    
    
//    for (int i = 0; i < state.uiIcons.size(); ++i) {
    int i = 0;
    for (Entity& icon : state.uiIcons){
        

        float x = -4.5f + i * 0.8f;
        i++;
        float y = 3.3f;
        float width = 0.6f;
        float height = 0.6f;

        float vertices[] = {
            x - width / 2, y - height / 2,
            x + width / 2, y - height / 2,
            x + width / 2, y + height / 2,
            x - width / 2, y - height / 2,
            x + width / 2, y + height / 2,
            x - width / 2, y + height / 2
        };

        float texCoords[] = {
            0.0f, 1.0f,
            1.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 1.0f,
            1.0f, 0.0f,
            0.0f, 0.0f
        };

        glBindTexture(GL_TEXTURE_2D, icon.textureID);
        glVertexAttribPointer(program->positionAttribute, 2, GL_FLOAT, false, 0, vertices);
        glEnableVertexAttribArray(program->positionAttribute);
        glVertexAttribPointer(program->texCoordAttribute, 2, GL_FLOAT, false, 0, texCoords);
        glEnableVertexAttribArray(program->texCoordAttribute);
        glDrawArrays(GL_TRIANGLES, 0, 6);
        glDisableVertexAttribArray(program->positionAttribute);
        glDisableVertexAttribArray(program->texCoordAttribute);
    }
}

