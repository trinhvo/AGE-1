#ifndef   __GLM_SERIALIZATION_HPP__
# define  __GLM_SERIALIZATION_HPP__

#include <glm/glm.hpp>
#include <cereal/cereal.hpp>
#include <cereal/types/common.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/archives/json.hpp>
#include <cereal/archives/binary.hpp>
#include <cereal/types/base_class.hpp>

namespace cereal
{
	template<typename Archive>
	void save(Archive &ar, const glm::vec2 &v)
	{
		ar(v.x, v.y);
	}

	template<typename Archive>
	void load(Archive &ar, glm::vec2 &v)
	{
		float x, y;
		ar(x, y);
		v = glm::vec2(x, y);
	}

	template<typename Archive>
	void save(Archive &ar, const glm::vec3 &v)
	{
		ar(v.x, v.y, v.z);
	}

	template<typename Archive>
	void load(Archive &ar, glm::vec3 &v)
	{
		float x, y, z;
		ar(x, y, z);
		v = glm::vec3(x, y, z);
	}

	template<typename Archive>
	void save(Archive &ar, const glm::vec4 &v)
	{
		ar(v.x, v.y, v.z, v.w);
	}

	template<typename Archive>
	void load(Archive &ar, glm::vec4 &v)
	{
		float x, y, z, w;
		ar(x, y, z, w);
		v = glm::vec4(x, y, z, w);
	}
}



#endif    //__GLM_SERIALIZATION_HPP__