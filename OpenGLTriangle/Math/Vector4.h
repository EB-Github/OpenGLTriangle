#pragma once
namespace math {
	class Vector4
	{
		public:
			Vector4();
			Vector4(float x, float y, float z, float w);
			~Vector4();
			float m_x = 0, m_y = 0, m_z = 0, m_w = 0;
		};
};

