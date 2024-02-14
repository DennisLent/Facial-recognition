# Facial-recognition
This project is an attempt to run facial recognition using the method of [Eigenfaces](https://www.face-rec.org/algorithms/PCA/jcn.pdf) a pretty old paper but I thought it was interesting, as it is a different way from CNNs and I thought that was a bit overused. The dataset used for this purpose was the ORL data base of faces and is saved in this repo or can be manually downloaded from [kaggle](https://www.kaggle.com/datasets/tavarez/the-orl-database-for-training-and-testing?resource=download). The main idea actually started with writing my own Matrix class, and it developed much further while trying to solve for eigenvalues and eigenvectors. 

All the necessary functions can be found in src/utils and the testing code can be found in src/tests.

## Prerequisites
* C++ compiler (e.g. GCC)
* [OpenCV](https://docs.opencv.org/4.x/d7/d9f/tutorial_linux_install.html)
* [OpenMP](https://www.iitgoa.ac.in/hpcshiksha/HPC%20Shiksha%20-%20OpenMP%20Installation%20Guide.pdf)

## Overview
The project can be broken down into 3 main parts
1. Matrix implementation
2. Data reading and formatting
3. PCA transform

### 1. Matrix Implementation
The first part was implementing a matrix that can take a type T, so that I could read the image data into it. I know OpenCV does that as well, but I still thought it would be more fun to implement it myself. To determine the eigenvectors, [QR decomposition](https://math.stackexchange.com/questions/575380/relationship-between-eigenvector-values-and-qr-decomposition) is used. Within QR I apply the [Modified Gram-Schmidt Process](https://www.math.uci.edu/~ttrogdon/105A/html/Lecture23.html) as it promised to be faster. Overall I tried to parallelize the code using OpenMP, however a bottlenck is the GMS which has to be improved to achieve proper training times on my machine.

### 2. Data reading
The second part uses OpenCV. I primarily chose to use OpenCV because I did not bother to write an entire decoder and encoder for the images, and OpenCV provides that. It is only used to extract the grayscale data from the image and is then fed into my own matrix struct. 

### 3. PCA transform
PCA transform is the main way to use Eigenfaces and helps by reducing the dimensions and we can pick out the most significant ones to compare the images on. Again, due to the eigenvector calculations taking very long, this process is not feasible on my machine and has to be sped up. 

## Quick setup
In order to run the program, you will need to make sure that you have OpenMP and OpenCV installed. 

Create directory and compile the projects

```mkdir build```

```cd build```

```cmake ..```

```cmake --build .```

To run the main file

```./main```

To run the tests

```./test```

## Future Changes
As of right now the program runs very slowly when training, which is in large part due to the GMS. Even for datasets this big, the GMS is too slow and not even OpenMP can help my parallelizing the code. A future suggestion would be to update the Matrix implementation to use CUDA. By running GMS on a GPU it could lead to significant increase. Additionally it would make multiplications and QR decomposition way faster. 


