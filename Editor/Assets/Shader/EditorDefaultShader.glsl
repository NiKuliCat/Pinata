#program   vertex      // this is vertex shader program
#version 450 core
layout(location = 0) in vec3 PositionOS;
layout(location = 1) in vec4 VertexColor;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in int index;
layout(location = 4) in int id;
uniform mat4 _MVP;
uniform vec4 _BaseColor;

layout(std140, binding = 0) uniform Camera
{
	mat4 ViewProjection;
}

struct Attributes
{
	vec4 color;
	vec2 uv;
};

layout(location = 0) out Attributes output;
layout(location = 2) out flat int TexIndex;
layout(location = 3) out flat int  v_ObjectID;

void main()
{
	output.color = VertexColor;
	output.uv = texcoord;
	TexIndex = index;
	v_ObjectID = id;
};


#program     fragment
#version 450 core
layout(location = 0) out vec4 FragColor;
layout(location = 1) out int IDColor;

struct Attributes
{
	vec4 color;
	vec2 uv;
};
layout(location = 0) in Attributes input;
layout(location = 2) in flat int TexIndex;
layout(location = 3) in flat int  v_ObjectID;

layout(binding = 0) uniform sampler2D _MainTex[32];
void main()
{
	FragColor = input.color * texture(_MainTex[TexIndex], input.uv);
	IDColor = v_ObjectID;
};