#pragma once
#ifndef UISPRITERENDERCOMPONENT
#define UISPRITERENDERCOMPONENT
#include "Component.h"
#include "Vector2.h"
#include "string"

namespace Ogre {
class Overlay;
class OverlayElement;
class OverlayContainer;
class OverlayManager;
}

namespace VeryReal {
    class UITransformComponent;

    class VERYREAL_API UiSpriteRenderer : public Component {
          public:
            //constructora de la clase UiSpriteRendererComponent
            UiSpriteRenderer();
                // Destructor de la clase UiSpriteRendererComponent
            virtual ~UiSpriteRenderer();
            // Inicializa el componente
            bool InitComponent(std::string name, std::string material, int order);
            void Update(const double& dt) override;

            //Establece el nombre del material registrado con el sprite.
            void setMaterialName(std::string materialName);

            //Establece el zOrder del Overlay.
            void setZOrder(int order);

            //Establece la posición y escala del sprite dentro de su overlay.
            //Establece la rotación del overlay en el que se representa
            void setSpriteTransform(VeryReal::Vector2 pos, VeryReal::Vector2 dimension);

                void demo();

          protected:      

              //Referencia al Overlay de Ogre.
              Ogre::Overlay* overlay;

              //Referencia al Overlay container de Ogre.
              Ogre::OverlayContainer* sprite;

              //Referencia al Overlay Manager de Ogre
              Ogre::OverlayManager* overlay_mgr;

              //Nombre con el que se registra la instancia de OverlayElement.
              //(se recomienda que sea el mismo de la imagen registrada en el material)
              std::string sprite_name;

              //Nombre del material registrado en el .material.
              std::string material_name;

              //Orden con el que se renderizan los Overlays.
              // Cuánto más alto sea el número más prioridad de renderizado tendrá el overlay.
              int z_order;

              //Posición del sprite en la pantalla.
              // El (0,0) se encuentra en la esquina superior iozquierda de la pantalla.
              //La esquina inferior derecha de la pantalla representa la coordenada (1,1).
              VeryReal::Vector2 position;

              //Escala del sprite en pantalla.
              VeryReal::Vector2 scale;

              //Transform de UI asociado a este sprite.
              UITransformComponent* transform;
    };
}
#endif   // !UISPRITERENDERCOMPONENT
