#pragma once
#include <memory>
#include <typeindex>
#include <unordered_map>
#include <functional>
#include "SFML/System/Vector2.hpp"

class Component;
using SetPositionCallback = std::function<void(sf::Vector2f)>;

class GameObject
{
private:
	int _nextSetPosCBID;
	sf::Vector2f _pos;
	std::unordered_map<std::type_index, std::shared_ptr<Component>> _Components;
	std::unordered_map<int, SetPositionCallback> _SetPositionCallbacks;

public:
	GameObject(sf::Vector2f pos, sf::Vector2f size);
	~GameObject();
	void Update();
	void Render();
	void RenderDebug();
	void Release();
	sf::Vector2f GetPosition() const;

	//コンポーネントを追加
	template<typename T, typename... Args>
	std::shared_ptr<T> AddComponent(Args&&... args)
	{
		auto component = std::make_shared<T>(std::forward<Args>(args)...);
		_Components[typeid(T)] = component;
		component->Initialize();

		if constexpr (std::is_base_of_v<std::enable_shared_from_this<T>, T>)
		{
			component = component->shared_from_this();
		}

		return component;
	}

	//コンポーネントを取得
	template<typename T>
	std::shared_ptr<T> GetComponent()
	{
		auto it = _Components.find(typeid(T));
		if (it != _Components.end())
		{
			return std::dynamic_pointer_cast<T>(it->second);
		}
		return nullptr;
	}

	template<typename T>
	bool TryGetComponent(std::shared_ptr<T>& outComponent)
	{
		auto it = _Components.find(typeid(T));
		if (it != _Components.end())
		{
			outComponent = std::dynamic_pointer_cast<T>(it->second);
			return true;
		}
		return false;
	}

	void AddPosition(sf::Vector2f delta);
	void SetPosition(sf::Vector2f pos);

	int AddSetPositionCallback(SetPositionCallback callback);
	void RemoveSetPositionCallback(int id);
};

inline sf::Vector2f GameObject::GetPosition() const { return _pos; }