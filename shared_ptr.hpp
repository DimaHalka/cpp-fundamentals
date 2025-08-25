#pragma once

template<typename T>
class shared_ptr {
public:
    shared_ptr()
        : mp_obj(nullptr)
        , mp_count(nullptr)
    {
    }
    
    explicit shared_ptr(T* p_obj)
        : mp_obj(p_obj)
        , mp_count(new size_t(1))
    {
    }
    
    shared_ptr(const shared_ptr<T>& obj)
        : mp_obj(obj.mp_obj)
        , mp_count(obj.mp_count)
    {
        if(mp_count)
            (*mp_count)++;
    }

    
    
    bool empty() const noexcept {
        return mp_obj == nullptr;
    }
    
    ~shared_ptr() {
        if(empty())
            return;
        (*mp_count)--;
        if((*mp_count) == 0) {
            delete mp_obj;
            delete mp_count;
            mp_obj = nullptr;
            mp_count = nullptr;
        }
    }
    
private:
    T* mp_obj;
    size_t* mp_count;
};
