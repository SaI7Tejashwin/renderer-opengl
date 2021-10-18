#shader vertex
#version 330 core

layout(location = 0) in vec4 position;

void main()
{
 gl_Position = position;  /*the positions array we have in Application.cpp is indexed in vec2*/
}						// but we need to take the gl_Position in vec4 format

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{
 color = vec4(1.0, 0.0, 0.0, 1.0); //color is formatted in RGBA format.
}
