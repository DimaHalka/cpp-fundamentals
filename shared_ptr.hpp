#pragma once

template <typename T>
class shared_ptr {
public:
  shared_ptr()
    : mp_data(nullptr)
    , mp_ref_count(nullptr)
  {
  }

  shared_ptr(T* ptr)
    : mp_data(ptr)
    , mp_ref_count(new size_t)
  {
    *mp_ref_count = 1;
  }

  shared_ptr(const shared_ptr<T>& other)
    : mp_data(other.mp_data)
    , mp_ref_count(other.mp_ref_count)
  {
    if (mp_data) {
      (*mp_ref_count)++;
    }
  }

  ~shared_ptr()
  {
    if (mp_data) {
      (*mp_ref_count)--;

      if (*mp_ref_count == 0) {
        delete mp_data;
        mp_data = nullptr;

        delete mp_ref_count;
        mp_ref_count = nullptr;
      }
    }
  }

  T* data() noexcept {
    return mp_data;
  }

  size_t ref_count() const noexcept {
    return mp_ref_count ? *mp_ref_count : 0;
  }

private:
  T* mp_data;
  size_t* mp_ref_count;
};

