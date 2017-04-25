#include "main.h"

/************************************************
 MAIN PROGRAM
************************************************/

int main(int argc, char** argv)
{
    if (!glfwInit())
        exit(EXIT_FAILURE);

    window = glfwCreateWindow(windowW, windowH, windowTitle, NULL, NULL);

    glfwWindowHint(GLFW_VISIBLE, GL_FALSE);
    context2 = glfwCreateWindow	(1, 1, "Context 2", NULL, window);

    glfwMakeContextCurrent(window);

    initGlutCallbacks();

    GLenum res = glewInit();
    if (res != GLEW_OK) {
      fprintf(stderr, "GLEW Error: '%s'\n", glewGetErrorString(res));
      return 1;
    }

    //glClearColor(102.0f/256.0f, 149.0f/256.0f, 239.0f/256.0f, 1.0f);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);

    glEnable(GL_BLEND);
    glEnable(GL_TEXTURE_2D);
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);
    gluOrtho2D(0, windowW, 0, windowH);

    //Init OpenAL
    alutInit(&argc, argv);

    //Initializations
    initialize();
    loadContent();

    //Init Main Loop
    while (!glfwWindowShouldClose(window))
    {
        mainLoop();
    }

    //Unload content
    unloadContent();

    alutExit();
    std::cout << "alutExit()\n";

    glfwDestroyWindow(context2);
    glfwDestroyWindow(window);
    glfwTerminate();

    return 0;
}

/************************************************
 MAIN FUNCTIONS
************************************************/

void initialize()
{
    //Initialize random seed
    srand (time(NULL));

    screenMng = new ScreenManager();
    screenMng->initialize(windowW, windowH, keyStates, context2);
}

void loadContent()
{

}

void unloadContent()
{
    screenMng->unload();
}

void update(float gameTime)
{
    screenMng->update(gameTime);

    int newChangeTime = (int)gameTime;
    if (newChangeTime - oldChangeTime > changeTime)
    {
        oldChangeTime = newChangeTime;

        ch = (++ch)%26;
    }
}

void draw()
{
    glClear(GL_COLOR_BUFFER_BIT);

    screenMng->draw();

    glfwSwapBuffers(window);
}

void mainLoop()
{
    //Check for inputs
    glfwPollEvents();

    //Update
    clock_t time = clock();
    update((float)time / (CLOCKS_PER_SEC/1000));

    //Draw
    draw();

    //Calculates FPS and show at the window title
    float newTime = (float)time / CLOCKS_PER_SEC;
    float dt  = newTime - oldTime;
    oldTime = newTime;

    char buffer[8];
    //itoa((int)calcFPS(dt), buffer, 10);
    sprintf(buffer, "%d", (int)calcFPS(dt));

    std::string a = std::string(windowTitle);
    std::string b = " (";
    std::string c = std::string(buffer);
    std::string d = " FPS)";

    glfwSetWindowTitle(window, (a + b + c + d).c_str());
}


/************************************************
 CALLBACKS
************************************************/

static void key_callback(GLFWwindow* window, int key, int scancode, int action, int mods)
{
    if (action == GLFW_PRESS)
    {
        keyStates[key] = true;
    }
    else if (action == GLFW_RELEASE)
    {
        keyStates[key] = false;
    }
}


/************************************************
 INITIALIZATIONS
************************************************/

void initGlutCallbacks()
{
    glfwSetKeyCallback(window, key_callback);
}


/************************************************
 FPS
************************************************/

float calcFPS(float dt)
{
    fpsSamples[currentSample] = 1.0f / dt;

    currentSample = (currentSample+1)%NUM_FPS_SAMPLES;

    float fps = 0;
    for (int i = 0; i < NUM_FPS_SAMPLES; i++)
    {
        fps += fpsSamples[i];
    }

    fps /= NUM_FPS_SAMPLES;

    return fps;
}
