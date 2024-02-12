#pragma once

#include <iostream>
#include <matrix.h>
#include <opencv2/opencv.hpp>
#include <string>
#include <regex>

using namespace std;
using namespace cv;

struct Image {
    string name;
    int imageNumber;
    std::shared_ptr<Matrix<float>> data;

    /*
    @brief constructor method for the Image struct
    @param imagePath path to the location of the jpg image
    @returns Image containing the grayscale values of the image in the Matrix struct
    */
    Image(const char* imagePath){
        Mat img = imread(imagePath, IMREAD_GRAYSCALE);
        int cols = img.cols;
        int rows = img.rows;

        //find the name of the file to add to the image
        string fullPath(imagePath);
        size_t found = fullPath.find_last_of("/\\");
        if (found != string::npos) {
            string filename = fullPath.substr(found + 1); 
            // use regex to match name and number
            smatch match;
            regex regexPattern("([0-9]+)_([0-9]+)\\.jpg");
            if (regex_search(filename, match, regexPattern)) {
                name = match.str(2);
                imageNumber = stoi(match.str(1)) % 10;
            } else {
                imageNumber = -1;
            }
        } else {
            // Unable to determine name and image number
            name = "Unknown";
            imageNumber = -1;
        }
        
        //copy into matrix and create image struct
        data = shared_ptr<Matrix<float>>(new Matrix<float>(rows, cols));

        for(int i = 0; i < rows; i++){
            const uchar* Mi = img.ptr<uchar>(i);
            for(int j = 0; j < cols; j++){
                data->operator()(i,j) = static_cast<float>(Mi[j]);
            }
        }
    }

    /*
    @brief basic method to display the name of subject (1 to 41)
    */
    string getName() const {
        return this->name;
    }

    /*
    @brief basic method to print the matrix
    */
    void print(){
        this->data->print();
    }
};