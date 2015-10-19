#include <Render/Properties/SkeletonProperty.hpp>
#include <Render/ProgramResources/Types/Uniform/Mat4Array255.hh>
#include <mutex>

namespace AGE
{
	SkeletonProperty::SkeletonProperty() :
		AProperty(std::string("bones"))
	{
		std::fill(_matrixArray, _matrixArray + sizeof(_matrixArray) / sizeof(glm::mat4), glm::mat4(1));
	}

	SkeletonProperty::~SkeletonProperty()
	{

	}


	SkeletonProperty::SkeletonProperty(SkeletonProperty &&move) :
		AProperty(std::move(move))
	{
		AGE_ASSERT("Pas implement�");
	}

	void SkeletonProperty::update(Mat4Array255 *res, SkeletonProperty *trans)
	{
		res->set(trans->_matrixArray, trans->_size);
	}

	void SkeletonProperty::instanciedUpdate(Mat4Array255 *, SkeletonProperty *)
	{
	}

	glm::mat4 *SkeletonProperty::get()
	{
		std::lock_guard<AGE::SpinLock> lock(_mutex);
		return (_matrixArray);
	}

	SkeletonProperty & SkeletonProperty::set(const glm::mat4 *skinningMatrix, std::size_t size)
	{
		std::lock_guard<AGE::SpinLock> lock(_mutex);
		AGE_ASSERT(size < 255);
		memcpy((void*)&_matrixArray, skinningMatrix, size * sizeof(glm::mat4));
		_size = size;
		return (*this);
	}
}