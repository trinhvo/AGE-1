#pragma once

#include "Entity.hh"
#include <Components/Component.hh>
#include <vector>
#include <cereal/types/vector.hpp>
#include <Entities/EntityData.hh>
#include <Components/ArchetypeComponent.hpp>
#include <Utils/Debug.hpp>

namespace AGE
{
	struct EntitySerializationInfos
	{
		std::vector <std::size_t> children;
		std::vector <ComponentBase*> components;
		std::vector <ComponentType> componentTypes;
		std::vector<std::string> archetypesDependency;
		Entity entity;
		std::map<ComponentType, std::size_t> *typesMap; // used to unserialize

		EntitySerializationInfos(EntityData *e, std::map<ComponentType, std::size_t> *_typesMap);

		EntitySerializationInfos();

		template < typename Archive >
		void save(Archive &ar, const std::uint32_t version) const
		{
			AGE::Link link = entity->getLink();
			ENTITY_FLAGS flags = entity.getFlags();
			ar(cereal::make_nvp("link", link)
				, cereal::make_nvp("children", children)
				, cereal::make_nvp("flags", flags)
				, cereal::make_nvp("components_number", componentTypes)
				, CEREAL_NVP(archetypesDependency)
				);
			for (auto &e : components)
			{
				ComponentRegistrationManager::getInstance().serializeJson(e, ar);
			}
		}

		template < typename Archive >
		void load(Archive &ar, const std::uint32_t version)
		{
			Link l;
			ENTITY_FLAGS f;

			assert(typesMap != nullptr);
			ar(
				l
				, children
				, f
				, componentTypes
				, archetypesDependency);

			_postLoad(l, f, ar);
		}

	private:
		void _postLoad(Link &link, ENTITY_FLAGS flags, cereal::JSONInputArchive &ar);
	};
}

CEREAL_CLASS_VERSION(AGE::EntitySerializationInfos, 0)