#ifndef JTL_VECTOR_H__
#define JTL_VECTOR_H__
#include <initializer_list>
#include <utility>

namespace jtl {

template <typename T, typename Allocator>
class vector_base {
  typedef T* pointer;  // TODO: figure out alloc_traits

  /**
   * Stores pointers to valid data range and allocated data range.
   */
  class vector_impl_data {
    /// Points to the beginning of the allocated storage block.
    pointer start;

    /// Points to the end of the used storage.
    pointer end;

    /// Points to the end of the allocated capacity.
    pointer end_of_storage;

    vector_impl_data() noexcept : start(), end(), end_of_storage() {}
    vector_impl_data(vector_impl_data&& x) noexcept
        : start(x.start), end(x.end), end_of_storage(x.end_of_storage) {
      // Clear data from x
      x.start = pointer();
      x.end = pointer();
      x.end_of_storage = pointer();
    }

    void swap_data(vector_impl_data& x) noexcept {
      std::swap(start, x.start);
      std::swap(end, x.end);
      std::swap(end_of_storage, x.end_of_storage);
    }

  };  // class vector_impl_data

  class vector_impl : public vector_impl_data {};  // class vector_impl

};  // class vector_base

template <typename T, typename Allocator>
class vector : protected vector_base<T, Allocator> {};  // class vector

}  // namespace jtl

#endif  // JTL_VECTOR_H__
