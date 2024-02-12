#pragma once

#include "../utils/image.h"
#include <iostream>
#include <cassert>

using namespace std;

void testInitImage1(){
    const char* path = "../images/archive/1_1.jpg";
    auto result = Image(path, 1);

    assert(result.name == "1");
    assert(result.imageNumber == 1);
}

void testInitImage2(){
    const char* path = "../images/archive/391_40.jpg";
    auto result = Image(path, 1);

    assert(result.name == "40");
    assert(result.imageNumber == 1);
}

void testInitImage3(){
    const char* path = "../images/archive/370_37.jpg";
    auto result = Image(path, 1);

    assert(result.name == "37");
    assert(result.imageNumber == 0);
}


int ImageTests(){

    cout << "===== Running Image Tests =====" << endl;

    testInitImage1();
    testInitImage2();
    testInitImage3();

    return 0;
}