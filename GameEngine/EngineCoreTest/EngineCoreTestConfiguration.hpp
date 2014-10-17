#pragma once

#include <Utils/FileSystemHelpers.hpp>
#include <Utils/Serialization/SerializationArchives.hpp>
#include <fstream>
#include <cereal/types/string.hpp>
#include <cereal/types/memory.hpp>
#include <Utils/Directory.hpp>
#include <Utils/Debug.hpp>
#include <Utils/Path.hpp>
#include <vector>
#include <list>

namespace AGE
{
	struct ECTConfigurations
	{
		std::string _cookedAssetsDirectory = "../../Assets/Serialized/";
		std::string _exportSceneFolder = "../../EngineCoreTest/DemoScenes/";
		std::string _exportArchetypeFolder = "../../EngineCoreTest/Archetypes/";
		std::string _lastSceneOpened = "";
		int _selectedScene = 0;

		// not serialized
		std::vector<std::string> _scenesPaths;
		std::list<std::string> _scenesNamesCache;
		std::vector<const char*> _scenesNames;

		friend class cereal::access;

		template <typename Archive>
		void serialize(Archive &ar, std::uint32_t const version)
		{
			ar(cereal::make_nvp("Cooked assets directory", _cookedAssetsDirectory));
			ar(cereal::make_nvp("Exported scenes directory", _exportSceneFolder));
			if (version == 0)
			{
				ar(cereal::make_nvp("deprecated", _selectedScene));
			}
			else
			{
				ar(cereal::make_nvp("Last scene opened", _lastSceneOpened));
			}
			ar(cereal::make_nvp("Archetypes directory", _exportArchetypeFolder));
		}
	};

	class EngineCoreTestConfiguration
	{
	public:
		~EngineCoreTestConfiguration()
		{
			saveConfigurations();
		}

		static bool _dirty;

		static std::shared_ptr<ECTConfigurations> _getConfigurations()
		{
			if (_configurations == nullptr)
			{
				if (!AGE::FileSystemHelpers::AgeExists("EngineCoreTestConfiguration.json"))
				{
					_configurations = std::make_shared<ECTConfigurations>();
					saveConfigurations();
				}
				else
				{
					std::ifstream file("EngineCoreTestConfiguration.json", std::ios::binary);
					assert(file.is_open());
					
					// if file is empty
					if (file.peek() == std::ifstream::traits_type::eof())
					{
						_configurations = std::make_shared<ECTConfigurations>();
						saveConfigurations();
					}
					else
					{
						auto ar = cereal::JSONInputArchive(file);
						ar(_configurations);
					}
					file.close();
				}
			}
			if (_dirty)
			{
				saveConfigurations();
			}
			return _configurations;
		}

		static std::shared_ptr<ECTConfigurations> _configurations;
	public:
		static const std::string &GetCookedDirectory()
		{
			return _getConfigurations()->_cookedAssetsDirectory;
		}
		static const std::string &GetExportedSceneDirectory()
		{
			return _getConfigurations()->_exportSceneFolder;
		}
		static const std::string &GetExportedArchetypeDirectory()
		{
			return _getConfigurations()->_exportArchetypeFolder;
		}
		static std::vector<const char*> getScenesName()
		{
			return _getConfigurations()->_scenesNames;
		}
		static const std::vector<std::string> &getScenesPath()
		{
			return _getConfigurations()->_scenesPaths;
		}
		static const std::string getSelectedScenePath()
		{
			if (_getConfigurations()->_selectedScene >= _getConfigurations()->_scenesPaths.size())
			{
				return "";
			}
			return _getConfigurations()->_scenesPaths[_getConfigurations()->_selectedScene];
		}
		static const std::string getSelectedSceneName()
		{
			if (_getConfigurations()->_selectedScene >= _getConfigurations()->_scenesNames.size())
			{
				return "";
			}
			return _getConfigurations()->_scenesNames[_getConfigurations()->_selectedScene];
		}
		static int &getSelectedSceneIndex()
		{
			auto &res = _getConfigurations()->_selectedScene;
			return res;
		}

		static void RefreshScenesDirectoryListing()
		{
			_dirty = true;

			Directory dir;
			const bool succeed = dir.open(GetExportedSceneDirectory().c_str());
			AGE_ASSERT(succeed && "Impossible to open directory");

			_getConfigurations()->_scenesPaths.clear();
			_getConfigurations()->_scenesNames.clear();
			_getConfigurations()->_scenesNamesCache.clear();

			for (auto it = dir.recursive_begin(); it != dir.recursive_end(); ++it)
			{
				if (Directory::IsFile(*it))
				{
					auto file = std::string(*it);
					auto find = file.find(".scene");
					if (find != std::string::npos)
					{
						_getConfigurations()->_scenesNamesCache.push_back(Path::BaseName(file.substr(0, find).c_str()));
						_getConfigurations()->_scenesNames.push_back(_getConfigurations()->_scenesNamesCache.back().c_str());
						_getConfigurations()->_scenesPaths.push_back(_getConfigurations()->_exportSceneFolder + _getConfigurations()->_scenesNames.back() + ".scene");
					}
				}
			}
			dir.close();

			auto &selectedIndex = _getConfigurations()->_selectedScene;
			selectedIndex = 0;

			if (!_getConfigurations()->_lastSceneOpened.empty())
			{
				for (auto &e : _getConfigurations()->_scenesNames)
				{
					if (e == _getConfigurations()->_lastSceneOpened)
					{
						break;
					}
					++selectedIndex;
				}
			}

			if (selectedIndex >= _getConfigurations()->_scenesNames.size())
			{
				selectedIndex = 0;
			}

			_dirty = true;
		}

		static void saveConfigurations()
		{
			if (_configurations && !_configurations->_scenesNames.empty())
			{
				_configurations->_lastSceneOpened = _configurations->_scenesNames[_configurations->_selectedScene];
			}

			std::ofstream file("EngineCoreTestConfiguration.json", std::ios::binary);
			assert(file.is_open());
			{
				auto ar = cereal::JSONOutputArchive(file);
				ar(_configurations);
			}
			file.close();
			_dirty = false;
		}
	};
}

CEREAL_CLASS_VERSION(AGE::ECTConfigurations, 1);