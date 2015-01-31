#pragma once

#include "Thread.hpp"
#include "QueuePusher.hpp"
#include "QueueOwner.hpp"
#include <Utils/Containers/Vector.hpp>
#include <memory>
#include <Render/GeometryManagement/Painting/PaintingManager.hh>
#include <Core/PrepareRender/RenderCamera.hh>
#include <Render/Pipelining/Pipelines/IRenderingPipeline.hh>

namespace AGE
{
	class SdlContext;
	class Input;

	class Engine;
	struct DrawableCollection;

	class RenderThread : public Thread, public QueueOwner
	{
	public:
		virtual bool init();
		virtual bool release();
		bool update();
		virtual bool launch();
		virtual bool stop();

	public:
		PaintingManager paintingManager;
		std::vector<std::unique_ptr<IRenderingPipeline>> _pipelines;

	private:
		RenderThread();
		virtual ~RenderThread();
		RenderThread(const RenderThread &) = delete;
		RenderThread(RenderThread &&) = delete;
		RenderThread &operator=(const RenderThread &) = delete;
		RenderThread &operator=(RenderThread &&) = delete;

		std::thread _threadHandle;
		std::atomic_bool _insideRun;
		bool _run;

		SdlContext *_context;
		AGE::Vector < AGE::RenderCamera > _drawlist;

		friend class ThreadManager;
	};
}