#include "ptapch.h"
#include "Renderer2D.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "ShaderLibrary.h"
#include <unordered_map>
namespace Pinata {

	struct TextureslotInfo
	{
		uint32_t TexID;
		uint32_t Slot;
	};
	//和layout排列一致，该顶点的数据
	struct QuadVertex
	{
		glm::vec3 Position;
		glm::vec4 Color;
		glm::vec2 Texcoord;
		int TexIndex;
		//normal,tangent .....
		QuadVertex(glm::vec3& position, glm::vec4& color, glm::vec2& texcoord, int index)
			:Position(position),Color(color),Texcoord(texcoord),TexIndex(index)
		{

		}

		QuadVertex()
		{

		}
	};

	struct Renderer2DBaseData
	{
		const uint32_t MaxCount = 10000;
		const uint32_t MaxVertices = MaxCount * 4;
		const uint32_t MaxIndices = MaxCount * 6;
		static const uint32_t MaxTextureSlots = 32;
		uint32_t DrawVertexCount = 0;
		Ref<VertexArray> VA_Quad;
		Ref<VertexBuffer> VB_Quad;
		uint32_t DefaultShader;
		Ref<Texture2D>DefaultTexture;


		QuadVertex* QuadVB_Start = nullptr;
		QuadVertex* QuadVB_End   = nullptr;
		QuadVertex RawQuad[4] = {
			{glm::vec3(0.5f,0.5f, 0.0f),glm::vec4(1.0f, 1.0f,1.0f,1.0f),glm::vec2(1.0f,1.0f),0},
			{glm::vec3(0.5f, -0.5f, 0.0f),glm::vec4(1.0f, 1.0f,1.0f,1.0f),glm::vec2(1.0f, 0.0f),0},
			{glm::vec3(-0.5f, -0.5f, 0.0f),glm::vec4(1.0f, 1.0f,1.0f,1.0f),glm::vec2(0.0f, 0.0f),0},
			{glm::vec3(-0.5f,  0.5f, 0.0f),glm::vec4(1.0f, 1.0f,1.0f,1.0f),glm::vec2(0.0f, 1.0f),0}
		};
		uint32_t CurrentTexCount;
		std::unordered_map<uint32_t, uint32_t> m_CurrentTextures;
		int32_t samplers[MaxTextureSlots];

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
			DrawVertexCount = 0;
			uint32_t QuadIndices[6] = { 0, 1, 3, 1, 2, 3 };

		
//////  --------------------------------------- index buffer ---------------------------------
			uint32_t* MaXQuadIndices = new uint32_t[MaxIndices];
			uint32_t offset = 0;
			for (int i = 0; i < MaxIndices; i+=6)
			{
				MaXQuadIndices[i + 0] = offset + 0;
				MaXQuadIndices[i + 1] = offset + 1;
				MaXQuadIndices[i + 2] = offset + 3;

				MaXQuadIndices[i + 3] = offset + 1;
				MaXQuadIndices[i + 4] = offset + 2;
				MaXQuadIndices[i + 5] = offset + 3;
				offset += 4;
			}
			Ref<IndexBuffer> IB_Quad;
			IB_Quad = IndexBuffer::Create(MaXQuadIndices, MaxIndices);

			delete[] MaXQuadIndices;
//////  --------------------------------------- index buffer ---------------------------------


//////  --------------------------------------- vertex buffer ---------------------------------
			VB_Quad = VertexBuffer::Create(MaxVertices * sizeof(QuadVertex));

			BufferLayout layout = {
				{ShaderDataType::Float3,"PositionOS"},
				{ShaderDataType::Float4,"Color"},
				{ShaderDataType::Float2,"Texcoord"},
				{ShaderDataType::Int,"TexIndex"}
			};

			VB_Quad->SetLayout(layout);
//////  --------------------------------------- vertex buffer ---------------------------------


			VA_Quad = VertexArray::Create();
			VA_Quad->AddVertexBuffer(VB_Quad);
			VA_Quad->SetIndexBuffer(IB_Quad);

			DefaultShader = 0;

			DefaultTexture = Texture2D::DefaultTexture(DefaultTexColor::White);
			m_CurrentTextures = std::unordered_map<uint32_t, uint32_t>(MaxTextureSlots);

			QuadVB_Start = new QuadVertex[MaxCount];


		}
	};
	
	static Renderer2DBaseData* s_BaseData;

	void Renderer2D::Init()
	{
		s_BaseData = new Renderer2DBaseData();
		s_BaseData->DefaultShader = ShaderLibrary::Load("Assets/Shader/DefaultShader.shader")->GetID();
	}

	void Renderer2D::Shutdown()
	{
		delete s_BaseData;
	}

	void Renderer2D::BeginScene(OrthographicCamera& mainCamera)
	{
		Renderer::BeginScene(mainCamera);
		s_BaseData->DrawVertexCount = 0;
		s_BaseData->QuadVB_End = s_BaseData->QuadVB_Start;

		s_BaseData->m_CurrentTextures.clear();                                
		s_BaseData->CurrentTexCount = -1;

		s_BaseData->CurrentTexCount++;
		s_BaseData->m_CurrentTextures.insert({ s_BaseData->DefaultTexture->GetID(),s_BaseData->CurrentTexCount });
		s_BaseData->DefaultTexture->Bind(s_BaseData->CurrentTexCount);
		s_BaseData->samplers[s_BaseData->CurrentTexCount] =(int32_t)s_BaseData->CurrentTexCount;
	}

	void Renderer2D::EndScene()
	{
		uint32_t dataSize = (uint8_t*)s_BaseData->QuadVB_End - (uint8_t*)s_BaseData->QuadVB_Start;
		s_BaseData->VB_Quad->SetData(s_BaseData->QuadVB_Start, dataSize);
		Flush();
	}

	void Renderer2D::DrawQuad(glm::vec4& color, Ref<Texture2D>& texture)
	{
		auto shader = ShaderLibrary::Get(s_BaseData->DefaultShader);

		shader->Bind();
		shader->SetColor("_BaseColor", color);

		texture->Bind(0);
		shader->SetInt("_MainTex", 0);


		Renderer::Submit(s_BaseData->VA_Quad, shader);
	}

	void Renderer2D::DrawQuad(Transform& transform, glm::vec4& color, Ref<Texture2D>& texture)
	{
		auto shader = ShaderLibrary::Get(s_BaseData->DefaultShader);
		glm::mat4 model = transform.GetModelMatrix();
		shader->Bind();
		shader->SetColor("_BaseColor", color);

		texture->Bind(0);
		shader->SetInt("_MainTex", 0);


		for (int i = 0; i < 4; i++)
		{
			s_BaseData->QuadVB_End->Position = model * glm::vec4(s_BaseData->RawQuad[i].Position, 1.0f);
			s_BaseData->QuadVB_End++;
		}
		s_BaseData->DrawVertexCount += 6;
		//Renderer::Submit(s_BaseData->VA_Quad, model, shader);
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

	void Renderer2D::DrawQuad(Transform& transform, Ref<Material>& material)
	{
		glm::mat4 model = transform.GetModelMatrix();
		auto texture = material->GetTexture();
		glm::vec4 color = material->GetColor();
		uint32_t textureID = texture->GetID();
		uint32_t  slot;

		//如果此纹理还未绑定,则加入map中，并分配slot槽位
		if (s_BaseData->m_CurrentTextures.find(textureID) == s_BaseData->m_CurrentTextures.end())
		{
			s_BaseData->CurrentTexCount++;
			slot = s_BaseData->CurrentTexCount;
			texture->Bind(s_BaseData->CurrentTexCount);
			s_BaseData->samplers[s_BaseData->CurrentTexCount] = slot;
			s_BaseData->m_CurrentTextures[textureID] = s_BaseData->CurrentTexCount;
		}
		//如果该纹理已经绑定过，找到其对应的slot;
		else
		{
			slot = s_BaseData->m_CurrentTextures[textureID];
		}

		for (int i = 0; i < 4; i++)
		{
			s_BaseData->QuadVB_End->Position = model * glm::vec4(s_BaseData->RawQuad[i].Position, 1.0f);
			s_BaseData->QuadVB_End->Color =  color * s_BaseData->RawQuad[i].Color;
			s_BaseData->QuadVB_End->Texcoord = s_BaseData->RawQuad[i].Texcoord;
			s_BaseData->QuadVB_End->TexIndex = slot;
			s_BaseData->QuadVB_End++;
		}


		s_BaseData->DrawVertexCount += 6;

		
	}

	void Renderer2D::Flush()
	{
		auto shader = ShaderLibrary::Get(s_BaseData->DefaultShader);
		shader->Bind();
		shader->SetIntArray("_MainTex", s_BaseData->samplers, s_BaseData->CurrentTexCount + 1);
		Renderer::Submit(s_BaseData->VA_Quad,s_BaseData->DrawVertexCount, glm::mat4(1.0f), shader);
	}

}