#pragma once

#include <iostream>
#include <cassert>
#include <stdexcept>
#include "../utils/matrix.h"
#include <cmath>



void testInitMatrix(){
    int data[] = {1,2,3,4,5,6,7,8,9};
    Matrix<int> mat(3,3,data);

    assert(mat.M == 3);
    assert(mat.N == 3);
    for(int i = 0; i<mat.M*mat.N; i++){
        assert(mat[i] == data[i]);
    }
}

void testExtract(){
    int data[] = {1,2,3,4,5,6,7,8,9};
    Matrix<int> mat(3,3,data);
    assert(mat(0,0) == 1);
    assert(mat(1,1) == 5);
}

void testMatMult(){
    int data[] = {1,2,3,4,5,6,7,8,9};
    Matrix<int> mat1(3,3,data);
    Matrix<int> mat2(3,3,data);
    Matrix<int> result1 = mat1*mat2;
    
    int result[] = {30,36,42,66,81,96,102,126,150};
    for(int i = 0; i<result1.M*result1.N; i++){
        assert(result1[i] == result[i]);
    }
}

void testScalarMult(){
    int data[] = {1,2,3,4,5,6,7,8,9};
    Matrix<int> mat1(3,3,data);
    Matrix<int> result1 = mat1*5;

    int result[] = {5, 10, 15, 20, 25, 30, 35, 40, 45};
    for(int i = 0; i<result1.M*result1.N; i++){
        assert(result1[i] == result[i]);
    }
}

void testSub(){
    int data[] = {1,2,3,4,5,6,7,8,9};
    Matrix<int> mat1(3,3,data);
    Matrix<int> mat2(3,3,data);
    Matrix<int> result1 = mat1 - mat2;

    for(int i = 0; i<result1.M*result1.N; i++){
        assert(result1[i] == 0);
    }
}

void testAdd(){
    int data[] = {1,2,3,4,5,6,7,8,9};
    Matrix<int> mat1(3,3,data);
    Matrix<int> mat2(3,3,data);
    Matrix<int> result1 = mat1 + mat2;

    int result[] = {2, 4, 6, 8, 10, 12, 14, 16, 18};
    for(int i = 0; i<result1.M*result1.N; i++){
        assert(result1[i] == result[i]);
    }
}

void testMatMultFloat(){
    float data1[] = {1.2,2.4,3.7,4.1,5.9,6.4,7.3,8.7,9.9};
    float data2[] = {1.4,2.7,3.0,4.5,5.7,6.4,7.1,8.5,9.3};
    Matrix<float> matrix1(3,3,data1);
    Matrix<float> matrix2(3,3,data2);
    Matrix<float> result1 = matrix1*matrix2;

    const float ep = 0.0001;

    float result[] = {38.75, 48.37, 53.37, 77.73, 99.1, 109.58, 119.66, 153.45, 169.65};
    for(int i = 0; i<result1.M*result1.N; i++){
        if (abs(result1[i] - result[i]) > ep) {
        std::cerr << "Error: Unexpected result at index " << i << std::endl;
        std::cerr << "Expected: " << result[i] << ", Actual: " << result1[i] << std::endl;
        assert(false);
        }
    }
}

void testGetColumn(){
    int data[] = {1,2,3,4,5,6,7,8,9};
    Matrix<int> mat1(3,3,data);
    Matrix<int> column = mat1.getColumn(1);

    int result[] = {2, 5, 8};
    for(int i = 0; i<column.M*column.N; i++){
        assert(column[i] == result[i]);
    }
}

void testSetColumn(){
    int data[] = {1,2,3,4,5,6,7,8,9};
    Matrix<int> mat1(3,3,data);

    int data2[] = {13, 14, 15};
    Matrix<int> column(3,1, data2);

    mat1.setColumn(1, column);

    int result[] = {1, 13, 3, 4, 14, 6, 7, 15, 9};
    for(int i = 0; i<mat1.M*mat1.N; i++){
        assert(mat1[i] == result[i]);
    }
}

void testNorm(){
    int data[] = {1,2,3,4,5,6,7,8,9};
    Matrix<int> mat1(3,3,data);

    float norm = mat1.norm();
    float norm_calculated = sqrt(1*1 + 2*2 + 3*3 + 4*4 + 5*5 + 6*6 + 7*7 + 8*8 + 9*9);

    float ep = 0.0001;

    if (abs(norm - norm_calculated) > ep) {
        std::cerr << "Expected: " << norm_calculated << ", Actual: " << norm << std::endl;
        assert(false);
    }
}

void testL2(){
    int data[] = {1,2,3,4,5,6,7,8,9};
    Matrix<int> mat1(3,3,data);
    Matrix<int> mat2(3,3,data);

    float L2 = Matrix<int>::L2(mat1, mat2);

    assert(L2 == 0.0);
}

void testDiagonal(){
    int data1[] = {1,2,3,4,5,6,7,8,9};
    int diagData1[] = {1, 5, 9};
    Matrix<int> mat1(3,3,data1);
    Matrix<int> diagonal1 = mat1.diagonal();

    for(int i = 0; i<diagonal1.M; i++){
        assert(diagonal1[i] == diagData1[i]);
    }

    int data2[] = {1,2,3,4,5,6,7,8,9,10,11,12,13,14,15,16,17,18,19,20};
    int diagData2[] = {1, 6, 11, 16};
    Matrix<int> mat2(5, 4, data2);
    Matrix<int> diagonal2 = mat2.diagonal();

    float ep = 0.0001;

    for(int i = 0; i<diagonal2.M; i++){
        if (abs(diagonal2[i] - diagData2[i]) > ep) {
            std::cerr << "Error: Unexpected result at index " << i << std::endl;
            std::cerr << "Expected: " << diagData2[i] << ", Actual: " << diagonal2[i] << std::endl;
            assert(false);
        }
    }
}

void testIdentity(){
    float data[] = {1.2,2.4,3.7,4.1,5.9,6.4,7.3,8.7,9.9};
    Matrix<float> mat(3,3,data);
    Matrix<float> id = mat.identity();

    for(int i = 0; i<id.M; i++){
        for(int j = 0; j<id.N; j++){
            if (i == j){
                assert(id(i,j) == 1.0);
            }
            else{
                assert(id(i,j) == 0.0);
            }
        }
    }
}

void testDivision(){
    float data[] = {1.2,2.4,3.7,4.1,5.9,6.4,7.3,8.7,9.9};
    Matrix<float> mat(3,3,data);
    Matrix<float> div = mat/float(5.5);
    float result[] = {0.218182, 0.436364, 0.672727, 0.745455, 1.07273, 1.16364, 1.32727, 1.58182, 1.8};

    float ep = 0.0001;

    for(int i = 0; i<mat.M*mat.N; i++){
        if (abs(result[i] - div[i]) > ep) {
            std::cerr << "Error: Unexpected result at index " << i << std::endl;
            std::cerr << "Expected: " << result[i] << ", Actual: " << div[i] << std::endl;
            assert(false);
        }
    }
}

//taken from https://en.wikipedia.org/wiki/Gram%E2%80%93Schmidt_process
void testGramSchmidt(){
    int data[] = {12, -51, 4, 6, 167, -68, -4, 24, -41};
    Matrix<int> mat(3,3,data);
    Matrix<float> GramSchmidt = mat.GramSchmidt();
    float result[] = {0.857143, -0.394286, -0.331429, 0.428571, 0.902857, 0.0342858, -0.285714, 0.171429, -0.942857};

    float ep = 0.0001;

    for(int i = 0; i<mat.M*mat.N; i++){
        if (abs(result[i] - GramSchmidt[i]) > ep) {
            std::cerr << "Error: Unexpected result at index " << i << std::endl;
            std::cerr << "Expected: " << result[i] << ", Actual: " << GramSchmidt[i] << std::endl;
            assert(false);
        }
    }
}

void testQR(){
    int data[] = {12, -51, 4, 6, 167, -68, -4, 24, -41};
    Matrix<int> mat(3,3,data);
    auto result = mat.QRDecomposition();
    Matrix<float> Q = get<0>(result);
    Matrix<float> R = get<1>(result);

    float Qresult[] = {0.857143, -0.394286, -0.331429, 0.428571, 0.902857, 0.0342858, -0.285714, 0.171429, -0.942857};
    float Rresult[] = {14, 21, -14, 0, 175, -70, 0, 0, 35};

    float ep = 0.0001;

    for(int i = 0; i<mat.M*mat.N; i++){
        if (abs(Qresult[i] - Q[i]) > ep) {
            std::cerr << "Error: Unexpected result at index " << i << std::endl;
            std::cerr << "Expected: " << Qresult[i] << ", Actual: " << Q[i] << std::endl;
            assert(false);
        }

        if (abs(Rresult[i] - R[i]) > ep) {
            std::cerr << "Error: Unexpected result at index " << i << std::endl;
            std::cerr << "Expected: " << Rresult[i] << ", Actual: " << R[i] << std::endl;
            assert(false);
        }
    }
}

//taken from https://en.wikipedia.org/wiki/Jacobi_eigenvalue_algorithm#:~:text=The%20Jacobi%20eigenvalue%20method%20repeatedly,(real)%20eigenvalues%20of%20S.
void testEigen(){
    int data[] = {4, -30, 60, -35, -30, 300, -675, 420, 60, -675, 1620, -1050, -35, 420, -1050, 700};
    Matrix<int> mat(4,4,data);
    auto result = mat.eigen();
    Matrix<float> E = get<0>(result);
    Matrix<float> e = get<1>(result);

    float eresult[] = {2585.2538, 37.1014, 1.4780, 0.1666};
    float Eresult[] = {0.02919, -0.17918, -0.5820, 0.7926, -0.3287, 0.7419, 0.3705, 0.4519, 0.7914, -0.1002, 0.5095, 0.3224, -0.51455, -0.6382, 0.5140, 0.2521};

    auto absdiff = [](float real, float approx){
        float ep = abs(real) - abs(approx);
        return ep;
    };

    float e_error = 0.0;
    for(int i = 0; i<e.N; i++){
        e_error += absdiff(eresult[i], e[i]);
    }

    float E_error = 0.0;
    for(int i = 0; i<E.M*E.N; i++){
        E_error += absdiff(Eresult[i], E[i]);
    }

    e_error /= e.M;
    E_error /= (E.M*E.M);

    //since this is an iterative method the error should be less that 1% = 0.01

    assert(e_error <= 0.01);
    assert(E_error <= 0.01);
}

void testFlatten(){
    int data[] = {4, -30, 60, -35, -30, 300, -675, 420, 60, -675, 1620, -1050, -35, 420, -1050, 700};
    Matrix<int> mat(4,4,data);
    
    auto flat = mat.flatten();

    assert(flat.M == 16);
    assert(flat.N == 1);
}

void testSlice(){
    int data[] = {4, -30, 60, -35, -30, 300, -675, 420, 60, -675, 1620, -1050, -35, 420, -1050, 700};
    Matrix<int> mat(4,4,data);

    auto slice = mat.slice(0, 3);

    assert(slice.M == mat.M);
    assert(slice.N == 3);

    int result[] = {4, -30, 60, -30, 300, -675, 60, -675, 1620, -35, 420, -1050};
    for(int i = 0; i<slice.M*slice.N; i++){
        assert(slice[i] == result[i]);
    }
}




int MatrixTests(){

    cout << "===== Running Matrix Tests =====" << endl;
    testInitMatrix();
    testExtract();
    testMatMult();
    testScalarMult();
    testSub();
    testAdd();
    testMatMultFloat();
    testGetColumn();
    testSetColumn();
    testNorm();
    testL2();
    testDiagonal();
    testIdentity();
    testDivision();
    testGramSchmidt();
    testQR();
    testEigen();
    testFlatten();
    testSlice();

    return 0;
}