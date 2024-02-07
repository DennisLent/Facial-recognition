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




    // int eigenData[] = {4, -30, 60, -35, -30, 300, -675, 420, 60, -675, 1620, -1050, -35, 420, -1050, 700};
    // cout << "\nMatrix before check: " << endl;
    // cout << "----------" << endl;
    // Matrix<int> eigenTestMatrix(4,4,eigenData);
    // eigenTestMatrix.print();
    // auto result = eigenTestMatrix.eigen();
    // Matrix<float> E = std::get<0>(result);
    // Matrix<float> e = std::get<1>(result);

    // cout << "\nMatrix eigen int " << endl;
    // E.print();
    // e.print();




    return 0;
}