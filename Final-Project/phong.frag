#version 130

// Phong fragment shader
//
// Contributor:  Saurabh Anant Wani (saw4058)

// INCOMING DATA
// Here is where you should add the variables you need in order
// to propogate data from the vertex shader to the fragment shader
// so that it can do the shading computations
uniform vec4 ambientMaterialColor;
uniform vec4 diffuseMaterialColor;
uniform vec4 specularMaterialColor;
uniform vec4 ambientLightColor;
uniform vec4 lightSourceColor;
uniform vec4 lightSourceColor1;

uniform float ambientReflectionCoefficient;
uniform float diffuseReflectionCoefficient;
uniform float specularReflectionCoefficient;
uniform float specularExponent;

vec4 ambientParameter, diffuseParameter, specularParameter;
vec3 L;
vec3 N;
vec3 V;

varying vec3 Lvector;
varying vec3 Nvector;
varying vec3 Vvector;
vec4 tempColor;
// OUTGOING DATA
out vec4 finalColor;


void main()
{

	vec4 ambientParameter;
	vec4 diffuseParameter;
	vec4 specularParameter;
	vec3 R;
	L = normalize(Lvector - Vvector);
	N = normalize(Nvector);
	V = normalize(Vvector);
	R = normalize(reflect(L, N));

	ambientParameter  = ambientLightColor     * ambientMaterialColor * ambientReflectionCoefficient;
	diffuseParameter  = diffuseMaterialColor  * lightSourceColor    * diffuseReflectionCoefficient  * dot(normalize(Lvector - Vvector),N);
	specularParameter = specularMaterialColor * lightSourceColor    * specularReflectionCoefficient * pow(clamp(dot(R,V), 0, 1), specularExponent);
	

    	// Replace this code with your implementation of this shader
    	finalColor = ambientParameter + diffuseParameter + specularParameter;
}
