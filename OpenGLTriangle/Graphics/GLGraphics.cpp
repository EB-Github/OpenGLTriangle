#include "GLGraphics.h"
#include <glad/wgl.h>
#include <glad/gl.h>
#include "../Math/Vector4.h"
bool GLGraphics::Clear()
{
	glClearColor(m_vec.m_x, m_vec.m_y, m_vec.m_z, m_vec.m_w);
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}

bool GLGraphics::setWindow()
{
	return false;
}

GLGraphics::GLGraphics(math::Vector4 vec)
{
	m_vec = vec;
}

GLGraphics::~GLGraphics()
{
}
