#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

#include "common/matrixMath.h"

#include "ball.h"

float ballPositions[] = {
    -S, -S,
    -S, S,
    S, -S,
    S, S
};

const unsigned int ballIndexes[] = {
    0, 1, 2,
    1, 2, 3
};

float stepX = 0.01;
float stepY = 0.01;

GLuint ballVAO; //Vertex Array Object to tell OpenGL that the array is divided into variables of 3 floats each
GLuint ballPositionsVBO; //vertex buffer object (VBO) - array of data - floats; {x,y,z,x,y,z..x,y,z}
GLuint ballIndexesVBO; //vertex buffer object (VBO) - array of data - floats; {x,y,z,x,y,z..x,y,z}

int positionBallLocation;
int matrixBallLocation;

Matrix4 ballMVP = {0.0f};

int initBall(GLuint programId, float aspectRatio) {
    ballPositions[1] *= aspectRatio;
    ballPositions[3] *= aspectRatio;
    ballPositions[5] *= aspectRatio;
    ballPositions[7] *= aspectRatio;
    
    //printf("ball after ratio width: %f\n", ballPositions[1]);
    
    glUseProgram(programId);

    glGenVertexArrays(1, &ballVAO);
    glBindVertexArray(ballVAO);

    positionBallLocation = glGetAttribLocation(programId, "position");
    if(positionBallLocation == -1) {
        printf("positionBatLocation not correct\n");
        return -1;
    }
    
    glGenBuffers(1, &ballPositionsVBO);
    glBindBuffer(GL_ARRAY_BUFFER, ballPositionsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(ballPositions), ballPositions, GL_STATIC_DRAW);
    
    glEnableVertexAttribArray(positionBallLocation);
    glVertexAttribPointer(positionBallLocation, VERTEX_POINTS, GL_FLOAT, GL_FALSE, VERTEX_POINTS * sizeof(float), 0);
    
    glGenBuffers(1, &ballIndexesVBO);
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ballIndexesVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(ballIndexes), ballIndexes, GL_STATIC_DRAW);
    
    matrixBallLocation = glGetUniformLocation(programId, "modelViewProjectionMatrix");
    
    Matrix4Translation(ballMVP, 0, 0, 0);
}

Matrix4 modelMatrix = {0.0f}, M = {1.0f};
float ballLocationX = 0;
float ballLocationY = 0;
const float batPlaceR = 0.1;
//const float ballSpeedUp = 0.005;
const float ballSpeedUp = 0.001;

void updateBall(float batPlace) {
    Matrix4Translation(ballMVP, ballLocationX, ballLocationY, 0);
    if((ballLocationX + ballPositions[4]) >= 0.98) { // ball - 0.05 + wall 0.02 = 1- 0.07 = 0.93
        stepX *= -1;
    }
    ballLocationX += stepX;
    
    if(ballLocationY + ballPositions[3] >= 0.98 || (ballLocationY + ballPositions[1]) <= -0.98) { // ball - 0.05 + wall 0.02 = 1- 0.07 = 0.93
        //printf("(ballLocationY: %f\n", ballLocationY);
        stepY *= -1;
    }
    ballLocationY += stepY;
    
    if((ballLocationX + ballPositions[0])  <= -0.95) { // -0.95 - bat X right
        if((batPlace - batPlaceR) <= (ballLocationY + ballPositions[1])
                && (batPlace + batPlaceR) >= (ballLocationY + ballPositions[1])
                ) {
            //printf("botton\n");
            
            // change direction
            stepX *= -1;
            
            // speed up
            if(stepX > 0) {
                stepX += ballSpeedUp;
            } else {
                stepX -= ballSpeedUp;
            }
            if(stepY > 0) {
                stepY += ballSpeedUp;
            } else {
                stepY -= ballSpeedUp;
            }
        } else if((batPlace - batPlaceR) <= (ballLocationY + ballPositions[3])
                && (batPlace + batPlaceR) >= (ballLocationY + ballPositions[3])
                ) {
            //printf("top\n");
            
            // change direction
            stepX *= -1;
            
            // speed up
            if(stepX > 0) {
                stepX += ballSpeedUp;
            } else {
                stepX -= ballSpeedUp;
            }
            if(stepY > 0) {
                stepY += ballSpeedUp;
            } else {
                stepY -= ballSpeedUp;
            }
        } else {
            //printf("stop ballLocationY: %f, batPlace: %f\n", ballLocationY, batPlace);
            ballLocationX = 0.0f;
            ballLocationY = 0.0f;
            stepX = 0.01f;
            stepY = 0.01f;
        }
    }
}

void renderBall(GLuint programId) {
    glUseProgram(programId);
    glBindVertexArray(ballVAO);
    
    glUniformMatrix4fv(matrixBallLocation, 1, GL_TRUE, ballMVP);
    glDrawElements(GL_TRIANGLES, sizeof(ballIndexes) / sizeof(ballIndexes[0]), GL_UNSIGNED_INT, 0);
}