#pragma once

#include <cstddef>

// #define OPERATIONS_MULTIPLY
// #define OPERATIONS_POWER
// #define OPERATIONS_MULTIPLY_FAST
// #define OPERATIONS_POWER_FAST

/// \brief Class which handles a two-dimensional matrix.
class Matrix {
 public:
  /// \brief Create instance with allocated memory for all value cells.
  /// \param vertical Size of the vertical dimension.
  /// \param horizontal Size of the horizontal dimension.
  Matrix(size_t vertical, size_t horizontal);

  /// \brief Destructor ensures freeing of allocated memory.
  ~Matrix();

  /// \brief Copy constructor which allocates its own memory and makes a deep copy of content data.
  Matrix(const Matrix& other);

  /// \brief Set all values in matrix to the provided value.
  /// \param value The value to set in all matrix cells. Default is 0.0.
  void SetAll(double value = 0.0);

  /// \brief Set all values to make an identity matrix.
  void SetIdentity();

  /// \brief Set all values to various random values.
  void SetRandom();

  /// \brief Access to raw internal data.
  /// \attention Only used for unit tests.
  /// \return Raw pointer to the internal allocated memory.
  const double* Data() const { return data_; }
  double* Data() { return data_; }

  /// \brief Get number of value cells.
  size_t Size() const;

  /// \brief Evaluate if the provided instance contains the same values as the own instance.
  /// \attention Use Math::AlmostEquals in utils/math.h for double comparison.
  /// \param other The instance to compare with.
  /// \return \c True if dimension and all values do match.
  bool Equals(const Matrix& other) const;

#ifdef OPERATIONS_MULTIPLY
  /// \brief Multiply two matrices.
  ///
  /// They have to form the following expression (represented by the dimension sizes):
  /// [a_vertical x a_horizontal] x [b_vertical x b_horizontal] = [a_vertical x b_horizontal]
  /// where a_horizontal and b_vertical must have the same size.
  ///
  /// \param other The matrix on the right side of the multiplication.
  /// \return A new instance of a matrix with the result values.
  Matrix Multiply(const Matrix& other) const;
#endif

#ifdef OPERATIONS_POWER
  /// \brief Exponential function for quadratic matrices.
  ///
  /// For expressions of form: m^k
  Matrix Power(size_t k) const;
#endif

#ifdef OPERATIONS_MULTIPLY_FAST
  /// \brief Fast implementation that uses cache optimized loops.
  Matrix MultiplyFast(const Matrix& other) const;
#endif

#ifdef OPERATIONS_POWER_FAST
  /// \brief Fast implementation that uses concept of exponentiation by squaring.
  /// \see https://en.wikipedia.org/wiki/Exponentiation_by_squaring#Computation_by_powers_of_2
  Matrix PowerFast(size_t k) const;
#endif

 private:
#ifdef OPERATIONS_MULTIPLY
  static void MultiplyIntern(const double* a,
                             const double* b,
                             double* res,
                             size_t a_vertical,
                             size_t b_horizontal,
                             size_t between);
#endif

#ifdef OPERATIONS_MULTIPLY_FAST
  static void MultiplyInternFast(const double* __restrict a,
                                 const double* __restrict b,
                                 double* __restrict res,
                                 size_t a_vertical,
                                 size_t b_horizontal,
                                 size_t between);
#endif

  const size_t vertical_;
  const size_t horizontal_;
  const size_t size_;
  double* data_;
};
