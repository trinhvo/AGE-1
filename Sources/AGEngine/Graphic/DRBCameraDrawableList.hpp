#pragma once

#include <vector>
#include <list>
#include <array>
#include <memory>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>

#include "Utils/Key.hh"

#include <Render/Pipelining/Prepare/MeshBufferingPrepare.hpp>

#include "Render\Pipelining\RenderInfos/SpotlightRenderInfos.hpp"
#include "Render\Pipelining\RenderInfos/CameraRenderInfos.hpp"


// to remove
#include "Utils/Debug.hpp"

namespace AGE
{
	struct DRBData;
	class TextureCubeMap;
	struct DRBPointLightData;
	struct DRBSpotLightData;

	struct DRBSpotLightOccluder
	{
		static const float invalidVector[4];

		struct KeyHolder
		{
			ConcatenatedKey key; // 8
			std::size_t     size; // 8
		};
		union
		{
			std::array<std::array<float, 4>, 4> matrix; // 64
			KeyHolder keyHolder; // 16
		};

		DRBSpotLightOccluder()
			: matrix({ std::array<float, 4>{ 1, 2, 3, 4 }, std::array<float, 4>{ 1, 2, 3, 4 }, std::array<float, 4>{ 1, 2, 3, 4 }, std::array<float, 4>{ 1, 2, 3, 4 } })
		{}

		DRBSpotLightOccluder(glm::mat4 &&mat)
		{
			memcpy(&matrix, glm::value_ptr(mat), sizeof(glm::mat4));
		}
		DRBSpotLightOccluder(ConcatenatedKey &&k)
		{
			keyHolder.key = std::move(k);
			keyHolder.size = 0;
			memcpy(&(matrix[3][0]), &(invalidVector), sizeof(invalidVector));
		}
		inline bool isKeyHolder() const
		{
			return (memcmp(&matrix[3][0], &invalidVector, sizeof(invalidVector)) == 0);
		}
	};
	struct DRBSpotLightDrawableList
	{
		std::vector<DRBSpotLightOccluder> occluders; // used for instancied rendering (non skinned)
		std::list<std::shared_ptr<DRBData>> skinnedMesh;
		std::shared_ptr<DRBData> spotLight;
	};

	struct CameraData
	{
		bool                            fxaa;
		bool                            bloom;
		bool                            dof;
		std::shared_ptr<TextureCubeMap> texture;
		glm::mat4                       projection;
		unsigned int                    pipeline;

		CameraData(CameraData const &cam);
		CameraData();
		CameraData &operator=(CameraData const &cam);
	};

	struct CameraInfos
	{
		glm::mat4 view;
		CameraData data;
	};

	struct PointlightInfos
	{
		glm::vec3 range;
		glm::vec3 position;
		glm::mat4 sphereTransform;
		glm::vec3 colorLight;
		glm::vec3 ambiantColor;
	};

	struct DRBCameraDrawableList
	{
		SpotlightRenderInfos::Output                  spotlightsOutput;
		CameraRenderInfos::Output                     camerasOutput;

		//TODO pass like spotlights
		BasicCommandGeneration::MeshAndMaterialOutput *cameraMeshs = nullptr;
		BasicCommandGeneration::SkinnedMeshAndMaterialOutput *cameraSkinnedMeshs = nullptr;

		std::list<std::shared_ptr<DRBData>> meshs;
		std::vector<PointlightInfos> pointLights;
		CameraInfos cameraInfos;
	};

	struct DRBCameraDrawableListCommand
	{
		DRBCameraDrawableListCommand(std::shared_ptr<DRBCameraDrawableList> _list);
		DRBCameraDrawableListCommand(DRBCameraDrawableListCommand &&o);
		std::shared_ptr<DRBCameraDrawableList> list;
	};
}