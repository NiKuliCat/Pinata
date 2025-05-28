#pragma once

namespace Pinata {

	enum class AllTags
	{
		default = 0,
		ui,
		camera,
		player
	};

	const std::unordered_map<AllTags, std::string> TagToStringMap = {
		{AllTags::default, "default"},
		{AllTags::ui, "ui"},
		{AllTags::camera, "camera"},
		{AllTags::player, "player" }
	};

	const std::unordered_map<std::string, AllTags> StringToTagMap = {
		{"default", AllTags::default},
		{"ui", AllTags::ui},
		{"camera", AllTags::camera},
		{"player", AllTags::player}
	};



	static std::string GetTagString(AllTags tag)
	{
		auto it = TagToStringMap.find(tag);
		if(it != TagToStringMap.end())
		{
			return it->second;
		}

		return "default";
	}

	static AllTags GetTag(std::string tag)
	{
		auto it = StringToTagMap.find(tag);
		if (it != StringToTagMap.end())
		{
			return it->second;
		}

		return AllTags::default;
	}

	struct Tag
	{
		AllTags m_Tag = AllTags::default;

		Tag() { m_Tag = AllTags::default; }
		Tag(const AllTags& tag)
			:m_Tag(tag){}
		Tag(const Tag& other) = default;

		//operator std::string& () const { return GetTagString(m_Tag); }

	};

	struct Name
	{
		std::string m_Name = "new Object";

		Name() { m_Name = "New Object"; }
		Name(const std::string& name)
			:m_Name(name) {}

		Name(const Name& other) = default;
	};

}