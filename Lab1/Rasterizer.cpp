//
//  Rasterizer.cpp
//
//  Created by Warren R. Carithers on 01/28/14.
//  Based on a C++ version created by Joe Geigel on 11/30/11.
//  Copyright 2014 Rochester Institute of Technology. All rights reserved.
//
//  Contributor:  Saurabh Anant Wani (saw4058)
//

#include <cmath>
#include <stdlib.h>
#include "Rasterizer.h"

///
//
// Simple class that performs rasterization algorithms
//
///

///
// Constructor
//
// @param n number of scanlines
// @param C the Canvas to be used
///

Rasterizer::Rasterizer( int n, Canvas &canvas ) : n_scanlines(n), C(canvas)
{
}


///
// Draw my initials
//
// Draw my own initials using calls to drawLine(), in the same
// manner that makeLines() in the driver program draws 'CG'.
///

void Rasterizer::myInitials( void ) {

    // ######## Use light blue (0.678,0.847,0.902) for initials ######## 

    C.setColor( 0.678, 0.847, 0.902 );
    
    // Points for drawing 'S'
    drawLine(   95, 40, 220, 40   );    
    drawLine(  220, 40, 260, 80   );   
    drawLine(  260, 80, 260, 140  ); 
    drawLine(  260, 140, 220, 180 );
    drawLine(  220, 180, 120, 180 );
    drawLine(  120, 180, 100, 200 );
    drawLine(  100, 200, 100, 220 );
    drawLine(  100, 220, 120, 240 );
    drawLine(  120, 240, 210, 240 );
    drawLine(  210, 240, 220, 230 ); 
    drawLine(  220, 230, 220, 210 );
    drawLine(  220, 210, 260, 210 );
    drawLine(  260, 210, 260, 245 );
    drawLine(  260, 245, 225, 280 );
    drawLine(  225, 280,  100, 280);
    drawLine(  100, 280, 60, 240  ); 
    drawLine(   60, 240,  60, 180 );
    drawLine(   60, 180, 100, 140 );
    drawLine(  100, 140,  200, 140); 
    drawLine(   200, 140, 220,120 ); 
    drawLine(   220, 120, 220, 100);
    drawLine(   220, 100, 200,80  ); 
    drawLine(   200, 80, 110, 80  ); 
    drawLine(   100, 90, 110, 80  ); 
    drawLine(   100, 90, 100, 110 );
    drawLine(   100, 110, 60, 110 );
    drawLine(   60, 110, 60, 75   ); 
    drawLine(   60, 75, 95, 40    ); 

    // Points for drawing 'W'
    drawLine( 340, 40, 390, 40  );
    drawLine( 390, 40, 440, 90  );
    drawLine( 440, 90, 490,40   ); 
    drawLine( 490, 40, 540, 40  );
    drawLine( 340, 40, 340, 280 );
    drawLine( 340,280, 390, 280 );
    drawLine( 390,280, 390,90   );
    drawLine( 390,90,440, 140   );
    drawLine( 440,140, 490, 90  );
    drawLine( 490, 90, 490, 280 );
    drawLine( 490,280, 540,280  );
    drawLine( 540, 280, 540, 40 );
 
    //
    // add code here to draw your initials
    // with calls to your drawLine() function
    // 

}



///
//  Draw vertical lines.
//  
// @param x0 x coord of both the points 
// @param y0 y coord of the first endpoint
// @param y1 y coord of the second endpoint
///
void Rasterizer::vertical(int x0, int y0, int y1)
{
	int temp1;
	int temp2;
	temp1 = x0;
	if ( y1 < y0 )
	{	
		temp2 = y0; 
		y0    = y1;
		y1    = temp2;
	}
	for ( int y = y0; y <= y1; y++)
	{C.setPixel(temp1, y);}
}

///
//  Draw horizontal lines.
//  
// @param x0 x coord of the first endpoint
// @param x1 x coord of the second endpoint
// @param y  y coord of both the points 
///
void Rasterizer::horizontal(int x0, int x1, int y)
{
	for ( int x = x0; x <=x1; x++)
	{C.setPixel(x,y);}
}


///
// Draw a line from (x0,y0) to (x1, y1)
//
// Implementation should be using the Midpoint Line Algorithm.
//
// You are to add the implementation here using only calls to the
// setPixel() method of the Canvas.
//
// @param x0 x coord of first endpoint
// @param y0 y coord of first endpoint
// @param x1 x coord of second endpoint
// @param y1 y coord of second endpoint
///
void Rasterizer::drawLine( int x0, int y0, int x1, int y1 )
{
  
	
    //
    // add code here to implement drawLine()
    // using the midpoint line algorithm
    //
	int x,y;
	
	int dy,dx;
	dy = y1 - y0;
	dx = x1 - x0;

	// Swapping the points if needed.
	if ( x1 < x0 )
	{	
		int temp1; 
		temp1 = x0;
		x0    = x1;
		x1    = temp1;
		temp1 = y0;
		y0    = y1;
		y1    = temp1;
	}


	// Drawing the horizontal lines
	if ( y0 == y1)
	{	
		horizontal(x0, x1, y0);
		return;
	}
	
	// Drawing the vertical lines 
	if ( x0 == x1)
	{	
		vertical(x0, y0, y1);
		return;
	}

	// Drawing the diagonal lines 
	else if ( abs(dy/dx) == 1 )
	{
		int xI,yI;
		xI = 1;
		yI = 1;
		if ( -1 > (y1 - y0))
		{yI = -1;}
		if ( -1 > (x1 - x0))
		{xI = -1;}

		for (x=x0, y=y0; x!= x1 && y!= y1; x += xI, y += yI)		
		{C.setPixel(x,y);}
	}

	else
	{		
		// Drawing lines having slope(m) between 0 < m < 1
		if( (dy/(float)dx) > 0 && (dy/(float)dx) < 1) 
		{
			dy      = abs (dy);
			dx      = abs (dx);
			int dE  = 2 * dy;
			int dNE = 2 * ( dy - dx );
			int d   = dE - dx;	
		
			for(x = std::min(x0,x1),y = std::min(y0,y1); x<= std::max(x0,x1); ++x)
			{
				C.setPixel(x,y);
				if ( d <= 0)
				{d += dE;}
				else
				{
					++y;
					d += dNE;
				}
			}
		}	
	
		// Drawing lines having slope(m) between -1 < m < 0
		else if( (dy/(float)dx) < 0 && (dy/(float)dx) > -1)
		{
			dy      = abs (dy);
			dx      = abs (dx);
			int dW  = 2 * dy;
			int dNW = 2 * ( dy - dx);
			int d   = dW - dx;	
		
			for ( x = std::min(x0,x1), y = std::max(y0,y1); x <= std::max(x0,x1); ++x)
			{
				C.setPixel(x,y);
				if ( d<= 0)
				{d += dW;}
				else
				{
					--y;
					d += dNW;
				}
			}
		}

		// Drawing lines having slope(m) m > 1
		else if ( (dy/(float)dx) > 1)
		{
			dy      = abs (dy);
			dx      = abs (dx);
			int dN  = 2 * dx;
			int dNE = 2 * ( dx - dy);
			int d   = dN - dy;

			for( x = std::min(x0,x1), y = std::min(y0,y1); y<= std::max(y0,y1); ++y)
			{
				C.setPixel(x,y);
				if( d<= 0)
				{d += dN;}
				else
				{					
					d+= dNE;
					++x;
				}
			}
		}				
	
		// Drawing lines having slope(m) m < -1
		else if ( (dy/(float)dx) < -1)
		{
			dy      = abs (dy);
			dx      = abs (dx);
			int dN  = 2 * dx;
			int dNW = 2 * (dx - dy);
			int d   = dN - dy;
			
			for (x = std::max(x0,x1), y = (std::min(y0,y1)); y <= std::max(y0,y1); ++y)
			{
				C.setPixel(x,y);
				if ( d <= 0)
				{d += dN;}
				else
				{					
					d += dNW;
					--x;				
				}
			}
		}		
	}
}
