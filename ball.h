/* 
 * File:   ball.h
 * Author: tapin13
 *
 * Created on May 29, 2017, 11:38 PM
 */

#ifndef BALL_H
#define BALL_H

#define S 0.025

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

#endif /* BALL_H */

