#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stddef.h>
#include <iterator.hpp>

namespace kstd {
    inline namespace v1 {

        template <class T, size_t N>
        struct array {
            using value_type      = T;
            using pointer         = T*;
            using const_pointer   = const T*;
            using reference       = T&;
            using const_reference = const T&;
            using size_type       = size_t;
            using difference_type = ptrdiff_t;
            using iterator        = pointer;
            using const_iterator  = const_pointer;

            value_type elems_[N];
            
            // iterators
            constexpr iterator begin() noexcept {
                return iterator(elems_);
            }

            constexpr const_iterator begin() const noexcept {
                return const_iterator(elems_);
            }

            constexpr iterator end() noexcept {
                return iterator(elems_ + N);
            }

            constexpr const_iterator end() const noexcept {
                return const_iterator(elems_ + N);
            }

            constexpr bool empty() const noexcept {
                return begin() == end();
            }


            // capacity
            constexpr size_type size() const noexcept {
                return N;
            }

            // element access
            constexpr T* data() noexcept {
                return elems_;
            }

            constexpr const T* data() const noexcept {
                return elems_;
            }

            constexpr reference operator[](size_type n) {
                return *(begin() + n);
            }

            constexpr const_reference operator[](size_t n) const {
                return *(begin() + n);
            }
        };

    }
}

#endif
