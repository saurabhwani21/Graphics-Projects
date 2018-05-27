//
// Shapes.h
//
// Prototypes for shape-drawing functions.
//
// Modified by: Saurabh Anant Wani (saw4058)
//

#ifndef _SHAPES_H_
#define _SHAPES_H_

#include "Canvas.h"
#include "Buffers.h"

// Macros for object and shading selection
#define OBJ_TEAPOT	1
#define OBJ_TEACUP	2
#define OBJ_SPOON	3
#define OBJ_PLATE	4
#define OBJ_GLASS	5
#define OBJ_COOKIE1	6
#define OBJ_COOKIE2	7
#define OBJ_COOKIE3	8
#define OBJ_COOKIE4	9
#define OBJ_COOKIE5	10
#define OBJ_BAGEL1	11
#define OBJ_BAGEL2	12
#define OBJ_APPLETEAPOT	13
#define OBJ_APPLEPLATE  14
#define OBJ_FERN1	15	
#define OBJ_FERN2	16
#define OBJ_FERN3	17	
#define OBJ_TABLE	18	


///
// drawShape
//
// Invoked whenever an object must be redrawn
//
// @param tshader - shader program for texture mapping
// @param pshader - shader program for Phong shading
// @param obj     - which object is being drawn
// @param bset    - the BufferSet containing the object's data
///
void drawShape( GLuint tshader, GLuint pshader, int obj, BufferSet &bset );

///
// Make the desired shape
//
// @param choice - which shape to make
// @param C      - the Canvas we'll use
///
void makeShape( int choice, Canvas &C );

#endif
