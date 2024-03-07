#include "CreatorMeshRenderComponent.h"
#include "MeshRender.h"
VeryReal::Component* VeryReal::CreatorMeshRenderComponent::CreatorSpecificComponent() {
	return new VeryReal::MeshRender();
}
