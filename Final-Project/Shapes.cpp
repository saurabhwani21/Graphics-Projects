//
//  Shapes.cpp
//
//  Created by Warren R. Carithers 2018/04/19.
//  Based on earlier versions by Warren R. Carithers and Joe Geigel.
//  Copyright 2018 Rochester Institute of Technology.  All rights reserved.
//
//  Contributor:  Saurabh Anant Wani (saw4058)
//
//  Reference: http://www.opengl-tutorial.org/beginners-tutorials/tutorial-7-model-loading/
//  Routines for shape-drawing functions.
//
//  This file should only be modified if you are replacing the Phong-
//  shaded version of the sphere with a texture-mapped version, and
//  in that case only the makeSphere() and drawShape() functions should
//  be changed.
//


using namespace std;
#include <cmath>
#include <string>
#include <fstream>
#include <iostream>
#include <cstring> 
#include "Canvas.h"
#include "Shapes.h"
#include "Lighting.h"
#include "Textures.h"
#include "Viewing.h"

vector< Vertex > vertex;
//
// Create the specified object
//
static void makeObject(Canvas &C, vector<unsigned int> vertexIndice)
{   
    int tempIndex, firstPoint, secondPoint, thirdPoint,norm1, norm2, norm3, index=0;
    while(index<vertexIndice.size()/3)
    {
	// Calculating the three vertex's base indices
	tempIndex       = index * 3;
        firstPoint      = vertexIndice[tempIndex  ];     
        secondPoint     = vertexIndice[tempIndex+1]; 
        thirdPoint      = vertexIndice[tempIndex+2]; 
	Vertex v1       = {vertex[firstPoint] .x,  vertex[firstPoint].y,  vertex[firstPoint].z};
        Vertex v2       = {vertex[secondPoint].x, vertex[secondPoint].y, vertex[secondPoint].z};
        Vertex v3       = {vertex[thirdPoint] .x,  vertex[thirdPoint].y,  vertex[thirdPoint].z};
	// Calculating the texture coordinate's base indices
        norm1           = vertexIndice[tempIndex  ];     
        norm2           = vertexIndice[tempIndex+1]; 
        norm3           = vertexIndice[tempIndex+2]; 
        // In order to align horizontally mapping the Z to Y of texture image
        UVcoord c1      = {vertex[norm1].x, vertex[norm1].z, 0};
        UVcoord c2      = {vertex[norm2].x, vertex[norm2].z, 0};
        UVcoord c3      = {vertex[norm3].x, vertex[norm3].z, 0};					  
	C.addTriangleWithUV(v1, c1, v2, c2, v3, c3);
	index++;
    }
}


//
// Reads the object file for the object information
//
void loadMesh(char const * path, Canvas &C, int choice, vector<unsigned int> &vertexIndice)
{
	char header[128];
	FILE * file = fopen(path, "r");
	if(file==NULL)
	{
		printf("Error: Unable to locate the file!\n");
		return;
	}
	while(1)
	{
		// Reading the line's 1st word and checking 
		// if end of file reached, then break from the loop.
		if (fscanf(file, "%s", header) == EOF)
		{break;}
		// Retrieving the vertices
		if (strcmp(header,"v")==0)
		{
			Vertex currentVertice;
			fscanf(file, "%f %f %f\n", &currentVertice.x, &currentVertice.y, &currentVertice.z );
			vertex.push_back(currentVertice);
		}
		// Read triangle vertex and normal indices.
		else if (strcmp(header,"f")==0)
		{
			unsigned int vertexInd[3];
			unsigned int normalInd[3];
			fscanf(file, "%d//%d %d//%d %d//%d\n", &vertexInd[0], &normalInd[0], &vertexInd[1], &normalInd[1], &vertexInd[2], &normalInd[2] );			
			// Pushing vertex indices to buffers.
			vertexIndice.push_back(vertexInd[0]-1);
			vertexIndice.push_back(vertexInd[1]-1);
			vertexIndice.push_back(vertexInd[2]-1);
		}
	}	
	makeObject( C , vertexIndice);
	// Clearing buffer
	vertex.clear();
}


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
void drawShape( GLuint tshader, GLuint pshader, int obj, BufferSet &bset ) {

    // extern declarations for things defined in the main
    // program source file that we need to use here
    extern void selectBuffers( GLuint, BufferSet & );
    extern GLfloat angles;
    extern GLfloat xlate[3];
   if(obj == OBJ_TABLE)
   {
 	// the quad is a texture-mapped shape
        glUseProgram( tshader );
        // set up viewing and projection parameters
        setUpFrustum( tshader );
        // set up the texture information
        setUpTexture( tshader, OBJ_TABLE );
        // set up the camera
        setUpCamera( tshader,
            0.2f, 3.0f, 6.5f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        );
	// set up the transform
        setUpTransforms( tshader,
           2.0f, 2.0f, 2.0f,
           angles, angles, angles,
           1.0f, -0.8f, -1.5f );
        // draw it
        selectBuffers( tshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
   }
   else
   {
        glUseProgram( pshader );
        // set up viewing and projection parameters
        setUpFrustum( pshader );
        // set up the camera
        setUpCamera( pshader,
            0.2f, 3.0f, 6.5f,
            0.0f, 1.0f, 0.0f,
            0.0f, 1.0f, 0.0f
        );
        setUpTransforms( pshader,
            2.0f, 2.0f, 2.0f,
            angles, angles, angles,
            1.0f, -0.8f, -1.5f );
    switch( obj ) 
    {
     case OBJ_SPOON:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_SPOON );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_TEACUP:  
	// set up the Phong shading information
        setUpPhong( pshader, OBJ_TEACUP );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_TEAPOT:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_TEAPOT );

        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_PLATE:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_PLATE );
       // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_GLASS:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_GLASS );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_COOKIE1:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_COOKIE1 );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_COOKIE2:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_COOKIE2 );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_COOKIE3:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_COOKIE3 );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_COOKIE4:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_COOKIE4 );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_COOKIE5:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_COOKIE5 );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_BAGEL1:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_BAGEL1 );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_BAGEL2:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_BAGEL2 );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_APPLETEAPOT:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_APPLETEAPOT );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_APPLEPLATE:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_APPLEPLATE );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_FERN1:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_FERN1 );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_FERN2:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_FERN2 );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      case OBJ_FERN3:
        // set up the Phong shading information
        setUpPhong( pshader, OBJ_FERN3 );
        // draw it
        selectBuffers( pshader, bset );
        glDrawElements( GL_TRIANGLES, bset.numElements,
            GL_UNSIGNED_INT, (void *)0 );
        break;

      default:
	cerr << "drawShape: unknown object " << obj << " - ignoring" << endl;

    }
   }
}

///
// Make the desired shape
//
// @param choice - which shape to make
// @param C      - the Canvas we'll use
///
void makeShape( int choice, Canvas &C )
{
    vector<unsigned int> vertexIndices;
    switch( choice ) 
    {
	case OBJ_SPOON:
		loadMesh( "spoon.obj" , C , OBJ_SPOON, vertexIndices);		
		break;
	case OBJ_TEACUP:
		loadMesh( "teacup.obj" , C , OBJ_TEACUP, vertexIndices);		
		break;
	case OBJ_TEAPOT:	
		loadMesh( "teapot.obj" , C , OBJ_TEAPOT, vertexIndices);
		break;
	case OBJ_PLATE:	
		loadMesh( "plate.obj" , C , OBJ_PLATE, vertexIndices);
		break;
	case OBJ_GLASS:	
		loadMesh( "glass.obj" , C , OBJ_GLASS, vertexIndices);	
		break;
	case OBJ_COOKIE1:	
		loadMesh( "cookie1.obj" , C , OBJ_COOKIE1, vertexIndices);
		break;
	case OBJ_COOKIE2:	
		loadMesh( "cookie2.obj" , C , OBJ_COOKIE2, vertexIndices);
		break;
	case OBJ_COOKIE3:	
		loadMesh( "cookie3.obj" , C , OBJ_COOKIE3,  vertexIndices);
		break;
	case OBJ_COOKIE4:	
		loadMesh( "cookie4.obj" , C , OBJ_COOKIE4, vertexIndices);
		break;
	case OBJ_COOKIE5:	
		loadMesh( "cookie5.obj" , C , OBJ_COOKIE5, vertexIndices);
		break;
	case OBJ_BAGEL1:	
		loadMesh( "bagel1.obj" , C , OBJ_BAGEL1, vertexIndices);
		break;
	case OBJ_BAGEL2:	
		loadMesh( "bagel2.obj" , C , OBJ_BAGEL2, vertexIndices);
		break;
	case OBJ_APPLETEAPOT:	
		loadMesh( "apple1.obj" , C , OBJ_APPLETEAPOT, vertexIndices);
		break;
	case OBJ_APPLEPLATE:	
		loadMesh( "apple2.obj" , C , OBJ_APPLEPLATE, vertexIndices);
		break;
	case OBJ_FERN1:	
		loadMesh( "fern1.obj" , C , OBJ_FERN1, vertexIndices);
		break;
	case OBJ_FERN2:	
		loadMesh( "fern2.obj" , C , OBJ_FERN2, vertexIndices);
		break;
	case OBJ_FERN3:	
		loadMesh( "fern3.obj" , C , OBJ_FERN3, vertexIndices);
		break;
	case OBJ_TABLE:	
		loadMesh( "table.obj" , C , OBJ_TABLE, vertexIndices);
		break;
	default:		
		loadMesh( "teapot.obj" , C , OBJ_TEAPOT, vertexIndices);
		break;
    }
    vertexIndices.clear();
}
