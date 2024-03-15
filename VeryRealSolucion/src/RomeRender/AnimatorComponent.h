#pragma once
#ifndef ANIMATIONCOMPONENT
#define ANIMATIONCOMPONENT
#include "Component.h"
#include <string>
#include <unordered_map>

namespace Ogre
{
	class AnimationState;
	class SceneManager;
	class Entity;
	class Animation;
	class KeyFrame;
	class AnimationStateSet;

}
namespace VeryReal {
	class MeshRenderComponent;
	class TransformComponent;
	class Vector3;
	class Vector4;

	class  AnimatorComponent : public Component
	{

		public:
			//constructora de la clase animación que es un componente de cualquier entidad que queramos que tenga movimiento
			AnimatorComponent();
			// Inicializa el componente con un nombre, un gestor de escena, y las componentes de transformación y renderizado de malla.
			bool InitComponent( std::string name);
			// Destructor de la clase AnimatorComponent.
			virtual ~AnimatorComponent(); 
			// Crea una animación con el nombre y la duración especificados.
			void createAnimation(std::string t_name, double t_duration);
			// Establece los fotogramas clave de una animación con la transformación especificada.
			void setFrameAnimation(std::string t_nameAnimation, double t_duration,
				Vector3 t_translate, Vector4 t_rotacion, Vector3 t_scale);
			// Activa o desactiva una animación según el nombre y el comportamiento de bucle.
			void setAnimation(std::string t_name, bool t_active, bool t_loop);
			// Activa o desactiva todas las animaciones.
			void allAnimations(bool t_active);
			// Obtiene el número de animaciones activas.
			int getAnimationsActive() { return num_animations_active; };
			// Actualiza el componente según el tiempo delta proporcionado.
			void Update(const double& dt) override;

		private:
			bool active;
			bool loop;
			std::unordered_map<std::string, Ogre::AnimationState*> animations;
			Ogre::SceneManager* scene_mngr;
			TransformComponent* transform;
			MeshRenderComponent* meshRender;
			int num_animations_active;
			std::string name;



	};

}
#endif // !ANIMATIONCOMPONENT