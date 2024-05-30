#include "Game.h"
#include "Box2DHelper.h"
#include <iostream>

Game::Game(int ancho, int alto, std::string titulo)
{
	wnd = new RenderWindow(VideoMode(ancho, alto), titulo);
	wnd->setVisible(true);
	fps = 60;
	wnd->setFramerateLimit(fps);
	frameTime = 1.0f / fps;
	SetZoom();
	InitPhysics();
}

void Game::Loop()
{
	while(wnd->isOpen())
	{
		wnd->clear(clearColor);
		DoEvents();
		CheckCollitions();
		UpdatePhysics();
		DrawGame();
		wnd->display();
	}
}

void Game::UpdatePhysics()
{
	phyWorld->Step(frameTime, 8, 8);
	phyWorld->ClearForces();
	phyWorld->DebugDraw();
}

void Game::DrawGame()
{ 
	// Dibujamos el suelo
	sf::RectangleShape groundShape(sf::Vector2f(200, 5));
	groundShape.setFillColor(sf::Color::Red);
	groundShape.setPosition(0, 195);
	wnd->draw(groundShape);

	// Dibujamos el techo
	sf::RectangleShape topShape(sf::Vector2f(200, 5));
	topShape.setFillColor(sf::Color::Green);
	topShape.setPosition(0,0);
	wnd->draw(topShape);

	// Dibujamos las paredes
	sf::RectangleShape leftWallShape(sf::Vector2f(5, 200)); // Alto de la ventana
	leftWallShape.setFillColor(sf::Color::Blue);
	leftWallShape.setPosition(0, 0); 
	wnd->draw(leftWallShape);

	sf::RectangleShape rightWallShape(sf::Vector2f(5, 200)); // Alto de la ventana
	rightWallShape.setFillColor(sf::Color::Cyan);
	rightWallShape.setPosition(195, 0);
	wnd->draw(rightWallShape);

	sf::RectangleShape cannonShape(sf::Vector2f(20, 20)); 
	cannonShape.setFillColor(sf::Color::Yellow);
	cannonShape.setPosition(20, 175);

	sf::RectangleShape staticShape(sf::Vector2f(10, 10));
	staticShape.setFillColor(sf::Color::Yellow);
	staticShape.setPosition(95, 95);
	wnd->draw(staticShape);
	
	for (size_t i = 0; i < ragdollList.size(); ++i) {
		Ragdoll ragdoll = ragdollList[i];
		ragdoll.Actualizar();
		ragdoll.Dibujar(*wnd);
	}

	wnd->draw(cannonShape);
	ballAvatar->Actualizar();
	ballAvatar->Dibujar(*wnd);

}

void Game::DoEvents()
{
	Event evt;
	
	while(wnd->pollEvent(evt))
	{
		switch(evt.type)
		{
			case Event::Closed:
				wnd->close();
				break;
			case Event::MouseButtonPressed:
				if (evt.key.code == Mouse::Button::Left)
				{
					Vector2i mousePos = Mouse::getPosition(*wnd);
					Vector2f worldMousePos = wnd->mapPixelToCoords(mousePos);

					Ragdoll* ragdoll = new Ragdoll(*phyWorld);
					b2Vec2 direction = b2Vec2(worldMousePos.x - ragdoll->GetChestPosition().x, worldMousePos.y - ragdoll->GetChestPosition().y); //Nuestro ragdoll siempre aparecera en el mismo lugar

					ragdoll->ApplyLinearImpulseToChestCenter(b2Vec2(direction.x * 100.0f, direction.y * 100.0f), true);
					ragdollList.push_back(*ragdoll);
				}
				break;
		}
	}
	
}

void Game::CheckCollitions()
{
	// Veremos mas adelante
}

// Definimos el area del mundo que veremos en nuestro juego
// Box2D tiene problemas para simular magnitudes muy grandes
void Game::SetZoom()
{
	View camara;
	// Posicion del view
	camara.setSize(200.0f, 200.0f); //Puse la camara mas grande para no jugar con la escala del ragdoll
	camara.setCenter(100.0f, 100.0f);
	wnd->setView(camara); //asignamos la camara
}

void Game::InitPhysics()
{
	phyWorld = new b2World(b2Vec2(0.0f, 9.8f));
	debugRender = new SFMLRenderer(wnd);
	phyWorld->SetDebugDraw(debugRender);

	// Creamos un piso, techo y paredes
	b2Body* topBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 200, 5);
	topBody->SetTransform(b2Vec2(100, 2.5f), 0.0f);

	b2Body* groundBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 200, 5);
	groundBody->SetTransform(b2Vec2(100, 197.5), 0.0f);
	groundBody->GetFixtureList()->SetFriction(0.2f);

	b2Body* leftWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 5, 200);
	leftWallBody->SetTransform(b2Vec2(2.5f, 100), 0.0f);

	b2Body* rightWallBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 5, 200);
	rightWallBody->SetTransform(b2Vec2(197.5, 100), 0.0f);

	
	b2Body* staticBody = Box2DHelper::CreateRectangularStaticBody(phyWorld, 10, 10);
	staticBody->SetTransform(b2Vec2(100, 100), 0.0f);

	dynamicBallBody = Box2DHelper::CreateCircularDynamicBody(phyWorld, 5, 1.0f, 0.5, 0.5f);
	dynamicBallBody->SetTransform(b2Vec2(100.0f, 90.0f), 0.0f);

	// Carga la textura de la pelota para el avatar
	texturaPelota.loadFromFile("Pelota.png");

	// Inicializa el avatar del jugador con el cuerpo físico creado y la textura de la pelota
	ballAvatar = new Avatar(dynamicBallBody, new sf::Sprite(texturaPelota));
}

Game::~Game(void)
{ }