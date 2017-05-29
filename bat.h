/* 
 * File:   bat.h
 * Author: tapin13
 *
 * Created on May 29, 2017, 11:37 PM
 */

#ifndef BAT_H
#define BAT_H

const float batPositions[][VERTEX_POINTS] = {
    { -0.97f, -0.1f }    // bottom right
    , { -0.97f, 0.1f }   // top right
    , { -0.95f, -0.1f }  // bottom left
    , { -0.95f, 0.1f }   // top let
};

const unsigned int batIndexes[] = {
    0, 1, 2, 
    1, 2, 3 
};

#endif /* BAT_H */

