#pragma once

#include <functional>
#include <memory>
#include <unordered_map>


struct factory_creatable {
    virtual ~factory_creatable() = default;
};


class factory {
public:
    using obj_pointer = std::unique_ptr<factory_creatable>;
    using creator = std::function<obj_pointer()>;

    static factory& instance();
    
    void register_type(const std::string& type_id, creator);
    bool is_registered(const std::string& type_id);
    void unregister_type(const std::string& type_id);
    
    obj_pointer create(const std::string& type_id);
    
private:
    factory() = default;
    
    std::unordered_map<std::string, creator> m_map;
};
