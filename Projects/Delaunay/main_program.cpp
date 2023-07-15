#include "empty_class.hpp"
#include <string>
#include <fstream>

using namespace std;
using namespace delaunay;

int main() {
    vector<Lati> sides;
    vector<Point> points;

    // Apro il file
    ifstream file;


    file.open("C:\\Users\\Huawei\\Desktop\\PCS2023_Exercises\\Projects\\Delaunay\\Dataset\\Test1.csv");
    string line;

    // Leggo i punti in una lista
    getline(file,line);
    while (getline(file, line))
    {
        stringstream ss; //converter
        ss << line;  //mette la linea in ss
        int id;
        ss>>id; //mette la prima cosa di ss in id
        double x,y;
        ss>>x>>y;  //le altre due in x e y
        points.push_back(Point(x,y)); // creo le istanze Punto nella lista points
    }
    file.close();

    // ordiniamo ora i punti trovati in senso antiorario
    vector<Point> sortedPoints = Point::sortPointsCounterclockwise(points) ;

    // costruisco il ConvexHull
    vector<Point> convexPoints = delaunay::convexHull(sortedPoints);

    // Area max
    //Triangle Triangle_area_max = Triangle::LargestTriangle(convexPoints);



    Point * p1;
    Point * p2;
    Point * p3;

    Point a(0.0, 0.0);
    Point b(7.5, 5.0);
    Point c(8.75, 3.75);

    p1=&a;
    p2=&b;
    p3=&c;

    addLatoIfNotExists(sides, Lati(&a, &b));
    addLatoIfNotExists(sides, Lati(&b, &c));
    addLatoIfNotExists(sides, Lati(&c, &a));

    // Creo una lista di triangoli
    vector<Triangle> triangles;
    triangles.push_back(Triangle(p1,p2,p3)); // aggiungo il primo triangolo ossiaquello di area max



    //creo una lista di punti senza p1 p2 p3
    vector<Point*> point_da_aggiungere;
    for (auto & point : points) {
        if(&point != p1 && &point != p2 && &point != p3)
        {
            point_da_aggiungere.push_back(&point);
        }
    }

    for (int i=0; i < int(point_da_aggiungere.size()); i++) {
        for (int j=0; j < int(triangles.size()); j++)
        {
            // se il punto da aggiungere è un vertice, break
            if (point_da_aggiungere[i] == triangles[j].points[0] ||
                point_da_aggiungere[i] == triangles[j].points[1]
                || point_da_aggiungere[i]==triangles[j].points[2]) {
                break;
            }

            if (triangles[j].dentro(triangles[j],*point_da_aggiungere[i])) {
                // creo 3 nuovi triangoli, eliminando quello vecchio
                Triangle old=triangles[j];


                triangles[j]=Triangle(old.points[0],old.points[1],point_da_aggiungere[i]);  // ho sostituito il triangolo grande
                triangles.push_back(Triangle(old.points[1],old.points[2],point_da_aggiungere[i]));
                triangles.push_back(Triangle(old.points[2],old.points[0],point_da_aggiungere[i]));

                // aggiungo i 3 nuovi lati
                addLatoIfNotExists(sides, delaunay::Lati(old.points[0], point_da_aggiungere[i]));
                addLatoIfNotExists(sides, delaunay::Lati(old.points[1],point_da_aggiungere[i]));
                addLatoIfNotExists(sides, delaunay::Lati(old.points[2],point_da_aggiungere[i]));

            } else {
                // 3 lati fittizi
                Lati l1 = Lati(point_da_aggiungere[i],triangles[j].points[0]);
                Lati l2 = Lati(point_da_aggiungere[i], triangles[j].points[1]);
                Lati l3 = Lati(point_da_aggiungere[i], triangles[j].points[2]);

                //vedo se i lati del triangolo con il punto intersecano qualsiasi lato
                    bool intersection = false;
                for (auto side: sides) {
                    if (l1.intersects(side)) {
                        intersection = true;
                        break;
                    }
                }

                if (!intersection)
                    addLatoIfNotExists(sides, l1);

                intersection = false;
                for (auto side: sides) {
                    if (l2.intersects(side)) {
                        intersection = true;
                        break;
                    }
                }

                if (!intersection)
                    addLatoIfNotExists(sides, l2);

                intersection = false;
                for (auto side: sides) {
                    if (l3.intersects(side)) {
                        intersection = true;
                        break;
                    }
                }
                if (!intersection)
                    addLatoIfNotExists(sides, l3);



                // coppie possibili con triangles[j]
                if (Point::isConnect(point_da_aggiungere[i], triangles[j].points[0], sides) &&
                    Point::isConnect(point_da_aggiungere[i], triangles[j].points[1], sides)) { triangles.push_back(Triangle(point_da_aggiungere[i],
                                                 triangles[j].points[0], triangles[j].points[1]));
                } else if (Point::isConnect(point_da_aggiungere[i], triangles[j].points[0], sides) &&
                           Point::isConnect(point_da_aggiungere[i], triangles[j].points[2], sides)) {
                    triangles.push_back(Triangle(point_da_aggiungere[i], triangles[j].points[0], triangles[j].points[2]));
                } else if (Point::isConnect(point_da_aggiungere[i], triangles[j].points[1], sides) &&
                           Point::isConnect(point_da_aggiungere[i], triangles[j].points[2], sides)) {
                    triangles.push_back(Triangle(point_da_aggiungere[i], triangles[j].points[1], triangles[j].points[2]));
                }
            }

            for (int e = 0; e < int(triangles.size()); e++) {
                // verifico l'adiacenza del triangolo j inizale con tutti i triangoli
                    if (delaunay::Triangle::areTrianglesAdjacent(triangles[j],triangles[e])) {
                    vector<Point> commonPoints =
                        Triangle::commonPoints(triangles[j], triangles[e]);
                    Point* punto1 = &commonPoints[0];
                    Point* punto2 = &commonPoints[1];

                    // Hai trovato due punti comuni tra i triangoli i e j
                    Lati latoAdiacente = Lati(punto1, punto2);
                    delaunay::Point* altropuntoj = nullptr; // punti non in comune
                    delaunay::Point* altropuntoe = nullptr;

                    // trovo i due punti non in comune inizializzati sopra
                    for (auto & point : triangles[j].points)     {
                        if (point != punto1 && point != punto2) {
                            altropuntoj = point;
                        }
                    }

                    for (auto & point : triangles[e].points) {
                        if (point != punto1 && point != punto2) {
                            altropuntoe = point;
                        }
                    }

                    // Devi ordinare i punti qui per usare deulanay devo usareordina  punti

                        if (triangles[j].isDelaunayValid(*altropuntoe)) { // sta fuori
                        continue;
                    } else { // sta dentro => flip
                        Lati l4 = Lati(altropuntoj, altropuntoe);
                        addLatoIfNotExists(sides, l4);

                        sides.erase(std::remove_if(sides.begin(), sides.end(),
                                                   [&](const Lati& l) {
                                                       return l == latoAdiacente;
                                                   }), sides.end());

                        //triangles.push_back(Triangle(punto1,punto2,altropuntoj));
                        //triangles.push_back(Triangle(punto1,punto2,altropuntoe));
                    }
                }
            }
        }
    }

    // output in due file .csv
    outputSidesToFile("./output_sides.csv", sides); // lati
    outputPointsToFile("./output_points.csv", points); // punti
    return 0;
}

