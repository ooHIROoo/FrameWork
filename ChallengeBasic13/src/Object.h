#pragma once
#include "Uncopyable.h"
#include "ComponentTask.h"
#include "ComponentInfo.h"
#include "Transform2D.h"
#include "Resource.h"
#include  <typeinfo>
#include <stack>

class ObjectTask;
class ObjectInfo;
class Object : private Uncopyable, public std::enable_shared_from_this<Object>
{
	bool is_delete = false;
protected:
	ComponentTask component_task;
	ComponentInfo component_info;

	int sorting_number;

	void ComponentAdd(std::shared_ptr<Component>component);
	void ComponetStart(){
		component_task.Start();
	}
	void ComponetnUpdate(){
		component_task.Update();
	}

	static const std::shared_ptr<Resource> GetResource();

public:
	Transform2D transform2D;
	Object() = default;
	Object(const Transform2D& transform2D,int sorting_number = 255):
		transform2D(transform2D),
		sorting_number(sorting_number)
	{}
	virtual ~Object() = default;
	virtual void Awake(){}
	virtual void Start(){}
	virtual void Update(){}
	virtual void Draw(){}

	static ObjectInfo& GetObjectInfo();
	static ObjectTask& GetObjectTask();

	std::string name;

	int SortingNum()const{ return sorting_number; }

	const std::shared_ptr<Object> ObjectFind(const std::string& name)const;

	template <class Type>
	const std::shared_ptr<Type>GetComponent()const{
		std::string name = typeid(Type).name();
		return std::dynamic_pointer_cast<Type>(component_info.Find(name.substr(6)));
	}

	template <class Type>
	const std::shared_ptr<Type>GetObjectType()const{
		std::string name = typeid(Type).name();
		return std::dynamic_pointer_cast<Type>(ObjectFind(name.substr(6)));
	}

	const ComponentInfo& GetComponentInfo()const{
		return component_info;
	}

	static void ObjectAdd(const std::string& name, std::shared_ptr<Object>object);
	void Destory(std::shared_ptr<Object>object);
	bool IsDelete()const{ return is_delete; }
	static std::stack<std::shared_ptr<Object>>& GetDeleteList();
};