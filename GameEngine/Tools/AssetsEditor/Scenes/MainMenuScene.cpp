#include "MainMenuScene.hpp"
#include <imgui\imgui.h>
#include "AssetsEditorScene.hpp"
#include "WorldEditorScene.hpp"
#include "MaterialEditorScene.hh"
#include <Core/Inputs/Input.hh>
#include "IMenuInheritrance.hpp"

namespace AGE
{
	const std::string MainMenuScene::Name = "Main menu";

	MainMenuScene::MainMenuScene(AGE::Engine *engine)
		: AScene(engine)
	{
	}

	MainMenuScene::~MainMenuScene(void)
	{
	}

	bool MainMenuScene::_userStart()
	{
		_selectedTool = WorldEditor;
		getEngine()->enableScene(AGE::WorldEditorScene::Name, 1000);

		// we register tools names
		_toolsName[WorldEditor] = WorldEditorScene::Name;
		_toolsName[MaterialEditor] = MaterialEditorScene::Name;
		_toolsName[AssetsEditor] = AssetsEditorScene::Name;

		_exitApp = false;
		
		return true;
	}

	bool MainMenuScene::_userUpdateBegin(float time)
	{
		if (ImGui::BeginMainMenuBar())
		{
			if (ImGui::BeginMenu("Tools"))
			{
				for (auto i = 0; i < TOOLS_NUMBER; ++i)
				{
					bool notAlreadyActive = ToolType(i) != _selectedTool;

					if (ImGui::MenuItem(_toolsName[i].c_str(), nullptr, nullptr, notAlreadyActive))
					{
						getEngine()->disableScene(_toolsName[_selectedTool]);
						_selectedTool = ToolType(i);
						getEngine()->enableScene(_toolsName[_selectedTool], 1000);
					}
				}

				ImGui::Separator();

				if (ImGui::MenuItem("Exit", "CTRL+SHIFT+Q"))
				{
					_exitApp = true;
				}

				ImGui::EndMenu();
			}
			
			auto currentToolScene = getEngine()->getScene(_toolsName[_selectedTool]);

			std::dynamic_pointer_cast<IMenuInheritance>(currentToolScene)->updateMenu();

			ImGui::EndMainMenuBar();
		}
		return true;
	}

	bool MainMenuScene::_userUpdateEnd(float time)
	{
		auto input = getInstance<Input>();
		
		auto ctrl = input->getPhysicalKeyPressed(AGE_LCTRL);
		ctrl |= input->getPhysicalKeyPressed(AGE_RCTRL);

		auto shift = input->getPhysicalKeyPressed(AGE_LSHIFT);
		shift |= input->getPhysicalKeyPressed(AGE_RSHIFT);

		auto qKey = input->getPhysicalKeyPressed(AGE_q);

		if (ctrl && shift && qKey)
		{
			_exitApp = true;
		}
		return !_exitApp;
	}
}