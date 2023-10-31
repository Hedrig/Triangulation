// BarrelMesh.cpp : Этот файл содержит функцию "main". Здесь начинается и заканчивается выполнение программы.
//

#include <iostream>
#include <list>
#include <vector>
#include <limits>
#include <fstream>
#include <sstream>
#include <string>
#include <stdexcept>
#include "Triangle.h"
#include "Point.h"
#include "Edge.h"

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
    for (auto& triangle : triangles)
    {
        outputFile << "\t" << triangle.a().index() << del
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
    std::list<Triangle> triangles = makeTriangulation(points);
    int result = writeResultsToFile(outputFileName, points, triangles);
    
    return result;
}