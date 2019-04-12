
// #define DEBUG
#define SAFEMATRIX

#include <iostream>

#include "MatrixH.h"
using namespace MatrixSpace;

int main ()
{
    std::ios::sync_with_stdio (false);
    using std::cout;
    using std::endl;



    Matrix <int> *A = new Matrix <int> (4, 5);
    Matrix <int> *B = new Matrix <int> (4, 5);


    cout << "Please input a Matrix <int> (4 * 5)" << endl;
    A->initfs ();

    cout << "Please input a Matrix <int> (4 * 5)" << endl;
    B->initfs ();

    Matrix <int> *C = (*A) + (*B);
    cout << "A+B:" << endl << *C << endl;
    delete C;
    C = nullptr;

    C = (*A) - (*B);
    cout << "A-B:" << endl << *C << endl;

    delete C;
    C = nullptr;
    delete A;
    A = nullptr;
    delete B;
    B = nullptr;

    # ifdef DEBUG
    cout << globtest << endl;
    # endif
    return 0;
}

/*
0 0 1 0 5
1 2 3 4 2
1 2 2 2 2
3 3 3 3 3
5 4 3 2 1
1 2 3 4 2
3 1 2 4 5
3 1 2 4 5
*/
