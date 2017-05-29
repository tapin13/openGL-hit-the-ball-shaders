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

int initWall(GLuint programId);
int drawWall(GLuint programId);

#endif /* WALL_H */

