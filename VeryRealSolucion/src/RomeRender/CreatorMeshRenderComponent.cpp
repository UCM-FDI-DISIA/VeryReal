#include "CreatorMeshRenderComponent.h"
#include "MeshRenderComponent.h"
VeryReal::Component* VeryReal::CreatorMeshRenderComponent::CreatorSpecificComponent() {
	return new VeryReal::MeshRenderComponent();
}
