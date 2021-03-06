#pragma once

#include <glm/glm.hpp>

namespace AGE
{

	enum ECollision
	{
		INSIDE,
		OUTSIDE,
		INTERSECT
	};

	struct AABoundingBox
	{
		glm::vec3		minPoint;
		glm::vec3		maxPoint;
		glm::vec3		center;

		AABoundingBox();
		~AABoundingBox();
		AABoundingBox(glm::vec3 const &min, glm::vec3 const &max);

		void recomputeCenter();

		glm::vec3	getPositivePoint(glm::vec3 const &normal) const;
		glm::vec3	getNegativePoint(glm::vec3 const &normal) const;
		glm::vec3   getCornerPoint(std::size_t index /*from 0 to 7*/);

		// create an AABB from another AABB and a transformation matrix
		void		fromTransformedBox(AABoundingBox const &oth, glm::mat4 const &transform);

		// check the state of collision between two AABB
		ECollision checkCollision(AABoundingBox const &oth, glm::i8vec3 &direction) const;
		bool		checkCollision(AABoundingBox const &oth) const;
		// check if a point is in the aabb
		bool checkPointIn(glm::vec3 point) const;
		glm::i8vec3 AABoundingBox::getDirection(glm::vec3 point) const;

		glm::vec3 getSize() const;

		template <class Archive>
		void serialize(Archive &ar)
		{
			ar(minPoint, maxPoint, center);
		}
	};
}