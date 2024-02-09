#include "matrix.h"
#include <iostream>

using namespace std;


int main(){

    int data[] = {1,2,3,4,5,6,7,8,9};
    Matrix<int> matrix1(3,3,data);
    Matrix<int> matrix2(3,3,data);

    cout << "Inputs" << endl;
    matrix1.print();
    cout << endl;
    matrix2.print();
    cout << endl;

    cout << "\ntest extraction " << endl;
    cout << "----------" << endl;
    cout << "matrix1(0,0) = " << matrix1(0,0) << endl;
    cout << "matrix1(1,1) = " << matrix1(1,1) << endl;

    cout << "\nMatrix mult int " << endl;
    cout << "----------" << endl;
    Matrix<int> result1 = matrix1*matrix2;
    result1.print();

    cout << "\nScalar Matrix mult int " << endl;
    cout << "----------" << endl;
    Matrix<int> mult1 = matrix1*5;
    mult1.print();

    cout << "\nMatrix sub int " << endl;
    cout << "----------" << endl;
    Matrix<int> result2 = matrix1 - matrix2;
    result2.print();

    cout << "\nMatrix add int " << endl;
    cout << "----------" << endl;
    Matrix<int> result3 = matrix1 + matrix2;
    result3.print();

    cout << "\nMatrix mult float " << endl;
    cout << "----------" << endl;
    float data1[] = {1.2,2.4,3.7,4.1,5.9,6.4,7.3,8.7,9.9};
    float data2[] = {1.4,2.7,3.0,4.5,5.7,6.4,7.1,8.5,9.3};
    Matrix<float> matrixf1(3,3,data1);
    Matrix<float> matrixf2(3,3,data2);
    Matrix<float> result4 = matrixf1*matrixf2;
    result4.print();

    cout << "\nMatrix get column 1" << endl;
    cout << "-----------" << endl;
    Matrix<float> result5 = result4.getColumn(1);
    result5.print();

    cout << "\nMatrix set column " << endl;
    cout << "-----------" << endl;
    float testData[] = {1.1, 2.2, 3.3};
    Matrix<float> testMatrix(3, 1, testData);
    testMatrix.print();
    result4.setColumn(2, testMatrix);
    result4.print();

    cout << "\nMatrix Norm & L2 of Matrix 1 & Matrix 2" << endl;
    cout << "-----------" << endl;
    float norm1 = matrix1.norm();
    float norm2 = matrix2.norm();
    float L2 = Matrix<int>::L2(matrix1, matrix2);
    cout << "norm1 = " << norm1 << endl;
    cout << "norm2 = " << norm2 << endl;
    cout << "L2 = " << L2 << endl;

    cout << "\nDiagonal of 3x3 and 4x5" << endl;
    cout << "-----------" << endl;
    Matrix<int> diagonalized1 = matrix1.diagonal();
    diagonalized1.print();
    int data3[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    Matrix<int> tester(5, 4, data3);
    tester.print();
    Matrix<int> diagonalized2 = tester.diagonal();
    diagonalized2.print();

    cout << "\nMatrix identity " << endl;
    cout << "----------" << endl;
    float data5[] = {1.2,2.4,3.7,4.1,5.9,6.4,7.3,8.7,9.9};
    Matrix<float> matrixf5(3,3,data5);
    Matrix<float> id = matrixf5.identity();
    id.print();

    cout << "\nMatrix division " << endl;
    cout << "----------" << endl;
    float data6[] = {1.2,2.4,3.7,4.1,5.9,6.4,7.3,8.7,9.9};
    Matrix<float> matrixf6(3,3,data5);
    Matrix<float> div = matrixf6/float(5.5);
    div.print();

    cout << "\nGram-Schmidt " << endl;
    cout << "----------" << endl;
    int data7[] = {12, -51, 4, 6, 167, -68, -4, 24, -41};
    Matrix<int> matrix7(3,3,data7);
    cout << "\nMatrix before" << endl;
    matrix7.print();
    cout << "\nMatrix after" << endl;
    Matrix<float> GramSchmidt = matrix7.GramSchmidt();
    GramSchmidt.print();

    cout << "\nQR Decomposition " << endl;
    cout << "----------" << endl;
    int data8[] = {12, -51, 4, 6, 167, -68, -4, 24, -41};
    Matrix<int> matrix8(3,3,data7);
    auto result = matrix8.QRDecomposition();
    Matrix<float> Q = get<0>(result);
    Matrix<float> R = get<1>(result);

    cout << "Q" << endl;
    Q.print();
    cout << "R" << endl;
    R.print();

    int eigenData[] = {4, -30, 60, -35, -30, 300, -675, 420, 60, -675, 1620, -1050, -35, 420, -1050, 700};
    cout << "\nMatrix eigenvalues and vectors: " << endl;
    cout << "----------" << endl;
    Matrix<int> eigenTestMatrix(4,4,eigenData);
    auto eigenResult = eigenTestMatrix.eigen();
    Matrix<float> E = get<0>(eigenResult);
    Matrix<float> e = get<1>(eigenResult);

    cout << "E" << endl;
    E.print();
    cout << "e" << endl;
    e.print();

    return 0;
}