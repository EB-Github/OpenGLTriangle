#pragma once
#include "../Math/Vector4.h"
#include "../Math/Rectangle.h"
#include <glad/wgl.h>
#include <glad/gl.h>
#include <vector>
class GLGraphics
{
	public:
		bool Clear();
		void setWindow(math::Rectangle rect);
		void setVertexArrays();
		void setVertexBuffers();
		void drawTriangle();
		void cleanUp();
		GLGraphics(math::Vector4 vec);
		GLGraphics();
		~GLGraphics();

		GLuint vertexBuffer;
		GLuint VertexArrayID;
		std::vector<GLfloat> g_vertex_buffer_data; 
	private:
		math::Vector4 m_vec;
};

