#include <iostream> //inclusione file di determinate librerie che hanno partiolcari funzioni
#include <fstream>
#include <sstream>

#include <iomanip>

using namespace std; //utilizziamo le classi e le funzioni in std

/// \brief ImporData reads the input data from the data file
/// \param inputFilePath: path name of the input file
/// \param S: the resulting initial wealth
/// \param n: the resulting number of assets
/// \param w: the resulting vector of the weights of assets in the portfolio
/// \param r: the resulting vector of the rates of return of assets
/// \return the result of the reading: true is success, false is error
bool ImportData(const string& inputFilePath,
                double& S, //bool restituisce true e false
                size_t& n,
                double*& w,
                double*& r);

/// \brief ComputeRateOfReturn computes the rate of return of the portfolio and the final amount of wealth
/// \param S: the initial wealth
/// \param n: the number of assets
/// \param w: the vector of the weights of assets in the portfolio
/// \param r: the vector of the rates of return of assets
/// \param rateOfReturn: the resulting rate of return of the portfolio
/// \param V: the resulting final wealth
void ComputeRateOfReturn(const double& S,
                         const size_t& n,  //void non restituisce un cazzo
                         const double* const& w,
                         const double* const& r,
                         double& rateOfReturn,
                         double& V);

/// \brief ExportData prints data on an output stream
/// \param out: object of type ostream
/// \param S: the initial wealth
/// \param n: the number of assets
/// \param w: the vector of the weights of assets in the portfolio
/// \param r: the vector of the rates of return of assets
/// \param rateOfReturn: the rate of return of the portfolio
/// \param V: the final wealth
void ExportData(ostream& out,
                const double& S,
                const size_t& n,
                const double* const& w,
                const double* const& r,
                const double& rateOfReturn,
                const double& V);

/// \brief Export a vector in a string
/// \param n: size of the vector
/// \param v: vector
/// \return the resulting string
string ArrayToString(const size_t& n,  //Questa è la dichiarazione della funzione ArrayToString, che prende in input due argomenti: n, che è una costante di tipo size_t passata per riferimento, e v, che è un puntatore costante a un array di valori double passato per riferimento costante. La funzione restituisce un valore di tipo string.
                     const double* const& v)
{

    ostringstream toString;  //Questa riga dichiara un oggetto ostringstream chiamato toString. Questo oggetto viene utilizzato per creare una rappresentazione in stringa dell’array.
    toString << "[ ";
    for (unsigned int i = 0; i < n; i++)  //inserisce ste cose in tostring
        toString<< v[i]<< " ";
    toString << "]";

    return toString.str();

}

int main()
{
    string inputFileName = "./data.csv";
    double S = 0.0;
    size_t n = 0;
    double* w = nullptr;
    double* r = nullptr;

    if (!ImportData(inputFileName, S, n, w, r))
    {
        cerr<< "Something goes wrong with import"<< endl;
        return -1;
    }

    // Compute the rate of return of the portfolio and the final wealth V
    double rateOfReturn;
    double V;
    ComputeRateOfReturn(S, n, w, r, rateOfReturn, V);


    // Export data on the standard output
    ExportData(cout, S, n, w, r, rateOfReturn, V);


    // Write data to a file
    string outputFileName = "./result.txt";
    ofstream file;
    file.open(outputFileName);

    if (!file.fail())
    {
        ExportData(file, S, n, w, r, rateOfReturn, V);
    }

    file.close();

    delete[] w;
    delete[] r;

    return 0;
}

bool ImportData(const string& inputFilePath,
                double& S,
                size_t& n,
                double*& w,
                double*& r)
{

    ifstream file;             //aprofile (input file stream mi fa leggere dal file)
    file.open(inputFilePath);


    string line;
    getline(file,line, ';');    //leggi fino a ; e poi fino alla fine
    getline(file,line, '\n');
        //come prendere la parte di stringa
    istringstream convertN; //mi converte la stringa in qulche altro formato
    convertN.str(line);
    convertN >> S;

    getline(file,line, ';');
    getline(file,line, '\n');

    istringstream convertD;
    convertD.str(line);
    convertD >> n;

    getline(file,line);

    w= new double[n];
    r= new double[n];


    for (unsigned int i=0; i<n; i++)
    {
        getline(file,line,';');    //converte quello che mi serve

        istringstream convertW;
        convertW.str(line);
        convertW >> w[i];
        getline(file,line, '\n');
        istringstream convertR;
        convertR.str(line);
        convertR >> r[i];
    }


    file.close();

    return true;



}


void ComputeRateOfReturn(const double& S,
                         const size_t& n,
                         const double* const& w,
                         const double* const& r,
                         double& rateOfReturn,
                         double& V)
{

    V=0.0;
    for (unsigned int i=0; i<n; i++)
        V += (S * w[i]) * (1 + r[i]);    //somma le cose ogni volta

    rateOfReturn= (V-S)/S;    //percentuale di guadagno

}


void ExportData(ostream& out,
                const double& S,
                const size_t& n,
                const double* const& w,
                const double* const& r,
                const double& rateOfReturn,
                const double& V)
{
    //qua praticamente sottoscrivo

    out << "S="<< setprecision(2) << fixed << S <<", " << "n=" << n << endl;
    out << "w=[";
    for(unsigned int i=0; i<n; i++)
        out  << w[i] << ' ';
    out << "]"<< endl;

    out << "r=[";
    for(unsigned int i=0; i<n; i++)
        out << r[i] << ' ';
    out << "]" << endl;

    out <<"Rate of return of the portfolio: "<< setprecision(4)<<fixed<< rateOfReturn << endl;
    out <<"V: " << setprecision(2)<<fixed<< V << endl;



}
