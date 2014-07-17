#pragma once

#include <Utils/OpenGL.hh>
#include <OpenGL/Key.hh>
#include <OpenGL/Buffer.hh>
#include <OpenGL/VertexArray.hh>
#include <OpenGL/Pool.hh>
#include <Utils/Dependency.hpp>
#include <map>
#include <unordered_map>
#include <vector>

namespace gl
{
	class Vertices;

	//!\file GeometryManager.hh
	//!\author Dorian Pinaud
	//!\version v1.0
	//!\class GeometryManager
	//!\brief Handle the geometry of the render
	class GeometryManager : public Dependency<GeometryManager>
	{
	public:
		template <typename TYPE, typename POOL>
		struct Attach
		{
			TYPE const *data;
			POOL *pool;
			Key<Pool::Element<TYPE>> element;
		};
	public:
		// constructor
		GeometryManager();
		~GeometryManager();

		// handle pools
		Key<VertexPool> addVertexPool();
		Key<VertexPool> addVertexPool(uint8_t nbrAttributes, GLenum *typeComponent, uint8_t *sizeTypeComponent, uint8_t *nbrComponent);
		Key<VertexPool> getVertexPool(size_t index) const;
		size_t nbrVertexPool() const;
		GeometryManager &rmVertexPool(Key<VertexPool> &key);
		Key<IndexPool> addIndexPool();
		Key<IndexPool> getIndexPool(size_t index) const;
		size_t nbrIndexPool() const;
		GeometryManager &rmIndexPool(Key<IndexPool> &key);

		//handle Vertices and Indices
		Key<Vertices> addVertices(size_t nbrVertices, uint8_t nbrBuffers, size_t *sizeBuffers, void **buffers);
		Key<Indices> addIndices(size_t nbrIndices, uint32_t *buffers);
		GeometryManager &rmVertices(Key<Vertices> &key);
		GeometryManager &rmIndices(Key<Indices> &key);
		Key<Vertices> getVertices(size_t index) const;
		Key<Indices> getIndices(size_t index) const;
		size_t getNbrVertices() const;
		size_t getNbrIndices() const;

		// attach vertices to pools
		GeometryManager &attachVerticesToVertexPool(Key<Vertices> const &vertices, Key<VertexPool> const &pool);
		GeometryManager &dettachVerticesToVertexPool(Key<Vertices> const &vertices);
		GeometryManager &attachIndicesToIndexPool(Key<Indices> const &vertices, Key<IndexPool> const &pool);
		GeometryManager &dettachIndicesToIndexPool(Key<Indices> const &vertices);
		GeometryManager &attachIndexPoolToVertexPool(Key<VertexPool> const &vertexpool, Key<IndexPool> const &indicespool);
		GeometryManager &dettachIndexPoolToVertexPool(Key<VertexPool> const &vertexpool, Key<IndexPool> const &indexpool);

		// draw
		GeometryManager &draw(GLenum mode, Key<Indices> const &keyindices, Key<Vertices> const &keyVertice);
		GeometryManager &draw(GLenum mode, Key<Vertices> const &keyvertices);
	private:
		// data represent pools
		std::unordered_map<Key<IndexPool>, IndexPool, Key<IndexPool>::hash_fn> _indexPool;
		std::unordered_map<Key<VertexPool>, VertexPool, Key<VertexPool>::hash_fn> _vertexPool;
		std::unordered_map<Key<Indices>, Indices, Key<Indices>::hash_fn>	_indices;
		std::unordered_map<Key<Vertices>, Vertices, Key<Vertices>::hash_fn> _vertices;
		std::unordered_map<Key<Vertices>, Attach<Vertices, VertexPool>, Key<Vertices>::hash_fn> _vertexAttach;
		std::unordered_map<Key<Indices>, Attach<Indices, IndexPool>, Key<Indices>::hash_fn> _indexAttach;
	
		std::pair<Key<IndexPool>, IndexPool *> _optimizerIndexPoolSearch;
		std::pair<Key<VertexPool>, VertexPool *> _optimizerVertexPoolSearch;
		std::pair<Key<Vertices>, Vertices *> _optimizerVerticesSearch;
		std::pair<Key<Indices>, Indices *> _optimizerIndicesSearch;
		std::pair<Key<Vertices>, Attach<Vertices, VertexPool> *> _optimizerVertexAttachSearch;
		std::pair<Key<Indices>, Attach<Indices, IndexPool> *> _optimizerIndexAttachSearch;

		// tool use in intern
		VertexPool *getVertexPool(Key<VertexPool> const &key, std::string const &in);
		IndexPool *getIndexPool(Key<IndexPool> const &key, std::string const &in);
		Indices *getIndices(Key<Indices> const &key, std::string const &in);
		Vertices *getVertices(Key<Vertices> const &key, std::string const &in);
		Attach<Vertices, VertexPool> *getVertexAttach(Key<Vertices> const &key, std::string const &in);
		Attach<Indices, IndexPool> *getIndexAttach(Key<Indices> const &key, std::string const &in);
	};
}