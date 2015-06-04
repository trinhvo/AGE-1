#include "BFCLinkTracker.hpp"
#include <Core/Link.hpp>
#include <Utils/Debug.hpp>
#include <Utils/Profiler.hpp>

namespace AGE
{
	BFCLinkTracker::BFCLinkTracker()
	{}

	std::size_t BFCLinkTracker::addLink(BFCLink *link)
	{
		SCOPE_profile_cpu_function("BFC");

		std::size_t result = -1;

		if (_free.empty() == false)
		{
			result = _free.front();
			_free.pop();
		}
		else
		{
			result = _links.size();
			_links.push_back(link);
		}
		return result;
	}

	void BFCLinkTracker::removeLink(std::size_t index)
	{
		SCOPE_profile_cpu_function("BFC");

		AGE_ASSERT(index != -1 && index < _links.size());
		_links[index] = nullptr;
		_free.push(index);
	}

	void BFCLinkTracker::reset()
	{
		SCOPE_profile_cpu_function("BFC");
		for (auto &e : _links)
		{
			// beurk
			if (e != nullptr)
			{
				e->resetBFCTrackerIndex();
			}
		}
		_links.clear();

		//beurk
		while (!_free.empty())
			_free.pop();
	}
}