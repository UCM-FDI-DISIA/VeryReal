#include "UIProgressBarComponent.h"
#include "../RenderManager.h"
#include "../conversorvectores.h"
#include "UITransformComponent.h"
#include "Entity.h"

#pragma warning(disable : 4251)
#include <OgreOverlayManager.h>
#include <OgreOverlay.h>
#include <OgreOverlaySystem.h>
#include <OgreTextAreaOverlayElement.h>
#include <OgreOverlayContainer.h>
#include <OgreOverlayElement.h>
#include <Ogre.h>
#pragma warning(default : 4251)

using namespace VeryReal;

    //constructora de la clase UIProgressBarComponent
    UIProgressBarComponent::UIProgressBarComponent() {

    }
    // Destructor de la clase UIProgressBarComponent
    UIProgressBarComponent::~UIProgressBarComponent() {

    }
    // Inicializa el componente
    bool UIProgressBarComponent::InitComponent(double maximo, double progres, std::string progressBarName,
                                               std::string frameMaterial, std::string contentMaterial, int order) { 
        max_progress = maximo;
        progress = progres;

        progress_bar_name = progressBarName;
        frame_material_name = frameMaterial;
        content_material_name = contentMaterial;
        z_order = order;
        overlay_mgr = VeryReal::RenderManager::Instance()->GetOverlayManager();
        overlay = overlay_mgr->create(progressBarName + "Overlay");
        progress_bar_container = dynamic_cast<Ogre::OverlayContainer*>(overlay_mgr->createOverlayElement("Panel", progressBarName + "Panel"));
        frame_element = overlay_mgr->createOverlayElement("Panel", progressBarName + "Frame");
        content_element = overlay_mgr->createOverlayElement("Panel", progressBarName + "Content");

        transform = GetEntity()->GetComponent<UITransformComponent>();

        //if (!transform) {
        //    ErrorInf().showErrorMessageBox("UiSpriteRenderer error", "An entity doesn't have transform component", EI_ERROR);
        //    //sceneManager().quit();
        //    return false;
        //}

        setProgressBarTransform(transform->getPosition(), transform->getScale());
        overlay->add2D(progress_bar_container);
        overlay->setZOrder(order);
        frame_element->setMaterialName(frame_material_name);
        content_element->setMaterialName(content_material_name);
        overlay->show();
        return true;
    }
    void UIProgressBarComponent::Update(const double& dt) {
        content_element->setDimensions(progress, 1);
        setProgressBarTransform(transform->getPosition(), transform->getScale(), transform->isHidden());
    }
    double UIProgressBarComponent::getProgress() { 
        return progress;
    }
    void UIProgressBarComponent::setProgress(double progres) {
        if (progress > max_progress) return;
        progress = progres;
    }
    double UIProgressBarComponent::getMaximun() { 
        return max_progress;
    }
    void UIProgressBarComponent::setMaximun(double maximo) { max_progress = maximo; }

    void VeryReal::UIProgressBarComponent::setFrameMaterialName(std::string materialName) {
        frame_material_name = materialName;
        frame_element->setMaterialName(materialName);
    }

    void VeryReal::UIProgressBarComponent::setContentMaterialName(std::string materialName) { 
        content_material_name = materialName;
        content_element->setMaterialName(materialName);
    }

    void VeryReal::UIProgressBarComponent::setZOrder(int order) {
        z_order = order;
        overlay->setZOrder(order);
    }

    void VeryReal::UIProgressBarComponent::setProgressBarTransform(VeryReal::Vector2 pos, VeryReal::Vector2 sc, bool show) {
        progress_bar_container->setPosition(pos.GetX(), pos.GetY());
        position = pos;
        progress_bar_container->setDimensions(sc.GetX(), sc.GetY());
        scale = sc;
    }


  
