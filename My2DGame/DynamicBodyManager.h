#pragma once
#include "Singleton.h"
#include <memory>
#include <vector>

class DynamicBody; //�O���錾

class DynamicBodyManager : public Singleton<DynamicBodyManager>
{
private:
	std::vector<std::shared_ptr<DynamicBody>> _dynamicBodies;

public:
	DynamicBodyManager();
	~DynamicBodyManager();
	void AddDynamicBody(std::shared_ptr<DynamicBody> dynamicBody);
	void RemoveDynamicBody(std::shared_ptr<DynamicBody> dynamicBody);
	void Update();

	bool Release() override;
};

