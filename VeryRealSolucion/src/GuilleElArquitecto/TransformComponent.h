#pragma once
#include "Component.h"
#include "Vector3.h"
class TransformComponent : public Component {
private:
	Vector3 position;
	Vector3 rotation;
	Vector3 scale;
public:
	TransformComponent();
	virtual ~TransformComponent();
	void Update();
	inline Vector3 GetPosition() { return position; }
	inline Vector3 GetRotation() { return rotation; }
	inline Vector3 GetScale() { return scale; }
	inline void SetPosition(Vector3 position) { this->position = position; }
	inline void SetRotation(Vector3 rotation) { this->rotation = rotation; }
	inline void SetScale(Vector3 scale) { this->scale = scale; }
	void translate(Vector3 translateposition);
	void rotate(Vector3 rotaterotation);
	void scaler(Vector3 scalerscale);
};