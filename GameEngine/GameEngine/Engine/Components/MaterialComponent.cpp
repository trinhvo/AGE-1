#include "MaterialComponent.h"
#include "Utils/PubSub.hpp"
#include <Core/Renderer.hh>

namespace Component
{
	MaterialComponent::MaterialComponent(Entity &entity)
		: ComponentBase<MaterialComponent>(entity),
		_material(nullptr)
	{
	}

	MaterialComponent::~MaterialComponent(void)
	{}

	void MaterialComponent::init(std::string const &name)
	{
		_material = _entity->getScene()->getEngine().getInstance<Renderer>().getMaterialManager().getMaterial(name);
	}

	void MaterialComponent::init(SmartPointer<Material> material)
	{
		_material = material;
	}

	void MaterialComponent::reset()
	{
		_material = nullptr;
	}


	bool                				MaterialComponent::setMaterial(std::string const &name)
	{
		SmartPointer<Material> old = _material;
		_material = _entity->getScene()->getEngine().getInstance<Renderer>().getMaterialManager().getMaterial(name);
		_entity->broadCast(std::string("MaterialComponentChanged"), this->getEntity(), old, _material);
		return (_material != nullptr);
	}

	SmartPointer<Material>              MaterialComponent::getMaterial() const
	{
		return _material;
	}

}