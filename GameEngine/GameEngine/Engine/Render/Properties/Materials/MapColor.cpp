# include <Render/Properties/Materials/MapColor.hh>
# include <Render/ProgramResources/Types/Uniform/Sampler/Sampler2D.hh>

namespace AGE
{
	MapColor::MapColor(std::string const &add_name) :
		AProperty(add_name + "_map")
	{

	}

	MapColor::MapColor(MapColor &&move) :
		AProperty(std::move(move)),
		_texture(std::move(move._texture))
	{

	}

	void MapColor::_update(std::shared_ptr<Program> const &p)
	{
		auto resource = std::static_pointer_cast<Sampler2D>(get_resource(p));
		if (resource) {
			*resource = _texture;
		}
	}

	std::shared_ptr<Texture2D> const & MapColor::get()
	{
		std::lock_guard<AGE::SpinLock> lock(_mutex);
		return (_texture);
	}

	MapColor & MapColor::set(std::shared_ptr<Texture2D> const &map)
	{
		std::lock_guard<AGE::SpinLock> lock(_mutex);
		_texture = map;
		return (*this);
	}
}