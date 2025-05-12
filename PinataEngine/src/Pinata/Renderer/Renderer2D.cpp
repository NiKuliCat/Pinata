#include "ptapch.h"
#include "Renderer2D.h"
#include "Renderer.h"
#include "VertexArray.h"
#include "Shader.h"
#include "ShaderLibrary.h"
namespace Pinata {
	//和layout排列一致，该顶点的数据

	struct TextureSlot
	{
		Ref<Texture2D> Tex;
		uint32_t  Slot;

	};
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

		//texture;
		std::vector<TextureSlot> CurrentTextures;
		uint32_t CurrentTexCount;



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

		s_BaseData->CurrentTexCount = 0;
		s_BaseData->CurrentTextures.clear();
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
		glm::mat4 model = Transform::GetModelMatrix(transform);
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
		glm::mat4 model = Transform::GetModelMatrix(transform);

		auto texture = material->GetTexture();

		if (s_BaseData->CurrentTexCount < 32)
		{
			TextureSlot textureslot;
			textureslot.Tex = texture;
			textureslot.Slot = s_BaseData->CurrentTexCount;

			s_BaseData->CurrentTextures.push_back(textureslot);
		}

		for (int i = 0; i < 4; i++)
		{
			s_BaseData->QuadVB_End->Position = model * glm::vec4(s_BaseData->RawQuad[i].Position, 1.0f);
			s_BaseData->QuadVB_End->Color = s_BaseData->RawQuad[i].Color;
			s_BaseData->QuadVB_End->Texcoord = s_BaseData->RawQuad[i].Texcoord;
			s_BaseData->QuadVB_End->TexIndex = s_BaseData->CurrentTexCount;
			s_BaseData->QuadVB_End++;
		}
		s_BaseData->DrawVertexCount += 6;

		s_BaseData->CurrentTexCount++;
		
	}

	void Renderer2D::Flush()
	{
		auto shader = ShaderLibrary::Get(s_BaseData->DefaultShader);
		int32_t samplers[s_BaseData->MaxTextureSlots];

		for (uint32_t i = 0; i < s_BaseData->CurrentTexCount; i++)
		{
			auto tex = s_BaseData->CurrentTextures[i];
			tex.Tex->Bind(tex.Slot);
			samplers[i] = tex.Slot;
		}

		shader->Bind();
		shader->SetIntArray("_MainTex", samplers, s_BaseData->CurrentTexCount);

		Renderer::Submit(s_BaseData->VA_Quad,s_BaseData->DrawVertexCount, glm::mat4(1.0f), shader);
	}

}