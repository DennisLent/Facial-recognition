#pragma once

#include <iostream>
#include <string>
#include <tuple>
#include "matrix.h"
#include "image.h"

using namespace std;

/*
@brief function to read all the data from the images folder and returns training and testing sets 
@param split amount of the images to be used as training data (deafult is 0.5)
@returns tuple of vector<Image> of train and test
*/
tuple<vector<Image>, vector<Image>> createData(float split = 0.5){

    vector<Image> train;
    vector<Image> test;

    int subject = 1;
    for(int i = 1; i < 411; i++){

        //create path
        string path = "../images/archive/" + to_string(i) + "_" + to_string(subject) + ".jpg";
        auto image = Image(path.c_str());

        if(image.imageNumber <= int(split*10) - 1){
            train.push_back(image);
        }
        else{
            test.push_back(image);
        }

        //update subject at the end
        if(i%10 == 0){
            subject++;
        }
    }

    return make_tuple(train, test);
}

/*
@brief creates the training matrix from the training data and performs PCA
@param trainData the training data extracted from the images
@param k amount of eigenvectors to use
@param verbose print more information about background processes (false by default)
@returns tuple<Matrix<float>, Matrix<float> of the average faces and the k-highest eigenvectors
*/
Matrix<float> Train(vector<Image> trainData, int k, bool verbose=false){
    
    

    int M = trainData[0].data->M;
    int N = trainData[1].data->N;

    if(verbose){
        cout << "===== Creating Face Matrix =====" << endl;
        cout << "Dimensions of images = " << M << " by " << N << endl;
        cout << "Amount of training data = " << trainData.size() << endl;
    }

    //calculate the average face vector
    //sum(face vectors)/number(vectors)
    Matrix<float> averageFaceVector(M*N, 1);

    for(const auto& image : trainData){
        Matrix<float>& imageData = *(image.data);
        auto flattenedData = imageData.flatten();
        averageFaceVector += flattenedData;
    }

    averageFaceVector /= trainData.size();

    //subtract average face vector from all data and create matrix
    Matrix<float> A(M*N, trainData.size());

    if(verbose){
        cout << "Dimensions of face matrix A = " << M*N << " by " << trainData.size() << endl;
    }

    for(int i = 0; i<trainData.size(); i++){
        Matrix<float>& imageData = *(trainData[i].data);
        auto flattenedData = imageData.flatten();

        flattenedData -= averageFaceVector;
        A.setColumn(i, flattenedData);
    }

    if(verbose){
        cout << "===== Calculate Cov. Matrix =====" << endl;
    }
    //C = A*A^T

    Matrix<float> AT = A.transpose();
    Matrix<float> C = A*AT;

    if(verbose){
        cout << "===== Find Eigenvectors and Values =====" << endl;
        cout << "Dimensions of C: " << C.M << " by " << C.N << endl; 
    }

    auto result = C.eigen(50000, verbose);
    auto E = get<0>(result);
    auto e = get<1>(result);

    //choose eigenvectors so that we reduce the dimensionality
    auto Vk = E.slice(0, k);

    return Vk;
}
