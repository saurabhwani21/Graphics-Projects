//
//  Lighting
//
//  Created by Warren R. Carithers 2016/11/22.
//  Based on code created by Joe Geigel on 1/23/13.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Contributor:  Saurabh Anant Wani (saw4058)
//
//  Simple class for setting up Phong illumination/shading.
//
//  This code can be compiled as either C or C++.
//

#include "Lighting.h"
#include "Shapes.h"


// Add any global definitions and/or variables you need here.
///
// This function sets up the lighting, material, and shading parameters
// for the Phong shader.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the vertex shader.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
// @param obj - The object type of the object being drawn
///
void setUpPhong( GLuint program, int obj )
{
    // Add your code here+
	if (obj == 2 || obj == 4 || obj == 5)
	{
		// Settings properties and characteristics for the teacup, plate and glass.
		glUniform4f(glGetUniformLocation(program, "ambientMaterialColor"),  1.0f,1.0f,1.0f,1.0f);
		glUniform4f(glGetUniformLocation(program, "diffuseMaterialColor"),  1.0f,1.0f,1.0f,1.0f);
		glUniform4f(glGetUniformLocation(program, "specularMaterialColor"), 1.0f,1.0f,1.0f,1.0f);
	}
	if (obj == 14 || obj == 13 || obj == 1)
	{
		// Settings properties and characteristics for the both apples and teapot		
		glUniform4f(glGetUniformLocation(program, "ambientMaterialColor"),  0.82f, 0.68f,0.0f,1.0f);
		glUniform4f(glGetUniformLocation(program, "diffuseMaterialColor"),  1.0f  ,0.82f,0.0f,1.0f);
		glUniform4f(glGetUniformLocation(program, "specularMaterialColor"), 0.633f,0.727811f,0.633f,1.0f);
	}
	if (obj == 12 || obj == 6 || obj == 7 || obj == 8 || obj == 9 || obj == 10 || obj == 11)
	{
		// Settings properties and characteristics for the cookies and bagels		
		glUniform4f(glGetUniformLocation(program, "ambientMaterialColor"),  1.0f,0.55f,0.56f,1.0f);
		glUniform4f(glGetUniformLocation(program, "diffuseMaterialColor"),  1.0f,0.63f,0.0f,1.0f);
		glUniform4f(glGetUniformLocation(program, "specularMaterialColor"), 0.633f,0.727811f,0.633f,1.0f);
	}
	if (obj == 3)
	{
		// Settings properties and characteristics for the spoon		
		glUniform4f(glGetUniformLocation(program, "ambientMaterialColor"), 1.0f,0.59f,0.32f,1.0f);
		glUniform4f(glGetUniformLocation(program, "diffuseMaterialColor"), 0.0f,0.0f,0.0f,1.0f);
		glUniform4f(glGetUniformLocation(program, "specularMaterialColor"), 0.633f,0.727811f,0.633f,1.0f);
	}
	if (obj == 15 || obj == 16 || obj == 17)
	{
		// Settings properties and characteristics for the green leaves.
		glUniform4f(glGetUniformLocation(program, "ambientMaterialColor"), 0.5f,  0.5f, 0.5f, 1.0f);
		glUniform4f(glGetUniformLocation(program, "diffuseMaterialColor"), 0.49f, 0.99f, 0.0f, 1.0f);
		glUniform4f(glGetUniformLocation(program, "specularMaterialColor"), 1.0,  1.0, 1.0, 1.0);
		glUniform1f(glGetUniformLocation(program, "ambientReflectionCoefficient"),  0.5);
		glUniform1f(glGetUniformLocation(program, "diffuseReflectionCoefficient"),  0.8);
		glUniform1f(glGetUniformLocation(program, "specularReflectionCoefficient"), 1.0);
		glUniform1f(glGetUniformLocation(program, "specularExponent"), 50.0);
	}
	glUniform1f(glGetUniformLocation(program, "ambientReflectionCoefficient"),  0.5);
	glUniform1f(glGetUniformLocation(program, "diffuseReflectionCoefficient"),  0.7);
	glUniform1f(glGetUniformLocation(program, "specularReflectionCoefficient"), 1.0);
	glUniform1f(glGetUniformLocation(program, "specularExponent"), 10.0);
	//Setting the light properties
	glUniform4f(glGetUniformLocation(program, "lightSourcePosition"),  3.0,  9.0, 2.0, 1.0);
	glUniform4f(glGetUniformLocation(program, "lightSourcePosition1"), 1.0,  1.0, 10.0, 1.0);
	glUniform4f(glGetUniformLocation(program, "lightSourceColor"),     1.0,  1.0, 1.0, 1.0);
	//Setting the ambient light of the scene
	glUniform4f(glGetUniformLocation(program, "ambientLightColor"),    0.5,  0.5, 0.5, 1.0);
}
