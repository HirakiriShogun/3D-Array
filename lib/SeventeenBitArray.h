#pragma once
#include <iostream>
#include <cstdint>

class SeventeenBitArray {
public:
    SeventeenBitArray(uint32_t x_coordinate, uint32_t y_coordinate, uint32_t z_coordinate);
    SeventeenBitArray(const SeventeenBitArray& other);
    ~SeventeenBitArray();

    SeventeenBitArray& operator=(uint32_t value);
    SeventeenBitArray& operator=(const SeventeenBitArray& other);

    SeventeenBitArray& operator[](uint32_t index);
    uint32_t operator[](uint32_t index) const;

    static SeventeenBitArray make_array(uint32_t x_coordinate, uint32_t y_coordinate, uint32_t z_coordinate);

    static void copy(uint32_t* first_array, const uint32_t* second_array, uint32_t size);

    void SetValue(uint32_t value);

    SeventeenBitArray operator+(const SeventeenBitArray& other);
    SeventeenBitArray operator-(const SeventeenBitArray& other);
    SeventeenBitArray operator*(const SeventeenBitArray& other);

    friend std::ostream& operator<<(std::ostream& stream, const SeventeenBitArray& array);
    friend std::istream& operator>>(std::istream& stream, SeventeenBitArray& array);

    bool operator==(const SeventeenBitArray& other) const;
    friend bool operator==(const SeventeenBitArray& other, const uint32_t number);
    friend bool operator==(uint32_t number, const SeventeenBitArray& other);

    bool operator!=(const SeventeenBitArray& other) const;

private:
    const uint8_t kSizeOfNumber = 17;

    uint32_t* array_ = nullptr;

    uint32_t width = 0;
    uint32_t length = 0;
    uint32_t height = 0;

    uint32_t current_x_ = 0;
    uint32_t current_y_ = 0;
    uint32_t current_z_ = 0;

    uint32_t number_positional_ = 0;
    uint32_t find_bit_of_number_ = 0;

    static bool TakeBit(const uint32_t* value, uint32_t bit_position);

    SeventeenBitArray& ClearBit(uint32_t* array, uint32_t bit_position);
    SeventeenBitArray& SetBit(uint32_t* array, uint32_t bit_position);

    uint32_t GetIndex(uint32_t x_coordinate, uint32_t y_coordinate, uint32_t z_coordinate) const;

    uint32_t ToNumber(const uint32_t* array_, uint32_t number_positional_) const;
};