#include "GLGraphics.h"
#include <glad/wgl.h>
#include <glad/gl.h>
#include "../Math/Vector4.h"
#include "../Math/Rectangle.h"
bool GLGraphics::Clear()
{
	glClearColor(m_vec.m_x, m_vec.m_y, m_vec.m_z, m_vec.m_w);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
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
	float vertices[] = {
		// positions         // colors
		 0.5f, -0.5f, 0.0f,  1.0f, 0.0f, 0.0f,  // bottom right
		-0.5f, -0.5f, 0.0f,  0.0f, 1.0f, 0.0f,  // bottom left
		 0.0f,  0.5f, 0.0f,  0.0f, 0.0f, 1.0f   // top 

	};
	glGenBuffers(1, &vertexBuffer);
	// The following commands will talk about our 'vertexbuffer' buffer
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	// Give our vertices to OpenGL.
	glBufferData(GL_ARRAY_BUFFER, sizeof(vertices), vertices, GL_STATIC_DRAW);	// 1st attribute buffer : vertices
	glVertexAttribPointer(0, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)0);
	glEnableVertexAttribArray(0);
	glBindBuffer(GL_ARRAY_BUFFER, vertexBuffer);
	glVertexAttribPointer(1, 3, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*)(3 * sizeof(float)));
	glEnableVertexAttribArray(1);
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
