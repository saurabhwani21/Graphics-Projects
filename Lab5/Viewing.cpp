//
//  Viewing
//
//  Created by Warren R. Carithers 2016/11/11.
//  Based on code created by Joe Geigel on 1/23/13.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Simple class for setting up the viewing and projection transforms
//  for the Transformation Assignment.
//
//  This code can be compiled as either C or C++.
//
//  Contributor:  Saurabh Anant Wani (saw4058)
//

#if defined(_WIN32) || defined(_WIN64)
#include <windows.h>
#endif

#ifndef __APPLE__
#include <GL/glew.h>
#endif

#include <GLFW/glfw3.h>

#include "Viewing.h"

///
// This function sets up the view and projection parameter for a frustum
// projection of the scene. See the assignment description for the values
// for the projection parameters.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void setUpFrustum( GLuint program )
{
    // Add your code here.
	glUniform1f(glGetUniformLocation(program, "prjTyp"), 1.0);
	//Left
	glUniform1f(glGetUniformLocation(program, "l"),     -1.0);
	//Right
	glUniform1f(glGetUniformLocation(program, "r"),      1.0);
	//Far	
	glUniform1f(glGetUniformLocation(program, "f"),    4.5);
	//Near	
	glUniform1f(glGetUniformLocation(program, "n"),    0.9);
	//Bottom	
	glUniform1f(glGetUniformLocation(program, "b"),     -1.0);
	//Top	
	glUniform1f(glGetUniformLocation(program, "t"),      1.0);

}


///
// This function sets up the view and projection parameter for an
// orthographic projection of the scene. See the assignment description
// for the values for the projection parameters.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void setUpOrtho( GLuint program )
{
    // Add your code here.
	glUniform1f(glGetUniformLocation(program, "prjTyp"), 2.0);
	//Left
	glUniform1f(glGetUniformLocation(program, "l"),     -1.0);
	//Right
	glUniform1f(glGetUniformLocation(program, "r"),      1.0);
	//Far	
	glUniform1f(glGetUniformLocation(program, "f"),    4.5);
	//Near	
	glUniform1f(glGetUniformLocation(program, "n"),    0.9);
	//Bottom	
	glUniform1f(glGetUniformLocation(program, "b"),     -1.0);
	//Top	
	glUniform1f(glGetUniformLocation(program, "t"),      1.0);

}


///
// This function clears any model transformations, setting the values
// to the defaults: no scaling (scale factor of 1), no rotation (degree
// of rotation = 0), and no translation (0 translation in each direction).
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void clearTransforms( GLuint program )
{
    // Add your code here.
	glUniform3f(glGetUniformLocation(program, "scale"    ), 1.0, 1.0, 1.0); 
	glUniform3f(glGetUniformLocation(program, "rotate"   ), 0.0, 0.0, 0.0); 
	glUniform3f(glGetUniformLocation(program, "translate"), 0.0, 0.0, 0.0); 
}


///
// This function sets up the transformation parameters for the vertices
// of the teapot.  The order of application is specified in the driver
// program.
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
// @param scaleX - amount of scaling along the x-axis
// @param scaleY - amount of scaling along the y-axis
// @param scaleZ - amount of scaling along the z-axis
// @param rotateX - angle of rotation around the x-axis, in degrees
// @param rotateY - angle of rotation around the y-axis, in degrees
// @param rotateZ - angle of rotation around the z-axis, in degrees
// @param translateX - amount of translation along the x axis
// @param translateY - amount of translation along the y axis
// @param translateZ - amount of translation along the z axis
///
void setUpTransforms( GLuint program,
    GLfloat scaleX, GLfloat scaleY, GLfloat scaleZ,
    GLfloat rotateX, GLfloat rotateY, GLfloat rotateZ,
    GLfloat translateX, GLfloat translateY, GLfloat translateZ )
{
    // Add your code here.
	glUniform3f(glGetUniformLocation(program, "scale"    ), scaleX,     scaleY,     scaleZ    ); 
	glUniform3f(glGetUniformLocation(program, "translate"), translateX, translateY, translateZ); 
	glUniform3f(glGetUniformLocation(program, "rotate"   ), rotateX,    rotateY,    rotateZ   );
}


///
// This function clears any changes made to camera parameters, setting the
// values to the defaults: eye (0.0,0.0,0.0), lookat (0,0,0.0,-1.0),
// and up vector (0.0,1.0,0.0).
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
///
void clearCamera( GLuint program )
{
    // Add your code here. 
	glUniform3f(glGetUniformLocation(program, "eye"        ), 0.0, 0.0,  0.0);
	glUniform3f(glGetUniformLocation(program, "upparameter"), 0.0, 1.0,  0.0); 
	glUniform3f(glGetUniformLocation(program, "look"       ), 0.0, 0.0, -1.0);
}

///
// This function sets up the camera parameters controlling the viewing
// transformation.
//
// You will need to write this function, and maintain all of the values
// which must be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
// @param eyeX - x coordinate of the camera location
// @param eyeY - y coordinate of the camera location
// @param eyeZ - z coordinate of the camera location
// @param lookatX - x coordinate of the lookat point
// @param lookatY - y coordinate of the lookat point
// @param lookatZ - z coordinate of the lookat point
// @param upX - x coordinate of the up vector
// @param upY - y coordinate of the up vector
// @param upZ - z coordinate of the up vector
///
void setUpCamera( GLuint program,
    GLfloat eyeX, GLfloat eyeY, GLfloat eyeZ,
    GLfloat lookatX, GLfloat lookatY, GLfloat lookatZ,
    GLfloat upX, GLfloat upY, GLfloat upZ )
{
    // Add your code here.
	glUniform3f(glGetUniformLocation(program, "eye"        ), eyeX, eyeY, eyeZ);
	glUniform3f(glGetUniformLocation(program, "look"       ), lookatX, lookatY, lookatZ);
	glUniform3f(glGetUniformLocation(program, "upparameter"), upX, upY, upZ); 


}
