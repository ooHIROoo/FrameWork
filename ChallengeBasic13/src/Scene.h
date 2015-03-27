#pragma once
#include "lib\appEnv.hpp"
#include "Resource.h"

enum class SceneType{
	TITLE,
	STAGE,
	RESULT,
};

class Scene
{
	SceneType type;
protected:
	SceneType Type()const{ return type; }
	std::unique_ptr<Resource>resource;
public:
	Scene() = default;
	virtual ~Scene() = default;

	virtual SceneType Update() = 0;
	virtual void Draw() = 0;
	void LoadScene(const SceneType type){ this->type = type; }

	//�@�g�p�֎~
	void Load(const SceneType type);
};
