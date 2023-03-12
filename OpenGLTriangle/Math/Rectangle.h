#pragma once
namespace math {
	class Rectangle
	{
		public:
			Rectangle(int width, int height, int left, int top);
			~Rectangle();
			int m_width, m_height, m_left, m_top;
	};
}

