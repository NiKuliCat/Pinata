#program   vertex    
#version 450 core
layout(location = 0) in vec3 PositionOS;
layout(location = 1) in vec4 VertexColor;
layout(location = 2) in vec2 texcoord;
layout(location = 3) in int index;
layout(location = 4) in int id;

layout(std140, binding = 0) uniform Camera
{
	mat4 ViewProjection;
};

struct Attributes
{
	vec4 color;
	vec2 uv;
};

layout(location = 0) out Attributes Attri_Output;
layout(location = 2) out flat int TexIndex;
layout(location = 3) out flat int  v_ObjectID;

void main()
{
	Attri_Output.color = VertexColor;
	Attri_Output.uv = texcoord;
	TexIndex = index;
	v_ObjectID = id;
	gl_Position = ViewProjection * vec4(PositionOS, 1.0);
}


#program     fragment
#version 450 core
layout(location = 0) out vec4 FragColor;
layout(location = 1) out int IDColor;

struct Attributes
{
	vec4 color;
	vec2 uv;
};
layout(location = 0) in Attributes Attri_Input;
layout(location = 2) in flat int TexIndex;
layout(location = 3) in flat int  v_ObjectID;
layout(binding = 0) uniform sampler2D _MainTex[32];
void main()
{
	FragColor = Attri_Input.color * texture(_MainTex[TexIndex], Attri_Input.uv);
	IDColor = v_ObjectID;
}