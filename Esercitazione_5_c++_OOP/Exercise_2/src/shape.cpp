#include "shape.hpp"
#include <math.h>

//qua dobbiamo sostanzialmente calcolarci l area con le classi che abbiamo definito e mostrare show
namespace ShapeLibrary {     //ossia d


Polygon::Polygon(Eigen::MatrixXd& points):   //riscrivo tuttp perche mi serve quel dato dallla classe polygon
    points(points) //copia points del costruttore nel points della classe polyogn
//nome della classe :: nome costrittupre        // all'input points do points
{
}
double Polygon::Area()  //definiscp polyogn area
{   //per calcolarmi l'area definisco il metodo di gauss
    //come funziona metodo di gauss partiamo da area x = 0
    // d corrisponde alle colonne della matrice points che non sono altro che il numero di vertici del poligono
    //
    double x=0;
    int d=Polygon::points.cols();     //numero di colonne della matrice points
    for ( int i=0; i<(d-1);i++)  //itero fino al numero di vertici - 1
    {
        x= x + points(0,i)*points(1,(i+1)) - points(0,(i+1))*points(1,i); //aggiorno l area facendo x+ la coordinata x corrente per la coordinata y successiva e sottraendo la coorudinata y del vertice corrente moltiplicato per il la coordinata x del vertice successivo
    }
    x = x + points(0,d-1)*points(1,0) - points(0,0)*points(1,d-1);  //ultimo verice

    x=abs(x/2);           //questo è relativo all'ultimo con il primo
    double area_poligono=x;
    return area_poligono;    //in questo modo Polyogn:: Area restituisce il valore area poligono
}
string Polygon::Show() {return "Polygon: "+to_string(Polygon::Area()) ;}  //show scrive soltanto


// Triangle as Polygon   //qui se ho in input points

Triangle::Triangle(Eigen::MatrixXd& points)
    : Polygon (points)
{
}
string Triangle::Show1() {return "Triangle As Polygon: "+to_string(Polygon::Area());}


// Triangle Area  qui se ho in input base e altezza

Triangle::Triangle(double& base, double& height):
    base(base),
    height(height)
{
}
double Triangle::Area()
{
    return (base*height)/2;
}
string Triangle::Show() {return "Triangle: "+to_string(Triangle::Area());}


// Triangle Equilateral as Traiangle   triangolo equilatero come se avessi in inpit base e altezza di triangle

TriangleEquilateral::TriangleEquilateral(double& base, double& height)
    : Triangle (base, height)
{
}
string TriangleEquilateral::Show1() {return "TriangleEquilateral As Triangle: "+to_string(Triangle::Area());}



// Triangle Equilateral Area se ho input lunghezza lato


TriangleEquilateral::TriangleEquilateral(double& edgeLength) :
    edgeLength(edgeLength)
{
}
double TriangleEquilateral::Area()
{
    return ((sqrt(3)/4)*edgeLength*edgeLength);
}
string TriangleEquilateral::Show() {return "TriangleEquilateral: "+to_string(TriangleEquilateral::Area());}



// Quadrilateral as Polygonal
//se ho input points

Quadrilateral::Quadrilateral(Eigen::MatrixXd& points)
    : Polygon(points)
{
}
string Quadrilateral::Show1() {return "Quadrilateral As Polygon: "+to_string(Polygon::Area());}


// Quadrilateral Area se ho input i due triangoli

Quadrilateral::Quadrilateral(Triangle& t1, Triangle& t2) :
    t1(t1),
    t2(t2)
{
}
double Quadrilateral::Area()
{
    return t1.Polygon::Area() + t2.Polygon::Area();
}
string Quadrilateral::Show() {return "Quadrilateral: "+to_string(Quadrilateral::Area());}


// Rectangle as Polygonal


Rectangle::Rectangle(Eigen::MatrixXd& points)
    : Quadrilateral(points)  //se ho in input points
{
}
string Rectangle::Show1() {return "Rectangle As Polygon: "+to_string(Polygon::Area());}



// Rectangle as Quadrilateral


Rectangle::Rectangle(Triangle& t1, Triangle& t2)
    : Quadrilateral(t1,t2)
{  // se ho in input i due trianfoli
}
string Rectangle::Show2() {return "Rectangle As Quadrilateral: "+to_string(Quadrilateral::Area());}


// Rectangle Area
//se ho in input base e altezza

Rectangle::Rectangle(double& base, double& height):
    base(base),
    height(height)
{
}
double Rectangle::Area()
{
    return base*height;
}
string Rectangle::Show() {return "Rectangle: "+to_string(Rectangle::Area()) ;}



// Square as Polygonal


Square::Square(Eigen::MatrixXd& points)
    : Rectangle(points)  //se ho input points
{
}
string Square::Show1() {return "Square As Polygon: "+to_string(Polygon::Area());}


// Square as Quadrilateral


Square::Square(Triangle& t1, Triangle& t2)
    : Rectangle(t1,t2)
{  //se ho in input triagoli
}
string Square::Show2() {return "Square As Quadrilateral: "+to_string(Quadrilateral::Area());}



// Square as Rectangle


Square::Square(double& base, double& height)
    : Rectangle(base, height)
{
}  //se ho in input base e altezza
string Square::Show3() {return "Square As Rectangle: "+to_string(Rectangle::Area());}



// Square Area
//se ho in input lunghezza lato

Square::Square(double& edgeLength):
    edgeLength(edgeLength)
{
}
double Square::Area()
{
    return edgeLength*edgeLength;
}
string Square::Show() {return "Square: "+to_string(Square::Area()); }

}
