//
//  finalMain.cpp
//
//  Created by Warren R. Carithers 2016/11/22.
//  Based on code created by Joe Geigel.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Main program for final project assignment.
//
//  Modified by: Saurabh Anant Wani (saw4058)
//

#include <cstdlib>
#include <iostream>

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include "Buffers.h"
#include "ShaderSetup.h"
#include "Canvas.h"
#include "Shapes.h"
#include "Viewing.h"
#include "Lighting.h"
#include "Textures.h"

using namespace std;

// do we need to do a display() call?
bool updateDisplay = true;

// How to calculate an offset into the vertex buffer
#define BUFFER_OFFSET(i) ((char *)NULL + (i))

// our drawing canvas
Canvas *canvas;

// dimensions of the drawing window
int w_width  = 600;
int w_height = 600;

//
// We need vertex buffers and element buffers for the
// quad (texture mapped), the teapot (Phong shaded),
// and the sphere (Phong shaded, by default).
//
BufferSet teapotBuffers;
BufferSet teacupBuffers;
BufferSet spoonBuffers;
BufferSet plateBuffers;
BufferSet glassBuffers;
BufferSet cookie1Buffers;
BufferSet cookie2Buffers;
BufferSet cookie3Buffers;
BufferSet cookie4Buffers;
BufferSet cookie5Buffers;
BufferSet bagel1Buffers;
BufferSet bagel2Buffers;
BufferSet appleTeapotBuffers;
BufferSet applePlateBuffers;
BufferSet fern1Buffers;
BufferSet fern2Buffers;
BufferSet fern3Buffers;
BufferSet tableBuffers;


// Animation flag
bool animating = false;

// Initial animation rotation angles for the objects
GLfloat angles = 0.0f;

// Initial translation factors for the sphere
GLfloat xlate[3] = { 1.3f, 2.2f, -1.5f };
int sphereState = 0;

// program IDs...for shader programs
GLuint pshader, tshader;

//
// createShape() - create vertex and element buffers for a shape
//
// @param obj - which shape to create
// @param C   - the Canvas to use
//
void createShape( int obj, Canvas &C )
{
    // clear any previous shape
    C.clear();

    // make the shape
    makeShape( obj, C );

    // create the necessary buffers
    if( obj == OBJ_TEAPOT ) {
        teapotBuffers.createBuffers( C );
    } else if( obj == OBJ_TEACUP ) {
        teacupBuffers.createBuffers( C );
    } else if( obj == OBJ_SPOON ) {
        spoonBuffers.createBuffers( C );
    } else if( obj == OBJ_PLATE ) {
        plateBuffers.createBuffers( C );
    } else if( obj == OBJ_GLASS ) {
        glassBuffers.createBuffers( C );
    } else if( obj == OBJ_COOKIE1 ) {
        cookie1Buffers.createBuffers( C );
    } else if( obj == OBJ_COOKIE2 ) {
        cookie2Buffers.createBuffers( C );
    } else if( obj == OBJ_COOKIE3 ) {
        cookie3Buffers.createBuffers( C );
    } else if( obj == OBJ_COOKIE4 ) {
        cookie4Buffers.createBuffers( C );
    } else if( obj == OBJ_COOKIE5 ) {
        cookie5Buffers.createBuffers( C );
    } else if( obj == OBJ_BAGEL1 ) {
        bagel1Buffers.createBuffers( C );
    } else if( obj == OBJ_BAGEL2 ) {
        bagel2Buffers.createBuffers( C );
    } else if( obj == OBJ_APPLETEAPOT ) {
        appleTeapotBuffers.createBuffers( C );
    } else if( obj == OBJ_FERN1) {
        fern1Buffers.createBuffers( C );
    } else if( obj == OBJ_FERN2) {
        fern2Buffers.createBuffers( C );
    } else if( obj == OBJ_FERN3) {
        fern3Buffers.createBuffers( C );
    } else if( obj == OBJ_TABLE) {
        tableBuffers.createBuffers( C );
    } else {
        applePlateBuffers.createBuffers( C );
    }
}

///
// OpenGL initialization
///
void init( void )
{
    // Create our Canvas
    canvas = new Canvas( w_width, w_height );

    if( canvas == NULL ) {
        cerr << "error - cannot create Canvas" << endl;
        glfwTerminate();
        exit( 1 );
    }

    // Load texture image(s)
    loadTexture();

    // Load shaders, verifying each
    ShaderError error;
    tshader = shaderSetup( "texture.vert", "texture.frag", &error );
    if( !tshader ) {
        cerr << "Error setting up texture shader - " <<
            errorString(error) << endl;
        glfwTerminate();
        exit( 1 );
    }

    pshader = shaderSetup( "phong.vert", "phong.frag", &error );
    if( !pshader ) {
        cerr << "Error setting up Phong shader - " <<
            errorString(error) << endl;
        glfwTerminate();
        exit( 1 );
    }

    // Other OpenGL initialization
    glEnable( GL_DEPTH_TEST );
    glPolygonMode( GL_FRONT_AND_BACK, GL_FILL );
    glClearColor( 0.0f, 0.0f, 0.0f, 0.0f );
    glDepthFunc( GL_LEQUAL );
    glClearDepth( 1.0f );

    // Create all our objects         
    createShape( 1,               *canvas );
    createShape( OBJ_TEACUP,      *canvas );
    createShape( OBJ_SPOON,       *canvas );
    createShape( OBJ_PLATE,       *canvas );
    createShape( OBJ_GLASS,       *canvas );
    createShape( OBJ_COOKIE1,     *canvas );
    createShape( OBJ_COOKIE2,     *canvas );
    createShape( OBJ_COOKIE3,     *canvas );
    createShape( OBJ_COOKIE4,     *canvas );
    createShape( OBJ_COOKIE5,     *canvas );
    createShape( OBJ_BAGEL1,      *canvas );
    createShape( OBJ_BAGEL2,      *canvas );
    createShape( OBJ_APPLETEAPOT, *canvas );
    createShape( OBJ_APPLEPLATE,  *canvas );
    createShape( OBJ_FERN1,       *canvas );
    createShape( OBJ_FERN2,       *canvas );
    createShape( OBJ_FERN3,       *canvas );
    createShape( OBJ_TABLE,       *canvas );
}

///
// selectBuffers() - bind the correct vertex and element buffers
//
// @param program - GLSL program object
// @param B       - the BufferSet to use
///
void selectBuffers( GLuint program, BufferSet &B ) {

    // bind the buffers
    glBindBuffer( GL_ARRAY_BUFFER, B.vbuffer );
    glBindBuffer( GL_ELEMENT_ARRAY_BUFFER, B.ebuffer );

    // set up the vertex attribute variables
    GLint vPosition = glGetAttribLocation( program , "vPosition" );
    glEnableVertexAttribArray( vPosition );
    glVertexAttribPointer( vPosition, 4, GL_FLOAT, GL_FALSE, 0,
                           BUFFER_OFFSET(0) );
    int offset = B.vSize;

    if( B.cSize ) {  // color data
        GLint vColor = glGetAttribLocation( program, "vColor" );
        glEnableVertexAttribArray( vColor );
        glVertexAttribPointer( vColor, 4, GL_FLOAT, GL_FALSE, 0,
                               BUFFER_OFFSET(offset) );
        offset += B.cSize;
    }

    if( B.nSize ) {  // normal data
        GLint vNormal = glGetAttribLocation( program, "vNormal" );
        glEnableVertexAttribArray( vNormal );
        glVertexAttribPointer( vNormal, 3, GL_FLOAT, GL_FALSE, 0,
                               BUFFER_OFFSET(offset) );
        offset += B.nSize;
    }

    if( B.tSize ) {  // texture coordinate data
        GLint vTexCoord = glGetAttribLocation( program, "vTexCoord" );
        glEnableVertexAttribArray( vTexCoord );
        glVertexAttribPointer( vTexCoord, 2, GL_FLOAT, GL_FALSE, 0,
                               BUFFER_OFFSET(offset) );
        offset += B.tSize;
    }
}

///
// Display callback
//
// Invoked whenever the image must be redrawn
///
void display( void )
{
    // clear and draw params..
    glClear( GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT );

    //draw the teapot
    drawShape( tshader, pshader, OBJ_TEAPOT,     teapotBuffers      );
    drawShape( tshader, pshader, OBJ_TEACUP,     teacupBuffers      );
    drawShape( tshader, pshader, OBJ_SPOON,      spoonBuffers       );
    drawShape( tshader, pshader, OBJ_PLATE,      plateBuffers       );
    drawShape( tshader, pshader, OBJ_GLASS,      glassBuffers       );
    drawShape( tshader, pshader, OBJ_COOKIE1,    cookie1Buffers     );
    drawShape( tshader, pshader, OBJ_COOKIE2,    cookie2Buffers     );
    drawShape( tshader, pshader, OBJ_COOKIE3,    cookie3Buffers     );
    drawShape( tshader, pshader, OBJ_COOKIE4,    cookie4Buffers     );
    drawShape( tshader, pshader, OBJ_COOKIE5,    cookie5Buffers     );
    drawShape( tshader, pshader, OBJ_BAGEL1,     bagel1Buffers 	    );
    drawShape( tshader, pshader, OBJ_BAGEL2,     bagel2Buffers      );
    drawShape( tshader, pshader, OBJ_APPLETEAPOT,appleTeapotBuffers );
    drawShape( tshader, pshader, OBJ_APPLEPLATE, applePlateBuffers  );
    drawShape( tshader, pshader, OBJ_FERN1,      fern1Buffers       );
    drawShape( tshader, pshader, OBJ_FERN2,      fern2Buffers       );
    drawShape( tshader, pshader, OBJ_FERN3,      fern3Buffers       );
    drawShape( tshader, pshader, OBJ_TABLE,      tableBuffers       );

}

///
// Keyboard callback
//
// We don't need to distinguish between (e.g.) 'a' and 'A', so
// we can use the simpler form of callback
///
void keyboard( GLFWwindow *window, int key, int scan, int action, int mods )
{
    if( action != GLFW_PRESS )    // only activate on press, not rpt/release
        return;

    switch( key ) {

        case GLFW_KEY_A:    // animate
            animating = true;
            break;

        case GLFW_KEY_S:    // stop animating
            animating = false;
            break;

        case GLFW_KEY_R:    // reset transformations
            angles = 0.0f;
            xlate[0] = 1.3f;
	    xlate[1] = 2.2f;
	    xlate[2] = -1.5f;
	    sphereState = 0;
            break;

        case GLFW_KEY_ESCAPE:   // terminate the program
        case GLFW_KEY_Q:
            glfwSetWindowShouldClose( window, 1 );
            break;
    }

    updateDisplay = true;
}

// Animate the objects (maybe)
void animate( void ) {
    if( animating ) {
	// first, rotation for the objects
        angles += 1.0f;
	if( angles >= 360.0f ) {
	    angles = 0.0f;
	}
	// next, translation for the sphere
	switch( sphereState ) {
	    case 0:  // first side
		// horizontal move until tx reaches 0.5
	        if( xlate[0] > 0.5f ) {
		    xlate[0] -= 0.025f;
		    break;
		} else {
		    // fall through into state 1
		    sphereState = 1;
		}
	    case 1:  // second side
		// move downward to the right until ty reaches 1.4
	        if( xlate[1] > 1.4f ) {
		    xlate[0] += 0.0125;
		    xlate[1] -= 0.025f;
		    break;
		} else {
		    // fall through into state 2
		    sphereState = 2;
		}
	    case 2:  // third side
		// move upward to the right until tx reaches 1.3
	        if( xlate[0] < 1.3f ) {
		    xlate[0] += 0.0125;
		    xlate[1] += 0.025f;
		    break;
		} else {
		    // move back to state 0
		    sphereState = 0;
		    xlate[0] = 1.3f;
		    xlate[1] = 2.2f;
		}
	}
        updateDisplay = true;
    }
}

void glfwError( int code, const char *desc )
{
    cerr << "GLFW error " << code << ": " << desc << endl;
    exit( 2 );
}

///
// main program for tessellation assignment
///
int main( int argc, char **argv ) {

    glfwSetErrorCallback( glfwError );

    if( !glfwInit() ) {
        cerr << "Can't initialize GLFW!" << endl;
        exit( 1 );
    }

    // NOTE:  Mac users may need to uncomment the following four lines
    // in order to force an OpenGL 3.2 (or better) context

    // glfwWindowHint( GLFW_CONTEXT_VERSION_MAJOR, 3 );
    // glfwWindowHint( GLFW_CONTEXT_VERSION_MINOR, 2 );
    // glfwWindowHint( GLFW_OPENGL_FORWARD_COMPAT, GL_TRUE );
    // glfwWindowHint( GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE );

    GLFWwindow *window = glfwCreateWindow( w_width, w_height,
        "Lab 6 - Shading and Texturing", NULL, NULL );

    if( !window ) {
        cerr << "GLFW window create failed!" << endl;
        glfwTerminate();
        exit( 1 );
    }

    glfwMakeContextCurrent( window );

#ifndef __APPLE__
    glewExperimental = GL_TRUE;
    GLenum err = glewInit();
    if( err != GLEW_OK ) {
        cerr << "GLEW error: " << glewGetErrorString(err) << endl;
        glfwTerminate();
        exit( 1 );
    }
    if( !GLEW_VERSION_3_2 ) {
        cerr << "GLEW: OpenGL 3.2 not available" << endl;
        if( !GLEW_VERSION_2_1 ) {
            cerr << "GLEW: OpenGL 2.1 not available, either!" << endl;
            glfwTerminate();
            exit( 1 );
        }
    }
#endif

    // determine whether or not we can use GLSL 1.50
    int maj = glfwGetWindowAttrib( window, GLFW_CONTEXT_VERSION_MAJOR );
    int min = glfwGetWindowAttrib( window, GLFW_CONTEXT_VERSION_MINOR );

    cerr << "GLFW: using " << maj << "." << min << " context" << endl;
    if( maj < 3 || (maj == 3 && min < 2) ) {
        // nope!
        cerr << "*** GLSL 1.50 shaders may not compile" << endl;
    }

    init();

    glfwSetKeyCallback( window, keyboard );

    while( !glfwWindowShouldClose(window) ) {
        animate();
        if( updateDisplay ) {
            updateDisplay = false;
            display();
            glfwSwapBuffers( window );
        }
        glfwPollEvents();
    }

    glfwDestroyWindow( window );
    glfwTerminate();


    return 0;
}
