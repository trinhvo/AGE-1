#include <Components/Light.hh>
#include <Core/AScene.hh>
#include <Utils/MathematicTools.hh>
#include <Threads/PrepareRenderThread.hpp>
#include <Threads/ThreadManager.hpp>
#include <glm/glm.hpp>

#ifdef EDITOR_ENABLED
#include <imgui\imgui.h>
#include <glm/gtc/type_ptr.hpp>
#endif

namespace AGE
{
	PointLightComponent::PointLightComponent()
		: _scene(nullptr)
		, _range(1)
		, _color(1)
	{
	}

	PointLightComponent::~PointLightComponent()
	{

	}

	PointLightComponent::PointLightComponent(PointLightComponent const &o)
		: _scene(o._scene)
		, _key(o._key)
		, _range(o._range)
		, _color(o._color)
	{

	}

	PointLightComponent &PointLightComponent::operator=(PointLightComponent const &p)
	{
		_scene = p._scene;
		_key = p._key;
		_range = p._range;
		_color = p._color;
		return (*this);
	}

	void PointLightComponent::reset()
	{
		if (!_key.invalid())
			entity.getLink().unregisterOctreeObject(_key);
		_key = AGE::PrepareKey();
		_color = glm::vec3(1);
		_range = glm::vec3(1);
	}

	void PointLightComponent::init()
	{
		_key = AGE::GetPrepareThread()->addPointLight();
		entity.getLink().registerOctreeObject(_key);
		assert(!_key.invalid());
	}

	PointLightComponent &PointLightComponent::set(glm::vec3 const &color, glm::vec3 const &range)
	{
		_color = color;
		_range = range;
		AGE::GetPrepareThread()->setPointLight(color, range, _key);
		return (*this);
	}

	void PointLightComponent::postUnserialization()
	{
		init();
		set(_color, _range);
	}

#ifdef EDITOR_ENABLED
	void PointLightComponent::editorCreate(AScene *scene)
	{}

	void PointLightComponent::editorDelete(AScene *scene)
	{}

	void PointLightComponent::editorUpdate(AScene *scene)
	{
		if (ImGui::ColorEdit3("Color", getColorPtr()))
		{
			set(_color, _range);
		}
		if (ImGui::SliderFloat3("Range", glm::value_ptr(_range), 0.0f, 1.0f))
		{
			set(_color, _range);
		}
	}
#endif
}