//
//  Textures
//
//  Created by Warren R. Carithers 2016/11/22.
//  Based on code created by Joe Geigel on 1/23/13.
//  Copyright 2016 Rochester Institute of Technology.  All rights reserved.
//
//  Contributor:  Saurabh Anant Wani (saw4058)
//
//  Simple class for setting up texture mapping parameters.
//
//  This code can be compiled as either C or C++.
//

#ifdef __cplusplus
#include <iostream>
#else
#include <stdio.h>
#endif

#include "Textures.h"
#include "Shapes.h"
#include <string>

// this is here in case you are using SOIL;
// if you're not, it can be deleted.
#include <SOIL.h>

#ifdef __cplusplus
using namespace std;
#endif

// Add any global definitions and/or variables you need here.
GLuint id1, id2;
GLint baseImageLoc, normalMapLoc, shadowMapLoc;

///
// This function loads texture data for the GPU.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the various shaders.
///
void loadTexture( void )
{
    // Add your code here.
	//Loading the first texture
    	id1 = SOIL_load_OGL_texture (
        "index.jpg", 
         SOIL_LOAD_AUTO, 
         SOIL_CREATE_NEW_ID, 
         SOIL_FLAG_MIPMAPS | SOIL_FLAG_INVERT_Y |
         SOIL_FLAG_TEXTURE_REPEATS
	);
}

///
// This function sets up the parameters for texture use.
//
// You will need to write this function, and maintain all of the values
// needed to be sent to the various shaders.
//
// @param program - The ID of an OpenGL (GLSL) shader program to which
//    parameter values are to be sent
// @param obj - The object type of the object being drawn
///
void setUpTexture( GLuint program, int obj )
{
	
	if(obj == 18)
	{
		// Applying texture for the table object.
		// Add your code here.
		//Setting the light properties
		glUniform4f(glGetUniformLocation(program, "lightSourcePosition1"), 3.0,  9.0, 2.0, 1.0);
		glUniform4f(glGetUniformLocation(program, "lightSourceColor1"),    1.0,  1.0, 1.0, 1.0);
		//Setting the ambient light of the scene
		glUniform4f(glGetUniformLocation(program, "ambientLightColor1"),   0.5,  0.5, 0.5, 1.0);
		//Setting the reflective characteristics of the quad
		glUniform1f(glGetUniformLocation(program, "reflectionCoefficientAmbient"),     0.7);
		glUniform1f(glGetUniformLocation(program, "reflectionCoefficientDiffuse"),     0.7);
		glUniform1f(glGetUniformLocation(program, "reflectionCoefficientReflection"),  1.0);
		glUniform1f(glGetUniformLocation(program, "specular_Exponent"),               40.0);
		//Activating the shader program
		glUseProgram( program );
	    	glActiveTexture(GL_TEXTURE0+0);
		glBindTexture(GL_TEXTURE_2D, id1);	
		glActiveTexture(GL_TEXTURE0 + 2); 
		glBindTexture(GL_TEXTURE_2D, id2);	
		//Getting sampler variables location
		baseImageLoc = glGetUniformLocation(program, "texture1");
		normalMapLoc = glGetUniformLocation(program, "texture2");	
		// Texutre unit 0
		glUniform1i(baseImageLoc, 0); 
		// Texutre unit 2
		glUniform1i(normalMapLoc, 2); 
	}	
	
}
