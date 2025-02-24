#include "DynamicBodyManager.h"
#include "DynamicBody.h"

DynamicBodyManager::DynamicBodyManager()
{
}

DynamicBodyManager::~DynamicBodyManager()
{
}

void DynamicBodyManager::AddDynamicBody(std::shared_ptr<DynamicBody> dynamicBody)
{
	_dynamicBodies.push_back(dynamicBody);
}

void DynamicBodyManager::RemoveDynamicBody(std::shared_ptr<DynamicBody> dynamicBody)
{
	_dynamicBodies.erase(std::remove(_dynamicBodies.begin(), _dynamicBodies.end(), dynamicBody), _dynamicBodies.end());
}

void DynamicBodyManager::Update()
{
	for (auto& dynamicBody : _dynamicBodies)
	{
		dynamicBody->Update();
	}
}

bool DynamicBodyManager::Release()
{
	return true;
}