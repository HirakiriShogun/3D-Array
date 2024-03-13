#include "SeventeenBitArray.h"

SeventeenBitArray::SeventeenBitArray(const uint32_t x_coordinate, const uint32_t y_coordinate, const uint32_t z_coordinate) {
    length = x_coordinate;
    width = y_coordinate;
    height = z_coordinate;
    array_ = new uint32_t[((x_coordinate * y_coordinate * z_coordinate * kSizeOfNumber + 31) / 32) + 1]{};
}
SeventeenBitArray::SeventeenBitArray(const SeventeenBitArray& other) {
    width = other.width;
    length = other.length;
    height = other.height;
    array_ = new uint32_t[((width * length * height * kSizeOfNumber + 31) / 32) + 1];
    copy(array_, other.array_, ((width * length * height * kSizeOfNumber + 31) / 32) + 1);
}

SeventeenBitArray::~SeventeenBitArray() {
    delete[] array_;
}
SeventeenBitArray& SeventeenBitArray::operator[](const uint32_t index) {
    static uint8_t counter = 0;
    if (counter == 0) {
        current_z_ = index;
        ++counter;
    }
    else if (counter == 1) {
        current_y_ = index;
        ++counter;
    }
    else if (counter == 2) {
        current_x_ = index;
        number_positional_ = GetIndex(current_x_, current_y_, current_z_);
        counter = 0;
    }
    if (current_x_ >= length || current_y_ >= width || current_z_ >= height) {
        throw std::out_of_range("Array indices are out of range!");
    }
    return *this;
}
uint32_t SeventeenBitArray::operator[](uint32_t index) const {
    return ToNumber(array_, number_positional_);
}
SeventeenBitArray& SeventeenBitArray::operator=(const SeventeenBitArray& other) {
    if (this != &other) {
        delete[] array_;
        width = other.width;
        length = other.length;
        height = other.height;
        array_ = new uint32_t[((width * length * height * kSizeOfNumber + 31) / 32) + 1];
        copy(array_, other.array_, ((width * length * height * kSizeOfNumber + 31) / 32) + 1);
    }
    return *this;
}
SeventeenBitArray& SeventeenBitArray::operator=(uint32_t value) {
    find_bit_of_number_ = kSizeOfNumber * number_positional_;

    for (int i = 0; i < kSizeOfNumber; ++i) {
        if (value & (1 << i)) {
            SetBit(array_, find_bit_of_number_ + i);
        }
        else {
            ClearBit(array_, find_bit_of_number_ + i);
        }
    }
    return *this;
}
SeventeenBitArray SeventeenBitArray::make_array(const uint32_t x_coordinate,
    const uint32_t y_coordinate,
    const uint32_t z_coordinate) {
    return SeventeenBitArray(x_coordinate, y_coordinate, z_coordinate);
}
void SeventeenBitArray::copy(uint32_t* first_array, const uint32_t* second_array, uint32_t size) {
    for (int i = 0; i < size; ++i) {
        first_array[i] = second_array[i];
    }
}
void SeventeenBitArray::SetValue(uint32_t value) {
    (*this)[current_z_][current_y_][current_x_] = value;
}
bool SeventeenBitArray::TakeBit(const uint32_t* value, uint32_t bit_position) {
    uint32_t array_index = bit_position / 32;
    uint32_t bit_index = bit_position % 32;
    return ((value[array_index] >> bit_index) & 1) != 0;
}
SeventeenBitArray& SeventeenBitArray::ClearBit(uint32_t* array, uint32_t bit_position) {
    array[bit_position / 32] &= ~(1 << (bit_position % 32));
    return *this;
}
SeventeenBitArray& SeventeenBitArray::SetBit(uint32_t* array, uint32_t bit_position) {
    array[bit_position / 32] |= (1 << (bit_position % 32));
    return *this;
}
uint32_t SeventeenBitArray::GetIndex(uint32_t x_coordinate, uint32_t y_coordinate, uint32_t z_coordinate) const {
    uint32_t offset = 0;
    offset += z_coordinate * width * length;
    offset += y_coordinate * length;
    offset += x_coordinate;
    return offset;
}
uint32_t SeventeenBitArray::ToNumber(const uint32_t* array, uint32_t number_positional) const {
    uint32_t find_bit_of_number = number_positional * kSizeOfNumber;
    uint32_t number = 0;
    uint32_t bit = 1;

    for (int i = 0; i < kSizeOfNumber; ++i) {
        if (TakeBit(array, find_bit_of_number + i)) {
            number += bit;
        }
        bit <<= 1;
    }
    return number;
}
SeventeenBitArray SeventeenBitArray::operator+(const SeventeenBitArray& other) {
    SeventeenBitArray sum(width, length, height);
    if (width != other.width || length != other.length
        || height != other.height) {
        throw std::out_of_range("Array dimensions are not equal!");
    }

    for (int z = 0; z < height; ++z) {
        for (int y = 0; y < length; ++y) {
            for (int x = 0; x < width; ++x) {
                uint32_t index = GetIndex(x, y, z);
                sum[z][y][x] = ToNumber(array_, index) + other.ToNumber(other.array_, index);
            }
        }
    }
    return sum;
}

SeventeenBitArray SeventeenBitArray::operator-(const SeventeenBitArray& other) {
    SeventeenBitArray minus(width, length, height);
    if (width != other.width || length != other.length
        || height != other.height) {
        throw std::out_of_range("Array dimensions are not equal!");
    }
    for (int z = 0; z < height; ++z) {
        for (int y = 0; y < length; ++y) {
            for (int x = 0; x < width; ++x) {
                uint32_t index = GetIndex(x, y, z);
                if (ToNumber(array_, index) < other.ToNumber(other.array_, index)) {
                    throw std::out_of_range("Negative numbers are not supported!");
                }
                minus[z][y][x] = ToNumber(this->array_, index) - other.ToNumber(other.array_, index);
            }
        }
    }
    return minus;
}

SeventeenBitArray SeventeenBitArray::operator*(const SeventeenBitArray& other) {
    SeventeenBitArray mult(width, length, height);
    if (width != other.width || length != other.length
        || height != other.height) {
        throw std::out_of_range("Array dimensions are not equal!");
    }
    for (int z = 0; z < height; ++z) {
        for (int y = 0; y < length; ++y) {
            for (int x = 0; x < width; ++x) {
                uint32_t index = GetIndex(x, y, z);
                mult[z][y][x] = ToNumber(this->array_, index) * other.ToNumber(other.array_, index);
            }
        }
    }
    return mult;
}

std::ostream& operator<<(std::ostream& stream, const SeventeenBitArray& array) {
    uint32_t value = array.ToNumber(array.array_, array.number_positional_);
    stream << value;
    return stream;
}
std::istream& operator>>(std::istream& stream, SeventeenBitArray& array) {
    uint32_t value;
    stream >> value;
    if (!stream) {
        return stream;
    }
    array.SetValue(value);
    return stream;
}
bool SeventeenBitArray::operator==(const SeventeenBitArray& other) const {
    if (width != other.width || length != other.length
        || height != other.height) {
        throw std::out_of_range("Array dimensions are not equal!");
    }
    for (uint32_t i = 0; i < height * width * length; i++) {
        if (ToNumber(array_, i) != other.ToNumber(other.array_, i)) {
            return false;
        }
    }
    return true;
}
bool SeventeenBitArray::operator!=(const SeventeenBitArray& other) const {
    if (width != other.width || length != other.length
        || height != other.height) {
        throw std::out_of_range("Array dimensions are not equal!");
    }
    return !(*this == other);
}
bool operator==(const SeventeenBitArray& other, const uint32_t number) {
    return (other.ToNumber(other.array_, other.number_positional_) == number);
}
bool operator==(uint32_t number, const SeventeenBitArray& other) {
    return (number = other.ToNumber(other.array_, other.number_positional_));
}