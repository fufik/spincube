#version 410 core
// Input vertex data, different for all executions of this shader.
layout (location = 0) in vec3 position;
//layout (location = 1) in vec3 vertexColor;
layout (location = 1) in vec2 vertexUV;
// Values that stay constant for the whole mesh.
uniform mat4 MVP;
//out vec3 fragmentColor;
out vec2 UV;
void main()
{
    gl_Position = MVP * vec4(position.x, position.y, position.z,1.0);
    //fragmentColor = vertexColor;
    UV = vertexUV;
}
