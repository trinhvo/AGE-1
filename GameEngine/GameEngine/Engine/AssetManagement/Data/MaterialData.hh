#pragma once

# include <string>
# include <glm/glm.hpp>
#include <stdint.h>
#include <Utils/Serialization/SerializationArchives.hpp>
#include <cereal/types/string.hpp>

namespace AGE
{

	struct MaterialData
	{
	public:
		// will scale UVs based on the scale of the mesh
		bool scaleUVs = false;
		float shininess = 100.0f;
		glm::vec4 diffuse;
		glm::vec4 ambient;
		glm::vec4 emissive;
		glm::vec4 reflective;
		glm::vec4 specular;
		std::string diffuseTexPath;
		std::string ambientTexPath;
		std::string emissiveTexPath;
		std::string reflectiveTexPath;
		std::string specularTexPath;
		std::string normalTexPath;
		std::string bumpTexPath;
#ifdef EDITOR_ENABLED
		int selectedTextureIndex[7];
#endif

	public:
		template <class Archive> void serialize(Archive &ar, const std::uint32_t version);
		MaterialData()
		{
#ifdef EDITOR_ENABLED
			for (auto i = 0; i < 7; ++i)
			{
				selectedTextureIndex[i] = 0;
			}
#endif
		}
	};

	struct MaterialDataSet
	{
	public:
		std::vector<MaterialData> collection;
		std::string name;
	public:
		template <class Archive> void serialize(Archive &ar, const std::uint32_t version);
	};

	template <class Archive>
	void MaterialDataSet::serialize(Archive &ar, const std::uint32_t version)
	{
		ar(collection, name);
	}

	template <class Archive>
	void MaterialData::serialize(Archive &ar, const std::uint32_t version)
	{
		if (version == 0)
		{
			ar(diffuse, ambient, emissive, reflective, specular, diffuseTexPath, ambientTexPath, emissiveTexPath, reflectiveTexPath, specularTexPath, normalTexPath, bumpTexPath);
		}
		else if (version == 1)
		{
			ar(scaleUVs, diffuse, ambient, emissive, reflective, specular, diffuseTexPath, ambientTexPath, emissiveTexPath, reflectiveTexPath, specularTexPath, normalTexPath, bumpTexPath);
		}
		else if (version == 2)
		{
			ar(scaleUVs, shininess, diffuse, ambient, emissive, reflective, specular, diffuseTexPath, ambientTexPath, emissiveTexPath, reflectiveTexPath, specularTexPath, normalTexPath, bumpTexPath);
		}
	}
}

CEREAL_CLASS_VERSION(AGE::MaterialData, 2)
CEREAL_CLASS_VERSION(AGE::MaterialDataSet, 0)