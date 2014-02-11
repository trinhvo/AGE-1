#pragma once

#include <Systems\System.h>
#include <OpenGL\VertexBuffer.hh>

class LightRenderingSystem : public System
{
public:
	LightRenderingSystem(AScene *scene);
	virtual ~LightRenderingSystem();

	virtual void updateBegin(double time) { }
	virtual void updateEnd(double time) { }
	virtual void mainUpdate(double time);
	virtual void initialize();

private:
	// Filters
	EntityFilter				_lightFilter;
	EntityFilter				_meshRendererFilter;

	void						initFrameBuffer();
	// Frame Buffer
	GLuint						_frameBuffer;
	// Render textures
	GLuint						_depthTexture;
	GLuint						_colorTexture;

	// Quad to draw full screen
	void						initQuad();
		
	OpenGLTools::VertexBuffer	_quad;

	// Light Buffer
	GLuint						_lights;
	std::vector<PointLight>		_contiguousLights;

};

