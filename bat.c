#include "bat.h"

int positionBatLocation;
GLint matrixLocation;

GLuint batVAO;
GLint batPositionsVBO, batIndexesVBO;

int initBat(GLuint programId) {
    glUseProgram(programId);    

    positionBatLocation = glGetAttribLocation(programId, "position");
    if(positionBatLocation == -1) {
        printf("positionBatLocation not correct\n");
        return -1;
    }
    
    glGenVertexArrays(1, &batVAO);
    glGenBuffers(1, &batPositionsVBO);
    glGenBuffers(1, &batIndexesVBO);
    glBindVertexArray(batVAO);
    
    glBindBuffer(GL_ARRAY_BUFFER, batPositionsVBO);
    glBufferData(GL_ARRAY_BUFFER, sizeof(batPositions), batPositions, GL_STATIC_DRAW);
    glVertexAttribPointer(positionBatLocation, VERTEX_POINTS, GL_FLOAT, GL_FALSE, VERTEX_POINTS * sizeof(float), 0);
    glEnableVertexAttribArray(positionBatLocation);
    
    glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, batIndexesVBO);
    glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(batIndexes), batIndexes, GL_STATIC_DRAW);
    
    matrixLocation = glGetUniformLocation(programId, "modelViewProjectionMatrix");
}

void drawBat(GLuint programId, float batPlace) {
    glUseProgram(programId);    
    glBindVertexArray(batVAO);
    
    Matrix4 MVP = {0.0f};
    
    Matrix4Translation(MVP, 0, batPlace, 0);
    
    glUniformMatrix4fv(matrixLocation, 1, GL_TRUE, MVP);
    
    glDrawElements(GL_TRIANGLES, sizeof(batIndexes) / sizeof(batIndexes[0]), GL_UNSIGNED_INT, 0);
}
