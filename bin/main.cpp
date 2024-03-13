#include "../lib/SeventeenBitArray.h"

int main() {
    int length = 1;
    int width = 2;
    int height = 3;
    SeventeenBitArray array = SeventeenBitArray::make_array(length, width, height);
    array[0][0][0] = 2;
    std::cout << (array[0][0][0] == 2);
    return 0;
}