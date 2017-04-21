#ifndef ARRAY_HPP
#define ARRAY_HPP

#include <stddef.h>

#include <iterator.hpp>

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

    constexpr size_type size() const noexcept {
        return N;
    }

    constexpr T* data() noexcept {
        return elems_;
    }

    constexpr const T* data() const noexcept {
        return elems_;
    }
};

#endif