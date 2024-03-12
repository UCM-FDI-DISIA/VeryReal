#pragma once
#ifndef COLLIDER
#define COLLIDER

#include <Component.h>


//Collider es una clase cuya única función es la de llamar a los métodos pertinentes de la clase Entity y estos metodos llamarán a métodos los homonimos.
//El proceso es:
	// 1.- Se detecta una colisión a través de las funciones callback definidas en PedroBullet
	// 2.- Se comprueba que ambos objetos físicos tienen el componente Collider
namespace VeryReal 
{
	class Entity;
	class Collider : public VeryReal::Component
	{
	public:
		Collider();
		virtual ~Collider();
		void Init();
		void OnCollisionEnter(Entity* other) override;
		void OnCollisionStay(Entity* other) override;
		void OnCollisionExit(Entity* other) override;
	private:
	};

	}

#endif