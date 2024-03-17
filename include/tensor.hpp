#pragma once

#include <iostream>
#include "shape.hpp"

#define EPSILON 1e-3

namespace core{
class Primitive;

class Tensor
{
public:
    template <typename Iterable>
    Tensor(Iterable &arraylike, float *data);
    Tensor(std::initializer_list<int> arraylike, float *data);
    Tensor(std::vector<int> shapes, std::vector<int> strides, float *data);
    Tensor(const std::vector<Tensor>& inputs, Primitive op);
    Tensor(const std::vector<int> arraylike, float *data);
    Tensor(const std::vector<int> shape);

    // Creation methods
    template <typename Iterable>
    static Tensor ones(Iterable &arraylike);
    static Tensor ones(std::initializer_list<int> arraylike);
    template <typename Iterable>
    static Tensor zeros(Iterable &arraylike);
    static Tensor zeros(std::initializer_list<int> arraylike);
    // static Tensor randn(unsigned int rows, unsigned int cols);

    // Operators
    template <typename T>
    Tensor operator+(T value);
    Tensor operator+(const Tensor &other);

    template <typename T>
    Tensor operator-(T value);
    Tensor operator-(const Tensor &other);

    template <typename T>
    Tensor operator/(T value);
    Tensor operator/(const Tensor &other);

    template <typename T>
    Tensor operator*(T value);
    Tensor operator*(const Tensor &other);
    
    Tensor log();
    Tensor sqrt();
    
    bool operator==(const Tensor &other);
    float& operator[](int index);

    Tensor matmul(const Tensor &other);
    Shape *shape() const;
    float *data() const;
    float *data();
    int size() const;
    std::vector<int> getStrides() const;

private:
    float *m_data = nullptr;
    Shape *m_shape = nullptr;
    std::vector<int> strides;

    
};

// Template functions definition
template <typename T>
Tensor Tensor::operator+(T value)
{
    int total_size = size();
    for (int i = 0; i < total_size; i++)
    {
        m_data[i] += value;
    }

    return *this;
}

template <typename T>
Tensor Tensor::operator-(T value)
{
    int total_size = size();
    for (int i = 0; i < total_size; i++)
    {
        m_data[i] -= value;
    }

    return *this;
}

template <typename T>
Tensor Tensor::operator/(T value)
{
    int total_size = size();
    for (int i = 0; i < total_size; i++)
    {
        m_data[i] /= value;
    }

    return *this;
}

template <typename T>
Tensor Tensor::operator*(T value)
{
    int total_size = size();
    for (int i = 0; i < total_size; i++)
    {
        m_data[i] *= value;
    }

    return *this;
}
}