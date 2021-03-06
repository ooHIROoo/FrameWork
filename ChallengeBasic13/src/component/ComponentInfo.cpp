#include "ComponentInfo.h"
#include "Component.h"

ComponentInfo::ComponentInfo()
{
}

//　追加
void ComponentInfo::Add(const std::shared_ptr<Component>& component){
	component_list.emplace(component->Name(), component);
}

//　検索
const std::shared_ptr<Component>& ComponentInfo::Find(const std::string& name)const{
	return component_list.find(name)->second;
}