#pragma once

#include <map>
#include <functional>
#include <Components/Component.hh>
#include <Entities/EntityTypedef.hpp>

#define TYPE_TO_STRING(T)(#T);

namespace AGE
{
	class AScene;
	struct ComponentBase;

	class ComponentRegistrar
	{
		typedef std::function<void(ComponentBase *, cereal::JSONOutputArchive &)> RegisterJsonFn;
		typedef std::function<void(void *, cereal::JSONInputArchive &)> LoadJsonFn;

		typedef std::function<void(ComponentBase *, cereal::PortableBinaryOutputArchive &)> RegisterBinaryFn;

	private:
		ComponentRegistrar();

	public:
		~ComponentRegistrar();
		static ComponentRegistrar &getInstance()
		{
			static ComponentRegistrar instance;
			return instance;
		}

		template <class T>
		void registerComponentType(const char *name)
		{
			std::size_t key = typeid(T).hash_code();
			auto ageId = Component<T>::getTypeId();
			auto it = _creationFunctions.find(key);
			if (it != std::end(_creationFunctions))
				return;
			_creationFunctions.insert(std::make_pair(key, [](Entity *e){return e->addComponent<T>(); }));
			_typeIds.insert(std::make_pair(key, ageId));
			_ageTypeIds.insert(std::make_pair(ageId, key));

			_jsonSaveMap.insert(std::make_pair(ageId, RegisterJsonFn([=](ComponentBase *c, cereal::JSONOutputArchive &ar)
			{
				ar(cereal::make_nvp(name,*(static_cast<T*>(c))));
			})));
			_jsonLoadMap.insert(std::make_pair(ageId, LoadJsonFn([=](void *ptr, cereal::JSONInputArchive &ar){
				T *c = new(ptr)T();
				ar(*c);
			})));


			_binarySaveMap.insert(std::make_pair(ageId, RegisterBinaryFn([](ComponentBase *c, cereal::PortableBinaryOutputArchive &ar)
			{
				ar(*(static_cast<T*>(c)));
			})));

			_componentNames.insert(std::make_pair(ageId, name));
		}

		const std::string &getComponentName(ComponentType type);
		void serializeJson(ComponentBase *c, cereal::JSONOutputArchive &ar);
		void loadJson(std::size_t componentHashId, Entity &e, cereal::JSONInputArchive &ar);
		std::size_t getSystemIdForAgeId(ComponentType id);

		inline const std::map<std::size_t, std::function<ComponentBase*(Entity *)>> &getCreationFunctions() { return _creationFunctions; }
		inline const std::map<std::size_t, ComponentType> &getSystemIdToAgeIdMap() const { return _typeIds; }
		inline const std::map<ComponentType, std::size_t> &getAgeIdToSystemIdMap() const { return _ageTypeIds; }

	private:
		std::map<std::size_t, std::function<ComponentBase*(Entity *)>> _creationFunctions;
		std::map<std::size_t, ComponentType> _typeIds;
		std::map<ComponentType, std::size_t> _ageTypeIds;
		std::map < ComponentType, RegisterJsonFn> _jsonSaveMap;
		std::map < ComponentType, LoadJsonFn> _jsonLoadMap;
		std::map < ComponentType, RegisterBinaryFn> _binarySaveMap;
		std::map < ComponentType, std::string> _componentNames;
	};
}

#define REGISTER_COMPONENT_TYPE(T)(AGE::ComponentRegistrar::getInstance().registerComponentType<T>(#T));