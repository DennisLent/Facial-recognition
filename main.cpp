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

    cout << "Matrix mult int " << endl;
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



    return 0;
}