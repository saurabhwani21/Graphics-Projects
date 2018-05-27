#version 130

// Texture mapping vertex shader
//
// Contributor:  Saurabh Anant Wani (saw4058)


// Here is where you should add the variables you need in order
// to propogate data from the vertex shader to the fragment shader
// so that it can do the shading and texture mapping computations
uniform vec4 ambientLightColor1;
uniform vec4 lightSourceColor1;

uniform float reflectionCoefficientAmbient;
uniform float reflectionCoefficientDiffuse;
uniform float reflectionCoefficientReflection;
uniform float specular_Exponent;

vec4 ambientParameter;
vec4 diffuseParameter;
vec4 specularParameter;
vec3 L;
vec3 N;
vec3 V;
vec3 R;
varying vec3 Lvector;
varying vec3 Nvector;
varying vec3 Vvector;

// OUTGOING DATA
out vec4 finalColor;

// INCOMING DATA
in vec2 vertexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;

//Temporary variables for front and the back of the back smiley
vec4 temp;
vec4 tempBack;

void main()
{
    // Replace this code with your implementation of this shader
	temp     	  = texture2D(texture1, vertexCoord);
	tempBack 	  = texture2D(texture2, vertexCoord);
	L        	  = normalize(Lvector - Vvector);
	N        	  = normalize(Nvector);
	V        	  = normalize(Vvector);
	R        	  = normalize(reflect(L, N));
	vec4 ambientTemp  = ambientLightColor1              * reflectionCoefficientAmbient;
	vec4 diffuseTemp  = reflectionCoefficientDiffuse    * lightSourceColor1 * dot(L,N);
	vec4 specularTemp = reflectionCoefficientReflection * lightSourceColor1 * pow(clamp(dot(R,V), 0, 1), specular_Exponent);
    	if(gl_FrontFacing)
	{
		// Showing smiley face for front side
		ambientParameter  = ambientTemp * temp;
		diffuseParameter  = temp        * diffuseTemp; 
		specularParameter = temp        * specularTemp;      
	}
	else
	{		
		// Showing frowny face for the back side
		ambientParameter  = ambientTemp * tempBack;
		diffuseParameter  = tempBack    * diffuseTemp;
		specularParameter = tempBack    * specularTemp;	
	}
	//Setting the final color
	finalColor        = ambientParameter  + diffuseParameter + specularParameter;
}
