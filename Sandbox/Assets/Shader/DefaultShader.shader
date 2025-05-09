#program   vertex      // this is vertex shader program
#version 330 core
layout(location = 0) in vec3 PositionOS;
layout(location = 1) in vec4 VertexColor;
layout(location = 2) in vec2 texcoord;
uniform mat4 _MVP;
uniform vec4 _BaseColor;
out vec4 ourColor;
out vec2 uv;
void main()
{
	gl_Position = _MVP * vec4(PositionOS, 1.0);
	ourColor = VertexColor ;
	uv = texcoord;
};


#program     fragment 
#version 330 core
layout(location = 0) out vec4 FragColor;
in vec2 uv;
in vec4 ourColor;
uniform sampler2D  _MainTex;
uniform vec4 _BaseColor;
uniform int _Intensity;
void main()
{
	FragColor = _BaseColor * texture(_MainTex, uv);
};