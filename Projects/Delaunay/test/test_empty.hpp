#define __TEST_EMPTY_H
#include <gtest/gtest.h>
#include "empty_class.hpp"

using namespace testing;
using namespace delaunay;

// Point
TEST(TestDelaunay, TestSortPointsCounterClockWise) {
    // Arrange
    Point p1(1.0,1.0);
    Point p2(1.0,2.0);
    Point p3(5.0,7.0);
    Point p4(8.0,10.0);
    vector<Point> points {p1, p2, p3, p4};
    vector<Point> expected {p1, p2, p4, p3};

    // Act
    vector<Point> sorted = Point::sortPointsCounterclockwise(points);

    // Assert
    for (int i = 0; i < sorted.size(); i++) {
        EXPECT_EQ(sorted[i], expected[i]);
    }
}

TEST(TestDelaunay, TestDistanzaPunti) {
    // Arrange
    Point p1(0.0,0.0);
    Point p2(0.0,1.0);

    // Act
    double distanza = Point::dist(p1, p2);

    // Assert
    EXPECT_EQ(distanza, 1);
}

TEST(TestDelaunay, TestPuntiNonConnessi) {
    // Arrange
    Point p1(0.0,0.0);
    Point p2(0.0,1.0);
    vector<delaunay::Lati> vec = {};

    // Act
    bool connessi = Point::isConnect(&p1, &p2, vec);

    // Assert
    EXPECT_FALSE(connessi);
}

TEST(TestDelaunay, TestPuntiConnessi) {
    // Arrange
    Point p1(0.0,0.0);
    Point p2(0.0,1.0);
    vector<delaunay::Lati> vec = {};
    Lati lato = Lati(&p1, &p2);
    vec.push_back(lato);

    // Act
    bool connessi = Point::isConnect(&p1, &p2, vec);

    // Assert
    EXPECT_TRUE(connessi);
}

// Triangle
TEST(TestDelaunay, TestTriangoliAdiacenti) {
    // Arrange
    Point p1_1(0.0,0.0);
    Point p1_2(0.0,1.0);
    Point p1_3(0.0,5.0);
    Point p2_1(0.0,0.0);
    Point p2_2(0.0,1.0);
    Point p2_3(0.0,1.0);

    Triangle t1 = Triangle(&p1_1, &p1_2, &p1_3);
    Triangle t2 = Triangle(&p2_1, &p2_2, &p2_3);

    // Act
    bool adiacenti = delaunay::Triangle::areTrianglesAdjacent(t1, t2);

    // Assert
    EXPECT_TRUE(adiacenti);
}

TEST(TestDelaunay, TestTriangoliNonAdiacenti) {
    // Arrange
    Point p1_1(0.0,4.0);
    Point p1_2(0.0,3.0);
    Point p1_3(0.0,8.0);
    Point p2_1(0.0,0.0);
    Point p2_2(0.0,1.0);
    Point p2_3(0.0,1.0);

    Triangle t1 = Triangle(&p1_1, &p1_2, &p1_3);
    Triangle t2 = Triangle(&p2_1, &p2_2, &p2_3);

    // Act
    bool adiacenti = delaunay::Triangle::areTrianglesAdjacent(t1, t2);

    // Assert
    EXPECT_FALSE(adiacenti);
}

TEST(TestDelaunay, TestTriangoliCoincidenti) {
    // Arrange
    Point p1_1(0.0,1.0);
    Point p1_2(0.0,3.0);
    Point p1_3(0.0,5.0);
    Point p2_1(0.0,3.0);
    Point p2_2(0.0,1.0);
    Point p2_3(0.0,5.0);

    Triangle t1 = Triangle(&p1_1, &p1_2, &p1_3);
    Triangle t2 = Triangle(&p2_1, &p2_2, &p2_3);

    // Act
    bool adiacenti = delaunay::Triangle::areTrianglesAdjacent(t1, t2);

    // Assert
    EXPECT_FALSE(adiacenti);
}

TEST(TestDelaunay, TestAllSharedVertices) {
    // Arrange
    Point p1_1(0.0,1.0);
    Point p1_2(0.0,3.0);
    Point p1_3(0.0,5.0);
    Point p2_1(0.0,3.0);
    Point p2_2(0.0,1.0);
    Point p2_3(0.0,5.0);

    Triangle t1 = Triangle(&p1_1, &p1_2, &p1_3);
    Triangle t2 = Triangle(&p2_1, &p2_2, &p2_3);

    // Act
    int shared = delaunay::Triangle::sharedVertices(t1, t2);

    // Assert
    EXPECT_EQ(3, shared);
}

TEST(TestDelaunay, TestNoSharedVertices) {
    // Arrange
    Point p1_1(0.0,1.0);
    Point p1_2(0.0,3.0);
    Point p1_3(0.0,5.0);
    Point p2_1(0.0,4.0);
    Point p2_2(0.0,6.0);
    Point p2_3(0.0,8.0);

    Triangle t1 = Triangle(&p1_1, &p1_2, &p1_3);
    Triangle t2 = Triangle(&p2_1, &p2_2, &p2_3);

    // Act
    int shared = delaunay::Triangle::sharedVertices(t1, t2);

    // Assert
    EXPECT_EQ(0, shared);
}

TEST(TestDelaunay, TestOneSharedVertices) {
    // Arrange
    Point p1_1(0.0,1.0);
    Point p1_2(0.0,3.0);
    Point p1_3(0.0,5.0);
    Point p2_1(0.0,1.0);
    Point p2_2(0.0,6.0);
    Point p2_3(0.0,8.0);

    Triangle t1 = Triangle(&p1_1, &p1_2, &p1_3);
    Triangle t2 = Triangle(&p2_1, &p2_2, &p2_3);

    // Act
    int shared = delaunay::Triangle::sharedVertices(t1, t2);

    // Assert
    EXPECT_EQ(1, shared);
}

TEST(TestDelaunay, TrianglesNotEqual) {
    Point p1_1(0.0,1.0);
    Point p1_2(0.0,3.0);
    Point p1_3(0.0,5.0);
    Point p2_1(0.0,1.0);
    Point p2_2(0.0,6.0);
    Point p2_3(0.0,8.0);

    Triangle t1 = Triangle(&p1_1, &p1_2, &p1_3);
    Triangle t2 = Triangle(&p2_1, &p2_2, &p2_3);

    // Act
    bool equals = t1 == t2;

    // Assert
    EXPECT_FALSE(equals);
}

TEST(TestDelaunay, TrianglesEqual) {
    Point p1_1(0.0,1.0);
    Point p1_2(0.0,3.0);
    Point p1_3(0.0,5.0);
    Point p2_1(0.0,5.0);
    Point p2_2(0.0,1.0);
    Point p2_3(0.0,3.0);

    Triangle t1 = Triangle(&p1_1, &p1_2, &p1_3);
    Triangle t2 = Triangle(&p2_1, &p2_2, &p2_3);

    // Act
    bool equals = t1 == t2;

    // Assert
    EXPECT_TRUE(equals);
}

TEST(TestDelaunay, PointDentroTriangle) {
    // Arrange
    Point p1(0.0,0.0);
    Point p2(10.0,0.0);
    Point p3(0.0,5.0);

    Triangle t = Triangle(&p1, &p2, &p3);

    Point toVerify(3.0, 1.0);

    // Act
    bool inside = Triangle::dentro(t, toVerify);

    // Assert
    EXPECT_TRUE(inside);
}

TEST(TestDelaunay, PointFuoriTriangle) {
    // Arrange
    Point p1(0.0,0.0);
    Point p2(10.0,0.0);
    Point p3(0.0,5.0);

    Triangle t = Triangle(&p1, &p2, &p3);

    Point toVerify(200.0, 1.0);

    // Act
    bool inside = Triangle::dentro(t, toVerify);

    // Assert
    EXPECT_FALSE(inside);
}

TEST(TestDelaunay, PointSulLatoTriangle) {
    // Arrange
    Point p1(0.0,0.0);
    Point p2(10.0,0.0);
    Point p3(0.0,5.0);

    Triangle t = Triangle(&p1, &p2, &p3);

    Point toVerify(5.0, 0.0);

    // Act
    bool inside = Triangle::dentro(t, toVerify);

    // Assert
    EXPECT_TRUE(inside);
}

// Lati
TEST(TestDelaunay, TestIntersects) {
    // Arrange
    Point p1(0.0,0.0);
    Point p2(10.0,10.0);
    Point p3(0.0,5.0);
    Point p4(10.0, 0.0);

    Lati l1(&p1, &p2);
    Lati l2(&p3, &p4);

    // Act
    bool intersects = l1.intersects(l2);

    // Assert
    EXPECT_TRUE(intersects);
}

TEST(TestDelaunay, TestNotIntersects) {
    // Arrange
    Point p1(0.0,0.0);
    Point p2(10.0,10.0);
    Point p3(11.0,11.0);
    Point p4(20.0, 0.0);

    Lati l1(&p1, &p2);
    Lati l2(&p3, &p4);

    // Act
    bool intersects = l1.intersects(l2);

    // Assert
    EXPECT_FALSE(intersects);
}

TEST(TestDelaunay, TestIntersectsCoincidenti) {
    // Arrange
    Point p1(0.0,0.0);
    Point p2(10.0,10.0);
    Point p3(10.0,10.0);
    Point p4(0.0, 0.0);

    Lati l1(&p1, &p2);
    Lati l2(&p3, &p4);

    // Act
    bool intersects = l1.intersects(l2);

    // Assert
    EXPECT_FALSE(intersects);
}

