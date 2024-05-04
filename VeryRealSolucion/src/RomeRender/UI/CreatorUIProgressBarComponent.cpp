#include "UIProgressBarComponent.h"
#include <string>
#include "CreatorUIProgressBarComponent.h"
using namespace VeryReal;

Component* VeryReal::CreatorUIProgressBarComponent::CreatorSpecificComponent() { return new UIProgressBarComponent; }

void VeryReal::CreatorUIProgressBarComponent::SpecificInitComponent(Component* c) {
    UIProgressBarComponent* progressbar = static_cast<UIProgressBarComponent*>(c);
    double maximo, progres;
    std::string progressBarName, frameMaterial, contentMaterial;
    int zOrder;


#pragma region Maximo

    if (parameters_map.find("maximo") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("maximo")->GetVariant())) {
            maximo = std::get<float>(parameters_map.at("maximo")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para maximo este sera seteado por defecto" << std::endl;
            maximo = 1;
        }
    }
    else {
        std::cout << "No existe ningun parametro maximo este sera seteado por defecto" << std::endl;
        maximo = 1;
    }
#pragma endregion

#pragma region Progres

    if (parameters_map.find("progres") != parameters_map.end()) {
        if (std::holds_alternative<float>(parameters_map.at("progres")->GetVariant())) {
            progres = std::get<float>(parameters_map.at("progres")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para progres este sera seteado por defecto" << std::endl;
            progres = 0;
        }
    }
    else {
        std::cout << "No existe ningun parametro progres este sera seteado por defecto" << std::endl;
        progres = 0;
    }
#pragma endregion

#pragma region ProgressBarName

    if (parameters_map.find("progressBarName") != parameters_map.end()) {
        if (std::holds_alternative<std::string>(parameters_map.at("progressBarName")->GetVariant())) {
            progressBarName = std::get<std::string>(parameters_map.at("progressBarName")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para progressBarName este sera seteado por defecto" << std::endl;
            progressBarName = " ";
        }
    }
    else {
        std::cout << "No existe ningun parametro progressBarName este sera seteado por defecto" << std::endl;
        progressBarName = " ";
    }
#pragma endregion

#pragma region FrameMaterial

    if (parameters_map.find("frameMaterial") != parameters_map.end()) {
        if (std::holds_alternative<std::string>(parameters_map.at("frameMaterial")->GetVariant())) {
            frameMaterial = std::get<std::string>(parameters_map.at("frameMaterial")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para frameMaterial este sera seteado por defecto" << std::endl;
            frameMaterial = " ";
        }
    }
    else {
        std::cout << "No existe ningun parametro frameMaterial este sera seteado por defecto" << std::endl;
        frameMaterial = " ";
    }
#pragma endregion

#pragma region ContentMaterial

    if (parameters_map.find("contentMaterial") != parameters_map.end()) {
        if (std::holds_alternative<std::string>(parameters_map.at("contentMaterial")->GetVariant())) {
            contentMaterial = std::get<std::string>(parameters_map.at("contentMaterial")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para contentMaterial este sera seteado por defecto" << std::endl;
            contentMaterial = " ";
        }
    }
    else {
        std::cout << "No existe ningun parametro contentMaterial este sera seteado por defecto" << std::endl;
        contentMaterial = " ";
    }
#pragma endregion

#pragma region zOrder

    if (parameters_map.find("zOrder") != parameters_map.end()) {
        if (std::holds_alternative<int>(parameters_map.at("zOrder")->GetVariant())) {
            zOrder = std::get<int>(parameters_map.at("zOrder")->GetVariant());
        }
        else {
            std::cout << "No se ha especificado ningun valor para zOrder este sera seteado por defecto" << std::endl;
            zOrder = 0;
        }
    }
    else {
        std::cout << "No existe ningun parametro zOrder este sera seteado por defecto" << std::endl;
        zOrder = 0;
    }
#pragma endregion


    /*  if (std::holds_alternative<float>(parameters_map.at("maximo")->GetVariant())) {
        maximo = std::get<float>(parameters_map.at("maximo")->GetVariant());
    }
    if (std::holds_alternative<float>(parameters_map.at("progres")->GetVariant())) {
        progres = std::get<float>(parameters_map.at("progres")->GetVariant());
    }
    if (std::holds_alternative<std::string>(parameters_map.at("progressBarName")->GetVariant())) {
        progressBarName = std::get<std::string>(parameters_map.at("progressBarName")->GetVariant());
    }
    if (std::holds_alternative<std::string>(parameters_map.at("frameMaterial")->GetVariant())) {
        frameMaterial = std::get<std::string>(parameters_map.at("frameMaterial")->GetVariant());
    }
    if (std::holds_alternative<std::string>(parameters_map.at("contentMaterial")->GetVariant())) {
        contentMaterial = std::get<std::string>(parameters_map.at("contentMaterial")->GetVariant());
    }
    if (std::holds_alternative<int>(parameters_map.at("zOrder")->GetVariant())) {
        zOrder = std::get<int>(parameters_map.at("zOrder")->GetVariant());
    }*/

    bool b = progressbar->InitComponent(maximo, progres, progressBarName, frameMaterial, contentMaterial, zOrder);
    if (!b) {
        //Gestionar error
    }
}

void VeryReal::CreatorUIProgressBarComponent::SpecificInitComponentByCopy(Component* c, Component* other) {
    UIProgressBarComponent* progressbar = static_cast<UIProgressBarComponent*>(c);
    UIProgressBarComponent* copia = static_cast<UIProgressBarComponent*>(other);

    bool b = progressbar->InitComponent(copia->getMaximun(), copia->getProgress(), copia->GetProgressBarName(), copia->GetFrameMaterialName(),
                                        copia->GetContententMaterialName(), copia->GetZOrder());
    if (!b) {
        //Gestionar error
    }
}
