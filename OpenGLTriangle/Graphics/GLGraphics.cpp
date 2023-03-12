#include "GLGraphics.h"
#include <glad/wgl.h>
#include <glad/gl.h>
#include "../Math/Vector4.h"
#include "../Math/Rectangle.h"
bool GLGraphics::Clear()
{
	glClearColor(m_vec.m_x, m_vec.m_y, m_vec.m_z, m_vec.m_w);
	glClear(GL_COLOR_BUFFER_BIT);
	return true;
}

void GLGraphics::setWindow(math::Rectangle rect)
{
	glViewport(rect.m_left, rect.m_top, rect.m_width, rect.m_height);
}

void GLGraphics::setVertexArrays()
{
	glGenVertexArrays(1, &VertexArrayID);
	glBindVertexArray(VertexArrayID);
}

void GLGraphics::setVertexBuffers()
{
	glGenBuffers(1, &vertexBuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, g_vertex_buffer_data.size() * sizeof(GLfloat), &g_vertex_buffer_data[0], GL_STATIC_DRAW);
	// 1st attribute buffer : vertices
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(
		0,                  // attribute 0. No particular reason for 0, but must match the layout in the shader.
		3,                  // size
		GL_FLOAT,           // type
		GL_FALSE,           // normalized?
		0,                  // stride
		(void*)0            // array buffer offset
	);
}

void GLGraphics::drawTriangle()
{
	// Draw the triangle !
	glDrawArrays(GL_TRIANGLES, 0, 4); // Starting from vertex 0; 3 vertices total -> 1 triangle
	glDisableVertexAttribArray(0);
}

void GLGraphics::cleanUp()
{
	glDeleteBuffers(1, &vertexBuffer);
	glDeleteVertexArrays(1, &VertexArrayID);
}

GLGraphics::GLGraphics(math::Vector4 vec)
{
	m_vec = vec;
	g_vertex_buffer_data = {
		-0.25f, -0.25f, 0.0f,
		0.25f, -0.25f, 0.0f,
		0.0f,  0.25f, 0.0f
	};
	VertexArrayID = NULL;
	vertexBuffer = NULL;
}
GLGraphics::GLGraphics()
{
}

GLGraphics::~GLGraphics()
{
}
