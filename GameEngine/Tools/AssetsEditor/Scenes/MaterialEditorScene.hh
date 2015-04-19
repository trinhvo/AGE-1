#pragma once

#include <Core/AScene.hh>
#include <Core/Engine.hh>
#include <AssetManagement\Data\MaterialData.hh>
#include <memory>

#define NAME_LENGTH 50
#define TEXTURE_LENGTH 255

#define InputTextCustom(name, diff1, diff2) memcpy(diff1, mat.diff2.c_str(), mat.diff2.size()); \
	ImGui::InputText(name, diff1, mat.diff2.size());

namespace AGE
{
	enum class ModeMaterialEditor {
		selectMaterial,
		selectSubMaterial,
		edit
	};

	enum ModeTexture
	{
		ambient = 0,
		diffuse,
		emissive,
		reflective,
		specular,
		normal,
		bump,
		size
	};

	class MaterialEditorScene : public AScene
	{
	public:
		static const std::string Name;

		MaterialEditorScene(Engine *engine);

		virtual ~MaterialEditorScene(void);
		virtual bool _userStart();
		virtual bool _userUpdateBegin(float time);
		virtual bool _userUpdateEnd(float time);
		void _selectMaterial();
		void _selectSubMaterial();
		void _editName();
		void _editTexture(std::string &texturePath, ModeTexture mode, MaterialData &current);
		void _editData();
		void _saveEdit();
		void _resetEdition();
	
	private:
		ModeMaterialEditor _mode;
		int _indexMaterial;
		int _indexSubMaterial;
		MaterialDataSet _current;
		bool _editModeName;
		char _bufferName[NAME_LENGTH];
	};
}