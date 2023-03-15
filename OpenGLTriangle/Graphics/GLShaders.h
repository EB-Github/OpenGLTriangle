#pragma once
#include <glad/wgl.h>
#include <glad/gl.h>
class GLShaders
{
	public:
		static GLuint LoadShaders(const char * vertex_file_path, const char * fragment_file_path);
};

