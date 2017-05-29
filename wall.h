/* 
 * File:   wall.h
 * Author: tapin13
 *
 * Created on May 21, 2017, 11:13 PM
 */

#ifndef WALL_H
#define WALL_H

#define VERTEX_POINTS 2

#define WALL_WIDTH 0.02
#define WALL_POSITION (1 - WALL_WIDTH)

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

int initWall(GLuint programId);
int drawWall(GLuint programId);

#endif /* WALL_H */

