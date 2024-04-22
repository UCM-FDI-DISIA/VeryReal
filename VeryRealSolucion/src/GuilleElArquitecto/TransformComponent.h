#pragma once
#ifndef TRANSFORMCOMPONENT
#define TRANSFORMCOMPONET
#include "Component.h"
#include "Vector3.h"
namespace VeryReal {
	
	class VERYREAL_API TransformComponent : public Component {
	private:
		Vector3 position;
		Vector3 rotation;
		Vector3 scale;
		int a = 0;
	public:
		TransformComponent();
		bool InitComponent(int a,Vector3 position, Vector3 rotation, Vector3 scale);
		virtual ~TransformComponent();

		inline Vector3 GetPosition() { return position; }
		inline Vector3 GetRotation() { return rotation; }
		inline Vector3 GetScale() { return scale; }

		inline void SetPosition(Vector3 position) { this->position = position; }
		inline void SetRotation(Vector3 rotation) { this->rotation = rotation; }
		inline void SetScale(Vector3 scale) { this->scale = scale; }

		void Translate(Vector3 translateposition);
		void Rotate(Vector3 rotaterotation);
		void Scaler(Vector3 scalerscale);

		/*
		Vector Up del componente transform.
		@return El valor del vector Up en el eje Y.		
		*/
        Vector3 up();

        /*
		Vector Forward del componente transform.
		@return El valor en Vector3 de forward a lo largo del eje Z.
		*/
        Vector3 forward();

        VeryReal::Vector3 getFacingDirection();
    };

	
}
#endif