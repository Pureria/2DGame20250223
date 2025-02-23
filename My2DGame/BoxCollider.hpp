#include <SFML/System/Vector2.hpp>

class BoxCollider
{
private:
	sf::Vector2f _pos, _size;

public:
	BoxCollider(sf::Vector2f pos, sf::Vector2f size);
	~BoxCollider();
	void DebugDraw();
	void SetPosition(sf::Vector2f pos);
	bool IsColliding(BoxCollider& other) const;
	sf::Vector2f GetSize() const;
	sf::Vector2f GetPosition() const;
};

inline sf::Vector2f BoxCollider::GetPosition() const { return _pos; }
inline sf::Vector2f BoxCollider::GetSize() const { return _size; }