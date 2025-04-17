#vertex
#version 330 core 
layout (location = 0) in vec3 PositionOS; 
layout (location = 1) in vec4 aColor; 
out vec4 ourColor;
void main() 
{ 
   gl_Position = vec4(PositionOS, 1.0); 
   ourColor = aColor;
};

#fragment
#version 330 core

out vec4 FragColor;
in vec4 ourColor;
void main()
{
   FragColor = ourColor;
};
