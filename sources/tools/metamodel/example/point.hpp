#pragma once

#include <cstdint>
#include <ostream>

namespace geometry {

class Point {
  public:
    // due to derive(Default)
    Point();
    Point(std::int32_t x, std::int32_t y);

    // due to derive(Copy)
    Point(const Point& other);
    Point& operator=(const Point& other);

    // due to derive(Print)
    void print(std::ostream& os) const;

  public:
    std::int32_t getX() const;
    std::int32_t getY() const;

    void setX(std::int32_t x);
    void setY(std::int32_t y);

  private:
    std::int32_t m_x;
    std::int32_t m_y;
};

} // namespace geometry
