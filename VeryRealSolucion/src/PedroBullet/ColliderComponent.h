#pragma once
#ifndef COLLIDERCOMPONENT
#define COLLIDERCOMPONENT
#include "exportPedroBullet.h"
#include <Component.h>

/*
* ColliderComponent es una clase cuyo objetivo es llamar a los metodos relacionados con colisiones de la clase Entity, sea se, OnCollisionEnter,OnCollisionStay.
* El proceso es:
*	1.- Se detecta una colision a traves de las funciones definidas en el PhysicManager
*	2.- Tras la deteccion se hacen varias comprobaciones como que las entidades no son nulas y que tienen ColliderComponent.
*	3.- Se llama al metodo de ColliderComponent (ej: OnCollisionEnter) y se le pasa la entidad con la que choca.
*	4.- Ese metodo llama al mismo metodo de Entity que propaga la llamada a todos los componentes.
*/
namespace VeryReal 
{
	class Entity;
	class VERYREAL_PEDROBULLET ColliderComponent : public Component
	{
	public:
        ColliderComponent(){};
		virtual ~ColliderComponent(){};
		void Init();
		void OnCollisionEnter(Entity* other) override;
		void OnCollisionStay(Entity* other) override;
	
	private:
	};

	}

#endif