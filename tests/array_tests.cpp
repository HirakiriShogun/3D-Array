#include "../lib/SeventeenBitArray.h"
#include <gtest/gtest.h>

TEST(ArrayTest, Equal) {
    int length = 10;
    int width = 20;
    int height = 30;
    SeventeenBitArray first_array = SeventeenBitArray::make_array(length, width, height);
    int value = 0;
    for (int z = 0; z < height; z++) {
        for (int y = 0; y < width; y++) {
            for (int x = 0; x < length; x++) {
                first_array[z][y][x] = value;
                value++;
            }
        }
    }
    SeventeenBitArray second_array = first_array;
    ASSERT_EQ(first_array, second_array);
}
TEST(ArrayTest, SumTest) {
    int length = 2;
    int width = 3;
    int height = 4;
    SeventeenBitArray first_array = SeventeenBitArray::make_array(length, width, height);
    first_array[0][0][0] = 1;
    first_array[0][0][1] = 2;
    SeventeenBitArray second_array = first_array;
    second_array = second_array + first_array;

    ASSERT_EQ(second_array[0][0][0], 2);
    ASSERT_TRUE(second_array[0][0][1] == 4);
}
TEST(ArrayTest, MinusTest) {
    int length = 5;
    int width = 8;
    int height = 12;
    SeventeenBitArray first_array = SeventeenBitArray::make_array(length, width, height);
    first_array[0][0][0] = 7;
    first_array[0][0][1] = 3;
    SeventeenBitArray second_array = SeventeenBitArray::make_array(length, width, height);
    second_array[0][0][0] = 6;
    second_array[0][0][1] = 3;
    second_array = first_array - second_array;
    std::cout << second_array[0][0][1] << std::endl;
    ASSERT_EQ(second_array[0][0][0], 1);
    ASSERT_TRUE(second_array[0][0][1] == 0);
}
TEST(ArrayTest, MultiplyTest) {
    int length = 5;
    int width = 8;
    int height = 12;
    SeventeenBitArray first_array = SeventeenBitArray::make_array(length, width, height);
    first_array[0][0][0] = 6;
    first_array[0][0][1] = 17;
    SeventeenBitArray second_array = SeventeenBitArray::make_array(length, width, height);
    second_array[0][0][0] = 3;
    second_array[0][0][1] = 21;
    second_array = first_array * second_array;
    std::cout << second_array[0][0][1] << std::endl;
    ASSERT_EQ(second_array[0][0][0], 18);
    ASSERT_TRUE(second_array[0][0][1] == 357);
}