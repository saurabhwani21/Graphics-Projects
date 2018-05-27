//
//  Clipper.cpp
//
//  Created by Warren R. Carithers on 01/15/14.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Copyright 2014 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Saurabh Anant Wani (saw4058)
//

#include "Vertex.h"
#include "Clipper.h"
#include <iostream>
#include <string>

///
// Simple module that performs clipping
///

///
// Constructor
///
Clipper::Clipper() {
}

//Bottom boundary of polygon
string Clipper::boundaryBottom = "Bottom";
//Top boundary of polygon
string Clipper::boundaryTop    = "Top";
//Right boundary of polygon
string Clipper::boundaryRight  = "Right";
//Left boundary of polygon
string Clipper::boundaryLeft   = "Left";


///
//   This function performs the Sutherland-Hodgman Algorithm.
//   Checks if a point is on the inside or outside of a polygon 
//   also if it is intersecting an boundary of the polygon, based on that 
//   stores the point in the output array. 
///
int Clipper::shPolygonCutting( int countIn, float xIn[], float yIn[], float xOut[], float yOut[], float x1, float y1, float x2, float y2, string boundary)
{
	int countOut=0;
	float xTemp;
	float yTemp;
	xTemp = xIn[countIn - 1];
	yTemp = yIn[countIn - 1];	
	//Iterating over all input points. 
	for (int i = 0; i < countIn; i++)
	{ 
		//If the starting point is inside. 
		if (inside(xIn[i],yIn[i],x1,y1,x2,y2,boundary))
		{
			//If the ending point is inside as well.
			if(inside(xTemp, yTemp, x1, y1, x2, y2, boundary))
			{
				xOut[countOut]         = xIn[i];
				yOut[countOut]         = yIn[i];
				countOut               = countOut + 1;
			}
			else
			{	
				if ( x1 == x2 )
				{
					xOut[countOut] = x1;
					yOut[countOut] = yIn[i] + (x1 - xIn[i]) * ( yTemp - yIn[i]) / (xTemp - xIn[i]);
				}
				else
				{
					xOut[countOut] = xIn[i] + (y1 - yIn[i]) * ( xTemp - xIn[i]) / (yTemp - yIn[i]);
					yOut[countOut] = y1;
				}

				countOut               = countOut + 1;
				xOut[countOut]         = xIn[i];
				yOut[countOut]         = yIn[i];
				countOut               = countOut + 1;
			}
		}
		else
		{
			//If the start point is outside, but end point is inside of the boundary. 
			if(inside(xTemp, yTemp, x1, y1, x2, y2, boundary))
			{
				if ( x1 == x2 )
				{
					xOut[countOut] = x1;
					yOut[countOut] = yIn[i] + (x1 - xIn[i]) * ( yTemp - yIn[i]) / (xTemp - xIn[i]);

				}
				else
				{
					xOut[countOut] = xIn[i] + (y1 - yIn[i]) * ( xTemp - xIn[i]) / (yTemp - yIn[i]);
					yOut[countOut] = y1;
				}
				countOut               = countOut + 1;
			}
		}
		xTemp = xIn[i];
		yTemp = yIn[i];
	}
	return countOut;
}


///
// Function to check if a point is inside or outside the polygon.
// Returns true if the point is inside the polygon or false if the 
// point is outside the polygon.
///
bool Clipper::inside(float x, float y, float x1, float y1, float x2, float y2, string boundary)
{
	if      (boundary == "Bottom" && y1 < y)	
	{return true;}
	else if (boundary == "Top"    && y1 > y)
	{return true;}
	else if (boundary == "Right"  && x2 > x)
	{return true;}
	else if (boundary == "Left"   && x2 < x)
	{return true;}
	else
	{return false;}	
}


///
// clipPolygon
//
// Clip the polygon with vertex count in and vertices inV against the
// rectangular clipping region specified by lower-left corner ll and
// upper-right corner ur. The resulting vertices are placed in outV.
//
// The routine should return the with the vertex count of polygon
// resulting from the clipping.
//
// @param in    the number of vertices in the polygon to be clipped
// @param inV   the incoming vertex list
// @param outV  the outgoing vertex list
// @param ll    the lower-left corner of the clipping rectangle
// @param ur    the upper-right corner of the clipping rectangle
//
// @return number of vertices in the polygon resulting after clipping
//
///

int Clipper::clipPolygon( int in, const Vertex inV[], Vertex outV[],
                          Vertex ll, Vertex ur )
{

    // YOUR CODE GOES HERE
	//For keeping track of number of vertices in the polygon after clipping
	int countOut = 0; 
	// For storing input x coordinates
	float *xIn  = new float[30];
	// For storing input y coordinates
	float *yIn  = new float[30];
	// For storing output x coordinates
	float *xOut = new float[30];
	// For storing output y coordinates
	float *yOut = new float[30]; 
	// Intermediate 1 x coordindates
	float *xOut1 = new float[30];
	// Intermediate 1 y coordinates
	float *yOut1 = new float[30];
	// Intermediate 2 x coordindates
	float *xOut2 = new float[30];
	// Intermediate 2 y coordinates
	float *yOut2 = new float[30];
	// Intermediate 3 x coordindates
	float *xOut3 = new float[30];
	// Intermediate 3 y coordinates
	float *yOut3 = new float[30];
	

	//Separate the x and y vertices in to different arrays. 
	for (int i = 0; i < in; i++)
	{
		xIn[i] = inV[i].x;
		yIn[i] = inV[i].y;
	}

	//Execution for the left boundary.
	countOut = shPolygonCutting(in      , xIn  , yIn  , xOut1, yOut1, ll.x, ll.y, ll.x, ur.y, boundaryLeft  );
	//Execution for the right boundary.
	countOut = shPolygonCutting(countOut, xOut1, yOut1, xOut2, yOut2, ur.x, ll.y, ur.x, ur.y, boundaryRight );
	//Execution for the top boundary.
	countOut = shPolygonCutting(countOut, xOut2, yOut2, xOut3, yOut3, ll.x, ur.y, ur.x, ur.y, boundaryTop   );
	//Execution for the bottom boundary.
	countOut = shPolygonCutting(countOut, xOut3, yOut3, xOut , yOut , ll.x, ll.y, ur.x, ll.y, boundaryBottom);


	//Combining the output x and y coordinates to be sent back 
	for (int i = 0; i < countOut; i++)
	{
		outV[i].x = xOut[i];
		outV[i].y = yOut[i];
	}	

    return( countOut );  // remember to return the outgoing vertex count!

}
