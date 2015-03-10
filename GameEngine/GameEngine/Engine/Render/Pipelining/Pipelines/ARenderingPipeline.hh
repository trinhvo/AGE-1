#pragma once

# include <Render/Pipelining/Pipelines/IRenderingPipeline.hh>
# include <utility>

namespace AGE
{

	class Painter;
	class Program;
	class PaintingManager;
	class PropertyManager;

	class ARenderingPipeline : public IRenderingPipeline
	{
	public:
		virtual ~ARenderingPipeline() {}
		virtual bool recompileShaders();
	protected:
		ARenderingPipeline(std::string &&name, std::shared_ptr<PaintingManager> const &painter_manager);
		ARenderingPipeline(ARenderingPipeline &&move);

	protected:
		virtual std::vector<std::shared_ptr<IRendering>> const &get_rendering() const override final;
		virtual std::vector<std::shared_ptr<Program>> const &get_programs() const override final;
		virtual std::string const &name() const override final;

	protected:
		std::string _name;
		std::shared_ptr<PaintingManager> _painter_manager;
		std::vector<std::shared_ptr<IRendering>> _rendering_list;
		std::vector<std::shared_ptr<Program>> _programs;
	};

}