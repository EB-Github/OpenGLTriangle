#pragma once
#include "../Math/Vector4.h"

class GLGraphics
{
	public:
		bool Clear();
		bool setWindow();
		GLGraphics(math::Vector4 vec);
		~GLGraphics();
	private:
		math::Vector4 m_vec;
};

