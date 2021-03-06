#pragma once

#include <Utils/Debug.hpp>
#include <Utils/OpenGL.hh>
#include <Render/Pipelining/Pipelines/ARenderingPipeline.hh>
#include <glm/glm.hpp>
#include <Render/Textures/Texture2D.hh>

#include <memory>

namespace AGE
{

	class DeferredMerging;
	class DeferredSkyBox;

	class DebugDeferredShading : public ARenderingPipeline
	{
	public:
		DebugDeferredShading(glm::uvec2 const &screen_size, std::shared_ptr<PaintingManager> const &painter_manager);
		DebugDeferredShading(DebugDeferredShading &&move);
		virtual ~DebugDeferredShading();
		DebugDeferredShading(DebugDeferredShading const &) = delete;
		DebugDeferredShading &operator=(DebugDeferredShading const &) = delete;
		virtual void renderBegin(const DRBCameraDrawableList &infos);
		virtual void renderEnd(const DRBCameraDrawableList &infos);
	public:
		void setAmbient(glm::vec3 const &ambient);
		void setSkyboxLighting(glm::vec3 const &lighting);
		virtual bool isDebug() const;

	private:
		std::shared_ptr<Texture2D> _depthStencil;
		std::shared_ptr<Texture2D> _diffuse;
		std::shared_ptr<Texture2D> _normal;
		std::shared_ptr<Texture2D> _specular;
		std::shared_ptr<Texture2D> _lightAccumulation;
		std::shared_ptr<Texture2D> _shinyAccumulation;
		std::shared_ptr<DeferredMerging> _deferredMerging;
		std::shared_ptr<DeferredSkyBox> _deferredSkybox;
	};

}