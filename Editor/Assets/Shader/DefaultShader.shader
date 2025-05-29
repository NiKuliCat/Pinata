#program   vertex      // this is vertex shader program
#version 450 core   
layout(location = 0) in vec3 PositionOS;
layout(location = 1) in vec4 VertexColor;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in int index;
layout(location = 4) in int id;
uniform mat4 _MVP;
uniform vec4 _BaseColor;
out vec4 ourColor;
out vec2 uv;
flat out int TexIndex;
flat out  int v_ObjectID;
void main()
{
	gl_Position = _MVP * vec4(PositionOS, 1.0);
	ourColor = VertexColor ;
	uv = texcoord;
	TexIndex = index;
	v_ObjectID = id;	
};


#program     fragment 
#version 450 core   
layout(location = 0) out vec4 FragColor;
layout(location = 1) out int IDColor;
in vec2 uv;
in vec4 ourColor;
flat in int TexIndex;
flat in int v_ObjectID;
uniform sampler2D   _MainTex[32];
uniform vec4 _BaseColor;
void main()
{
	FragColor = ourColor *  texture(_MainTex[TexIndex], uv);
	IDColor =   v_ObjectID;
};