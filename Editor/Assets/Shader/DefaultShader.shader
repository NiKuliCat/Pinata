#program   vertex      // this is vertex shader program
#version 330 core
layout(location = 0) in vec3 PositionOS;
layout(location = 1) in vec4 VertexColor;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in int index;
uniform mat4 _MVP;
uniform vec4 _BaseColor;
out vec4 ourColor;
varying vec2 uv;
out float TexIndex;
void main()
{
	gl_Position = _MVP * vec4(PositionOS, 1.0);
	ourColor = VertexColor ;
	uv = texcoord;
	TexIndex = index;
};


#program     fragment 
#version 330 core
layout(location = 0) out vec4 FragColor;
varying vec2 uv;
in vec4 ourColor;
in float TexIndex;
uniform sampler2D   _MainTex[32];
uniform vec4 _BaseColor;
void main()
{
	FragColor = ourColor *  texture(_MainTex[int(TexIndex + 0.01f)], uv);
	//FragColor = vec4(int(TexIndex) ,int(TexIndex) ,int(TexIndex) ,1.0f);
};