#include <memory>
#include "BoxCollider.hpp"
#include "Singleton.h"

class IColliderManager : Singleton<IColliderManager>
{
	public:
		virtual void AddCollider(std::shared_ptr<BoxCollider> collider) = 0;
		virtual void RemoveCollider(std::shared_ptr<BoxCollider> collider) = 0;
		virtual void Update() = 0;
		virtual ~IColliderManager() = default;
};