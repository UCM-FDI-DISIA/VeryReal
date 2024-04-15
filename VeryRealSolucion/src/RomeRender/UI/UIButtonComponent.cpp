#include "UIButtonComponent.h"
#include "Entity.h"
#include "../RenderManager.h"
#include "../Window.h"
#include "UItransformComponent.h"
#include "InputManager.h"
#include "TonMapeo.h"
using namespace VeryReal;
     
    //constructora de la clase UIButtomComponent
UIButtonComponent::UIButtonComponent() { 
      if (GetEntity()->HasComponent("UITransformComponent")) UItransform = GetEntity()->GetComponent<UITransformComponent>();

}
    // Destructor de la clase UIButtomComponent
UIButtonComponent::~UIButtonComponent() {

}
    // Inicializa el componente
bool UIButtonComponent::InitComponent() { 

  return true;
}
// 
void UIButtonComponent::Update(const double& dt) {
    //si esta oculto no se hace nada
    if (!UItransform->isHidden())
    mousePosition();
}

 
 //metodo que llama cuando se haga click en el boton
void UIButtonComponent::OnButtonClick() {
    isclicked = true;
    accion();
}
//metodo que compueba en todo momento las posiciones del raton 
void UIButtonComponent::mousePosition() { 
    std::pair<int, int> mouseposition = InputManager::Instance()->GetMousePos();
    std::pair<int, int> windowDimensions = VeryReal::RenderManager::Instance()->GetVRWindow()->GetWindowHeightWidth();
    Vector2 positionobj = UItransform->getPosition();
    Vector2 scaleobj = UItransform->getScale();

    if (mouseposition.first > (positionobj.GetX() * windowDimensions.first) && 
        mouseposition.first < (positionobj.GetX() * windowDimensions.first) + (windowDimensions.first * scaleobj.GetX()) && 
        mouseposition.second > (positionobj.GetY() * windowDimensions.second) && 
        mouseposition.second < (positionobj.GetY() * windowDimensions.second) + (windowDimensions.second * scaleobj.GetY())
        && isclicked ==false) {
    //si entra es que está dentro del recuadro y no esta marcado como  clickado 
         overbuttom = true;
        if (InputManager::Instance()->GetMouseButtonState(TI_MOUSE_LEFT)) {
            // si esta haciendo click
            OnButtonClick();
        }
       

    }
    else {
        overbuttom = false;
    }

}
   