#version 130

// Texture mapping vertex shader
//
// Contributor:  Saurabh Anant Wani (saw4058)


// Here is where you should add the variables you need in order
// to propogate data from the vertex shader to the fragment shader
// so that it can do the shading and texture mapping computations

// OUTGOING DATA
out vec4 finalColor;

// INCOMING DATA
in vec2 vertexCoord;
uniform sampler2D texture1;
uniform sampler2D texture2;

vec4 temp;
vec4 tempBack;

void main()
{
   // Replace this code with your implementation of this shader
    finalColor = texture2D(texture1, vertexCoord);
	
}
