/* 
 * File:   ball.h
 * Author: tapin13
 *
 * Created on May 29, 2017, 11:38 PM
 */

#ifndef BALL_H
#define BALL_H

#define VERTEX_POINTS 2

#define S 0.025


int initBall(GLuint programId, float aspectRatio);

void updateBall(float batPlace);

void renderBall(GLuint programId);

#endif /* BALL_H */

