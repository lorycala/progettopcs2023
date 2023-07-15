#include "empty_class.hpp"
#include <vector>
#include <sstream>

#include <algorithm>
#include <cmath>

using namespace std;
using namespace delaunay;

namespace delaunay {
bool Point::comparePoints(const Point &a, const Point &b, const Point &center) {
    double angleA = atan2(a.y - center.y, a.x - center.x);
    double angleB = atan2(b.y - center.y, b.x - center.x);
    return angleA < angleB;
}

// Qual è lo scopo?
vector<Point> Point::sortPointsCounterclockwise(const vector<Point> &points) {
    vector<Point> sortedPoints = points;

    // Costruisco il punto medio
    Point center;
    for (const Point &point: points) {
        center.x += point.x;
        center.y += point.y;
    }
    center.x /= (double) points.size();
    center.y /= (double) points.size();

    // Ordina i punti in base all'angolo rispetto al punto medio
    sort(sortedPoints.begin(), sortedPoints.end(), [&](const Point &a, const
                                                       Point &b) {
        return comparePoints(a, b, center);
    });

    return sortedPoints;
}

Point Point::operator-(const Point &other) const {
    return {x - other.x, y - other.y};
}

Point Point::operator+(const Point &right) const {
    return {x + right.x, y + right.y};
}

bool Point::operator==(const Point &p2) const {
    return (x == p2.x && y == p2.y);
}

bool Point::operator!=(const Point &p2) const {
    return (x != p2.x || y != p2.y);
}

double Point::dist(Point &p1, Point &p2) {
    double dx = p1.x - p2.x;
    double dy = p1.y - p2.y;
    return std::sqrt(dx * dx + dy * dy);
}

vector<Point> convexHull(vector<Point> &sortedPoints) {
    int n = (int) sortedPoints.size();

    if (n < 3) {
        cerr << "At least 3 points required\n";
        return {};
    }

    // Build the ConvexHull
    vector<Point> hull;
    hull.push_back(sortedPoints[0]);
    hull.push_back(sortedPoints[1]);

    for (int i = 2; i < n; ++i) {
        while (hull.size() >= 2) {
            Point b = hull.back();
            Point a = hull[hull.size() - 2];
            Point c = sortedPoints[i];
            double cross = (c.x - a.x) * (b.y - a.y) - (c.y - a.y) * (b.x -
                                                                      a.x);
            if (cross > 0)
                break;
            hull.pop_back();
        }
        hull.push_back(sortedPoints[i]);
    }

    return hull;
}

bool areInterleaving(const Triangle& triangle1, const Triangle& triangle2, const
                     vector<Point> v3) { //dove convexHull è un sortedPoints
    bool isTriangle1Next = false;
    bool isTriangle2Next = false;
    int iter = 0;

    for (const Point& point : v3) {
        // punti iniziali
        if (!isTriangle1Next && !isTriangle2Next && point.x ==
                                                        triangle1.points[0]->x && point.y == triangle1.points[0]->y) {
            isTriangle1Next = true; // se ho trovato un punto di triangle 1,    aggiorno isTriangle1next a true
            isTriangle2Next = false;
            iter++;
            break;
        } else if (!isTriangle1Next && !isTriangle2Next && point.x ==
                                                               triangle2.points[0]->x && point.y == triangle2.points[0]->y) {
            isTriangle1Next = false;
            isTriangle2Next = true; // se ho trovato un punto di triangle 2, aggiorno isTriangle2next a true
            iter++;
            break;
        } else continue;


        // già ne ho trovato uno

        if (iter >= 1) {
            for (int k = 0; k < 3; k++) {
                // se ho trovato un punto del primo triangolo, ne cerco uno delsecondo
                if (isTriangle1Next && (point.x == triangle2.points[k]->x && point.y == triangle2.points[k]->y)) {
                    isTriangle1Next = false;
                    isTriangle2Next = true;
                    iter++;
                    break;

                    // se ho trovato un punto del secondo triangolo, ne cerco uno del primo
                } else if (isTriangle2Next && (point.x == triangle1.points[k]->x && point.y == triangle1.points[k]->y)) {
                    isTriangle1Next = true;
                    isTriangle2Next = false;
                    iter++;
                    break;
                } else continue; // Il punto in v3 non corrisponde a nessuno dei punti dei triangoli o viola la sequenza
            }
        }
    }
    return iter == 6;
}

vector<Point> LargestTriangle(vector<Point> P) {
    if (P.size() == 3) {
        return P;
    } else {
        int max_area = 0;
        Point a = P[0];
        vector<Point> Ta = {a, P[1], P[2]};
        for (unsigned i = 1; i < P.size(); i++) {
            for (unsigned j = i+1; j < P.size(); j++) {
                double temp_area = Triangle::calculateTriangleArea(Triangle(&a, &P[i], &P[j]));
                if (temp_area > max_area) {
                    max_area = temp_area;
                    Ta = {a, P[i], P[j]};
                }

            }
        }

        int m_index = -1;
        double max_interval = 0;
        for (unsigned i = 0; i < Ta.size(); i++) {
            int next_i = (i+1)%Ta.size();
            int interval = 0;
            for (unsigned j = 0; j < P.size(); j++) {
                if (P[j] == Ta[i]) {
                    while (P[(j+1)%P.size()] != Ta[next_i]) {
                        interval++;
                        j = (j+1)%P.size();
                    }
                    break;
                }
            }
            if (interval > max_interval) {
                max_interval = interval;
                m_index = (next_i + interval/2 + 1)%P.size();
            }
        }
        Point m = P[m_index];

        vector<Point> Tm = {m, P[1], P[2]};
        max_area = Triangle::calculateTriangleArea(Triangle(&m, &P[1], &P[2]));
        for (unsigned i = 1; i < P.size(); i++) {
            for (unsigned j = i+1; j < P.size(); j++) {
                double temp_area = Triangle::calculateTriangleArea(Triangle(&m, &P[i], &P[j]));
                if (temp_area > max_area) {
                    max_area = temp_area;
                    Tm = {m, P[i], P[j]};
                }
            }
        }

        //        vector<Point> P0;
        //        vector<Point> P00;
        //        if (areInterleaving(Triangle(&Ta[0], &Ta[1], &Ta[2]), Triangle(&Tm[0], &Tm[1], &Tm[2]), P )) {
        //            vector<Point> res0 = LargestTriangle(P0);
        //            vector<Point> res00 = LargestTriangle(P00);
        //            if (Triangle::calculateTriangleArea(Triangle(&res0[0], &res0[1], &res0[2])))  {
        //                return res0;
        //            } else {
        //                return res00;
        //            }
        //        } else if (/* P0 can include the largest-area triangle */) {
        //            return LargestTriangle(P0);
        //        } else {
        //            return LargestTriangle(P00);
        //        }
    }
}

Lati::Lati(delaunay::Point *p1, delaunay::Point *p2) // costruttore
{
    points[0] = p1;  //nel vettore adesso abbiamo nella posizione 0 il punatorep1 e nella posizione 1 il puntatore p2
    points[1] = p2;
}

bool Lati::intersects(const Lati &other) const {
    if (*this == other) {
        // Lati coincidenti
        return false;
    }

    double x1 = points[0]->x;
    double y1 = points[0]->y;
    double x2 = points[1]->x;
    double y2 = points[1]->y;

    double x3 = other.points[0]->x;
    double y3 = other.points[0]->y;
    double x4 = other.points[1]->x;
    double y4 = other.points[1]->y;

    double d = (x1 - x2) * (y3 - y4) - (y1 - y2) * (x3 - x4);

    if (d == 0.0) {
        return false; // I lati sono paralleli
    }

    double ua = ((x4 - x3) * (y1 - y3) - (y4 - y3) * (x1 - x3)) / d;
    double ub = ((x2 - x1) * (y1 - y3) - (y2 - y1) * (x1 - x3)) / d;

    return ua >= 0.0 && ua <= 1.0 && ub >= 0.0 && ub <= 1.0;
}

bool Lati::operator==(Lati l2) const {
    Point startA = *this->points[0];
    Point startB = *l2.points[0];
    Point endA = *this->points[1];
    Point endB = *l2.points[1];

    return (startA == startB && endA == endB) || (startA == endB && startB == endA);
}

Triangle::Triangle(delaunay::Point *p1, delaunay::Point *p2, delaunay::Point *p3) {
    points[0] = p1;
    points[1] = p2;
    points[2] = p3;
}

double Triangle::calculateTriangleArea(const Triangle &triangle) {
    return abs((triangle.points[0]->x * (triangle.points[1]->y - triangle.points[2]->y) + triangle.points[1]->x * (triangle.points[2]->y -
                                         triangle.points[0]->y) + triangle.points[2]->x * (triangle.points[0]->y - triangle.points[1]->y)) / 2.0);
}

bool Triangle::isDelaunayValid(Point &q)
{
    Triangle t = *this;
    delaunay::Point a = *t.points[0];
    delaunay::Point b = *t.points[1];
    delaunay::Point c = *t.points[2];
    double ax = a.x - q.x;
    double ay = a.y - q.y;
    double bx = b.x - q.x;
    double by = b.y - q.y;
    double cx = c.x - q.x;
    double cy = c.y - q.y;

    double det = ax * (by * (cx * cx + cy * cy) - cy * (bx * bx + by * by)) -
                 bx * (ay * (cx * cx + cy * cy) - cy * (ax * ax + ay * ay)) +
                 cx * (ay * (bx * bx + by * by) - by * (ax * ax + ay * ay));
    return det > 0.0;
}

bool Triangle::dentro(const Triangle &triangle, const Point &p) {
    delaunay::Point AB = *triangle.points[1] - *triangle.points[0];
    delaunay::Point BC = *triangle.points[2] - *triangle.points[1];
    delaunay::Point CA = *triangle.points[0] - *triangle.points[2];
    delaunay::Point AP = p - *triangle.points[0];
    delaunay::Point BP = p - *triangle.points[1];
    delaunay::Point CP = p - *triangle.points[2];

    double crossProductAB = AB.x * AP.y - AB.y * AP.x;
    double crossProductBC = BC.x * BP.y - BC.y * BP.x;
    double crossProductCA = CA.x * CP.y - CA.y * CP.x;

    return (crossProductAB >= 0 && crossProductBC >= 0 && crossProductCA >= 0)
           ||
           (crossProductAB < 0 && crossProductBC < 0 && crossProductCA < 0);
}

bool Triangle::operator==(const Triangle t2) const {
    return sharedVertices(*this, t2) == 3;
}

bool Triangle::areTrianglesAdjacent(const Triangle &triangle1, const Triangle &triangle2) {
    return sharedVertices(triangle1, triangle2) == 2;
}

int Triangle::sharedVertices(const Triangle &triangle1, const Triangle &triangle2) {
    int sharedVertices = 0;
    bool second[3]{true, true, true};

    for (auto point : triangle1.points) {
        for (int j = 0; j < 3; j++) {
            if (*point == *triangle2.points[j] && second[j]) {
                sharedVertices ++;
                second[j] = false;
                break;
            }
        }
    }

    return sharedVertices;
}

vector<Point> Triangle::commonPoints(const Triangle &triangle1, const Triangle &triangle2) {
    vector<Point> vec;

    bool second[3]{true, true, true};

    for (auto point : triangle1.points) {
        for (int j = 0; j < 3; j++) {
            if (*point == *triangle2.points[j] && second[j]) {
                vec.push_back(*point);
                second[j] = false;
                break;
            }
        }
    }

    return vec;
}

bool Point::isConnect(const delaunay::Point *p1, const delaunay::Point *p2,
                      const vector<delaunay::Lati> &sides) {
    for (const auto &side: sides) {
        if ((*side.points[0] == *p1 && *side.points[1] == *p2) ||
            (*side.points[0] == *p2 && *side.points[1] == *p1)) {
            return true;
        }
    }
    return false;
}

void outputSidesToFile(const string& filename, const vector<Lati>& sides) {
    ofstream outputFile;
    outputFile.open(filename);
    for (auto & side : sides) {
        Point start = *side.points[0];
        Point end = *side.points[1];
        outputFile << std::scientific << start.x << ";" << start.y << ";" <<
            end.x << ";" << end.y << "\n";
    }
    outputFile.close();
}

void addLatoIfNotExists(vector<Lati>& sides, const Lati& side) {
    bool found = false;

    for (auto & lato : sides) {
        if (lato == side) {
            found = true;
        }
    }

    if (!found) {
        sides.push_back(side);
    }
}

void outputPointsToFile(const string &filename, const vector<Point> &points) {
    ofstream outputFile;
    outputFile.open(filename);
    for (auto & point : points) {
        outputFile << std::scientific << point.x << ";" << point.y << "\n";
    }
    outputFile.close();
}
}

