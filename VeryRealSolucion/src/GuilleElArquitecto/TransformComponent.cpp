#include "TransformComponent.h"
void TransformComponent::translate(Vector3 translateposition) {
	position += translateposition;
}
void TransformComponent::rotate(Vector3 rotaterotation) {
	rotation += rotaterotation;
}
void TransformComponent::scaler(Vector3 scalerscale) {
	scale += scalerscale;
}