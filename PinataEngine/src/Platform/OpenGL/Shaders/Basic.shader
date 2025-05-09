#vertex
#version 330 core 
layout (location = 0) in vec3 PositionOS; 
layout (location = 1) in vec4 aColor; 
layout (location = 2) in vec2 Texcoord;
uniform mat4 _ViewProjectMatrix;
uniform vec4 _TintColor;
out vec4 ourColor;
out vec2 uv;
void main() 
{ 
   gl_Position = _ViewProjectMatrix * vec4(PositionOS, 1.0); 
   ourColor = aColor * _TintColor;
   uv = Texcoord;
};

#fragment
#version 330 core
out vec4 FragColor;
in vec2 uv;
in vec4 ourColor;
uniform sampler2D  _MainTex;
uniform vec4 _TintColor;
uniform int _Intensity;
void main()
{
	vec4 baseColor = texture(_MainTex,uv);
	FragColor = uv.yyyy;
};
