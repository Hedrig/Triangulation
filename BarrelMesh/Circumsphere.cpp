#include "Circumsphere.h"

Circumsphere::Circumsphere(const std::vector<Point> points)
    :pts{ points }
{
    std::vector<Vector> vrs;
    for (auto& point : points)
        vrs.push_back(Vector(point));
    a = det3({ vrs[1] - vrs[0], vrs[2] - vrs[0], vrs[3] - vrs[0] });
    std::vector<float> ls = { vrs[0].length(), vrs[1].length(), vrs[2].length(), vrs[3].length() };
    std::vector<Vector> vrsDx = { 
        { ls[0], vrs[0].y(), vrs[0].z()},
        { ls[1], vrs[1].y(), vrs[1].z()},
        { ls[2], vrs[2].y(), vrs[2].z()},
        { ls[3], vrs[3].y(), vrs[3].z()}
    };
    dx = det3({ vrsDx[1] - vrsDx[0], vrsDx[2] - vrsDx[0], vrsDx[3] - vrsDx[0] });
    std::vector<Vector> vrsDy = {
        { ls[0], vrs[0].x(), vrs[0].z()},
        { ls[1], vrs[1].x(), vrs[1].z()},
        { ls[2], vrs[2].x(), vrs[2].z()},
        { ls[3], vrs[3].x(), vrs[3].z()}
    };
    dy = det3({ vrsDy[1] - vrsDy[0], vrsDy[2] - vrsDy[0], vrsDy[3] - vrsDy[0] });
    std::vector<Vector> vrsDz = {
        { ls[0], vrs[0].x(), vrs[0].y()},
        { ls[1], vrs[1].x(), vrs[1].y()},
        { ls[2], vrs[2].x(), vrs[2].y()},
        { ls[3], vrs[3].x(), vrs[3].y()}
    };
    dz = det3({ vrsDz[1] - vrsDz[0], vrsDz[2] - vrsDz[0], vrsDz[3] - vrsDz[0] });

    c = ls[3] * det3(vrs) - vrs[3].x() * det3(vrsDx) + vrs[3].y() * det3(vrsDy) - vrs[3].z() * det3(vrsDz);
    center = Point(dx / (a + a), dy / (a + a), dz / (a + a));
    r = sqrt(dx * dx + dy * dy + dz * dz - 4 * a * c) / abs(a + a);
}

bool Circumsphere::hasInside(const Point& point) const
{
    // Точка находится внутри сферы, если детерминант матрицы координат определяющих точек сферы
    // и длин их векторов, сопряжённой с координатами этой точки, больше нуля
    Vector v = point;
    return a * v.length() - dx * point.x() - dy * point.y() - dz * point.z() + c > 0;
}

float Circumsphere::det3(std::vector<Vector> m)
{
    return m[0].x() * (m[1].y() * m[2].z() - m[1].z() * m[2].y())
         - m[0].y() * (m[1].x() * m[2].z() - m[1].z() * m[2].x())
         + m[0].z() * (m[1].x() * m[2].y() - m[1].y() * m[2].x());
}

