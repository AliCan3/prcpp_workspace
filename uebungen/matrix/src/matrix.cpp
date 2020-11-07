#include "matrix.h"
#include <iostream>
#include <cstddef>
#include <assert.h>
#include <random>
#include <utils/math.h>
#include <asm/socket.h>

Matrix::Matrix(size_t vertical, size_t horizontal)
: vertical_(vertical), horizontal_(horizontal), size_(horizontal*vertical) {
  assert(size_ == horizontal*vertical);
  data_ = new double[size_];
  for (size_t i = 0; i < size_; i++) {
    data_[i] = 0;
  }
}
Matrix::Matrix(const Matrix& other) : vertical_(other.vertical_), horizontal_(other.horizontal_),
 size_(other.size_) {
  data_ = new double[size_];
  for (size_t i = 0; i< size_; i++) {
    data_[i] = other.data_[i];
  }
}

Matrix::~Matrix() {
  delete [] data_;
}

size_t Matrix::Size() const {return size_;}

void Matrix::SetAll(double value) {
  for ( size_t  i = 0; i < size_; i++ ) {
    data_[i] = value;
  }
}

void Matrix::SetIdentity() {
  for ( size_t i = 0; i < size_; i++ ) {
    data_[i] = 0;
  }
  for (size_t i = 0; i < horizontal_; i++) {
    if ( i == 0 ) {
      *(data_) = 1;
    } else {
      *(data_+i*horizontal_+ i) = 1;
    }
  }
}

void Matrix::SetRandom() {
  std::random_device rd;
  std::mt19937 gen(rd());
  std::uniform_real_distribution<double> dis(0.0, 1.0);
  for (size_t i = 0; i< size_; i++) {
    *(data_+i) = dis(gen);
  }
}

bool Matrix::Equals(const Matrix& other) const {
  if ((other.vertical_ != vertical_)) { return false; }
  if ((other.horizontal_ != horizontal_)) { return false; }
  for (size_t i = 0; i < size_; i++) {
    if (!Math::AlmostEquals(data_[i], *(other.Data()+i))) {
      return false;
    }
  }
  return true;
}

void Matrix::MultiplyIntern(const double* a, const double* b, double* res, size_t a_vertical,
                            size_t b_horizontal, size_t between) {
  for (size_t i = 0; i < a_vertical; i++) {
    for (size_t j = 0; j < b_horizontal; j++) {
      double sum = 0;
      for (size_t k = 0; k < between; k++) {
        double elema = (*(a+k+(i*between)));
        double elemb = (*(b+j+(k*b_horizontal)));
        sum += (elema * elemb);
      }
      *(res+j+(b_horizontal*i)) = sum;
    }
  }
}

Matrix Matrix::Power(size_t k) const {
  Matrix m(vertical_, horizontal_);
  double* temp = new double[size_];
  for (size_t i = 0; i < size_; i++) {
    *(temp+i) = *(data_+i);
  }
  for (size_t i = 1; i < k; i++) {
    MultiplyIntern(temp, data_, m.Data(), vertical_, horizontal_, horizontal_);
    for (size_t j = 0; j < size_; j++) {
      *(temp+j) = *(m.data_+j);
    }
  }
  delete [] temp;
  return m;
}

Matrix Matrix::Multiply(const Matrix& other) const {
  assert(horizontal_ == other.vertical_);
  Matrix m = Matrix(vertical_, other.horizontal_);
  MultiplyIntern(data_, other.Data(), m.Data(), vertical_, other.horizontal_, horizontal_);
  return m;
}
void Matrix::MultiplyInternFast(const double* a, const double* b, double* res, size_t a_vertical,
                                size_t b_horizontal, size_t between) {
  for (size_t i = 0; i < a_vertical; ++i) {
    const size_t result_colum = i * b_horizontal;
    const size_t a_colum = i * between;
    for (size_t k = 0; k < between; ++k) {
      const size_t a_index = a_colum + k;
      const size_t b_colum = k * b_horizontal;
      for (size_t j = 0; j < b_horizontal; ++j) {
        res[result_colum + j] += a[a_index] * b[b_colum + j];
      }
    }
  }
}

Matrix Matrix::MultiplyFast(const Matrix& other) const {
  assert(horizontal_ == other.vertical_);
  Matrix result = Matrix(vertical_, other.horizontal_);
  MultiplyInternFast(data_, other.data_, result.data_, vertical_, other.horizontal_, horizontal_);
  return result;
}





