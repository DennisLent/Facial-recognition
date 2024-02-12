#include "utils/matrix.h"
#include "utils/image.h"
#include "utils/pca.h"
#include <iostream>

using namespace std;

int main(){

    setbuf(stdout, NULL);

    auto data = createData(0.5, 2);
    auto trainData = get<0>(data);
    auto testData = get<1>(data);

    auto Vk = Train(trainData, 100, true);

    return 0;
}