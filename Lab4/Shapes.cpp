//
//  Shapes
//
//  Routines for tessellating a number of basic shapes
//
//  Students are to supply their implementations for the functions in
//  this file using the function addTriangle() to do the tessellation.
//
//  This code can be compiled as either C or C++.
//
//  Modified by : Saurabh Anant Wani (saw4058)
//

#include <cmath>

// Canvas.h pulls in all the OpenGL/GLFW/etc. header files for us
#include "Shapes.h"
#include "Canvas.h"
#include "Vertex.h"

//Vertex constructor
Vertex vertex(float x, float y, float z)
{
	Vertex vert;
	vert.x = x;
	vert.y = y;
	vert.z = z;
	return vert;
}

///
// makeCube - Create a unit cube, centered at the origin, with a given number
// of subdivisions in each direction on each face.
//
// @param subdivision - number of equal subdivisions to be made in each 
//        direction along each face
//
// Can only use calls to C.addTriangle()
///
void makeCube( Canvas &C, int subdivisions )
{
    if( subdivisions < 1 )
        subdivisions = 1;

    // YOUR IMPLEMENTATION HERE
	float ptX1; 
	float ptY1; 
	float ptX2;
	float ptY2;
	
	for (int x = 1; x <= subdivisions; x++)
	{
		ptX1 = 	((x - 1) * float( 1.0 / subdivisions ) - 0.5 ); 
		ptX2 =  (   x    * float( 1.0 / subdivisions ) - 0.5 ); 
		for( int y = 1; y <= subdivisions; y++)
		{
			ptY2 = (   y    * float( 1.0 / subdivisions ) - 0.5 ); 
			ptY1 = ((y - 1) * float( 1.0 / subdivisions ) - 0.5 ); 
			C.addTriangle(vertex(ptX2, ptY1, -0.5), vertex(ptX1, ptY1, -0.5), vertex(ptX1, ptY2, -0.5));
			C.addTriangle(vertex(ptX2, ptY1, -0.5), vertex(ptX1, ptY1, -0.5), vertex(ptX1, ptY2, -0.5));			
			C.addTriangle(vertex(ptX1, ptY1, 0.5),  vertex(ptX2, ptY1, 0.5),  vertex(ptX1, ptY2, 0.5));			
			C.addTriangle(vertex(ptX1, ptY2, 0.5),  vertex(ptX2, ptY1, 0.5),  vertex(ptX2, ptY2, 0.5));
			C.addTriangle(vertex(-0.5, ptX1, ptY2), vertex(-0.5, ptX2, ptY1), vertex(-0.5, ptX1, ptY1));			
			C.addTriangle(vertex(-0.5, ptX2, ptY2), vertex(-0.5, ptX2, ptY2), vertex(-0.5, ptX1, ptY2));
			C.addTriangle(vertex(0.5, ptX2, ptY1),  vertex(0.5, ptX1, ptY2),  vertex(0.5, ptX1, ptY1));			
			C.addTriangle(vertex(0.5, ptX2, ptY1),  vertex(0.5, ptX2, ptY2),  vertex(0.5, ptX1, ptY2));
			C.addTriangle(vertex(ptX2, -0.5, ptY1), vertex(ptX1, -0.5, ptY2), vertex(ptX1, -0.5, ptY1));			
			C.addTriangle(vertex(ptX2, -0.5, ptY1), vertex(ptX2, -0.5, ptY2), vertex(ptX1, -0.5, ptY2));
			C.addTriangle(vertex(ptX1, 0.5, ptY2),  vertex(ptX2, 0.5, ptY1),  vertex(ptX1, 0.5, ptY1));			
			C.addTriangle(vertex(ptX2, 0.5, ptY2),  vertex(ptX2, 0.5, ptY1),  vertex(ptX1, 0.5, ptY2));			
		}
	}
}




///
// makeCylinder - Create polygons for a cylinder with unit height, centered at
// the origin, with separate number of radial subdivisions and height 
// subdivisions.
//
// @param radius - Radius of the base of the cylinder
// @param radialDivision - number of subdivisions on the radial base
// @param heightDivisions - number of subdivisions along the height
//
// Can only use calls to C.addTriangle()
///
void makeCylinder( Canvas &C, float radius, int radialDivisions, int heightDivisions )
{
    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    // YOUR IMPLEMENTATION HERE
	float ptX1; 
	float ptY1; 
	float ptZ1;
	float ptX2;
	float ptY2;
	float ptZ2;	
	for(int x =1 ; x <= radialDivisions; x++)
	{
		ptX1 = float(radius * cos(2 * (x - 1) * 3.14 / radialDivisions));
		ptX2 = float(radius * cos(2 *  (x)    * 3.14 / radialDivisions));
		ptZ1 = float(radius * sin(2 * (x - 1) * 3.14 / radialDivisions));
		ptZ2 = float(radius * sin(2 *  (x)    * 3.14 / radialDivisions));
		C.addTriangle(vertex(0, -0.5, 0),      vertex(ptX1, -0.5, ptZ1), vertex(ptX2, -0.5, ptZ2));
		C.addTriangle(vertex(ptX2, 0.5, ptZ2), vertex(ptX1, 0.5, ptZ1),  vertex(0, 0.5, 0));
		for(int y=1; y <= heightDivisions; y++)
		{
			ptY2 = float(  y   / heightDivisions - 0.5);
			ptY1 = float((y-1) / heightDivisions - 0.5);
			C.addTriangle(vertex(ptX1, ptY2, ptZ1), vertex(ptX2, ptY2, ptZ2), vertex(ptX1, ptY1, ptZ1));
			C.addTriangle(vertex(ptX2, ptY2, ptZ2), vertex(ptX2, ptY1, ptZ2), vertex(ptX1, ptY1, ptZ1));
		}
	}
}


///
// makeCone - Create polygons for a cone with unit height, centered at the
// origin, with separate number of radial subdivisions and height 
// subdivisions.
//
// @param radius - Radius of the base of the cone
// @param radialDivision - number of subdivisions on the radial base
// @param heightDivisions - number of subdivisions along the height
//
// Can only use calls to C.addTriangle()
///
void makeCone( Canvas &C, float radius, int radialDivisions, int heightDivisions )
{
    if( radialDivisions < 3 )
        radialDivisions = 3;

    if( heightDivisions < 1 )
        heightDivisions = 1;

    // YOUR IMPLEMENTATION HERE
	float pX1, pX2, pY1;
	float pZ1, pZ2;
	for(int x = 1; x <= radialDivisions; x++)
	{
		pX1 = float(radius * cos(2 * (x - 1) * 3.14 / radialDivisions));
		pZ1 = float(radius * sin(2 * (x - 1) * 3.14 / radialDivisions));
		pX2 = float(radius * cos(2 *  (x)    * 3.14 / radialDivisions));
		pZ2 = float(radius * sin(2 *  (x)    * 3.14 / radialDivisions));
		C.addTriangle(vertex(pX1, -0.5, pZ1), vertex(pX2, -0.5, pZ2), vertex(0, -0.5, 0));
		pY1 = -0.5;
		for(int y = 1; y <= heightDivisions - 1; y++)
		{
			C.addTriangle(vertex(pX1, pY1, pZ1), vertex(pX1 - (pX1/heightDivisions), pY1 + (1/(float)heightDivisions), pZ1 - (pZ1/heightDivisions)), vertex( pX2, pY1, pZ2)); 
			C.addTriangle(vertex(pX1 - (pX1/heightDivisions), pY1 + (1/(float)heightDivisions), pZ1 - (pZ1/heightDivisions)),
				      vertex(pX2 - (pX2/heightDivisions), pY1 + (1/(float)heightDivisions), pZ2 - (pZ2/heightDivisions)),
				      vertex(pX2, pY1, pZ2));
			pX1 = pX1 - (pX1/heightDivisions);	
			pX2 = pX2 - (pX2/heightDivisions);	
			pY1 = pY1 + (1/(float)heightDivisions);
			pZ1 = pZ1 - (pZ1/heightDivisions);	
			pZ2 = pZ2 - (pZ2/heightDivisions);	
		}
		C.addTriangle(vertex(pX1, pY1, pZ1), vertex(0, 0.5, 0), vertex(pX2, pY1, pZ2));
	}
}


/*
Function to draw sphere recursively. 
param slices Number of slices
param radius Radius of sphere
param v1     Vertex 1
param v2     Vertex 2
param v3     Vertex 3
*/
void sphere(int slices, float radius, Canvas &C, Vertex v1, Vertex v2, Vertex v3)
{
	if ( slices > 1)
	{
		sphere((slices-1), radius, C, vertex(v1.x, v1.y, v1.z),                            vertex((v1.x+v2.x)/2, (v1.y+v2.y)/2, (v1.z+v2.z)/2), vertex((v1.x+v3.x)/2, (v1.y+v3.y)/2, (v1.z+v3.z)/2));		
		sphere((slices-1), radius, C, vertex((v1.x+v2.x)/2, (v1.y+v2.y)/2, (v1.z+v2.z)/2), vertex((v3.x+v2.x)/2, (v3.y+v2.y)/2, (v3.z+v2.z)/2), vertex((v1.x+v3.x)/2, (v1.y+v3.y)/2, (v1.z+v3.z)/2));
		sphere((slices-1), radius, C, vertex((v1.x+v2.x)/2, (v1.y+v2.y)/2, (v1.z+v2.z)/2), vertex(v2.x, v2.y, v2.z),                            vertex((v2.x+v3.x)/2, (v2.y+v3.y)/2, (v2.z+v3.z)/2));
		sphere((slices-1), radius, C, vertex((v1.x+v3.x)/2, (v1.y+v3.y)/2, (v1.z+v3.z)/2), vertex((v3.x+v2.x)/2, (v3.y+v2.y)/2, (v3.z+v2.z)/2), vertex(v3.x, v3.y, v3.z));
	}
	//Print the triangle on screen once normalization is performed. 
	else
	{
		C.addTriangle(vertex((v1.x/(float(sqrt(v1.x*v1.x+v1.y*v1.y+v1.z*v1.z))))*radius, (v1.y/(float(sqrt(v1.x*v1.x+v1.y*v1.y+v1.z*v1.z))))*radius, (v1.z/(float(sqrt(v1.x*v1.x+v1.y*v1.y+v1.z*v1.z))))*radius),
			      vertex((v2.x/(float(sqrt(v2.x*v2.x+v2.y*v2.y+v2.z*v2.z))))*radius, (v2.y/(float(sqrt(v2.x*v2.x+v2.y*v2.y+v2.z*v2.z))))*radius, (v2.z/(float(sqrt(v2.x*v2.x+v2.y*v2.y+v2.z*v2.z))))*radius),
			      vertex((v3.x/(float(sqrt(v3.x*v3.x+v3.y*v3.y+v3.z*v3.z))))*radius, (v3.y/(float(sqrt(v3.x*v3.x+v3.y*v3.y+v3.z*v3.z))))*radius, (v3.z/(float(sqrt(v3.x*v3.x+v3.y*v3.y+v3.z*v3.z))))*radius));
	}
}

///
// makeSphere - Create sphere of a given radius, centered at the origin, 
// using spherical coordinates with separate number of thetha and 
// phi subdivisions.
//
// @param radius - Radius of the sphere
// @param slices - number of subdivisions in the theta direction
// @param stacks - Number of subdivisions in the phi direction.
//
// Can only use calls to C.addTriangle()
///
void makeSphere( Canvas &C, float radius, int slices, int stacks )
{
    // IF DOING RECURSIVE SUBDIVISION:
    //   use a minimum value of 1 instead of 3
    //   add an 'else' clause to set a maximum value of 5
    if( slices < 3 )
        slices = 3;

    if( stacks < 3 )
        stacks = 3;
    
    // YOUR IMPLEMENTATION HERE
        sphere(slices, radius, C, vertex(radius, 1, 0),   vertex(1, 0, radius),    vertex(1, 0, -radius));
        sphere(slices, radius, C, vertex(radius, -1, 0),  vertex(1, 0, -radius),   vertex(1, 0, radius));
        sphere(slices, radius, C, vertex(-radius, 1, 0),  vertex(-1, 0, -radius),  vertex(-1, 0, radius));
        sphere(slices, radius, C, vertex(-radius, -1, 0), vertex(-1, 0, radius),   vertex(-1, 0, -radius));
        sphere(slices, radius, C, vertex(0, radius, 1),   vertex(-radius, 1, 0),   vertex(-1, 0, radius));
        sphere(slices, radius, C, vertex(0, radius, 1),   vertex(1, 0, radius),    vertex(radius, 1, 0));
        sphere(slices, radius, C, vertex(0, radius, -1),  vertex(-1, 0, -radius),  vertex(-radius, 1, 0));
        sphere(slices, radius, C, vertex(0, radius, -1),  vertex(radius, 1, 0),    vertex(1, 0, -radius));
        sphere(slices, radius, C, vertex(0, -radius, -1), vertex(-radius, -1, 0),  vertex(-1, 0, -radius));
        sphere(slices, radius, C, vertex(0, -radius, -1), vertex(1, 0, -radius),   vertex(radius, -1, 0));
        sphere(slices, radius, C, vertex(0, -radius, 1),  vertex( -1, 0, radius),  vertex(-radius, -1, 0));
        sphere(slices, radius, C, vertex(0, -radius, 1),  vertex(radius, -1, 0),   vertex(1, 0, radius));
	sphere(slices, radius, C, vertex(0, radius, -1),  vertex(-radius, 1, 0),   vertex(radius, 1, 0));
        sphere(slices, radius, C, vertex(0, radius, 1),   vertex(radius, 1, 0),    vertex(-radius, 1, 0));
        sphere(slices, radius, C, vertex(0, radius, 1),   vertex(-1, 0, radius),   vertex(0, -radius, 1));
        sphere(slices, radius, C, vertex(0, radius, 1),   vertex(0, -radius, 1),   vertex(1, 0, radius));
        sphere(slices, radius, C, vertex(0, radius, -1),  vertex(1, 0, -radius),   vertex(0, -radius, -1));
        sphere(slices, radius, C, vertex(0, radius, -1),  vertex( 0, -radius, -1), vertex(-1, 0, -radius));
        sphere(slices, radius, C, vertex(0, -radius, 1),  vertex(-radius, -1, 0),  vertex(radius, -1, 0));
        sphere(slices, radius, C, vertex(0, -radius, -1), vertex(radius, -1, 0),   vertex(-radius, -1, 0));

}
