#pragma once

// TODO: deleter as a parameter, calling delete in dtor won't work correctly for arrays

template <typename T>
class unique_ptr {
public:
    unique_ptr()
        : m_ptr(nullptr)
    {}
    
    ~unique_ptr() {
        reset();
    }
    
    unique_ptr(const unique_ptr&) = delete;
    unique_ptr& operator=(const unique_ptr&) = delete;
        
    explicit unique_ptr(T* ptr)
        : m_ptr(ptr)
    {}
        
    unique_ptr(unique_ptr&& other) noexcept {
        m_ptr = other.m_ptr;
        other.m_ptr = nullptr;
    }

    unique_ptr& operator=(T* ptr) {
        if(m_ptr != ptr) {
            reset();
            m_ptr = ptr;
        }
        return *this;
    }
    
    unique_ptr& operator=(unique_ptr&& other) noexcept {
        if (this != &other) {
            reset();
            m_ptr = other.m_ptr;
        }
        other.m_ptr = nullptr;
        return *this;
    }

    T* get() const noexcept {
        return m_ptr;
    }
    
    void reset() {
        if(m_ptr)
            delete m_ptr;
        m_ptr = nullptr;
    }
    
    

private:
    T* m_ptr;
};
