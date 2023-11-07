﻿// BarrelMesh.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <list>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include <stack>
#include <algorithm>
#include <unordered_map>
#include <unordered_set>

#include "Triangle.h"
#include "Point.h"
#include "Edge.h"
#include "Tetrahedron.h"

std::list<Point> readPointsFromFile(const std::string &inputFileName)
{
    std::ifstream inputFile(inputFileName);
    if (!inputFile.is_open())
        throw std::runtime_error("Input file with that name was not found");
    int n; float x, y, z; char c;
    std::list<Point> points;
    std::string line;
    while (std::getline(inputFile, line))
    {
        if (line[0] == '*')
            continue;
        std::istringstream iss(line);
        if (!(iss >> n >> c >> x >> c >> y >> c >> z))
        {
            std::string error;
            std::ostringstream iss(error);
            iss << "A line in an input file is incorrectly formatted." << std::endl
                << "Problem line: \"" << line << "\"" << std::endl;
            throw std::runtime_error(error);
        }
        points.push_back(Point(n, x, y, z));
    }
    return points;
}

int writeResultsToFile(const std::string &outputFileName, const std::list<Point> points, const std::list<Triangle> triangles)
{
    std::ofstream outputFile(outputFileName);
    if (!outputFile.is_open())
        throw std::runtime_error("Failed to open or create an output file");
    outputFile << "*\tN\tX\tY\tZ" << std::endl
        << "* Nodes:" << std::endl;
    std::string del = ",\t";
    for (auto& point : points)
    {
        outputFile << "\t" << point.index() << del
                           << point.x() << del
                           << point.y() << del
                           << point.z() << std::endl;
    }
    outputFile << "* Elements:" << std::endl;
    int triangleIndex = 1;
    for (auto& triangle : triangles)
    {
        outputFile << "\t" << triangleIndex++ << del
                           << triangle.a().index() << del
                           << triangle.b().index() << del
                           << triangle.c().index() << std::endl;
    }
    return 0;
}

std::list<Triangle> makeTriangulation(const std::list<Point>& p_points)
{
    std::list<Triangle> triangles;
    std::list<Point> points = p_points;
    std::vector<Point> first_points;
    for (int i = 0; i < 3; i++)
    {
        first_points.push_back(points.front());
        points.pop_front();
    }
    triangles.push_back(Triangle(first_points));
    float min;
    Edge minimumEdge;
    /* Алгоритм простой: для каждой новой точки найти ближайшую к ней грань последнего добавленного треугольника.
     * Затем построить треугольник с этой гранью и этой точкой.
     * Алгоритм предполагает, что точки в массиве точек отсортированы.
     */
    for (auto& point : points)
    {
        min = std::numeric_limits<float>().max();
        minimumEdge = Edge();
        for (auto& edge : triangles.back().edges())
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
    return triangles;
}

std::list<Triangle> makeTRSPH3Triangulation(const std::list<Point>& p_points)
{
    std::unordered_set<Triangle> boundary;
    std::stack<Triangle> interior;
    std::list<Triangle> visible;
    std::unordered_map<Triangle, Tetrahedron, std::hash<Triangle>> triangles;
    std::list<Point> points = p_points;
    points.sort();
    std::vector<Point> first_points;
    for (int i = 0; i < 4; i++)
    {
        first_points.push_back(points.front());
        points.pop_front();
    }
    {
        auto t = Tetrahedron(first_points);
        boundary.insert(t.triangles().begin(), t.triangles().end());
        for (auto& triangle : boundary)
            triangles[triangle] = t;
    }
    int i = 4;
    for (auto& point : points)
    {
        for (auto& triangle : boundary)
            if (triangle.isVisible(point))
                visible.push_back(triangle);
            else
                continue;
        while (!visible.empty())
        {
            auto& tr = visible.front();
            Tetrahedron tetra = triangles[tr];
            if (tetra.inCircumsphere(point))
            {
                boundary.erase(tr);
                for (auto& triangle : tetra.triangles())
                {
                    if (boundary.find(triangle) != boundary.end())
                        interior.push(triangle);
                    else
                        if (std::find(visible.begin(), visible.end(), triangle) != visible.end())
                        {
                            boundary.erase(triangle);
                            triangles.erase(triangle);
                        }
                        else
                            visible.push_back(triangle);
                }
                triangles.erase(tr);
            }
            else
                interior.push(tr);
            visible.pop_front();
        }
        while (!interior.empty())
        {
            auto &tr = interior.top();
            if (boundary.find(tr) != boundary.end()
                && tr.isOnPlane(point))
            {
                boundary.erase(tr);
                triangles.erase(tr);
            }
            else
            {
                Tetrahedron t(tr, point);
                for (auto &triangle : t.triangles())
                {
                    auto duplicate = boundary.find(triangle);
                    if (duplicate != boundary.end())
                    {
                        boundary.erase(triangle);
                        triangles.erase(triangle);
                    }
                    else
                    {
                        boundary.insert(triangle);
                        triangles[triangle] = t;
                    }
                }
            }
            interior.pop();
        }
        std::cout << "Points triangulated: " << ++i << "/" << p_points.size() << '\r';
    }
    std::cout << std::endl;
    std::list<Triangle> result;
    for (auto it = triangles.begin(); it != triangles.end(); ++it)
        result.push_back(it->first);
    result.unique();
    return result;
}

int main(int argc, char* argv[])
{
    if (argc != 5)
    {
        std::cout << "Usage: BarrelMesh -i <input file name> -o <output file name>" << std::endl
                  << "-i | --input <input file name> - specify path to the input file" << std::endl
                  << "-o | --output <output file name> - specify path to the output file" << std::endl;
        return 0;
    }
    std::string inputFileName, outputFileName;
    for (int i = 1; i < argc; i++)
    {
        std::string arg = argv[i];
        if (arg == "-i" || arg == "--input")
        {
            if (inputFileName == "")
                inputFileName = argv[++i];
            else
            {
                std::cout << "-i parameter was specified twice" << std::endl;
                return 1;
            }
            continue;
        }
        if (arg == "-o" || arg == "--output")
        {
            if (outputFileName == "")
                outputFileName = argv[++i];
            else
            {
                std::cout << "-o parameter was specified twice" << std::endl;
                return 1;
            }
            continue;
        }
    }
    std::list<Point> points = readPointsFromFile(inputFileName);
    if (points.size() == 0)
    {
        std::cout << "Points weren't read; possible file formatting error?";
        return 1;
    }
    std::list<Triangle> triangles = makeTRSPH3Triangulation(points);
    int result = writeResultsToFile(outputFileName, points, triangles);
    std::cout << "File " << outputFileName << " created successfully";
    return result;
}