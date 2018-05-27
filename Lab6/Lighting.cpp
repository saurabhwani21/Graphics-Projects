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
	
	if (obj == 1 )
	{
		// Settings properties and characteristics for the teapot
		glUniform4f(glGetUniformLocation(program, "ambientMaterialColor"), 0.5f,  0.1f, 0.9f, 1.0f);

		glUniform4f(glGetUniformLocation(program, "diffuseMaterialColor"), 0.89f, 0.0f, 0.0f, 1.0f);

		glUniform4f(glGetUniformLocation(program, "specularMaterialColor"), 1.0,  1.0, 1.0, 1.0);

		glUniform1f(glGetUniformLocation(program, "ambientReflectionCoefficient"),  0.5);

		glUniform1f(glGetUniformLocation(program, "diffuseReflectionCoefficient"),  0.7);

		glUniform1f(glGetUniformLocation(program, "specularReflectionCoefficient"), 1.0);

		glUniform1f(glGetUniformLocation(program, "specularExponent"), 10.0);

	}
	else if (obj == 2)
	{
		// Settings properties and characteristics for the sphere
		glUniform4f(glGetUniformLocation(program, "ambientMaterialColor"), 0.5f,  0.5f, 0.5f, 1.0f);

		glUniform4f(glGetUniformLocation(program, "diffuseMaterialColor"), 0.49f, 0.99f, 0.0f, 1.0f);

		glUniform4f(glGetUniformLocation(program, "specularMaterialColor"), 1.0,  1.0, 1.0, 1.0);

		glUniform1f(glGetUniformLocation(program, "ambientReflectionCoefficient"),  0.5);

		glUniform1f(glGetUniformLocation(program, "diffuseReflectionCoefficient"),  0.8);

		glUniform1f(glGetUniformLocation(program, "specularReflectionCoefficient"), 1.0);

		glUniform1f(glGetUniformLocation(program, "specularExponent"), 50.0);
	}
	//Setting the light properties
	glUniform4f(glGetUniformLocation(program, "lightSourcePosition"), 3.0,  9.0, 2.0, 1.0);
	glUniform4f(glGetUniformLocation(program, "lightSourceColor"),    1.0,  1.0, 1.0, 1.0);
	//Setting the ambient light of the scene
	glUniform4f(glGetUniformLocation(program, "ambientLightColor"),   0.5,  0.5, 0.5, 1.0);

}
