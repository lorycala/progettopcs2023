#include <iostream>
#include "Eigen/Eigen"
#include <fstream>
#include "map"

using namespace std;  //è una dichiarazione in C++ che consente di utilizzare i nomi definiti nello spazio dei nomi std senza dover specificare il prefisso std::
using namespace Eigen;

struct PolygonalMesh
{
    unsigned int NumberCell0D = 0;  //sostanzialmente prenditi un vettore in std e vcrealo di quel tipo
    std::vector<unsigned int> Cell0DId = {};  //la classe std::vector permette di creare un array dinamico
    // e di accedere o manipolare un suo elemento data la posizione
    //(indice) usando l’operatore [
    std::vector<Vector2d> Cell0DCoordinates = {};
    std::map<unsigned int, list<unsigned int>> Cell0DMarkers = {};

    unsigned int NumberCell1D = 0; ///< number of Cell1D
    std::vector<unsigned int> Cell1DId = {}; ///< Cell1D id, size 1 x NumberCell1D
    std::vector<Vector2i> Cell1DVertices = {}; ///indice dei vertici che mi delimitano il lato< Cell1D vertices indices, size 2 x NumberCell1D (fromId,toId)
    std::map<unsigned int, list<unsigned int>> Cell1DMarkers = {}; ///< Cell1D propertoes, size 1 x NumberCell1D (marker)

    unsigned int NumberCell2D = 0; ///celle 2d < number of Cell2D     array piu facile da usare
    std::vector<unsigned int> Cell2DId = {}; ///< Cell2D id, size 1 x NumberCell2D
    std::vector<unsigned int> Cell2DNumvertices = {};
    std::vector<VectorXi> Cell2DVertices = {}; ///< Cell2D Vertices indices, size 1 x NumberCell2DVertices[NumberCell2D]
    std::vector<unsigned int> Cell2DNumedges = {};
    std::vector<VectorXi> Cell2DEdges = {}; ///< Cell2D Cell1D indices, size 1 x NumberCell2DEdges[NumberCell2D]




};

///\brief Import the Polygonal mesh and test if the mesh is correct
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportMesh(PolygonalMesh& mesh);  //true o false  //mesh il reticolo quello che noi gli diamo e modifichiamo

///\brief Import the Cell0D properties from Cell0Ds.csv file
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportCell0Ds(PolygonalMesh& mesh);

///\brief Import the Cell1D properties from Cell1Ds.csv file
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportCell1Ds(PolygonalMesh& mesh);

///\brief Import the Cell2D properties from Cell2Ds.csv file
///\param mesh: a PolygonalMesh struct
///\return the result of the reading, true if is success, false otherwise
bool ImportCell2Ds(PolygonalMesh& mesh);

// ***************************************************************************
int main()
{

    PolygonalMesh mesh;

    if(!ImportMesh(mesh))
    {
        return 1;
    }

    return 0;
}
// ***************************************************************************
bool ImportMesh(PolygonalMesh& mesh)
{

    if(!ImportCell0Ds(mesh))
    {
        return false;
    }
    else  //i markers sono map quindi devo accedere alla chiave e ai valori
    //it è un iteratore
    {
        cout << "Cell0D marker:" << endl;   //da it auto fino alla fine quindi fino al nulla
        for(auto it = mesh.Cell0DMarkers.begin(); it != mesh.Cell0DMarkers.end(); it++)
        {                        //deferenziare e accedere a first
            cout << "key:\t" << it -> first << "\t values:";  //L’espressione it->first restituisce la chiave dell’elemento a cui punta l’iteratore it first denota la chiave second il valore
            for(const unsigned int id : it -> second)
                cout << "\t" << id;    //stampo elementi della chiave iterando sulla chiave

            cout << endl;
        }
    }

    if(!ImportCell1Ds(mesh))
    {
        return false;
    }
    else
    {
        cout << "Cell1D marker:" << endl;
        for(auto it = mesh.Cell1DMarkers.begin(); it != mesh.Cell1DMarkers.end(); it++)
        {
            cout << "key:\t" << it -> first << "\t values:";
            for(const unsigned int id : it -> second)
                cout << "\t" << id;

            cout << endl;
        }
    }
    // Test:  //cerca di trovare errori
    for(unsigned int c = 0; c < mesh.NumberCell2D; c++)
    {
        VectorXi edges = mesh.Cell2DEdges[c]; // Ottiene gli indici dei bordi della cella corrente


        for(unsigned int e = 0; e < mesh.Cell2DNumedges[c] ; e++)  // Itera attraverso i bordi della cella corrente
        {
            const unsigned int origin = mesh.Cell1DVertices[edges[e]][0];// Ottiene il vertice di origine del bordo corrente
            const unsigned int end = mesh.Cell1DVertices[edges[e]][1]; // Ottiene il vertice finale del bordo corrente

            auto findOrigin = find(mesh.Cell2DVertices[c].begin(), mesh.Cell2DVertices[c].end(), origin);   // Cerca il vertice di origine nei vertici della cella corrente
            if(findOrigin == mesh.Cell2DVertices[c].end())  // Se il vertice di origine non viene trovato
            {
                cerr << "Wrong mesh" << endl;  //errore
                return 2;
            }

            auto findEnd = find(mesh.Cell2DVertices[c].begin(), mesh.Cell2DVertices[c].end(), end); // Cerca il vertice finale nei vertici della cella corrente
            if(findEnd == mesh.Cell2DVertices[c].end())  // Se il vertice finale non viene trovato
            {
                cerr << "Wrong mesh" << endl;
                return 3;
            }

        }
        return true; }
    return true;}





// ***************************************************************************
bool ImportCell0Ds(PolygonalMesh& mesh)
{
    ifstream file;    //leggo il contenuto del file
    file.open("./Cell0Ds.csv");
    char toDelete;
    if(file.fail())    //zona di verifica
        return false;

    list<string> listLines;     //lista di stringhe
    string line;
    while (getline(file, line))   //finche leggo memorizzo pushback
        listLines.push_back(line);

    file.close();

    listLines.pop_front();    //elimino il testo all'inizio della lista

    mesh.NumberCell0D = listLines.size();     //dimensione della numbercell0 della mesh deve essere uiguale a

    if (mesh.NumberCell0D == 0)  //verifica
    {
        cerr << "There is no cell 0D" << endl;
        return false;
    }

    mesh.Cell0DId.resize(mesh.NumberCell0D);  //resize risozza il vettore in modo che abbia la stessa dimensione dli numbercellss e pushback inserisce al fondo
    mesh.Cell0DCoordinates.resize(mesh.NumberCell0D);

    for (const string& line : listLines) //for range per ogni riga splitto la riga e converto i valori
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2d coord;

        converter >>  id >> toDelete >> marker >> toDelete >> coord(0) >> toDelete  >> coord(1);   //riconosce cosa abbiamo e i dati e li separa direttamente lui

        mesh.Cell0DId.push_back(id);   //pushbacco inserisco in coda
        mesh.Cell0DCoordinates.push_back(coord);

        if( marker != 0)  //se il marker è diverso da zero   // Il codice controlla se il valore di marker è diverso da zero. Se lo è, il codice cerca il valore di marker nel membro Cell0DMarkers dell’oggetto mesh. Se marker non è presente in Cell0DMarkers, il codice inserisce una nuova coppia chiave-valore in Cell0DMarkers, dove la chiave è marker e il valore è un vettore contenente il valore di id. Altrimenti, il codice aggiunge il valore di id al vettore associato alla chiave marker in Cell0DMarkers
        {
            if (mesh.Cell0DMarkers.find(marker) == mesh.Cell0DMarkers.end())
                mesh.Cell0DMarkers.insert({marker, {id}});    //aggiungo marker e id del vertice
            else
                mesh.Cell0DMarkers[marker].push_back(id);  //
        }

    }
    file.close();

    return true;
}
// ***************************************************************************
bool ImportCell1Ds(PolygonalMesh& mesh)
{
    ifstream file;
    file.open("./Cell1Ds.csv");

    if(file.fail())
        return false;
    char toDelete;
    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();

    mesh.NumberCell1D = listLines.size();

    if (mesh.NumberCell1D == 0)
    {
        cerr << "There is no cell 1D" << endl;
        return false;
    }

    mesh.Cell1DId.resize(mesh.NumberCell1D);
    mesh.Cell1DVertices.resize(mesh.NumberCell1D);

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        Vector2i vertices;     //qui abbiamo i vertici

        converter >>  id >> toDelete >> marker >> toDelete >> vertices(0) >> toDelete >> vertices(1);

        mesh.Cell1DId.push_back(id);    //memorizzo id
        mesh.Cell1DVertices.push_back(vertices);    //memorizzo vertici

        if( marker != 0)
        {
            if (mesh.Cell1DMarkers.find(marker) == mesh.Cell1DMarkers.end())
                mesh.Cell1DMarkers.insert({marker, {id}});
            else
                mesh.Cell1DMarkers[marker].push_back(id);
        }
    }

    file.close();


    return true;
}
// ***************************************************************************
bool ImportCell2Ds(PolygonalMesh& mesh)
{
    ifstream file;
    file.open("./Cell2Ds.csv");

    if(file.fail())
        return false;

    list<string> listLines;
    string line;
    while (getline(file, line))
        listLines.push_back(line);

    listLines.pop_front();  //linea testazione elinimo

    mesh.NumberCell2D = listLines.size();

    if (mesh.NumberCell2D == 0)
    {
        cerr << "There is no cell 2D" << endl;
        return false;
    }

    mesh.Cell2DId.resize(mesh.NumberCell2D);
    mesh.Cell2DVertices.resize(mesh.NumberCell2D);
    mesh.Cell2DEdges.resize(mesh.NumberCell2D);

    char toDelete;

    for (const string& line : listLines)
    {
        istringstream converter(line);

        unsigned int id;
        unsigned int marker;
        unsigned int numvertices;
        VectorXi vertices;              //todelete mi elimina punti e virgola e cose
        unsigned int numedges;
        VectorXi edges;

        converter >>  id >> toDelete >> marker >> toDelete >> numvertices >> toDelete;
        for(unsigned int i = 0; i < numvertices; i++)
            converter >> vertices[i] >> toDelete;
        converter >> numedges >> toDelete;
        for(unsigned int i = 0; i < numedges; i++)
            converter >> edges[i]>> toDelete;

        mesh.Cell2DId.push_back(id);           //salvo i dati trovati all'interno delle varie cell
        mesh.Cell2DVertices.push_back(vertices);
        mesh.Cell2DEdges.push_back(edges);
        mesh.Cell2DNumedges.push_back(numedges);
    }
    file.close();


    return true;
}
