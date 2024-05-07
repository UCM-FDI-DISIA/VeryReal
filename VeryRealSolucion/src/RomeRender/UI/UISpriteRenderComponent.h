#pragma once
#ifndef UISPRITERENDERCOMPONENT
#define UISPRITERENDERCOMPONENT
#include "Component.h"
#include "Vector2.h"
#include "string"
#include "../exportRomeRender.h"

namespace Ogre {
class Overlay;
class OverlayElement;
class OverlayContainer;
class OverlayManager;
}

#pragma warning(disable : 4251)

namespace VeryReal {
    class UITransformComponent;

    class VERYREAL_ROMERENDER UISpriteRendererComponent : public Component {
          public:
            //constructora de la clase UISpriteRendererComponentComponent
      UISpriteRendererComponent();
                // Destructor de la clase UISpriteRendererComponentComponent
      virtual ~UISpriteRendererComponent();
            // Inicializa el componente
            std::pair<bool, std::string> InitComponent(std::string name, std::string material, int order);
            void Update(const double& dt) override;

            //Establece el nombre del material registrado con el sprite.
            void setMaterialName(std::string materialName);

            //Establece el zOrder del Overlay.
            void setZOrder(int order);

            void setVisibility(bool hide = false);

            //Establece la posici�n y escala del sprite dentro de su overlay.
            void setSpriteTransform(VeryReal::Vector2 pos, VeryReal::Vector2 sc);
            //metodo que escala la imagen
            void setScale(VeryReal::Vector2 sc);
            //metodo que cambia la imagen de posicion
            void setPosition(VeryReal::Vector2 pos);

            inline std::string GetSpriteName() { return sprite_name; }
            inline std::string GetMaterialName() { return material_name; }
            inline int GetZOrder() { return z_order; }


          protected:      

              //Referencia al Overlay de Ogre.
              Ogre::Overlay* overlay = nullptr;

              //Referencia al Overlay container de Ogre.
              Ogre::OverlayContainer* sprite_container = nullptr;;

              //Referencia al Overlay Manager de Ogre
              Ogre::OverlayManager* overlay_mgr = nullptr;

              //Nombre con el que se registra la instancia de OverlayContainer.
              //(se recomienda que sea el mismo de la imagen registrada en el material)
              std::string sprite_name = "";

              //Nombre del material registrado en el .material.
              std::string material_name = "";

              //Orden con el que se renderizan los Overlays.
              // Cu�nto m�s alto sea el n�mero m�s prioridad de renderizado tendr� el overlay.
              int z_order = 0;

              //Posici�n del sprite en la pantalla.
              // El (0,0) se encuentra en la esquina superior iozquierda de la pantalla.
              //La esquina inferior derecha de la pantalla representa la coordenada (1,1).
              VeryReal::Vector2 position;

              //Escala del sprite en pantalla.
              //Una escala de (1,1) representa que el sprite colocado en la coordenada (0,0) se ajusta a la altura y anchura de la pantalla.
              VeryReal::Vector2 scale;

              //Transform de UI asociado a este sprite.
              UITransformComponent* transform = nullptr;
    };
}

#pragma warning(default : 4251)

#endif   // !UISPRITERENDERCOMPONENT
