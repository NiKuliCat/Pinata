#pragma once
#include  "magic_enum/magic_enum.hpp"
namespace Pinata {

	enum class AllTags
	{
		default = 0,
		ui,
		camera,
		player
	};


	static AllTags GetTagByString(const std::string& str)
	{
		return magic_enum::enum_cast<AllTags>(str).value_or(AllTags::default);
	}
	static  std::string GetTagString(const AllTags& tag)
	{
		return magic_enum::enum_name(tag).data();
	}

	struct Tag
	{
		AllTags m_Tag = AllTags::default;

		Tag() { m_Tag = AllTags::default; }
		Tag(const AllTags& tag)
			:m_Tag(tag){}
		Tag(const Tag& other) = default;

		operator std::string()  { return GetTagString(m_Tag);}

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