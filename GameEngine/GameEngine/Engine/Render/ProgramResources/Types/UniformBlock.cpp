#include <Render/ProgramResources/Types/UniformBlock.hh>
#include <iostream>

UniformBlock::UniformBlock(GLint id, std::string &&name, std::vector<std::shared_ptr<BlockResources>> &&blockResources) :
AProgramResources(id, std::move(name), GL_UNIFORM_BLOCK),
_blockResources(std::move(blockResources)),
_buffer(std::make_shared<UniformBuffer>()),
_block_binding(0)
{
}

UniformBlock::UniformBlock(UniformBlock &&move) :
AProgramResources(std::move(move)),
_buffer(std::move(move._buffer)),
_block_binding(move._block_binding)
{

}

IProgramResources & UniformBlock::operator()()
{
	if (!_update) {
		for (auto &blockResource : _blockResources) {
			(*blockResource)();
		}
		_update = true;
	}
	return (*this);
}

size_t UniformBlock::size() const
{
	return (sizeof(type_t));
}

bool UniformBlock::safe(size_t s) const
{
	return ((size() == s) ? true : false);
}

void UniformBlock::print() const
{
	std::cout << "uniform block " << _name << ";" << std::endl;
}

UniformBlock & UniformBlock::update()
{
	_update = false;
	return (*this);
}
