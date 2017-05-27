/* 
 * Author: tapin13
 *
 */

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "common/loadShader.c"
#include "common/matrixMath.c"

GLuint programId;

#include "wall.c"
#include "bat.c"
#include "ball.c"

#define true  1
#define false 0

#define WINDOW_WIDTH 640
#define WINDOW_HEIGHT 480

#define CIRCLE_POINTS 12
#define VERTEX_POINTS 2

struct point {
    float x, y;
};

struct square {
    struct point left_buttom;
    struct point left_top;
    struct point right_top;
    struct point right_buttom;
    float position;
    float step;
};

struct ball {
    float x, y;
    float radius;
    float step_x;
    float step_y;
    int lives;
    struct point points[CIRCLE_POINTS];
};

struct ball gameBall = { 
    0.0, 0.0, // x, y
    0.05, // radius
    0.05, // step_x
    0.015, // step_y
    3 // lives
};

struct square bat = {
    -0.99, 0.0, // left_buttom
    -0.99, 0.2, // left_top
    -0.95, 0.2, // right_top
    -0.95, 0.0, // right_buttom
    0.0, // position
    0.08 // step
};

int score = 0;

int init_resources() {
    return 1;
}

void drawScore() {
    /*
    char txt[3];
    sprintf(txt, "%d", score);
    int i;
    for(i = 0; i < strlen(txt); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, txt[i]);
    }
    */
}

void drawLives() {
    /*
    char txt[3];
    sprintf(txt, "%d", gameBall.lives);
    int i;
    for(i = 0; i < strlen(txt); i++) {
        glutBitmapCharacter(GLUT_BITMAP_HELVETICA_18, txt[i]);
    }
    */
}

void gameOver() {
    /*
    glClearColor(1.0, 1.0, 1.0, 1.0);
    glClear(GL_COLOR_BUFFER_BIT);
    
    glColor3d(1.0, 0.0, 0.0);
    
    glBegin(GL_LINES);
        glVertex2f(-1.0, 1.0);
        glVertex2f(0.99, -0.99);
    glEnd();
    
    glBegin(GL_LINES);
        glVertex2f(1.0, 1.0);
        glVertex2f(-1.0, -1.0);
    glEnd();
    
    glutSwapBuffers();
    
    sleep(1);
    */
}

void updateGame() {
    /*
    if(gameBall.lives == 0) {
        gameOver();
        glutLeaveMainLoop();
    }

    // Ball hit the wall
    if(gameBall.x > (1.0 - gameBall.radius)) { // || gameBall.x < (-1.0 + gameBall.radius)
        gameBall.step_x *= -1;
    }
    
    if(gameBall.y > (0.97 - gameBall.radius) || gameBall.y <= (-0.97 + gameBall.radius)) {
        gameBall.step_y *= -1;
    }
    
    // Ball out of table
    if(gameBall.x < (-1.0 + gameBall.radius)) {
        gameBall.lives--;
        if(gameBall.lives > 0) {
            // set default values
            gameBall.x = 0.0;
            gameBall.y = 0.0;
            gameBall.step_x = 0.05;
            gameBall.step_y = 0.05;
            sleep(3);
        }
    }
    
    // Ball hit the bat
    if(bat.right_top.x >= (gameBall.x - gameBall.radius) 
            && (bat.right_top.y + bat.position) >= (gameBall.y)
            && (bat.right_buttom.y + bat.position) <= (gameBall.y)
            ) {
        gameBall.step_x *= -1;
        
        // speed up the ball
        gameBall.step_x += 0.001;
        gameBall.step_y += 0.001;
        
        score++;
    }

    //gameBall.x += gameBall.step_x;
    //gameBall.y += gameBall.step_y;
    
    glutPostRedisplay();
    */
}

void free_resources() {
    
}

float batPlace = 0.0f;

void keyboardInput(GLFWwindow *window) {
    int state;
    
    if (glfwGetKey(window,GLFW_KEY_ESCAPE) == GLFW_PRESS) {
        glfwSetWindowShouldClose(window,true);
        
        return;
    }    
    
    state = glfwGetKey(window, GLFW_KEY_LEFT);
    if (state == GLFW_PRESS) {
        if((0.02 + 0.1 + 0.02) <= (1 + batPlace)) {
            batPlace -= 0.01;
            //printf("left\n");
            //printf("batPlace: %f\n", batPlace);
        } else {
            //printf("stop\n");
        }
        return;
    }
    
    state = glfwGetKey(window, GLFW_KEY_RIGHT);
    if (state == GLFW_PRESS) {
        if((0.02 + 0.1 + 0.02) <= (1 - batPlace)) {
            batPlace += 0.01;
            //printf("right\n");
            //printf("batPlace: %f\n", batPlace);
        } else {
            //printf("stop\n");
        }
        return;
    }
}    

float aspectRatio;

void window_size_callback(GLFWwindow *window, int width, int height) {
    //aspectRatio = (float)width / (float)height;
    printf("window_size_callback\n");
}

int width, height;

int main(int argc, char** argv) {
    
    if(!glfwInit()) {
        fprintf(stderr, "Failed to initialize GLFW.");
        return EXIT_FAILURE;
    }
    
    glfwWindowHint(GLFW_SAMPLES, 4); // 4x antialiasing
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3); // OpenGL 3.3
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE); // Don't use old openGL
    
    GLFWwindow *window;
    window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hit the ball", NULL, NULL);
    //window = glfwCreateWindow(WINDOW_WIDTH, WINDOW_HEIGHT, "Hit the ball", glfwGetPrimaryMonitor(), NULL); // Full Screen
    if(window == NULL) {
        fprintf(stderr, "Failed to open GLFW windows. If you have an Intel GPU, they are not 3.3 compatible.");
        return EXIT_FAILURE;
    }
    
    glfwMakeContextCurrent(window);
    glewExperimental = true;
    if(glewInit() != GLEW_OK) {
        fprintf(stderr, "Failed to init GLEW");
        return EXIT_FAILURE;
    }
    
    // Ensure we can capture Esc.
    glfwSetInputMode(window, GLFW_STICKY_KEYS, GL_TRUE);
    
    
    glfwGetWindowSize(window, &width, &height);    
    
    float aspectRatio = (float)width / (float)height;
    //printf("aspectRatio: %f\n", aspectRatio);
    
    glfwSetWindowSizeCallback(window, window_size_callback);
    
    glfwSwapInterval(1);    
    
    /*************************************************************************/
    
    programId = loadShader("shaders/vertex.sh", "shaders/fragment.sh");
    if(programId == -1) {
        printf("Error load shaders\n");
        return -1;        
    }
    
    initWall();
    
    initBat();
    
    initBall(aspectRatio);
    
    glClearColor(0.0f, 0.0f, 0.0f, 0.0f);    
    
    /***/
    
    static double limitFPS = 1.0 / 60.0;
    double lastTime = glfwGetTime();
    double timer = lastTime;
    double deltaTime = 0.0;
    double nowTime = 0.0;
    unsigned int frames = 0;
    unsigned int updates = 0;
    
    /***/    
    
    while(glfwGetKey(window, GLFW_KEY_ESCAPE) != GLFW_PRESS && glfwWindowShouldClose(window) == 0) {
        
        nowTime = glfwGetTime();
        deltaTime += (nowTime - lastTime) / limitFPS;
        lastTime = nowTime;

        glClear(GL_COLOR_BUFFER_BIT);
        
        drawWall();
        
        drawBat(batPlace);

        while(deltaTime >= 1.0) {
            updateBall(batPlace);
            
            updates++;
            deltaTime -= 1.0;
        }

        renderBall();
        
        keyboardInput(window);
        
        glfwSwapBuffers(window);
        
        frames++;
        
        if(glfwGetTime() - timer > 1.0) {
            timer++;
            //printf("FPS: %u, Updates: %u\n", frames, updates);
            updates = 0;
            frames = 0;
        }        
        
        glfwPollEvents();
    }
    
    glDisableVertexAttribArray(0);
    
    /*************************************************************************/
    
    glfwDestroyWindow(window);
    glfwTerminate();    
    
    return (EXIT_SUCCESS);    
    
    /*************************************************************************/
    
    /*
    // Fill ball array
    const float angle = 2.1 * 3.1416 / CIRCLE_POINTS;
    float drawAngle = 0.0;
    int point;
    for(point = 0; point < CIRCLE_POINTS; point++) {
        gameBall.points[point].x = floor(gameBall.radius * cos(drawAngle) * 100) / 100;
        gameBall.points[point].y = floor(gameBall.radius * sin(drawAngle) * 100) / 100;
        drawAngle += angle;
    }
    */
}