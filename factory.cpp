#include "factory.h"

factory& factory::instance() {
    static factory inst;
    return inst;
}

void factory::register_type(const std::string& type_id, creator the_creator) {
    m_map.emplace(type_id, std::move(the_creator));
}

bool factory::is_registered(const std::string& type_id) {
    return m_map.find(type_id) != m_map.end();
}


void factory::unregister_type(const std::string& type_id) {
    m_map.erase(type_id);
}

factory::obj_pointer factory::create(const std::string& type_id) {
    const auto& creator = m_map.find(type_id);
    if(creator == m_map.end())
        throw std::runtime_error("factory::create - such type is not registered");
    
    return creator->second();
}

