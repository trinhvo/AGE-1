#include <Core/EntityIdRegistrationManager.hh>
#include <cassert>

namespace AGE
{
	EntityIdRegistrationManager::EntityIdRegistrationManager()
	{}

	EntityIdRegistrationManager::~EntityIdRegistrationManager()
	{}


	void EntityIdRegistrationManager::registrarUnserializedEntity(Entity e, std::size_t id)
	{
		_unser.insert(std::make_pair(id, e));
	}

	std::size_t EntityIdRegistrationManager::registrarSerializedEntity(std::size_t id)
	{
		static std::size_t counter = 0;
		if (_ser.find(id) != std::end(_ser))
			return _ser[id];
		_ser.insert(std::make_pair(id, ++counter));
		return counter;
	}

	void EntityIdRegistrationManager::entityHandle(std::size_t id, Entity *e)
	{
		_toUpdate.insert(std::make_pair(id, e));
	}

	void EntityIdRegistrationManager::updateEntityHandles()
	{
		//TODO
		//std::stack<Entity> stack;
		//for (auto &e : _unser)
		//{
		//	stack.push(e.second);
		//	updateEntityHandle(e.second, e.first);
		//}
		//while (!stack.empty())
		//{
		//	stack.top()->computeTransformAndUpdateGraphnode();
		//	stack.pop();
		//}
		//assert(_toUpdate.size() == 0 && _graphNode.size() == 0 && "All handles have not been unserialized correctly.");
		//_ser.clear();
		//_unser.clear();
	}

	void EntityIdRegistrationManager::updateEntityHandle(Entity e, std::size_t id)
	{
		//TODO
		//auto ret = _toUpdate.equal_range(id);
		//for (auto it = ret.first; it != ret.second; ++it)
		//{
		//	auto test = it->second;
		//	auto testy = *test;
		//	*(it->second) = e;
		//}
		//_toUpdate.erase(id);

		//auto t = _graphNode.find(id);
		//if (t == std::end(_graphNode))
		//	return;
		////for (auto it : t->second.childs)
		////{
		////	auto h = _unser.find(it);
		////	if (h == std::end(_unser))
		////		continue;
		////	e->addChild(h->second);
		////}
		//if (t->second.haveParent)
		//{
		//	auto h = _unser.find(t->second.parent);
		//	if (h != std::end(_unser))
		//		e->setParent(h->second, true);
		//}
		//else
		//{
		//	e->_globalTransform = e->_localTransform;
		//}
		//_graphNode.erase(id);
	}

	void EntityIdRegistrationManager::registrarGraphNode(std::size_t e, GraphNodeUnserialize g)
	{

		//TODO
		//_graphNode.insert(std::make_pair(e, g));
	}
}