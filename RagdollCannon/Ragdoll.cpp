#include "Ragdoll.h"

Ragdoll::Ragdoll(b2World& phyWorld)
{
	//TODO: Hacer que reciba posicion de inicio y escala a usar, por el momento a fines del TP apareceran siempre en el mismo lugar

	//En x restamos 5 y en Y sumamos 0
	headBody = Box2DHelper::CreateRectangularDynamicBody(&phyWorld, 4.0f, 4.0f, 0.8f, 0.5f, 0.5f);
	headBody->SetTransform(b2Vec2(25, 165), 0.0f);

	chestBody = Box2DHelper::CreateRectangularDynamicBody(&phyWorld, 6.0f, 10.0f, 3.0f, 0.5f, 0.5f);
	chestBody->SetTransform(b2Vec2(25, 173), 0.0f);

	leftArmBody = Box2DHelper::CreateRectangularDynamicBody(&phyWorld, 2.0f, 8.0f, 0.2f, 0.5f, 0.1f);
	leftArmBody->SetTransform(b2Vec2(21, 172), 0.0f);

	rightArmBody = Box2DHelper::CreateRectangularDynamicBody(&phyWorld, 2.0f, 8.0f, 0.2f, 0.5f, 0.1f);
	rightArmBody->SetTransform(b2Vec2(29, 172), 0.0f);

	leftLegBody = Box2DHelper::CreateRectangularDynamicBody(&phyWorld, 2.0f, 10.0f, 0.4f, 0.5f, 0.1f);
	leftLegBody->SetTransform(b2Vec2(23, 184), 0.0f);

	rightLegBody = Box2DHelper::CreateRectangularDynamicBody(&phyWorld, 2.0f, 10.0f, 0.4f, 0.5f, 0.1f);
	rightLegBody->SetTransform(b2Vec2(27, 184), 0.0f);

	// Atamos las partes mediante resortes
	//NOTA: Al utilizar el getworldpoint las coordenadas pasan a ser desde el origen de la pieza
	Box2DHelper::CreateDistanceJoint(&phyWorld, headBody, headBody->GetWorldPoint(b2Vec2(0, 2)),
		chestBody, chestBody->GetWorldPoint(b2Vec2(0, -5)), 0.25f, 2.0f, 1.0f);
	Box2DHelper::CreateDistanceJoint(&phyWorld, leftArmBody, leftArmBody->GetWorldPoint(b2Vec2(1, -4)),
		chestBody, chestBody->GetWorldPoint(b2Vec2(-3.0f, -4.5)), 0.25f, 2.0f, 1.0f);
	Box2DHelper::CreateDistanceJoint(&phyWorld, rightArmBody, rightArmBody->GetWorldPoint(b2Vec2(-1, -4)),
		chestBody, chestBody->GetWorldPoint(b2Vec2(3.0f, -4.5)), 0.25f, 2.0f, 1.0f);
	Box2DHelper::CreateDistanceJoint(&phyWorld, leftLegBody, leftLegBody->GetWorldPoint(b2Vec2(0.0, -5)),
		chestBody, chestBody->GetWorldPoint(b2Vec2(-1, 5.0)), 0.25f, 10.0f, 1.0f);
	Box2DHelper::CreateDistanceJoint(&phyWorld, rightLegBody, rightLegBody->GetWorldPoint(b2Vec2(0.0, -5)),
		chestBody, chestBody->GetWorldPoint(b2Vec2(1, 5.0)), 0.25f, 10.0f, 1.0f);

	// Carga la textura de la pelota para el avatar, decidi dejarla para ver como funcionaba con sprites

	texture.loadFromFile("Box.png");

	// Inicializa el avatar del jugador con el cuerpo físico creado y la textura de la pelota
	headAvatar = new Avatar(headBody, new sf::Sprite(texture));
	chestAvatar = new Avatar(chestBody, new sf::Sprite(texture));
	leftArmAvatar = new Avatar(leftArmBody, new sf::Sprite(texture));
	rightArmAvatar = new Avatar(rightArmBody, new sf::Sprite(texture));
	leftLegAvatar = new Avatar(leftLegBody, new sf::Sprite(texture));
	rightLegAvatar = new Avatar(rightLegBody, new sf::Sprite(texture));

}
void Ragdoll::Dibujar(sf::RenderWindow& RW)
{	
	headAvatar->Dibujar(RW);
	chestAvatar->Dibujar(RW);
	leftArmAvatar->Dibujar(RW);
	rightArmAvatar->Dibujar(RW);
	leftLegAvatar->Dibujar(RW);
	rightLegAvatar->Dibujar(RW);
}

void Ragdoll::Actualizar()
{
	headAvatar->Actualizar();
	chestAvatar->Actualizar();
	leftArmAvatar->Actualizar();
	rightArmAvatar->Actualizar();
	leftLegAvatar->Actualizar();
	rightLegAvatar->Actualizar();
}

void Ragdoll::SetAwake(bool awake)
{
	headAvatar->SetAwake(awake);
	chestAvatar->SetAwake(awake);
	leftArmAvatar->SetAwake(awake);
	rightArmAvatar->SetAwake(awake);
	leftLegAvatar->SetAwake(awake);
	rightLegAvatar->SetAwake(awake);
}

b2Vec2 Ragdoll::GetChestPosition()
{
	return chestBody->GetPosition();
}

void Ragdoll::ApplyLinearImpulseToChestCenter(b2Vec2 direction, bool awake)
{
	chestBody->ApplyLinearImpulseToCenter(b2Vec2(direction.x, direction.y), awake);
}

