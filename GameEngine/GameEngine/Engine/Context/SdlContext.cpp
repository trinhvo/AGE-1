#include "context/SdlContext.hh"
#include "Utils/OpenGL.hh"
#include <iostream>
#include <Utils/DependenciesInjector.hpp>
#include <Core/Input.hh>
#include <SDL/SDL.h>
#include <Core/Input.hh>
#include <Configuration.hpp>
#include <Threads/ThreadManager.hpp>
#include <Threads/MainThread.hpp>

#ifdef USE_IMGUI
#include <Utils/Age_Imgui.hpp>
#endif


namespace AGE
{
	bool SdlContext::_init(int mode)
	{
		_dependencyManager->setInstance<Input>();

		if (SDL_Init(SDL_INIT_VIDEO) != 0 ||
			//SDL_GL_SetAttribute(SDL_GL_DOUBLEBUFFER, 1) != 0 ||
			//SDL_GL_SetAttribute(SDL_GL_STENCIL_SIZE, 8) != 0 ||
			(_window = SDL_CreateWindow(_windowName.c_str(), SDL_WINDOWPOS_UNDEFINED, SDL_WINDOWPOS_UNDEFINED,
			_screenSize.x, _screenSize.y, SDL_WINDOW_OPENGL | SDL_WINDOW_BORDERLESS | mode)) == NULL ||
			(_glContext = SDL_GL_CreateContext(_window)) == NULL)
		{
			std::cerr << "SDL_GL_CreateContext Failed : " << SDL_GetError() << std::endl;
			return (false);
		}
		if (glewInit() != GLEW_OK)
		{
			std::cerr << "glewInit Failed" << std::endl;
			return (false);
		}
		glEnable(GL_ALPHA_TEST);
		glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

		return (true);
	}

	SdlContext::SdlContext() { }
	SdlContext::~SdlContext() { }
	void SdlContext::swapContext()
	{
		SDL_GL_SwapWindow(_window);
	}

	void SdlContext::refreshInputs()
	{
		SDL_Event events;
		auto input = _dependencyManager->getInstance<Input>();
		std::lock_guard<AGE::SpinLock>(input->getMutex());
		input->clearInputs();
		const Uint8 *keys = SDL_GetKeyboardState(NULL);
		while (SDL_PollEvent(&events))
		{

			if (events.type == SDL_KEYDOWN)
			{
				input->addKeyInput(events.key.keysym.sym);
#ifdef USE_IMGUI
				events.key.keysym.mod = SDL_GetModState();
				GetMainThread()->getQueue()->emplaceTask<ImGuiKeyEvent>(events.key.keysym, true);
#endif
			}
			else if (events.type == SDL_KEYUP)
			{
#ifdef USE_IMGUI
				events.key.keysym.mod = SDL_GetModState();
				GetMainThread()->getQueue()->emplaceTask<ImGuiKeyEvent>(events.key.keysym, false);
#endif
				input->removeKeyInput(events.key.keysym.sym);
			}
			else if (events.type == SDL_MOUSEBUTTONDOWN)
				input->addKeyInput(events.button.button);
			else if (events.type == SDL_MOUSEBUTTONUP)
				input->removeKeyInput(events.button.button);
			else if (events.type == SDL_MOUSEWHEEL)
				input->setMouseWheel(glm::i8vec2(events.wheel.x, events.wheel.y));
			else if (events.type == SDL_MOUSEMOTION)
				input->setMousePosition(glm::i8vec2(events.motion.x, events.motion.y), glm::i8vec2(events.motion.xrel, events.motion.yrel));
			else
				input->addInput(events.type);
		}
	}

	const glm::uvec2 &SdlContext::getScreenSize()
	{
		return _screenSize;
	}

	void SdlContext::setScreenSize(const glm::uvec2 &screenSize)
	{
		_screenSize = screenSize;
		SDL_SetWindowSize(_window, _screenSize.x, _screenSize.y);
		SDL_SetWindowPosition(_window, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED);
	}
}
