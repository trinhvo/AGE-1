#include <Render/Pipelining/Pipelines/CustomPipeline/DeferredShading.hh>
#include <Render/Pipelining/Pipelines/CustomRenderPass/DeferredBasicBuffering.hh>
#include <Render/Pipelining/Pipelines/CustomRenderPass/DeferredPointLightning.hh>
#include <Render/Pipelining/Pipelines/CustomRenderPass/DeferredMerging.hh>

namespace AGE
{

	DeferredShading::DeferredShading(glm::uvec2 const &screen_size, std::shared_ptr<PaintingManager> const &painter_manager) :
		ARenderingPipeline(std::string("deferred shading"), painter_manager)
	{
		_diffuse = createRenderPassOutput<Texture2D>(screen_size.x, screen_size.y, GL_RGBA8, true);
		_normal = createRenderPassOutput<Texture2D>(screen_size.x, screen_size.y, GL_RGBA8, true);
		_specular = createRenderPassOutput<Texture2D>(screen_size.x, screen_size.y, GL_RGBA8, true);
		_depthStencil = createRenderPassOutput<Texture2D>(screen_size.x, screen_size.y, GL_DEPTH24_STENCIL8, true);
		// RGB = light color, A = specular power
		_lightAccumulation = createRenderPassOutput<Texture2D>(screen_size.x, screen_size.y, GL_RGBA8, true);
		
		// We create the render pass
		std::shared_ptr<DeferredBasicBuffering> basicBuffering = std::make_shared<DeferredBasicBuffering>(_painter_manager, _diffuse, _normal, _specular, _depthStencil);
		std::shared_ptr<DeferredPointLightning> pointLightning = std::make_shared<DeferredPointLightning>(_painter_manager, _normal, _depthStencil, _lightAccumulation);
		std::shared_ptr<DeferredMerging> merging = std::make_shared<DeferredMerging>(_painter_manager, _diffuse, _specular, _lightAccumulation);

		// The entry point is the basic buffering pass
		_rendering_list.emplace_back(basicBuffering);
		// We link the entry point with the other pass
		basicBuffering->setNextPass(pointLightning);
		pointLightning->setNextPass(merging);
	}

	DeferredShading::DeferredShading(DeferredShading &&move) :
		ARenderingPipeline(std::move(move))
	{

	}

	IRenderingPipeline & DeferredShading::render(RenderPipeline const &pipeline, RenderLightList const &lights, CameraInfos const &infos)
	{
		// We iterate over the entry points
		for (auto &renderPass : _rendering_list)
		{
			renderPass->render(pipeline, lights, infos);
		}
		return (*this);
	}

}