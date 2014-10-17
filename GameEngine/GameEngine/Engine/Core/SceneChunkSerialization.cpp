#include "SceneChunkSerialization.hpp"
#include <Components/ArchetypeComponent.hpp>

namespace AGE
{
	SceneChunkSerialization SceneChunkSerialization::CreateForSerialization(const CptIdsRefTable &refTable, std::vector<EntitySerializationInfos> entities)
	{
		SceneChunkSerialization instance;
		instance.componentsIdReferenceTable = refTable;

		for (auto &e : entities)
		{
			auto &components = e.entity->getComponentList();

			bool continueEntityFiltering = true;

			if (e.entity->haveComponent<ArchetypeComponent>() && continueEntityFiltering)
			{
				e.componentTypes.push_back(Component<ArchetypeComponent>::getTypeId());
				e.components.push_back(e.entity->getComponent<ArchetypeComponent>());
				e.archetypesDependency.push_back(e.entity->getComponent<ArchetypeComponent>()->archetypeName);
				continueEntityFiltering = false;
			}

			if (continueEntityFiltering)
			{
				for (auto &c : components)
				{
					if (c)
					{
#ifdef EDITOR_ENABLED
						if (WESerialization::SerializeForEditor() == false && !c->serializeInExport())
						{
							continue;
						}
#endif
						e.componentTypes.push_back(c->getType());
						e.components.push_back(c);
					}
				}
			}
			instance.list.push_back(e);
		}

		instance.entityNbr = instance.list.size();
		return instance;
	}

	SceneChunkSerialization SceneChunkSerialization::CreateForLoad(AScene *scene)
	{
		SceneChunkSerialization instance;
		instance.sceneToLoad = scene;
		return instance;
	}
}