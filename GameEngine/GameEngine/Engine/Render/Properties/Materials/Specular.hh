#pragma once

#include <Render/Properties/AProperty.hh>
#include <Render/Properties/Materials/Ratio.hh>
#include <Render/Properties/Materials/Color.hh>
#include <Render/Properties/Materials/MapColor.hh>

namespace AGE
{
	class Texture2D;

	class Specular : public AProperty
	{
	public:
		Specular();
		Specular(Specular &&move);

	private:
		virtual void _update(std::shared_ptr<Program> const &p) override final;

	public:
		float get_ratio();
		Specular &set_ratio(float ratio);
		glm::vec4 const &get_color();
		Specular &set_color(glm::vec4 const &color);
		std::shared_ptr<Texture2D> const &get_map();
		Specular &set_map(std::shared_ptr<Texture2D> const &m);

	private:
		Ratio _ratio;
		Color _color;
		MapColor _mapColor;
	};
}