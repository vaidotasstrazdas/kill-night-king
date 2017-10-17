#include "Point.h"

namespace Game
{
    namespace Model
    {
        Point::Point()
            : Point(0, 0)
        {
        }

        Point::Point(unsigned int x, unsigned int y)
            : m_x(x)
            , m_y(y)
        {
        }

        bool Point::operator==(const Point& other) const
        {
            return m_x == other.m_x && m_y == other.m_y;
        }

        bool Point::operator!=(const Point& other) const
        {
            return !(*this == other);
        }

        bool Point::operator<(const Point& other) const
        {
            if (m_x < other.m_x)
                return true;

            if (m_x > other.m_x)
                return false;

            if (m_y < other.m_y)
                return true;

            return false;
        }

        std::string Point::ToString() const
        {
            return "(" + std::to_string(m_x) + ", " + std::to_string(m_y) + ")";
        }
    }
}
