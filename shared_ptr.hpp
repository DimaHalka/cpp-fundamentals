#pragma once

#include <cstddef> // size_t

template <typename T>
class shared_ptr {
public:
  shared_ptr()
    : mp_data(nullptr)
    , mp_ref_count(nullptr)
  {
  }

  shared_ptr(T* ptr)
  {
    if (ptr) {
      mp_data = ptr;
      mp_ref_count = new size_t(1);
    }
    else {
      mp_data = nullptr;
      mp_ref_count = nullptr;
    }
  }

  shared_ptr(const shared_ptr<T>& other)
    : mp_data(other.mp_data)
    , mp_ref_count(other.mp_ref_count)
  {
    if (mp_ref_count) {
      (*mp_ref_count)++;
    }
  }

  ~shared_ptr()
  {
    if (mp_ref_count) {
      (*mp_ref_count)--;

      if (*mp_ref_count == 0) {
        delete mp_data;
        delete mp_ref_count;
      }
    }
  }

  T* get() noexcept {
    return mp_data;
  }

  T* get() const noexcept {
    return mp_data;
  }

  size_t ref_count() const noexcept {
    return mp_ref_count ? *mp_ref_count : 0;
  }

  bool empty() const noexcept {
    return mp_ref_count == nullptr;
  }

  operator bool() const noexcept {
    return !empty();
  }

  bool operator!() const noexcept {
    return empty();
  }

private:
  T* mp_data;

  // The reference count defines the invariant.
  // If it is nullptr, the shared_ptr is empty.
  // Otherwise, it owns a control state.
  size_t* mp_ref_count;
};

