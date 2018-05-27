//
// Alternate vertex shader for the transformation assignment
//
// Created by Warren R. Carithers 2016/04/22.
//
// Contributor:  Saurabh Anant Wani (saw4058)
//

#version 120

// attribute:  vertex position
attribute vec4 vPosition;

// add other global shader variables to hold the
// parameters your application code is providing
//Vectors 
uniform vec3 eye, look, upparameter, scale, rotate, translate;
//Variables
uniform float l, r, f, n, t, b, prjTyp;

void main()
{
	// Calculating vector n, vector u, vector v.
	vec3 vectN = normalize(eye-look);
	vec3 vectU = normalize(cross(upparameter,vectN));
	vec3 vectV = normalize(cross(vectN, vectU));

	// With help of n, u, v vectors and view transform matrix, calculating world to camera co-ordinates. 
	mat4 matrixWorld2Cam = mat4(vectU.x, 	      vectV.x,  	vectN.x, 	  0,
				    vectU.y, 	      vectV.y, 		vectN.y, 	  0,
				    vectU.z, 	      vectV.z, 		vectN.z,	  0,
				    -dot(vectU, eye), -dot(vectV, eye), -dot(vectN, eye), 1);

	// Using the x, y and z scaling parameters, calculating the scaling matrix.
	mat4 matrixScale   = mat4(scale.x,     0,	    0,       0,
			      	    0,           scale.y,   0,       0,
				    0,           0,         scale.z, 0,
				    0,           0,         0,       1);

	// Using the x, y and z translation parameters, calculating the translation matrix.
	mat4 matrixTranslate = mat4(1,           0,	      0,	   0,
				    0,	         1,           0,           0,
				    0,           0,	      1,           0,
				    translate.x, translate.y, translate.z, 1);



	// Considering the sine and cosine of the rotational angle, calculating the rotation matrix about X-axis.
	mat4 XmatrixRotate = mat4(1,         0,                       0,  	                  0,
				    0,         cos(radians(rotate.x)),  -sin(radians(rotate.x)),  0,
				    0,	       sin(radians(rotate.x)),  cos(radians(rotate.x)),   0,
				    0,         0, 			0,			  1);

	// Considering the sine and cosine of the rotational angle, calculating the rotation matrix about Y-axis.
	mat4 YmatrixRotate = mat4(cos(radians(rotate.y)), 0, -sin(radians(rotate.y)),   0,
				    0,  		    1, 0,                         0,
				    sin(radians(rotate.y)), 0, cos(radians(rotate.y)),    0,
				    0,  		    0, 0,                       1);

	// Considering the sine and cosine of the rotational angle, calculating the rotation matrix about Z-axis.
	mat4 ZmatrixRotate = mat4( cos(radians(rotate.z)), sin(radians(rotate.z)), 0, 0,
				    -sin(radians(rotate.z)), cos(radians(rotate.z)), 0, 0,
				     0,                      0,                      1, 0,
				     0,                      0,                      0, 1);

	mat4 matRotate = XmatrixRotate * YmatrixRotate * ZmatrixRotate;

	// Merging translation matrix, rotation matrix around x,y,z axes and scaling matrix.
	mat4 matrixTransform = matrixTranslate * matRotate * matrixScale;


	
	// Considering the projection type calculating the projection matrix. 
	mat4 matrixProjection;
	// Orthographic projection
	if(prjTyp ==2.0)
	{
		matrixProjection = mat4((2.0/(r-l)),    0,            0,            0,
					0,              (2.0/(t-b)),  0,            0,
				        0,              0,            -2.0/(f-n),   0,
					-(r+l)/(r-l), -(t+b)/(t-b), -(f+n)/(f-n),   1);
	}
	// Frustum projection
	else
	{
		matrixProjection = mat4((2.0*n/(r-l)), 0,             0,              0,
					0,             (2.0*n/(t-b)), 0,              0,
				        (r+l)/(r-l),   (t+b)/(t-b),   -(f+n)/(f-n),   -1,
					0,             0,             -2.0*f*n/(f-n),  0);
	}

	// Calculating the model view matrix. 
	mat4 matrixModelView = matrixWorld2Cam * matrixTransform;

    // Obtaining the co-ordinates via multiplication of projection matrix and model view matrix with the object co-ordinates. 
    gl_Position =  matrixProjection * matrixModelView * vPosition;
}
