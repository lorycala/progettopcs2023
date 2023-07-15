#ifndef __EMPTY_H
#define __EMPTY_H

#include <algorithm>
#include <fstream>
#include <vector>
#include <sstream>
#include <string>
#include <cmath>
#include <vector>
#include <iostream>

using namespace std;

namespace delaunay {
class Lati;
class Point {
public:
    double x;
    double y;
    std::vector<delaunay::Lati *> sides = {};

    Point(double x, double y) : x(x), y(y) {}
    Point() : x(0), y(0) {}

    delaunay::Point operator-(const delaunay::Point &other) const;

    Point operator + (const Point &right) const;

    bool operator == (const Point& p2) const;

    bool operator != (const Point& p2) const;

    static bool comparePoints(const Point &a, const Point &b, const Point &center);

    static vector<Point> sortPointsCounterclockwise(const std::vector<Point> &points);

    static double dist(Point &p1, Point &p2);

    static bool isConnect(const delaunay::Point *p1, const delaunay::Point *p2,
                          const std::vector<delaunay::Lati> &sides);
};

class Lati {
public:
    Point *points[2] {};
    Lati() = default;
    Lati(delaunay::Point *p1, delaunay::Point *p2);

    bool intersects(const Lati &other) const;
    bool operator==(Lati l2) const;
};

class Triangle {
public:
    delaunay::Point *points[3]{};
    delaunay::Lati *sides[3]{};
    Triangle(delaunay::Point *p1, delaunay::Point *p2, delaunay::Point *p3);
    Triangle() = default;

    static Triangle LargestTriangle(vector<Point> &vector) ;

    static double calculateTriangleArea(const Triangle &triangle);

    bool isDelaunayValid(delaunay::Point &q);

    static bool dentro(const Triangle &triangle, const delaunay::Point &p);

    bool operator==(Triangle t2) const;

    static bool areTrianglesAdjacent(const Triangle &triangle1, const Triangle &triangle2);

    static int sharedVertices(const Triangle &triangle1, const Triangle &triangle2);

    static vector<Point> commonPoints(const Triangle &triangle1, const Triangle &triangle2);
};

void outputSidesToFile(const string& filename, const vector<Lati>& sides);

void outputPointsToFile(const string& filename, const vector<Point>& points);

void addLatoIfNotExists(vector<Lati>& vec, const Lati& lato);

vector<Point> convexHull(vector<Point> &sortedPoints);
}

#endif // PROG_H

