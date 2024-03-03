#pragma once
#ifndef TRANSFORMCOMPONENT
#define TRANSFORMCOMPONET
#include "Component.h"
#include "Vector3.h"
//class Component; PREGUNTAR
namespace VeryReal {
	class TransformComponent : public Component {
	private:
		VeryReal::Vector3 position;
		VeryReal:: Vector3 rotation;
		VeryReal::Vector3 scale;
	public:
		TransformComponent();
		TransformComponent(VeryReal::Vector3 position, VeryReal::Vector3 rotation, VeryReal::Vector3 scale);
		virtual ~TransformComponent();

		inline VeryReal::Vector3 GetPosition() { return position; }
		inline VeryReal::Vector3 GetRotation() { return rotation; }
		inline VeryReal::Vector3 GetScale() { return scale; }

		inline void SetPosition(VeryReal::Vector3 position) { this->position = position; }
		inline void SetRotation(VeryReal::Vector3 rotation) { this->rotation = rotation; }
		inline void SetScale(VeryReal::Vector3 scale) { this->scale = scale; }

		void Translate(VeryReal::Vector3 translateposition);
		void Rotate(VeryReal::Vector3 rotaterotation);
		void Scaler(VeryReal::Vector3 scalerscale);
	};
}
#endif