#include "RenderThread.hpp"

namespace AGE
{
	RenderThread::RenderThread()
		: Thread(AGE::Thread::ThreadType::Render)
		, _activeContext(nullptr)
	{}

	RenderThread::~RenderThread()
	{}

	bool RenderThread::init()
	{
		this->registerTaskCallback<MainThreadToRenderThread::CreateRenderContext>([&](MainThreadToRenderThread::CreateRenderContext &msg)
		{
			this->_contexts.push_back(std::make_unique<RenderContext>(msg.engine));
			msg.setValue(true);
		});
		return true;
	}

	bool RenderThread::release()
	{
		return true;
	}

	bool RenderThread::launch()
	{
		if (!init())
			return false;
		_threadHandle = std::thread([&](){
			this->_run = true;
			while (this->_run)
			{
				update();
			}
		});
		return true;
	}

	bool RenderThread::stop()
	{
		_run = false;
		_threadHandle.join();
		return true;
	}

	bool RenderThread::update()
	{
		/*
		- Tant qu'il n'y a pas de command
		    -> je pop des task
		- Une fois que j'ai mes commandes
            -> pour chacunes d'elles
			    -> je regarde si c'est a moi de les traiter (ex : changement de scene)
				-> si ca n'est pas a moi de les traiter
				    -> je les passe au render context actif
					-> si il n'y a pas de render context actif, c'est que j'ai fait une erreur, et j'assert dans ta face :D
		*/

		_registerId();

		TMQ::PtrQueue commands;
		TMQ::PtrQueue tasks;

		bool commandsCleared = false;

		if (!getCommandQueue()->getReadableQueue(commands))
		{
			getTaskQueue()->getReadableQueue(tasks);
			while (!tasks.empty())
			{
				//pop all tasks
				auto task = tasks.front();
				assert(executeTask(task)); // we receive a task that we cannot treat
				tasks.pop();
			}
		}
		else
		{
			// pop all commands
			while (!commands.empty())
			{
				auto command = commands.front();
				if (!executeCommand(command))
				{
					assert(!_activeContext);
					/*_activeContext->executeCommand(command);*/ // TO UNCOMMENT
				}
				commands.pop();
			}
		}
		return true;
	}
}