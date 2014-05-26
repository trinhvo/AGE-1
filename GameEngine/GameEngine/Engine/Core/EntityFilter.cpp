#include <Core/EntityFilter.hpp>

EntityFilter::EntityFilter(std::weak_ptr<AScene> &&scene)
: _scene(std::move(scene))
, _locked(false)
, entityAdded(nullptr)
, entityRemoved(nullptr)
{
	assert(_scene.lock() != nullptr && "System Scene is not valid.");
}

EntityFilter::~EntityFilter()
{
}

std::set<Entity> &EntityFilter::getCollection()
{
	return _collection;
}

void EntityFilter::requireTag(TAG_ID id)
{
	_barcode.setTag(id);
	_scene.lock()->filterSubscribe(id, this);
}

void EntityFilter::unRequireTag(TAG_ID id)
{
	_barcode.unsetTag(id);
	_scene.lock()->filterUnsubscribe(id, this);
}

void EntityFilter::componentAdded(EntityData &&e, COMPONENT_ID typeId)
{
	if (e.barcode.match(_barcode))
	{
		if (_locked)
		{
			_toAdd.insert(e.entity);
		}
		else
		{
			_collection.insert(e.entity);
			if (entityAdded != nullptr)
				entityAdded(_scene, std::move(e.entity));
		}
	}
}

void EntityFilter::componentRemoved(EntityData &&e, COMPONENT_ID typeId)
{
	if (!e.barcode.match(_barcode))
	{
		if (_locked)
		{
			_trash.insert(e.entity);
		}
		else
		{
			_collection.erase(e.entity);
			if (entityRemoved != nullptr)
				entityRemoved(_scene, std::move(e.entity));			
		}
	}
}

void EntityFilter::tagAdded(EntityData &&e, TAG_ID typeId)
{
	if (e.barcode.match(_barcode))
	{
		if (_locked)
		{
			_toAdd.insert(e.entity);
		}
		else
		{
			_collection.insert(e.entity);
			if (entityAdded != nullptr)
				entityAdded(_scene, std::move(e.entity));

		}
	}
}

void EntityFilter::tagRemoved(EntityData &&e, TAG_ID typeId)
{
	if (!e.barcode.match(_barcode))
	{
		if (_locked)
		{
			_trash.insert(e.entity);
		}
		else
		{
			_collection.erase(e.entity);
			if (entityRemoved != nullptr)
				entityRemoved(_scene, std::move(e.entity));	
		}
	}
}

void EntityFilter::lock()
{
	if (_locked)
		return;
	_locked = true;
}

void EntityFilter::unlock()
{
	if (!_locked)
		return;
	_locked = false;
	for (auto &&e : _toAdd)
	{
		_collection.insert(e);
		if (entityAdded != nullptr)
			entityAdded(_scene, std::move(const_cast<Entity&>(e)));
	}
	for (auto &&e : _trash)
	{
		_collection.erase(e);
		if (entityRemoved != nullptr)
			entityRemoved(_scene, std::move(const_cast<Entity&>(e)));
	}
	_trash.clear();
	_toAdd.clear();
}

bool EntityFilter::isLocked() const
{
	return _locked;
}
