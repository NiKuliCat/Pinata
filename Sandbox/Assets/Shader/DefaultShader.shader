#program   vertex      // this is vertex shader program
#version 330 core
layout(location = 0) in vec3 PositionOS;
layout(location = 1) in vec4 VertexColor;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in float index;
uniform mat4 _MVP;
uniform vec4 _BaseColor;
out vec4 ourColor;
out vec2 uv;
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
in vec2 uv;
in vec4 ourColor;
in float TexIndex;
uniform sampler2D   _MainTex[32];
uniform vec4 _BaseColor;
uniform int _Intensity;
void main()
{
	FragColor = ourColor *  texture(_MainTex[int(TexIndex)], uv);
};