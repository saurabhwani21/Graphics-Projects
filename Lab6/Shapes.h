//
// Shapes.h
//
// Prototypes for shape-drawing functions.
//
// This file should not be modified by students.
//

#ifndef _SHAPES_H_
#define _SHAPES_H_

#include "Canvas.h"
#include "Buffers.h"

// Macros for object and shading selection
#define OBJ_QUAD	0
#define OBJ_TEAPOT	1
#define OBJ_SPHERE	2

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
