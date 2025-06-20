#pragma once

#include <filesystem>
namespace Pinata {


	class ContentBrowserPanel
	{
	public:
		ContentBrowserPanel();

	public:
		void OnImGuiRender();

	private:
		std::string m_ContentDir;
		std::filesystem::path m_CurrentBrowserDir;

	};

}