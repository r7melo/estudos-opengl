#version 330 core

// POsitions/Coordinates
layout (location = 0) in vec3 aPos;

// Color
layout (location = 1) in vec3 aColor;

// Texture Coordinates
layout (location = 2) in vec2 aTex;

// Output to fragment shader
out vec3 color;

// Texture coordinates output
out vec2 texCoord;

// Scale
uniform float scale;

// Matrices
uniform mat4 model; 
uniform mat4 view; 
uniform mat4 proj;




void main()
{
   // Apply transformations
   gl_Position = proj * view * model * vec4(aPos * scale, 1.0);

   // Pass color to fragment shader
   color = aColor;

   // Pass texture coordinates to fragment shader
   texCoord = aTex;
}