#include <Components/RigidBody.hpp>
#include <Components/Collider.hpp>
#include <Components/PhysicsData.hpp>
#include <Core/AScene.hh>
#include <Physics/WorldInterface.hpp>

namespace AGE
{
	// Methods
	void RigidBody::init(void)
	{
		assert(rigidBody == nullptr && "RigidBody already initialized");
		rigidBody = entity.getScene()->getInstance<Physics::WorldInterface>()->createRigidBody(entity.addComponent<Private::PhysicsData>()->getData());
		rigidBody->rigidBody = this;
		Link *link = entity.getLinkPtr();
		setPosition(link->getPosition());
		setRotation(link->getOrientation());
	}

	void RigidBody::setAngularDrag(float angularDrag)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->setAngularDrag(angularDrag);
	}

	float RigidBody::getAngularDrag(void) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->getAngularDrag();
	}

	void RigidBody::setAngularVelocity(const glm::vec3 &angularVelocity)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->setAngularVelocity(angularVelocity);
	}

	glm::vec3 RigidBody::getAngularVelocity(void) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->getAngularVelocity();
	}

	void RigidBody::setCenterOfMass(const glm::vec3 &centerOfMass)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->setCenterOfMass(centerOfMass);
	}

	glm::vec3 RigidBody::getCenterOfMass(void) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->getCenterOfMass();
	}

	void RigidBody::setLinearDrag(float linearDrag)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->setLinearDrag(linearDrag);
	}

	float RigidBody::getLinearDrag(void) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->getLinearDrag();
	}

	void RigidBody::setLinearVelocity(const glm::vec3 &linearVelocity)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->setLinearVelocity(linearVelocity);
	}

	glm::vec3 RigidBody::getLinearVelocity(void) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->getLinearVelocity();
	}

	void RigidBody::setMass(float mass)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->setMass(mass);
	}

	float RigidBody::getMass(void) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->getMass();
	}

	void RigidBody::setDiagonalInertiaTensor(const glm::vec3 &diagonalInertiaTensor)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->setDiagonalInertiaTensor(diagonalInertiaTensor);
	}

	glm::vec3 RigidBody::getDiagonalInertiaTensor(void) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->getDiagonalInertiaTensor();
	}

	void RigidBody::setMaxAngularVelocity(float maxAngularVelocity)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->setMaxAngularVelocity(maxAngularVelocity);
	}

	float RigidBody::getMaxAngularVelocity(void) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->getMaxAngularVelocity();
	}

	void RigidBody::setMaxDepenetrationVelocity(float maxDepenetrationVelocity)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->setMaxDepenetrationVelocity(maxDepenetrationVelocity);
	}

	float RigidBody::getMaxDepenetrationVelocity(void) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->getMaxDepenetrationVelocity();
	}

	void RigidBody::setPosition(const glm::vec3 &position)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->setPosition(position);
	}

	glm::vec3 RigidBody::getPosition(void) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->getPosition();
	}

	void RigidBody::setRotation(const glm::quat &rotation)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->setRotation(rotation);
	}

	glm::quat RigidBody::getRotation(void) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->getRotation();
	}

	void RigidBody::affectByGravity(bool mustBeAffectedByGravity)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->affectByGravity(mustBeAffectedByGravity);
	}

	bool RigidBody::isAffectedByGravity(void) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->isAffectedByGravity();
	}

	void RigidBody::setAsKinematic(bool mustBeKinematic)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->setAsKinematic(mustBeKinematic);
	}

	bool RigidBody::isKinematic(void) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->isKinematic();
	}

	void RigidBody::setCollisionDetectionMode(Physics::CollisionDetectionMode collisionDetectionMode)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->setCollisionDetectionMode(collisionDetectionMode);
	}

	Physics::CollisionDetectionMode RigidBody::getCollisionDetectionMode(void) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->getCollisionDetectionMode();
	}

	void RigidBody::addExplosionForce(float explosionForce, const glm::vec3 &explosionPosition, float explosionRadius, Physics::ForceMode forceMode)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->addExplosionForce(explosionForce, explosionPosition, explosionRadius, forceMode);
	}

	void RigidBody::addForce(const glm::vec3 &force, Physics::ForceMode forceMode)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->addForce(force, forceMode);
	}

	void RigidBody::addForceAtWorldPosition(const glm::vec3 &force, const glm::vec3 &position, Physics::ForceMode forceMode)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->addForceAtWorldPosition(force, position, forceMode);
	}

	void RigidBody::addForceAtLocalPosition(const glm::vec3 &force, const glm::vec3 &position, Physics::ForceMode forceMode)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->addForceAtLocalPosition(force, position, forceMode);
	}

	void RigidBody::addAbsoluteTorque(const glm::vec3 &torque, Physics::ForceMode forceMode)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->addAbsoluteTorque(torque, forceMode);
	}

	void RigidBody::addRelativeTorque(const glm::vec3 &torque, Physics::ForceMode forceMode)
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		rigidBody->addRelativeTorque(torque, forceMode);
	}

	glm::vec3 RigidBody::getVelocityAtWorldPosition(const glm::vec3 &position) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->getVelocityAtWorldPosition(position);
	}

	glm::vec3 RigidBody::getVelocityAtLocalPosition(const glm::vec3 &position) const
	{
		assert(rigidBody != nullptr && "Invalid RigidBody");
		return rigidBody->getVelocityAtLocalPosition(position);
	}

	// Inherited Methods
	void RigidBody::reset(void)
	{
		if (rigidBody != nullptr)
		{
			entity.getScene()->getInstance<Physics::WorldInterface>()->destroyRigidBody(rigidBody);
			rigidBody = nullptr;
		}
		if (!entity.haveComponent<Collider>())
		{
			entity.removeComponent<Private::PhysicsData>();
		}
	}
}