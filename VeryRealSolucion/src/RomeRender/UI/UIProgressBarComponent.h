#pragma once
#ifndef UIPROGRESSBARCOMPONENT
#define UIPROGRESSBARCOMPONENT
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

    class VERYREAL_API UIProgressBarComponent : public Component {
      public:
        //constructora de la clase UIProgressBarComponent
        UIProgressBarComponent();
        // Destructor de la clase UIProgressBarComponent
        virtual ~UIProgressBarComponent();
        // Inicializa el componente
        bool InitComponent(double maximo, double progres, std::string progressBarName, std::string frameMaterial, std::string contentMaterial,
                           int order = 0);
        void Update(const double& dt) override;

        double getProgress();
        void setProgress(double progres);

        double getMaximun();
        void setMaximun(double maximo);

        //Establece el nombre del material del marco registrado con el sprite.
        void setFrameMaterialName(std::string materialName);

        //Establece el nombre del material del contenido de la progress bar registrado con el sprite.
        void setContentMaterialName(std::string materialName);

        //Establece el zOrder del Overlay.
        void setZOrder(int order);

        //Establece la posici�n y escala de la progress bar dentro de su overlay.
        void setProgressBarTransform(VeryReal::Vector2 pos, VeryReal::Vector2 sc, bool show = true);

      private:
        //Referencia al Overlay de Ogre.
        Ogre::Overlay* overlay;

        //Referencia al Overlay Manager de Ogre
        Ogre::OverlayManager* overlay_mgr;

        //Referencia al Overlay container de Ogre.
        Ogre::OverlayContainer* progress_bar_container;

        //Referencia al Overlay element de Ogre del marco de la progress bar. 
        Ogre::OverlayElement* frame_element;

        //Referencia al Overlay element de Ogre del contenido de la progress bar. 
        Ogre::OverlayElement* content_element;

        //Nombre con el que se registra la instancia de OverlayContainer.
        //(se recomienda que sea el mismo de la imagen registrada en el material)
        std::string progress_bar_name;

        //Nombre del material del frame registrado en el .material.
        std::string frame_material_name;

        //Nombre del material del contenido de la progress bar registrado en el .material.
        std::string content_material_name;

        //Orden con el que se renderizan los Overlays.
        // Cu�nto m�s alto sea el n�mero m�s prioridad de renderizado tendr� el overlay.
        int z_order;

        //Posici�n del sprite en la pantalla.
        // El (0,0) se encuentra en la esquina superior iozquierda de la pantalla.
        //La esquina inferior derecha de la pantalla representa la coordenada (1,1).
        VeryReal::Vector2 position;

        //Escala del sprite en pantalla.
        //Una escala de (1,1) representa que el sprite colocado en la coordenada (0,0) se ajusta a la altura y anchura de la pantalla.
        VeryReal::Vector2 scale;

        //Transform de UI asociado a este sprite.
        UITransformComponent* transform;
        //PRogress va de 0 a 1
        double max_progress = 1;
        double progress = 0;
    };
}
#endif   // !UIPROGRESSBARCOMPONENT
