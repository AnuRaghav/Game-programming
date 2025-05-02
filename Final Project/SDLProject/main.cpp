/**
* Author: Anuraghav Padmaprasad
* Assignment: Final Project
* Date due: 2025-04-25, 11:59pm
* I pledge that I have completed this assignment without
* collaborating with anyone else, in conformance with the
* NYU School of Engineering Policies and Procedures on
* Academic Misconduct.
**/
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

#include <SDL_mixer.h>

#include "Entity.h"
#include "Map.h"

#include <iostream>
#include <vector>

#include "Util.h"

#include "Scene.h"
#include "Menu.h"
#include "Level1.h"
#include "Level2.h"
#include "Level3.h"
#include "Lose.h"

#include "Win.h"

GLuint sampleIcons[12];
Mix_Chunk* sampleSounds[10] = {0};
using namespace std;

SDL_Window* displayWindow;
bool gameIsRunning = true;

int numLives = 3;
float missionPass = 0;

ShaderProgram program;
glm::mat4 viewMatrix, modelMatrix, projectionMatrix;

Mix_Music *music;
Mix_Chunk *jump;


Scene *currentScene;
Scene *sceneList[6];

void SwitchToScene(Scene *scene) {
    currentScene = scene;
    currentScene->Initialize(numLives);
}

void Initialize() {
    SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO);
    displayWindow = SDL_CreateWindow("feline studio", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 640, 480, SDL_WINDOW_OPENGL);
    SDL_GLContext context = SDL_GL_CreateContext(displayWindow);
    SDL_GL_MakeCurrent(displayWindow, context);
    
#ifdef _WINDOWS
    glewInit();
#endif
    
    
    
    program.Load("shaders/vertex_textured.glsl", "shaders/fragment_textured.glsl");
    
    viewMatrix = glm::mat4(1.0f);
    modelMatrix = glm::mat4(1.0f);
    projectionMatrix = glm::ortho(-5.0f, 5.0f, -3.75f, 3.75f, -1.0f, 1.0f);
    
    program.SetProjectionMatrix(projectionMatrix);
    program.SetViewMatrix(viewMatrix);
    
    glUseProgram(program.programID);
    
    glClearColor(0.2f, 0.2f, 0.2f, 1.0f);
    glEnable(GL_BLEND);

    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
 
    if (Mix_OpenAudio(44100, MIX_DEFAULT_FORMAT, 2, 4096) == -1) {
        std::cout << "Mix_OpenAudio failed: " << Mix_GetError() << std::endl;
    }
    Mix_AllocateChannels(16);

    
    music = Mix_LoadMUS("Xtal.wav");
    if (music) {
        Mix_PlayMusic(music, -1);
        Mix_VolumeMusic(MIX_MAX_VOLUME / 4);  
    } else {
        std::cout << "Failed to load Xtal.wav: " << Mix_GetError() << std::endl;
    }

    jump = Mix_LoadWAV("jump.wav");
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
    sampleIcons[10] = Util::LoadTexture("bonus1.png");
    sampleIcons[11] = Util::LoadTexture("bonus2.png");
    
    sampleSounds[0] = Mix_LoadWAV("1.wav");
    sampleSounds[1] = Mix_LoadWAV("2.wav");
    sampleSounds[2] = Mix_LoadWAV("3.wav");
    sampleSounds[3] = Mix_LoadWAV("4.wav");
    sampleSounds[4] = Mix_LoadWAV("5.wav");
    sampleSounds[5] = Mix_LoadWAV("7.wav");
    sampleSounds[6] = Mix_LoadWAV("6.wav");
    sampleSounds[7] = Mix_LoadWAV("8.wav");
    sampleSounds[8] = Mix_LoadWAV("9.wav");
    sampleSounds[9] = Mix_LoadWAV("10.wav");
    
    
    
    for (int i = 0; i < 10; ++i) {
        std::cout << "sampleIcons[" << i << "] = " << sampleIcons[i] << std::endl;
    }
    
    sceneList[0] = new Menu();
    sceneList[1] = new Level1();
    sceneList[2] = new Level2();
    sceneList[3] = new Level3();
    sceneList[4] = new Lose();
    sceneList[5] = new Win();
    SwitchToScene(sceneList[0]);
    
}

void ProcessInput() {
    
    currentScene->state.player->movement = glm::vec3(0);
    
    SDL_Event event;
    while (SDL_PollEvent(&event)) {
        switch (event.type) {
            case SDL_QUIT:
            case SDL_WINDOWEVENT_CLOSE:
                gameIsRunning = false;
                break;
                
            case SDL_KEYDOWN:
                switch (event.key.keysym.sym) {
                    case SDLK_LEFT:
                        // Move the player left
                        break;
                        
                    case SDLK_RIGHT:
                        // Move the player right
                        break;
                    case SDLK_DOWN:
                        break;
                    case SDLK_UP:
                        break;
                        
                    case SDLK_SPACE:
                        // Some sort of action
                        if (currentScene->state.player->collidedBottom) {
                            currentScene->state.player->jump = true;
                            Mix_PlayChannel(-1, jump, 0);
                        }
                        break;
                    case SDLK_RETURN:
                        if (currentScene == sceneList[0]) {
                            currentScene->Update(-1);
                        }
                }
                break;
        }
    }
    
    const Uint8 *keys = SDL_GetKeyboardState(NULL);

    static bool rPressedLastFrame = false;
    bool rPressed = keys[SDL_SCANCODE_R];
    bool attackTriggered = rPressed && !rPressedLastFrame;
    rPressedLastFrame = rPressed;

    static bool ePressedLastFrame = false;
    bool ePressed = keys[SDL_SCANCODE_E];
    bool useItemTriggered = ePressed && !ePressedLastFrame;
    ePressedLastFrame = ePressed;

    if (attackTriggered && !currentScene->state.player->isAttacking) {
        currentScene->state.player->isAttacking = true;
        currentScene->state.player->animIndex = 0;
        currentScene->state.player->animTime = 0.0f;
        currentScene->state.player->animIndices = currentScene->state.player->facingLeft
            ? currentScene->state.player->animAttackLeft
            : currentScene->state.player->animAttackRight;
        currentScene->state.player->animFrames = 4;
    }

    if (useItemTriggered && !currentScene->state.player->isUsingItem) {
        
        currentScene->state.player->isUsingItem = true;
        currentScene->state.player->animIndex = 0;
        currentScene->state.player->animTime = 0.0f;
        currentScene->state.player->animIndices = currentScene->state.player->facingLeft
            ? currentScene->state.player->animUseItemLeft
            : currentScene->state.player->animUseItemRight;
        currentScene->state.player->animFrames = 5;

        
    }

    if (keys[SDL_SCANCODE_LEFT]) {
        currentScene->state.player->movement.x = -1.0f;
        currentScene->state.player->facingLeft = true;
        if (currentScene->state.player->isAttacking || currentScene->state.player->isUsingItem) {
            // Keep current attack or use item animation
        } else {
            currentScene->state.player->animIndices = currentScene->state.player->animLeft;
            currentScene->state.player->animFrames = 10;
        }
    }
    else if (keys[SDL_SCANCODE_RIGHT]) {
        currentScene->state.player->movement.x = 1.0f;
        currentScene->state.player->facingLeft = false;
        if (currentScene->state.player->isAttacking || currentScene->state.player->isUsingItem) {
            // Keep current attack or use item animation
        } else {
            currentScene->state.player->animIndices = currentScene->state.player->animRight;
            currentScene->state.player->animFrames = 10;
        }
    }
    else if(keys[SDL_SCANCODE_DOWN]){
        currentScene->state.player->movement.y = -1.0f;
    }
    else if(keys[SDL_SCANCODE_UP]){
        currentScene->state.player->movement.y = 1.0f;
    }

    if (currentScene->state.player->movement.x == 0 && currentScene->state.player->movement.y == 0 &&
        !currentScene->state.player->isAttacking && !currentScene->state.player->isUsingItem) {
        if (currentScene->state.player->facingLeft) {
            currentScene->state.player->animIndices = currentScene->state.player->animIdleLeft;
        } else {
            currentScene->state.player->animIndices = currentScene->state.player->animIdle;
        }
        currentScene->state.player->animFrames = 8;
    }

    if (glm::length(currentScene->state.player->movement) > 1.0f) {
        currentScene->state.player->movement = glm::normalize(currentScene->state.player->movement);
    }

}

#define FIXED_TIMESTEP 0.0166666f
float lastTicks = 0;
float accumulator = 0.0f;
void Update() {
   float ticks = (float)SDL_GetTicks() / 1000.0f;
   float deltaTime = ticks - lastTicks;
   lastTicks = ticks;
   deltaTime += accumulator;
   if (deltaTime < FIXED_TIMESTEP) {
       accumulator = deltaTime;
       return;
   }
   while (deltaTime >= FIXED_TIMESTEP) {
       
       currentScene->Update(FIXED_TIMESTEP);
       
       deltaTime -= FIXED_TIMESTEP;
   }
   accumulator = deltaTime;
    
    
    viewMatrix = glm::mat4(1.0f);
    viewMatrix = glm::translate(viewMatrix, glm::vec3(
        -currentScene->state.player->position.x,
        -currentScene->state.player->position.y,
        0
    ));
}


void Render() {
    glClear(GL_COLOR_BUFFER_BIT);
    
    program.SetViewMatrix(viewMatrix);
    
    currentScene->Render(&program);
    
    SDL_GL_SwapWindow(displayWindow);
}


void Shutdown() {
    SDL_Quit();
}

int main(int argc, char* argv[]) {
    Initialize();
    
    while (gameIsRunning) {
        ProcessInput();
        Update();

        if (currentScene->state.nextScene >= 0) {
            int next = currentScene->state.nextScene;
            sceneList[next]->state.uiIcons = currentScene->state.uiIcons;
            sceneList[next]->state.samples = currentScene->state.samples;
            if (next == 5 && Mix_PlayingMusic()) {
                Mix_HaltMusic();
            }
            SwitchToScene(sceneList[next]);
        }
        numLives = currentScene->state.player->numLives;

        Render();
    }
    
    Shutdown();
    return 0;
}

