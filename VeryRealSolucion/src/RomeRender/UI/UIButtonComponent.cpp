#include "UIButtonComponent.h"
#include "Entity.h"
#include "UItransformComponent.h"
#include "InputManager.h"
#include "TonMapeo.h"
using namespace VeryReal;
     
    //constructora de la clase UIButtomComponent
UIButtomComponent::UIButtomComponent() { 
      if (GetEntity()->HasComponent("UITransformComponent")) UItransofrm = GetEntity()->GetComponent<UITransformComponent>();

}
    // Destructor de la clase UIButtomComponent
UIButtomComponent::~UIButtomComponent() {

}
    // Inicializa el componente
bool UIButtomComponent::InitComponent() { 

  return true;
}
// 
void UIButtomComponent::Update(const double& dt)  {
    //si esta oculto no se hace nada
    if (!UItransofrm->isHidden())
    mousePosition();
}

 
 //metodo que llama cuando se haga click en el boton
void UIButtomComponent::OnButtonClick() {
    isclicked = true;
}
//metodo que compueba en todo momento las posiciones del raton 
void UIButtomComponent::mousePosition() { 
    std::pair<int, int> mouseposition = InputManager::Instance()->GetMousePos();
    Vector2 positionobj = UItransofrm->getPosition();
    Vector2 dimensionobj = UItransofrm->getSize();

    if (mouseposition.first > positionobj.GetX() && mouseposition.first < positionobj.GetX()+ dimensionobj.GetX() 
        &&
        mouseposition.second > positionobj.GetY() && mouseposition.second < positionobj.GetY() + dimensionobj.GetY()
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
   