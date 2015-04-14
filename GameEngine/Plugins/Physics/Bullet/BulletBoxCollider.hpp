#pragma once

#include "BoxColliderInterface.hpp"
#include "BulletCollider.hpp"

#pragma warning(push)
#pragma warning(disable: 4250)

namespace AGE
{
	namespace Physics
	{
		class BulletBoxCollider final : public BoxColliderInterface, public BulletCollider
		{
		public:
			// Constructors
			BulletBoxCollider(void) = delete;

			BulletBoxCollider(WorldInterface *world, void *&data);

			BulletBoxCollider(const BulletBoxCollider &) = delete;

			// Assignment Operators
			BulletBoxCollider &operator=(const BulletBoxCollider &) = delete;

		private:
			// Destructor
			~BulletBoxCollider(void) = default;

			// Inherited Methods
			void setCenter(const glm::vec3 &center) override final;

			glm::vec3 getCenter(void) const override final;

			void setSize(const glm::vec3 &size) override final;

			glm::vec3 getSize(void) const override final;
		};
	}
}

#pragma warning(pop)