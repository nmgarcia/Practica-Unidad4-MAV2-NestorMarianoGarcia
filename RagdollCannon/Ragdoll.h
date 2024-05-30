#pragma once
#include "Avatar.h"
#include "Box2DHelper.h"

class Ragdoll
{
private:
	b2Body* headBody;
	Avatar* headAvatar;

	b2Body* chestBody;
	Avatar* chestAvatar;

	b2Body* rightArmBody;
	Avatar* rightArmAvatar;

	b2Body* leftArmBody;
	Avatar* leftArmAvatar;

	b2Body* rightLegBody;
	Avatar* rightLegAvatar;

	b2Body* leftLegBody;
	Avatar* leftLegAvatar;

	sf::Texture texture;
public:
	Ragdoll(b2World& phyWorld);
	void Dibujar(sf::RenderWindow& RW);
	void Actualizar();
	void SetAwake(bool awake);
};

