#pragma once
#ifndef TRANSFORMCOMPONENT
#define TRANSFORMCOMPONET
#include "Component.h"
#include "Vector3.h"
#include "Vector4.h"

namespace VeryReal {
	class VERYREAL_GUILLEELARQUITECTO TransformComponent : public Component {
	private:
		Vector3 position;
		Vector3 rotationInit;
		Vector4 rotation;
		Vector3 scale;
		Vector3 velocity;
	public:
		TransformComponent();
		bool InitComponent(Vector3 position, Vector3 rotation, Vector3 scale);
		virtual ~TransformComponent();

		inline Vector3 GetPosition() { return position; }
		inline Vector4 GetRotation() { return rotation; }
        inline Vector3 GetRotationInit() { return rotationInit; }
		inline Vector3 GetScale() { return scale; }
		inline Vector3 GetVelocity() { return velocity; }

		inline void SetPosition(Vector3 position) { this->position = position; }
		inline void SetRotation(Vector4 rotation) { this->rotation = rotation; }
		inline void SetScale(Vector3 scale) { this->scale = scale; }
        inline void SetVelocity(Vector3 velocity) { this->velocity = velocity; }

		void Translate(Vector3 translateposition);
		void Rotate(Vector3 rotaterotation);
		void Scaler(Vector3 scalerscale);

		/*
		Vector Up del componente transform.
		@return El valor del vector Up en el eje Y.		
		*/
        VeryReal::Vector3 up();

        VeryReal::Vector3 getFacingDirection();
    };

	
}
#endif