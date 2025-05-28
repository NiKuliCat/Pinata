#include "ptapch.h"
#include "SceneSerialize.h"
#include <yaml-cpp/yaml.h>
#include "Pinata/Scene/Object.h"
#include "Pinata/Component/Component.h"
#include <fstream>

namespace YAML {

	template<>
	struct convert<glm::vec3>
	{
		struct Node encode(const glm::vec3& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			return node;
		}

		static bool decode(const Node& node, glm::vec3& rhs)
		{
			if (!node.IsSequence() || node.size() != 3)
			{
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			return true;
		}
	};


	template<>
	struct convert<glm::vec4>
	{
		struct Node encode(const glm::vec4& rhs)
		{
			Node node;
			node.push_back(rhs.x);
			node.push_back(rhs.y);
			node.push_back(rhs.z);
			node.push_back(rhs.w);
			return node;
		}

		static bool decode(const Node& node, glm::vec4& rhs)
		{
			if (!node.IsSequence() || node.size() != 4)
			{
				return false;
			}

			rhs.x = node[0].as<float>();
			rhs.y = node[1].as<float>();
			rhs.z = node[2].as<float>();
			rhs.w = node[3].as<float>();
			return true;
		}
	};



}




namespace Pinata {


	YAML::Emitter& operator << (YAML::Emitter& emitter, const glm::vec3& value)
	{
		emitter << YAML::Flow;
		emitter << YAML::BeginSeq << value.x << value.y << value.z << YAML::EndSeq;

		return emitter;
	}

	YAML::Emitter& operator << (YAML::Emitter& emitter, const glm::vec4& value)
	{
		emitter << YAML::Flow;
		emitter << YAML::BeginSeq << value.x << value.y << value.z << value.w << YAML::EndSeq;

		return emitter;
	}

	YAML::Emitter& operator << (YAML::Emitter& emitter, const Tag& tag) 
	{

		auto str = GetTagString(tag.m_Tag);
		emitter << str;
		return emitter;
	}

	YAML::Emitter& operator << (YAML::Emitter& emitter, const ProjectionMode& mode)
	{
		auto str = GetProjectionModeString(mode);
		emitter << std::string(str);
		return emitter;
	}


	SceneSerialize::SceneSerialize(const Ref<Scene>& scene)
		:m_Scene(scene)
	{

	}
	static void SerializeObject(YAML::Emitter& emitter, Object object)
	{
		emitter << YAML::BeginMap;
		emitter << YAML::Key << "Object" << YAML::Value << "1235312512";

		if (object.HasComponent<Name>())
		{
			emitter << YAML::Key << "NameComponent";
			emitter << YAML::BeginMap;
			auto& name = object.GetComponent<Name>().m_Name;
			emitter << YAML::Key << "Name" << YAML::Value << name;

			emitter << YAML::EndMap;
		}

		if (object.HasComponent<Tag>())
		{
			emitter << YAML::Key << "TagComponent";
			emitter << YAML::BeginMap;
			auto& tag = object.GetComponent<Tag>().m_Tag;
			emitter << YAML::Key << "Tag" << YAML::Value << tag;

			emitter << YAML::EndMap;
		}


		if (object.HasComponent<Transform>())
		{
			emitter << YAML::Key << "TransformComponent";
			emitter << YAML::BeginMap;
			auto& transform = object.GetComponent<Transform>();
			emitter << YAML::Key << "Position" << YAML::Value << transform.Position;
			emitter << YAML::Key << "Rotation" << YAML::Value << transform.Rotation;
			emitter << YAML::Key << "Scale" << YAML::Value << transform.Scale;

			emitter << YAML::EndMap;
		}


		if (object.HasComponent<RuntimeCamera>())
		{
			emitter << YAML::Key << "CameraComponent";
			emitter << YAML::BeginMap;

			auto& camera = object.GetComponent<RuntimeCamera>();
			emitter << YAML::Key << "ProjectionMode" << YAML::Value << camera.m_ProjectionMode;
			emitter << YAML::Key << "FOV" << YAML::Value << camera.m_FOV;
			emitter << YAML::Key << "OrthSize" << YAML::Value << camera.m_OrthSize;
			emitter << YAML::Key << "Aspect" << YAML::Value << camera.m_Aspect;
			emitter << YAML::Key << "Near" << YAML::Value << camera.m_Near;
			emitter << YAML::Key << "Far" << YAML::Value << camera.m_Far;
			emitter << YAML::Key << "OrthNear" << YAML::Value << camera.m_OrthNear;
			emitter << YAML::Key << "OrthFar" << YAML::Value << camera.m_OrthFar;
			emitter << YAML::Key << "Sort" << YAML::Value << camera.m_Sort;

			emitter << YAML::EndMap;
		}


		emitter << YAML::EndMap;
	}

	void SceneSerialize::Serialize(const std::string& filepath)
	{
		YAML::Emitter emitter;
		emitter << YAML::BeginMap;

		emitter << YAML::Key << "Scene" << YAML::Value << m_Scene->m_Name ;

		emitter << YAML::Key << "Objects" << YAML::Value <<YAML::BeginSeq;

		m_Scene->m_Registry.view<entt::entity>().each([&](auto entity) {
			Object obj = { entity,m_Scene.get()};
			if (!obj)
				return;

			SerializeObject(emitter, obj);
			});
		emitter << YAML::EndSeq;

		emitter << YAML::EndMap;

		std::ofstream fout(filepath);
		fout << emitter.c_str();

	}

	void SceneSerialize::SerializeRuntime(const std::string* filepath)
	{
	}

	bool SceneSerialize::Deserialize(const std::string& filepath)
	{
		std::ifstream stream(filepath);
		std::stringstream strstream;
		strstream << stream.rdbuf();


		YAML::Node node = YAML::Load(strstream.str());
		if (!node["Scene"])
		{
			return false;
		}
		std::string sceneName = node["Scene"].as<std::string>();

		m_Scene->m_Name = sceneName;
		PTA_INFO("current deserialize scene : {0}", sceneName);
		auto objects = node["Objects"];
		if (objects)
		{
			for (auto obj : objects)
			{
				std::string name = "DeSerialize Object";
				uint64_t uuid = obj["Object"].as<uint64_t>();     //id
				auto  objNameComponent = obj["NameComponent"];
				if (objNameComponent)
				{
					name = objNameComponent["Name"].as<std::string>();
				}
				PTA_INFO("current deserialize object: {0}", name);

				Object deserializeObject = m_Scene->CreateObject(name);

				auto objTagComponent = obj["TagComponent"];
				if (objTagComponent)
				{
					AllTags tag = GetTagByString(objTagComponent["Tag"].as<std::string>());
					deserializeObject.GetComponent<Tag>().m_Tag = tag;
				}

				auto objTransformComponent = obj["TransformComponent"];
				if (objTransformComponent)
				{
					auto& transform = deserializeObject.GetComponent<Transform>();
					transform.Position = objTransformComponent["Position"].as<glm::vec3>();
					transform.Rotation = objTransformComponent["Rotation"].as<glm::vec3>();
					transform.Scale = objTransformComponent["Scale"].as<glm::vec3>();

				}

				auto objCameraComponent = obj["CameraComponent"];
				if (objCameraComponent)
				{
					auto& camera = deserializeObject.AddComponent<RuntimeCamera>();
					camera.m_ProjectionMode = GetProjectionModeByString(objCameraComponent["ProjectionMode"].as<std::string>());
					camera.m_FOV = objCameraComponent["FOV"].as<float>();
					camera.m_OrthSize = objCameraComponent["OrthSize"].as<float>();
					camera.m_Aspect = objCameraComponent["Aspect"].as<float>();
					camera.m_Near = objCameraComponent["Near"].as<float>();
					camera.m_Far = objCameraComponent["Far"].as<float>();
					camera.m_OrthNear = objCameraComponent["OrthNear"].as<float>();
					camera.m_OrthFar = objCameraComponent["OrthFar"].as<float>();
					camera.m_Sort = objCameraComponent["Sort"].as<int>();
				}
			}
		}

		return true;
	}

	bool SceneSerialize::DeserializeRuntime(const std::string& filepath)
	{
		return false;
	}

}