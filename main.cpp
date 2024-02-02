#include "matrix.h"
#include <iostream>


int main(){

    int data[] = {1,2,3,4,5,6};
    Matrix<int> matrix1(2,3,data);
    Matrix<int> matrix2(3,2,data);

    Matrix<int> result = matrix1*matrix2;
    

    std::cout << "Matrix" << std::endl;
    std::cout << "----------" << std::endl;
    result.print();



    return 0;
}