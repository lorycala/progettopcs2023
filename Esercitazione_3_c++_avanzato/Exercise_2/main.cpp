#include <iostream>
#include "Eigen/Eigen"

using namespace std;
using namespace Eigen;

/// \brief Test the real solution of system Ax = b
/// \return the relative error for PALU solver
/// \return the relative error for QR solver
void TestSolution(const MatrixXd& A,   //dati const double riferimenti all'originale  e non copie
                  const VectorXd& b,
                  const VectorXd& solution,
                  double& errRelPALU,
                  double& errRelQR);

/// \brief Solve linear system with PALU
/// \return the solution
VectorXd SolveSystemPALU(const MatrixXd& A,
                         const VectorXd& b);

/// \brief Solve linear system with PALU
/// \return the solution
VectorXd SolveSystemQR(const MatrixXd& A,
                       const VectorXd& b);

int main()  //creo il vettore soluzione e i vettori particolari per poi scrivere una cosa generale
{
    Vector2d solution(-1.0000e+0, -1.0000e+00);
        //prendo in output le cose particolari sotto scrivero una funzione genrale
    Matrix2d A1(2,2);
    A1 << 5.547001962252291e-01, -3.770900990025203e-02,
        8.320502943378437e-01,-9.992887623566787e-01;

    Vector2d b1(2);
    b1 << -5.169911863249772e-01,
        1.672384680188350e-01;

    double errRel1PALU, errRel1QR;
    TestSolution(A1, b1, solution, errRel1PALU, errRel1QR);

    if (errRel1PALU < 1e-15 && errRel1QR < 1e-15)
        cout<< scientific<< "1 - "<< "PALU: "<< errRel1PALU<< " QR: "<< errRel1QR<< endl;
    else
    {
        cerr<< "1 - Wrong system solution found"<< endl;
        return -1;
    }

    Matrix2d A2(2,2);
    A2 << 5.547001962252291e-01, -5.540607316466765e-01,
        8.320502943378437e-01, -8.324762492991313e-01;

    Vector2d b2(2);
    b2<< -6.394645785530173e-04,
        4.259549612877223e-04;

    double errRel2PALU, errRel2QR;
    TestSolution(A2, b2, solution, errRel2PALU, errRel2QR);

    if (errRel2PALU < 1e-12 && errRel2QR < 1e-12)
        cout<< scientific<< "2 - "<< "PALU: "<< errRel2PALU<< " QR: "<< errRel2QR<< endl;
    else
    {
        cerr<< "2 - Wrong system solution found"<< endl;
        return -1;
    }

    Matrix2d A3(2,2);
    A3 << 5.547001962252291e-01, -5.547001955851905e-01,
        8.320502943378437e-01, -8.320502947645361e-01;

    Vector2d b3(2);
    b3 << -6.400391328043042e-10,
        4.266924591433963e-10;
    //scrivo i valori numerici qui e poi scrivo una funzione genrale

    double errRel3PALU, errRel3QR;

    TestSolution(A3, b3, solution, errRel3PALU, errRel3QR);

    if (errRel3PALU < 1e-5 && errRel3QR < 1e-5)
        cout<< scientific<< "3 - "<< "PALU: "<< errRel3PALU<< " QR: "<< errRel3QR<< endl;
    else
    {
        cerr<< "3 - Wrong system solution found"<< endl;
        return -1;
    }

    return 0;
}

void TestSolution(const MatrixXd& A,
                  const VectorXd& b,
                  const VectorXd& solution,
                  double& errRelPALU,
                  double& errRelQR)

{
    errRelPALU = numeric_limits<double>::max();
    errRelQR= numeric_limits<double>::max();       //creo funzione generale per risolvere le particolari
        //richiamo le funzioni e i risultati e mi calcolo gli errori
    Vector2d soluzionepalu= SolveSystemPALU(A,b);

    errRelPALU= (soluzionepalu-solution).norm()/solution.norm();

    Vector2d soluzioneqr= SolveSystemQR(A,b);
    errRelQR= (soluzioneqr-solution).norm()/solution.norm();


}

VectorXd SolveSystemPALU(const MatrixXd& A,
                         const VectorXd& b)
{
    VectorXd x = A.fullPivLu().solve(b);
    return x ;   //per risolvere con palu
}

VectorXd SolveSystemQR(const MatrixXd& A,
                       const VectorXd& b)
{
    VectorXd x = A.fullPivHouseholderQr().solve(b);   //per risolvere con qr
        //eigen main page link_
    return x;
}
