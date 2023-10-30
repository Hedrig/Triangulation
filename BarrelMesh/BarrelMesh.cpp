// BarrelMesh.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <list>
#include <vector>
#include <limits>
#include "Triangle.h"
#include "Point.h"
#include "Edge.h"

int main()
{
    std::cout << "Hello World!\n";
}

std::list<Triangle> makeTriangulation(const std::list<Point> &p_points)
{
    std::list<Triangle> triangles;
    auto points = p_points;
    triangles.push_back(Triangle(points.begin(), points.end()));
    for (int i = 0; i < 3; i++)
        points.pop_front();
    float min;
    Edge minimumEdge;
    for (auto &point : points)
    {
        min = std::numeric_limits<float>().max();
        minimumEdge = Edge();
        for (auto &triangle : triangles)
            for (auto &edge : triangle.edges())
            {
                float distance = edge.distance(point);
                if (distance < min)
                {
                    minimumEdge = edge;
                    min = distance;
                }
            }
        triangles.push_back(Triangle(point, minimumEdge.a(), minimumEdge.b()));
    }
}