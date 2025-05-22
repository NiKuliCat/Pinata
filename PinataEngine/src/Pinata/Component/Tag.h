#pragma once

namespace Pinata {

	enum class AllTags
	{
		default = 0,
		ui,
		camera,
		player
	};

	class Tag
	{
	public:
		Tag() = default;
		Tag(const AllTags& tag)
			:m_Tag(tag){}
		Tag(const Tag& other) = default;

	public:
		AllTags& GetTag() { return m_Tag; }
		const AllTags& GetTag() const { return m_Tag; }
	private:
		AllTags m_Tag = AllTags::default;
	};

	class Name
	{
	public:
		Name() = default;
		Name(const std::string& name)
			:m_Name(name) {}

		Name(const Name& other) = default;

	public:
		std::string& GetName() { return m_Name; }
		const std::string& GetName() const { return m_Name; }
	private:
		std::string m_Name = "new Object";
	};

}