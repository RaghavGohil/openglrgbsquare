#shader vertex
#version 330 core

layout(location = 0) in vec4 vertexPosition;

out vec4 _color; // from the fragment shader..

void main()
{

   gl_Position = vertexPosition;

};

#shader fragment
#version 330 core

layout(location = 0) out vec4 color;

void main()
{

	//set it to default _color after
    color = vec4(0.2f,0.3f,0.8f,1.0f);

};

/** Moving a variable from vertex to fragment shader..

#version 330 core
layout (location = 0) in vec3 aPos; // the position variable has attribute position 0

out vec4 vertexColor; // specify a color output to the fragment shader

void main()
{    gl_Position = vec4(aPos, 1.0); // see how we directly give a vec3 to vec4's constructor
    vertexColor = vec4(0.5, 0.0, 0.0, 1.0); // set the output variable to a dark-red color
}

#version 330 core
out vec4 FragColor;

in vec4 vertexColor; // the input variable from the vertex shader (same name and same type)

void main()
{
    FragColor = vertexColor;
}

*/