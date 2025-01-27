#include "Collider.h"
using namespace sf;
using namespace std;



Collider::Collider(RectangleShape& body) :
	body(body)
{
}


Collider::~Collider()
{
}

bool Collider::CheckCollide(Collider other, Vector2f& direction, float push, bool pushback)
{
	Vector2f otherPosition = other.GetPosition();
	Vector2f otherHalfSize = other.GetHalfSize();
	Vector2f thisPosition = GetPosition();
	Vector2f thisHalfSize = GetHalfSize();

	float deltaX = otherPosition.x - thisPosition.x;
	float deltaY = otherPosition.y - thisPosition.y;
	float intersectX = abs(deltaX) - (otherHalfSize.x + thisHalfSize.x);
	float intersectY = abs(deltaY) - (otherHalfSize.y + thisHalfSize.y);

	if (intersectX < 0.0f && intersectY < 0.0f)
	{
		push = min(max(push, 0.0f), 1.0f);

		if (intersectX > intersectY)
		{
			if (deltaX > 0.0f)
			{
				if (pushback)
				{
					Move(intersectX * (1.0f - push), 0.0f);
					other.Move(-intersectX * push, 0.0f);
				}
				
				direction.x = 1.0f;
				direction.y = 0.0f;
			}
			else
			{
				if (pushback)
				{
					Move(-intersectX * (1.0f - push), 0.0f);
					other.Move(intersectX * push, 0.0f);
				}
				direction.x = -1.0f;
				direction.y = 0.0f;
			}
		}
		else
		{
			if (deltaY > 0.0f)
			{
				if (pushback)
				{
					Move(0.0f, intersectY * (1.0f - push));
					other.Move(0.0f, -intersectY * push);
				}

				direction.x = 0.0f;
				direction.y = 1.0f;
			}
			else
			{
				if (pushback)
				{
					Move(0.0f, -intersectY * (1.0f - push));
					other.Move(0.0f, intersectY * push);
				}

				direction.x = 0.0f;
				direction.y = -1.0f;
			}
		}
		return true;
	}
	return false;
}
