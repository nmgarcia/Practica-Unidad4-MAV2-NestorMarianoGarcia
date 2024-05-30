#pragma once
#include <SFML/Graphics.hpp>
#include <SFML/System.hpp>
#include "SFMLRenderer.h"
#include "Ragdoll.h"

using namespace sf;
using namespace std;

class Game
{
private:
	// Propiedades de la ventana
	int alto;
	int ancho;
	RenderWindow* wnd;
	Color clearColor;

	// Objetos de box2d
	b2World* phyWorld;
	SFMLRenderer* debugRender;

	//tiempo de frame
	float frameTime;
	int fps;

	vector<Ragdoll> ragdollList;
	b2Body* dynamicBallBody;
	Avatar* ballAvatar;
	Texture texturaPelota;


public:

	// Constructores, destructores e inicializadores
	Game(int ancho, int alto,std::string titulo);
	void CheckCollitions();
	~Game(void);
	void InitPhysics();

	// Main game loop
	void Loop();
	void DrawGame();
	void UpdatePhysics();
	void DoEvents();
	void SetZoom();
};

