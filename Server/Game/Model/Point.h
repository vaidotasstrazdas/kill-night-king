#pragma once
#include <string>

namespace Game
{
    namespace Model
    {
        struct Point
        {
            Point();
            Point(unsigned int x, unsigned int y);

            unsigned int m_x;
            unsigned int m_y;

            bool operator==(const Point& other) const;
            bool operator!=(const Point& other) const;
            bool operator<(const Point& other) const;

            std::string ToString() const;
        };
    }
}
