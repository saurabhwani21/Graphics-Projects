//
//  clipper.h
//
//  Created by Warren R. Carithers on 02/27/14.
//  Based on a version created by Joe Geigel on 11/30/11.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Saurabh Anant Wani (saw4058)
//

#ifndef _CLIPPER_H_
#define _CLIPPER_H_

#include "Vertex.h"
#include <string>
using namespace std;

///
// Simple module that performs clipping
///

class Clipper {

public:

    ///
    // Constructor
    ///
    Clipper();

    //Bottom boundary of polygon
    static string boundaryBottom;    
    //Top boundary of polygon
    static string boundaryTop;
    //Right boundary of polygon
    static string boundaryRight;
    //Left boundary of polygon
    static string boundaryLeft;

    ///
    //   This function performs the Sutherland-Hodgman Algorithm.
    //   Checks if a point is on the inside or outside of a polygon 
    //   also if it is intersecting an boundary of the polygon, based on that 
    //   stores the point in the output array. 
    ///
    int shPolygonCutting( int countIn, float xIn[], float yIn[], float xOut[], float yOut[], float x1, float y1, float x2, float y2, string boundary);

    ///
    // Function to check if a point is inside or outside the polygon.
    // Returns true if the point is inside the polygon or false if the 
    // point is outside the polygon.
    ///
    bool inside(float x, float x1, float x2, float y, float y1, float y2, string boundary);

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
    int clipPolygon( int in, const Vertex inV[], Vertex outV[],
		     Vertex ll, Vertex ur );



};

#endif
