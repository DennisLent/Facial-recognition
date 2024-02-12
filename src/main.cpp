#include "utils/matrix.h"
#include "utils/image.h"
#include "utils/pca.h"
#include <iostream>

using namespace std;


int main(){

    auto data = createData(0.5);
    auto trainData = get<0>(data);
    auto testData = get<1>(data);

    auto Vk = Train(trainData, 15, true);

    return 0;
}