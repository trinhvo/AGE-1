#ifndef VERTEX_HH_
# define VERTEX_HH_

# include <iostream>
# include <stdint.h>
# include <array>

class VertexData
{
private:
	uint32_t _id;
	uint32_t _nbrByte;
	uint32_t _nbrComponent;
	uint32_t _nbrElement;
	uint32_t _sizeBuffer;
	void *_buffer;
public:
	VertexData(uint32_t nbrByte, uint32_t nbrComponent, uint32_t nbrBuffer, void *buffer);
	VertexData(VertexData const &copy);
	~VertexData();
	VertexData &operator=(VertexData const &vertexdata);
	uint32_t getNbrComponent() const;
	uint32_t getNbrElement() const;
	uint32_t getNbrByte() const;
	uint32_t getSizeBuffer() const;
	void const * const getBuffer() const;
	bool operator==(VertexData const &vertexData) const;
	bool operator!=(VertexData const &vertexData) const;
	void clearBuffer();
};

template <uint32_t NBR_ATTRIBUTE>
class Vertex
{
public:
	Vertex(std::array<VertexData, NBR_ATTRIBUTE> attributes, VertexData const * const indices = NULL);
	~Vertex();
	Vertex(Vertex const &copy);
	Vertex &operator=(Vertex const &vertex);
	std::array<VertexData, NBR_ATTRIBUTE> const &getAttributes() const;
	VertexData const * const getIndices() const;
	bool operator==(Vertex<NBR_ATTRIBUTE> const &vertex) const;
	bool operator!=(Vertex<NBR_ATTRIBUTE> const &vertex) const;
	uint32_t getSizeAttributes() const;
	uint32_t getSizeIndices() const;
private:
	std::array<VertexData, NBR_ATTRIBUTE> _attributes;
	VertexData *_indices;
	uint32_t _sizeAttributes;
	uint32_t _sizeIndices;
};

template <uint32_t NBR_ATTRIBUTE>
Vertex<NBR_ATTRIBUTE>::Vertex(std::array<VertexData, NBR_ATTRIBUTE> attributes, VertexData const * const indices)
: _attributes(attributes),
	_sizeIndices(0)
{
	for (uint32_t index = 0; index < NBR_ATTRIBUTE; ++index)
		_sizeAttributes += _attribute[index].getSizeBuffer();
	if (indices)
	{
		_indices = new VertexData(indices);
		_sizeIndices = _indices->getSizeBuffer();
	}
}

template <uint32_t NBR_ATTRIBUTE>
Vertex<NBR_ATTRIBUTE>::Vertex(Vertex<NBR_ATTRIBUTE> const &copy)
: _attributes(copy._attributes),
_size(copy._size)
{
	if (copy.indices)
	{
		_indices = new VertexData(copy.indices);
	}
}

template <uint32_t NBR_ATTRIBUTE>
Vertex<NBR_ATTRIBUTE>::~Vertex()
{
	if (_indices)
		delete _indices;
}

template <uint32_t NBR_ATTRIBUTE>
Vertex<NBR_ATTRIBUTE> &Vertex<NBR_ATTRIBUTE>::operator=(Vertex<NBR_ATTRIBUTE> const &vertex)
{
	_attributes = vertex._attributes;
	_indices = new VertexData(vertex.indices);
	return (*this);
}

template <uint32_t NBR_ATTRIBUTE>
std::array<VertexData, NBR_ATTRIBUTE> const &Vertex<NBR_ATTRIBUTE>::getAttributes() const
{
	return (_attributes);
}

template <uint32_t NBR_ATTRIBUTE>
VertexData const * const Vertex<NBR_ATTRIBUTE>::getIndices() const
{
	return (_indices);
}

template <uint32_t NBR_ATTRIBUTE>
bool Vertex<NBR_ATTRIBUTE>::operator==(Vertex<NBR_ATTRIBUTE> const &vertex) const
{
	if (vertex._indices && _indices)
	{
		if (vertex._indices != _indices)
			return (false);
	}
	for (uint32_t index = 0; index < NBR_ATTRIBUTE; ++index)
		if (_attributes[index] == vertex._attributes[index])
			return (false);
	return (true);
}

template <uint32_t NBR_ATTRIBUTE>
bool Vertex<NBR_ATTRIBUTE>::operator!=(Vertex<NBR_ATTRIBUTE> const &vertexdata) const
{
	return (!(*this == vertexdata));
}

template <uint32_t NBR_ATTRIBUTE>
uint32_t Vertex<NBR_ATTRIBUTE>::getSizeAttributes() const
{
	return (_sizeAttributes);
}

template <uint32_t NBR_ATTRIBUTE>
uint32_t Vertex<NBR_ATTRIBUTE>::getSizeIndices() const
{
	return (_sizeIndices);
}

#endif /* !VERTEX_HH_ */