#include "CreatorMeshRenderComponent.h"
#include "MeshRenderComponent.h"
#include <string>

VeryReal::Component* VeryReal::CreatorMeshRenderComponent::CreatorSpecificComponent() { return new MeshRenderComponent(); }


std::pair<bool, std::string> VeryReal::CreatorMeshRenderComponent::SpecificInitComponent(Component* c) {
    MeshRenderComponent* m = static_cast<MeshRenderComponent*>(c);
    bool isstatic;
    std::string modelname, entityname, materialname;


#pragma region ModelName

    if (parameters_map.find("modelname") != parameters_map.end()) {
        if (std::holds_alternative<std::string>(parameters_map.at("modelname")->GetVariant())) {
            modelname = std::get<std::string>(parameters_map.at("modelname")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para modelname este sera seteado por defecto" << std::endl;
            modelname = " ";
        }
    }
    else {
        std::cout << "No existe ningun parametro modelname este sera seteado por defecto" << std::endl;
        modelname = " ";
    }
#pragma endregion

#pragma region EntityName

    if (parameters_map.find("entityname") != parameters_map.end()) {
        if (std::holds_alternative<std::string>(parameters_map.at("entityname")->GetVariant())) {
            entityname = std::get<std::string>(parameters_map.at("entityname")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para entityname este sera seteado por defecto" << std::endl;
            entityname = " ";
        }
    }
    else {
        std::cout << "No existe ningun parametro entityname este sera seteado por defecto" << std::endl;
        entityname = " ";
    }
#pragma endregion

#pragma region MaterialName
    if (parameters_map.find("materialname") != parameters_map.end()) {
        if (std::holds_alternative<std::string>(parameters_map.at("materialname")->GetVariant())) {
            materialname = std::get<std::string>(parameters_map.at("materialname")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para materialname este sera seteado por defecto" << std::endl;
            materialname = " ";
        }
    }
    else {
        std::cout << "No existe ningun parametro materialname este sera seteado por defecto" << std::endl;
        materialname = " ";
    }
#pragma endregion

#pragma region IsStatic
    if (parameters_map.find("isstatic") != parameters_map.end()) {
        if (std::holds_alternative<bool>(parameters_map.at("isstatic")->GetVariant())) {
            isstatic = std::get<bool>(parameters_map.at("isstatic")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para isstatic este sera seteado por defecto" << std::endl;
            isstatic = false;
        }
    }
    else {
        std::cout << "No existe ningun parametro isstatic este sera seteado por defecto" << std::endl;
        isstatic = false;
    }
#pragma endregion


    /* if (std::holds_alternative<std::string>(parameters_map.at("modelname")->GetVariant())) {
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
    }*/

    return m->InitComponent(isstatic, modelname, entityname, materialname);
}


std::pair<bool, std::string> VeryReal::CreatorMeshRenderComponent::SpecificInitComponentByCopy(VeryReal::Component* c, VeryReal::Component* other) {
    MeshRenderComponent* a = static_cast<MeshRenderComponent*>(c);
    MeshRenderComponent* copia = static_cast<MeshRenderComponent*>(other);

    bool isstatic = false;
    std::string modelname = copia->getMeshName(), entityname = copia->getNameEntity(), materialname = copia->getMaterialName();

    return a->InitComponent(isstatic, modelname, entityname, materialname);
}