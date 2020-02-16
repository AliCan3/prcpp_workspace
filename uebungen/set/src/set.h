#pragma once

#include <cstddef>
#include <memory>
#include <ostream>
#include <initializer_list>

// #define OPERATION_MERGE
// #define OPERATION_INTERSECTION
// #define OPERATION_DIFFERENCE
// #define OPERATION_INTERSECTION_MOVE
// #define OPERATION_DIFFERENCE_MOVE

class Set {
 public:
  Set();
  explicit Set(size_t size);
  Set(const Set& other);
  Set(Set&& other) noexcept;
  Set(const std::initializer_list<int>& list);

  virtual ~Set();

  /// \brief Get the number of elements managed by this instance.
  size_t size() const { return size_; }

  /// \brief Check if this instance contains no element at all.
  bool empty() const { return size() == 0; }

  /// \brief Check if a single element is contained in this set.
  bool Contains(int e) const;

  /// \brief Check if this set is a super-set of the provided set.
  bool ContainsAll(const Set& set) const;

  /// \brief Compare operator to check that both sets contain exactly the same elements.
  bool operator==(const Set& set) const;

  /// \brief Compare operator. Inversion of operator==.
  bool operator!=(const Set& set) const;

  /// \brief Access operator for individual elements in range [0, size()).
  int operator[](size_t i) const;

#ifdef OPERATION_MERGE
  static Set Merge(const Set& set1, const Set& set2) {
    return set1.Merge(set2);
  }
#endif

#ifdef OPERATION_INTERSECTION
  static Set Intersection(const Set& set1, const Set& set2) {
    return set1.Intersection(set2);
  }
#endif

#ifdef OPERATION_DIFFERENCE
  static Set Difference(const Set& set1, const Set& set2) {
    return set2.Difference(set1);
  }
#endif

#ifdef OPERATION_INTERSECTION_MOVE
  static Set Intersection(const Set& set1, Set&& set2) {
    return set1.Intersection(std::move(set2));
  }
  static Set Intersection(Set&& set1, const Set& set2) {
    return set2.Intersection(std::move(set1));
  }
  static Set Intersection(Set&& set1, Set&& set2) {
    return set1.Intersection(std::move(set2));
  }
#endif

#ifdef OPERATION_DIFFERENCE_MOVE
  static Set Difference(Set&& set1, const Set& set2) {
    return set2.Difference(std::move(set1));
  }
  static Set Difference(Set&& set1, Set&& set2) {
    return set2.Difference(std::move(set1));
  }
#endif

  /// \brief Output-Operator for debugging.
  friend std::ostream& operator<<(std::ostream& os, const Set& s) {
    const int* const vptr = s.begin();
    os << "{";
    if (!s.empty()) os << vptr[0];
    for (size_t i = 1; i < s.size_; ++i) { os << ", " << vptr[i]; }
    os << "}";
    return os;
  }

  /// \brief Return a Pointer to the first element in the set.
  /// \attention Only this method should be used in all other methods to access the internal elements.
  virtual int* begin() const { return values_.get(); }
  virtual int* end() const { return begin() + size(); }

 protected:
  /// \brief Internal helper to copy in an element and to use the existing memory without to allocate new memory.
  void AddUnchecked(int e);

  /// \brief Internal helper to remove an element and managing the new size.
  void RemoveUnchecked(int e);

  /// \brief Internal helper to access the element at a specific address in memory without range checks.
  int& AtUnchecked(size_t i);
  int AtUnchecked(size_t i) const;

#ifdef OPERATION_MERGE
  /// \brief Return the union of the this and other set.
  virtual Set Merge(const Set& other) const;
#endif

#ifdef OPERATION_INTERSECTION
  /// \brief Return the intersection of this and other set.
  virtual Set Intersection(const Set& other) const;
#endif

#ifdef OPERATION_DIFFERENCE
  /// \brief Return the difference between other and this set.
  virtual Set Difference(const Set& other) const;
#endif

#ifdef OPERATION_INTERSECTION_MOVE
  virtual Set Intersection(Set&& other) const;
#endif

#ifdef OPERATION_DIFFERENCE_MOVE
  virtual Set Difference(Set&& other) const;
#endif

  std::shared_ptr<int[]> values_;
  size_t size_;
};
