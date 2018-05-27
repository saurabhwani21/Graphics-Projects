//
//  Rasterizer.cpp
//
//  Created by Joe Geigel on 11/30/11.
//  Modifications by Warren R. Carithers.
//  Copyright 2011 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Saurabh Anant Wani (saw4058)
//

#include <list>
#include <algorithm>
#include <iostream>
#include <float.h>
#include "Rasterizer.h"
#include "Canvas.h"
#include <math.h>
using namespace std;

///
// Simple class that performs rasterization algorithms
///

///
// Constructor
//
// @param n number of scanlines
// @param C The Canvas to use
///
Rasterizer::Rasterizer( int n, Canvas &canvas ) : n_scanlines(n), C(canvas)
{
}

///
// Draw a filled polygon.
//
// Implementation should use the scan-line polygon fill algorithm
// discussed in class.
//
// The polygon has n distinct vertices.  The coordinates of the vertices
// making up the polygon are stored in the x and y arrays.  The ith
// vertex will have coordinate (x[i],y[i]).
//
// You are to add the implementation here using only calls to the
// setPixel() function.
//
// @param n - number of vertices
// @param x - array of x coordinates
// @param y - array of y coordinates
///
void Rasterizer::drawPolygon(int n, const int x[], const int y[] )
{
    // YOUR IMPLEMENTATION HERE

        //
	edgebucket gebucket;  		// To store global edges
	vector<edgebucket> edges; 	// Represent edges
	vector<edgebucket> getable; 	// Represent all global edge
	vector<edgebucket> activeList;	// Represent active edges
	
	int xmin,ymin,xmax,ymax;
	float inverseSlope;
	int i=0;
	//Fill the global edge table
	for (i = 0; i < n; i++ )
	{
		xmin = x[i%n];			
		ymin = y[i%n];			
		xmax = x[(i+1)%n];
		ymax = y[(i+1)%n];
		// Calculating slope
		inverseSlope 	= ((float) (xmin - xmax)) / ((float) (ymin - ymax));
		gebucket.yMax 	= (ymin < ymax ? ymax : ymin);
		gebucket.yMin 	= (ymin > ymax ? ymax : ymin);
		gebucket.x 	= ((gebucket.yMin == ymin) ? (float) xmin : (float) xmax);
		if ((gebucket.yMax - gebucket.yMin) != 0)
		{
			gebucket.inverseSlope = inverseSlope;
			getable.push_back(gebucket);
		}		
	}

	//Sorting values of the global edge table
	int i1 = 0;
	for(i = 0; i < (getable.size() - 1); i ++)
	{
		for (i1 = (i+ 1); i1 < getable.size(); i1++)
		{
			if (((getable.at(i1).yMin < getable.at(i).yMin) || (getable.at(i1).x < getable.at(i).x)) && (getable.at(i1).yMin <= getable.at(i).yMin))
			{
				gebucket       = getable.at(i1);
				getable.at(i1) = getable.at(i);
				getable.at(i)  = gebucket;
			}
		}		
	}

	int scanMaxLine = getable.at(getable.size()-1).yMax;
	int scanMinLine = getable.at(0).yMin;
	int checkParity;	
	//Process
	while (scanMinLine <=scanMaxLine)
	{		
		i=0;
		checkParity = 0;
		while ( i < getable.size())
		{
			gebucket = getable.at(i);
			if (gebucket.yMin == scanMinLine)
			{
				activeList.push_back(gebucket);
				getable.erase(getable.begin() + i);
			}
			else
			{i++;}
		}
	
		// Stores the size of the Active edges list. 
		int activeListSize = activeList.size();	
		int edge = 0;
		if ( scanMinLine < scanMaxLine)
		{
			i = 0;
			while ( i < activeListSize)
			{
				gebucket = activeList.at(i);
				if(gebucket.yMax == scanMinLine)
				{
					//Remove edge if ymax equals scanline
					activeList.erase(activeList.begin() + i);
					activeListSize--;
				}
				else
				{i++;}
			}
		}
	
		for (i=0; i < activeListSize -1; i++)
		{
			for(i1 = i+1; i1 < activeListSize; i1++)
			{
				if (activeList.at(i1).x < activeList.at(i).x)
				{
					gebucket          = activeList.at(i1);
					activeList.at(i1) = activeList.at(i);
					activeList.at(i)  = gebucket;
				}
			}
		}

		int whole;
		//Polygon filling
		for ( i =0; i <= (*max_element(x, x + n)) && edge < activeListSize; i++)
		{
			whole = floor(activeList.at(edge).x);
			if (i == whole)
			{
				if ( edge+1 < activeListSize && i != floor(activeList.at(edge + 1).x))
				{checkParity = ((checkParity == 0) ? 1 : 0);}
				while (edge < activeListSize && i == floor(activeList.at(edge).x))
				{
					edgebucket buck = activeList.at(edge);
					edgebucket buck1;
					buck1.yMin  	    = buck.yMin;
					buck1.yMax  	    = buck.yMax;
					buck1.x		    = buck.x + buck.inverseSlope;
					buck1.inverseSlope  = buck.inverseSlope;
					activeList.at(edge) = buck1;
					C.setPixel(i,scanMinLine);
					edge                = edge + 1;
				}
			}
			if (checkParity == 1)
			{C.setPixel(i,scanMinLine);}
		}
		scanMinLine = scanMinLine + 1;
	}	
}
