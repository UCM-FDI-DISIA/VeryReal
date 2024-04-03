#include "CreatorMeshRenderComponent.h"
#include "MeshRenderComponent.h"
#include <string>

VeryReal::Component* VeryReal::CreatorMeshRenderComponent::CreatorSpecificComponent() { 
    return new MeshRenderComponent();
}

void VeryReal::CreatorMeshRenderComponent::SpecificInitComponent(Component* c) {
    MeshRenderComponent* m = static_cast<MeshRenderComponent*>(c);
    bool isstatic;
    std::string modelname, entityname, materialname;
    if (std::holds_alternative<std::string>(parameters_map.at("modelname")->GetVariant())) {
        modelname = std::get<std::string>(parameters_map.at("modelname")->GetVariant());
    }
    if (std::holds_alternative<std::string>(parameters_map.at("entityname")->GetVariant())) {
        entityname = std::get<std::string>(parameters_map.at("entityname")->GetVariant());
    }
    if (std::holds_alternative<std::string>(parameters_map.at("materialname")->GetVariant())) {
        materialname = std::get<std::string>(parameters_map.at("materialname")->GetVariant());
    }
    if (std::holds_alternative<bool>(parameters_map.at("isstatic")->GetVariant())) {
        isstatic = std::get<bool>(parameters_map.at("isstatic")->GetVariant());
    }
    bool b = m->InitComponent(isstatic, modelname, entityname, materialname);
    if (!b) {
        // Gestion error
    }
}
