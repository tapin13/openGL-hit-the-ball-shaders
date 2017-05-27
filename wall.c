#include "wall.h"

#include <stdio.h>
#include <stdlib.h>
#include <math.h>

#include <GL/glew.h>
#include <GLFW/glfw3.h>

const float wallPositions[][VERTEX_POINTS] = {
//    { -1.0f, -1.0f },    // bottom right
//    { -1.0f, 1.0f },   // top right
//    { -WALL_POSITION, -1.0f },  // bottom left
//    { -WALL_POSITION, 1.0f },   // top let

    { WALL_POSITION, -1.0f }    // bottom right
    , { WALL_POSITION, 1.0f }   // top right
    , { 1.0f, -1.0f }  // bottom left
    , { 1.0f, 1.0f }   // top let

    , { -1.0f, 1.0f }    // bottom right
    , { 1.0f, 1.0f }   // top right
    , { -1.0f, WALL_POSITION }  // bottom left
    , { 1.0f, WALL_POSITION }   // top let

    , { -1.0f, -WALL_POSITION }    // bottom right
    , { 1.0f, -WALL_POSITION }   // top right
    , { -1.0f, -1.0f }  // bottom left
    , { 1.0f, -1.0f }   // top let
};

const unsigned int wallIndexes[] = {
    0, 1, 2, 
    1, 2, 3 

    , 4, 5, 6, 
    5, 6, 7 

    , 8, 9, 10, 
    9, 10, 11 
            
//    ,12, 13, 14, 
//    13, 14, 15 
};

    // Vertex Buffer Object,  Vertex Array Object
    //  Vertex Array Objects (VAO). 
    //  VAOs store all of the links between the attributes and your VBOs with raw vertex data.
    //  As soon as you've bound a certain VAO, every time you call glVertexAttribPointer, 
    //  that information will be stored in that VAO. This makes switching between 
    //  different vertex data and vertex formats as easy as binding a different VAO! 
    //  Just remember that a VAO doesn't store any vertex data by itself, it just 
    //  references the VBOs you've created and how to retrieve the attribute 
    //  values from them.
    // !!!! Since only calls after binding a VAO stick to it, make sure that 
    // you've created and bound the VAO at the start of your program. !!!!!!!!
    // Any vertex buffers and element buffers bound before it will be ignored.

    
GLuint wallVAO;

GLuint positionLocation;

GLuint wallPositionsVBO; 
GLuint wallIndexesVBO; 

GLuint matrixWallLocation;

int initWall() {
    glUseProgram(programId);

    positionLocation = glGetAttribLocation(programId, "position");
    if(positionLocation == -1) {
        printf("positionLocation not correct\n");
        return -1;
    }
    
    glGenVertexArrays(1, &wallVAO);
    glGenBuffers(1, &wallPositionsVBO);
    glGenBuffers(1, &wallIndexesVBO);
    
    glBindVertexArray(wallVAO);

    glBindBuffer(GL_ARRAY_BUFFER, wallPositionsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(wallPositions), wallPositions, GL_STATIC_DRAW);

    glVertexAttribPointer(positionLocation, VERTEX_POINTS, GL_FLOAT, GL_FALSE, VERTEX_POINTS * sizeof(float), 0);
    glEnableVertexAttribArray(positionLocation);

    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, wallIndexesVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(wallIndexes), wallIndexes, GL_STATIC_DRAW);
    
    matrixWallLocation = glGetUniformLocation(programId, "modelViewProjectionMatrix");
}

int drawWall() {
    Matrix4 MVP = {0.0f};
    
    glUseProgram(programId);
    
    glBindVertexArray(wallVAO);

    Matrix4Translation(MVP, 0, 0, 0);
    
    glUniformMatrix4fv(matrixWallLocation, 1, GL_TRUE, MVP);    
    
    glDrawElements(GL_TRIANGLES, sizeof(wallIndexes) / sizeof(wallIndexes[0]), GL_UNSIGNED_INT, 0);
}
