#ifndef __SHAPE_H  //macro è una è un'istruzione o un insieme di istruzioni che viene utilizzato per eseguire una specifica operazione o per definire un valore costante. stiamo definendo della classi infatti che saranno sempre cosi ma cambieranno i valori per calcolare lm area ecc
#define __SHAPE_H     //ridefinisce la macro solo se non è stata definita precedentemente, evitandone la ridefinizione

#include <iostream>
#include "Eigen/Eigen"

using namespace std;   //sempre per usare le sue funzioni invece di scrivere std::.....

namespace ShapeLibrary {   //definisco le classi in shapelibrary e poi dovrò scrivere shapelibrary::.....
class Polygon {

public:
    Eigen::MatrixXd points;   //matrice points di tipo matrixxd presa da eigen che definisce i punti del poligono
    Polygon() = default; //crea un oggetto nella classe
    Polygon(Eigen::MatrixXd& points);   //points in input
    string Show(); //rappresentazione tetsuale poligpno
    double Area();//calcolo area
};


class Triangle : public Polygon   //  i due punti classe figlia in modo che eredita tutto
{
public:
    double base;
    double height;
    Triangle() = default;   // costruttore: crea un oggetto triangolo della classe triangolo
    Triangle(double& base,
             double& height);  //si crea un oggetto reiangle poligon con base e altezza specificate
    //contrasto tra i due triangle???????
    Triangle(Eigen::MatrixXd& points);  //prende ovviamente in inpiut la matrice points
    string Show1();
    string Show();
    double Area();
};


class TriangleEquilateral final : public Triangle    //eredita triangle ma se metto final non puo ereditare
{
public:
    double edgeLength;  //lunghezza lato triangolo equilatero
    TriangleEquilateral(double& edgeLength);
    TriangleEquilateral(double& base,
                        double& height);
    string Show();
    string Show1();
    double Area();
};

class Quadrilateral : public Polygon
{ private:
    Triangle t1;   //ogni quadrilatero ha dentro 2 oggetti di tipo triangle
    Triangle t2;
public:
    Quadrilateral() = default;
    Quadrilateral(Eigen::MatrixXd& points);
    Quadrilateral(Triangle& t1, Triangle& t2);
    string Show();
    string Show1();
    double Area();
};

class Rectangle : public Quadrilateral
{ private:
    double base;
    double height;
public:
    Rectangle() = default;
    Rectangle(Eigen::MatrixXd& points);
    Rectangle(Triangle& t1, Triangle& t2);
    Rectangle(double& base, double& height);
    string Show();
    string Show1();
    string Show2();
    double Area();
};

class Square final: public Rectangle
{ private:
    double edgeLength;
public:
    Square(Eigen::MatrixXd& points);
    Square(Triangle& t1, Triangle& t2);
    Square(double& base, double& height);
    Square(double& edgeLength);
    string Show();
    string Show1();
    string Show2();
    string Show3();
    double Area();
};
}

#endif // __SHAPE_H

