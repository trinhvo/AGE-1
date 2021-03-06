#pragma once

#include <System/System.h>
#include <Core/EntityFilter.hpp>

namespace AGE
{
	class FPSCharacterSystem : public System<FPSCharacterSystem>
	{
	public:
		FPSCharacterSystem() = delete;
		FPSCharacterSystem(AScene *scene);
		~FPSCharacterSystem() = default;

	private:
		virtual bool initialize();
		virtual void updateBegin(float time);
		virtual void mainUpdate(float time);
		virtual void updateEnd(float time);

		EntityFilter _filter;
	};
}

