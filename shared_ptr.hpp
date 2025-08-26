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
        , mp_count(new size_t(0))
    {
        if(mp_obj)
            (*mp_count)++;
    }
    
    shared_ptr(const shared_ptr<T>& obj)
        : mp_obj(obj.mp_obj)
        , mp_count(obj.mp_count)
    {
        if(mp_count)
            (*mp_count)++;
    }

    shared_ptr(shared_ptr<T>&& obj) noexcept
        : mp_obj(obj.mp_obj)
        , mp_count(obj.mp_count)
    {
        obj.mp_obj = nullptr;
        obj.mp_count = nullptr;
    }
        
    ~shared_ptr() noexcept {
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
    
    bool empty() const noexcept {
        return mp_obj == nullptr;
    }
    
    size_t ref_count() const noexcept {
        return mp_count ? *mp_count : 0;
    }
    
    void reset(T* p_obj = nullptr) {
        if(p_obj == mp_obj)
            return;
        
        if(!empty()) {
            (*mp_count)--;
            if((*mp_count) == 0) {
                delete mp_obj;
                delete mp_count;
                mp_obj = nullptr;
                mp_count = nullptr;
            }
        }
        
        mp_obj = p_obj;
        mp_count = nullptr;
        
        if(mp_obj)
            mp_count = new size_t(1);
    }

private:
    T* mp_obj;
    size_t* mp_count;
};
