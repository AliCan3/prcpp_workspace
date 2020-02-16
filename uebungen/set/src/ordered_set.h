#pragma once

#include <cstddef>
#include <initializer_list>

#include "set.h"

// #define ORDERED_SET_BASE
// #define ORDERED_SET_GET_SMALLER
// #define ORDERED_SET_GET_LARGER
// #define ORDERED_SET_MERGE

#ifdef ORDERED_SET_BASE
class OrderedSet : public Set {
 public:
  OrderedSet();
  explicit OrderedSet(size_t size);
  explicit OrderedSet(const Set& other);
  explicit OrderedSet(Set&& other);
  OrderedSet(const OrderedSet& other);
  OrderedSet(OrderedSet&& other) noexcept;
  OrderedSet(const std::initializer_list<int>& list);

#ifdef ORDERED_SET_GET_SMALLER
  /// \brief Create new Set which contains all elements of this, that are smaller then x.
  OrderedSet GetSmaller(int x) const;
#endif

#ifdef ORDERED_SET_GET_LARGER
  /// \brief Create new Set which contains all elements of this, that are larger then x.
  OrderedSet GetLarger(int x) const;
#endif

#ifdef ORDERED_SET_MERGE
  Set Merge(const Set& other) const override;
#endif

  int* begin() const override { return values_.get() + start_; }
  int* end() const override { return begin() + size(); }

 private:
  void SortIntern();

  size_t start_;
};
#endif
