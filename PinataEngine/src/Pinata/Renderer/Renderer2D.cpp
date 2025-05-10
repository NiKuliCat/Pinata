#include "ptapch.h"
#include "Renderer2D.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Shader.h"
namespace Pinata {

	struct Renderer2DBaseData
	{
		Ref<VertexArray> VA_Quad;
		Ref<Shader> DefaultShader;
		Ref<Texture2D>DefaultTexture;

		Renderer2DBaseData()
		{
			float QuadPos[9 * 4] =
			{
				//     ---- 位置 ----       ---- 颜色 ----     - 纹理坐标 -
				 0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,1.0f,   1.0f, 1.0f,   // 右上
				 0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,1.0f,   1.0f, 0.0f,   // 右下
				-0.5f, -0.5f, 0.0f,   1.0f, 1.0f, 1.0f,1.0f,   0.0f, 0.0f,   // 左下
				-0.5f,  0.5f, 0.0f,   1.0f, 1.0f, 1.0f,1.0f,   0.0f, 1.0f    // 左上
			};

			uint32_t QuadIndices[6] = { 0, 1, 3, 1, 2, 3 };
			Ref<VertexBuffer> VB_Quad;
			Ref<IndexBuffer> IB_Quad;

			VA_Quad = VertexArray::Create();
			VB_Quad = VertexBuffer::Create(QuadPos, sizeof(QuadPos));
			IB_Quad = IndexBuffer::Create(QuadIndices, sizeof(QuadIndices) / sizeof(uint32_t));

			BufferLayout layout = {
				{ShaderDataType::Float3,"PositionOS"},
				{ShaderDataType::Float4,"Color"},
				{ShaderDataType::Float2,"Texcoord"}
			};
			VB_Quad->SetLayout(layout);

			VA_Quad->AddVertexBuffer(VB_Quad);
			VA_Quad->SetIndexBuffer(IB_Quad);

			DefaultShader = Shader::Creat("Assets/Shader/DefaultShader.shader");
			DefaultTexture = Texture2D::DefaultTexture(DefaultTexColor::White);

		}
	};
	
	static Renderer2DBaseData* s_BaseData;

	void Renderer2D::Init()
	{
		s_BaseData = new Renderer2DBaseData();
	}

	void Renderer2D::Shutdown()
	{
		delete s_BaseData;
	}

	void Renderer2D::BeginScene(OrthographicCamera& mainCamera)
	{
		Renderer::BeginScene(mainCamera);
	}

	void Renderer2D::EndScene()
	{

	}

	void Renderer2D::DrawQuad(glm::vec4& color, Ref<Texture2D>& texture)
	{
		s_BaseData->DefaultShader->Bind();
		s_BaseData->DefaultShader->SetColor("_BaseColor", color);

		texture->Bind(0);
		s_BaseData->DefaultShader->SetInt("_MainTex", 0);

		Renderer::Submit(s_BaseData->VA_Quad,s_BaseData->DefaultShader);
	}

	void Renderer2D::DrawQuad(Transform& transform, glm::vec4& color, Ref<Texture2D>& texture)
	{
		glm::mat4 model = Transform::GetModelMatrix(transform);
		s_BaseData->DefaultShader->Bind();
		s_BaseData->DefaultShader->SetColor("_BaseColor", color);

		texture->Bind(0);
		s_BaseData->DefaultShader->SetInt("_MainTex", 0);

		Renderer::Submit(s_BaseData->VA_Quad, model, s_BaseData->DefaultShader);
	}

	void Renderer2D::DrawQuad(glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, glm::vec4& color, Ref<Texture2D>& texture)
	{
		Transform tra = Transform(position, rotation, scale);
		DrawQuad(tra, color, texture);
	}

	void Renderer2D::DrawQuad(glm::vec4& color)
	{
		DrawQuad(color, s_BaseData->DefaultTexture);
	}

	void Renderer2D::DrawQuad(Transform& transform, glm::vec4& color)
	{
		DrawQuad(transform,color, s_BaseData->DefaultTexture);
	}

	void Renderer2D::DrawQuad(glm::vec3& position, glm::vec3& rotation, glm::vec3& scale, glm::vec4& color)
	{
		DrawQuad(position, rotation, scale, color, s_BaseData->DefaultTexture);
	}

}