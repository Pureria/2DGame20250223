#include <memory>

class BoxCollider;

class IColliderManager
{
	public:
		virtual void AddCollider(std::shared_ptr<BoxCollider> collider) = 0;
		virtual void RemoveCollider(std::shared_ptr<BoxCollider> collider) = 0;
		virtual void Update() = 0;
		virtual ~IColliderManager() = default;
};