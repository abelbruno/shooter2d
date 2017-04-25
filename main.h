#ifndef __MAIN_H__
#define __MAIN_H__

#include <GL/glew.h>

#include <ctime>
#include <vector>
#include <string>
#include <cstdio>
#include <cstdlib>
#include <iostream>
#include <GLFW/glfw3.h>
#include <AL/al.h>
#include <AL/alut.h>

#include "util/game_util.h"
#include "StateManagement/screenmanager.h"

/***********************************************
* CONSTANTS
************************************************/

const char *windowTitle = "Shooter 2D";

static const int NUM_FPS_SAMPLES = 64;


/***********************************************
* VARIABLES
************************************************/

//Window
GLFWwindow* window;
GLFWwindow* context2;
unsigned int windowW = 800;
unsigned int windowH = 480;

//Time
float fpsSamples[NUM_FPS_SAMPLES];
int currentSample = 0;
float oldTime = 0;

//Input
bool *keyStates = new bool[512];

//Variables
unsigned char ch  = 0;
unsigned char ch2 = 65;
int changeTime = 1000;
int oldChangeTime = 0;

//Screens
ScreenManager *screenMng;

/***********************************************
* FUNCTION PROTOTYPES
************************************************/

//Callbacks
static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods);

//Main Funcitons
void initialize();
void loadContent();
void unloadContent();
void update(float gameTime);
void draw();
void mainLoop();

//Initializations
void initGlutCallbacks();

//FPS
float calcFPS(float dt);

#endif // __MAIN_H__
