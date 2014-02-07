#ifndef   __COLLISION_SPHERE_FILE_HPP__
# define  __COLLISION_SPHERE_FILE_HPP__

#include <MediaFiles/MediaFile.hpp>
#include <Utils/File.hpp>
#include <btBulletDynamicsCommon.h>
#include <btBulletWorldImporter.h>

struct CollisionSphereFile : public MediaFile<CollisionSphereFile>
{
public:
	CollisionSphereFile()
		: MediaFile<CollisionSphereFile>()
		, shape(nullptr)
	{
		_type = COLLISION_SPHERE;
	}

	virtual ~CollisionSphereFile()
	{
	}

	CollisionSphereFile(const CollisionSphereFile &o)
		: MediaFile<CollisionSphereFile>(o)
		, shape(nullptr)
	{
			shape = o.shape;
	}

	CollisionSphereFile &operator=(const CollisionSphereFile &o)
	{
		if (&o != this)
		{
			shape = o.shape;
		}
		return *this;
	}

	void unserialize(const File &f)
	{
		btBulletWorldImporter import(0);
		assert(f.exists() == true && "File do not exists");
		assert(import.loadFile(f.getFullName().c_str()) == true && "Bullet importer cannot open file.");
		int n = import.getNumCollisionShapes();
		assert(n > 0 && "Bullet file is not correct. No collision box inside.");
		shape = std::shared_ptr<btSphereShape>(static_cast<btSphereShape*>(import.getCollisionShapeByIndex(0)));
	}

	// WILL NEVER BE CALLED
	template <class Archive>
	void serialize(Archive &ar)
	{}

	void serialize(std::ofstream &s)
	{
		btDefaultSerializer	serializer;
		serializer.startSerialization();
		shape->serializeSingleShape(&serializer);
		serializer.finishSerialization();
		s.write((const char *)(serializer.getBufferPointer()), serializer.getCurrentBufferSize());
	}

	std::shared_ptr<btSphereShape> shape;
};

#endif    //__COLLISION_SPHERE_FILE_HPP__