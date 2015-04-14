#pragma once

#include "WorldInterface.hpp"
#include "BulletPhysics.hpp"

namespace AGE
{
	namespace Physics
	{
		class BulletWorld final : public WorldInterface
		{
		public:
			// Constructors
			BulletWorld(void) = delete;

			BulletWorld(BulletPhysics *physics, const glm::vec3 &gravity);

			BulletWorld(const BulletWorld &) = delete;

			// Assignment Operators
			BulletWorld &operator=(const BulletWorld &) = delete;

			// Destructor
			virtual ~BulletWorld(void) = default;

		private:
			// Inherited Methods
			void setGravity(const glm::vec3 &gravity) override final;

			glm::vec3 getGravity(void) const override final;

			void enableCollisionBetweenGroups(FilterGroup group1, FilterGroup group2) override final;

			void disableCollisionBetweenGroups(FilterGroup group1, FilterGroup group2) override final;

			void simulate(float stepSize) override final;

			RigidBodyInterface *createRigidBody(void *&data) override final;

			ColliderInterface *createCollider(ColliderType colliderType, void *&data) override final;

			MaterialInterface *createMaterial(ColliderInterface *collider) override final;
		};
	}
}