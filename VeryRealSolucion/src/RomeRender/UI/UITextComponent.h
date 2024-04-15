#pragma once
#ifndef UITEXTCOMPONENT
#define UITEXTCOMPONENT
#include "Component.h"
#include "string"
#include <Vector2.h>
#include <Vector3.h>
namespace Ogre {
class Overlay;
class OverlayElement;
class OverlayContainer;
class TextAreaOverlayElement;
class OverlayManager;
}
namespace VeryReal {
    class UITransformComponent;

    class UITextComponent : public Component {

      public:
        //constructora de la clase UITransformComponent
        UITextComponent();
        // Destructor de la clase UITransformComponent
        virtual ~UITextComponent();

        // Inicializa el componente
        bool InitComponent(std::string name, std::string font, int order, float height, VeryReal::Vector3 clr, std::string caption);
        bool InitComponent(std::string name, std::string font, int order, float height, VeryReal::Vector3 bottomcolor, VeryReal::Vector3 topcolor, std::string caption);

        void Update(const double& dt) override;

        //Establece el nombre del font registrado para el texto.
        void setFontName(std::string fontName);

        //Establece el zOrder del Overlay.
        void setZOrder(int order);

        //Establece el texto que ser� renderizado.
        void setCaption(std::string newCap);

        //Establece el tama�o de los car�cteres en relaci�n con el tama�o de la fuente.
        void setCharHeight(int height);


        //Establece el color del texto.
        void setColor(VeryReal::Vector3 newColor);

        //Establece el color de la parte superior del texto.
        void setTopColor(VeryReal::Vector3 newColor);

        //Establece el color de la parte inferior del texto.
        void setBottomColor(VeryReal::Vector3 newColor);

        //Establece la posici�n y escala del sprite dentro de su overlay.
        void setTextTransform(VeryReal::Vector2 pos, VeryReal::Vector2 sc, bool show = true);


      protected:
            //Referencia al Overlay de Ogre.
            Ogre::Overlay* overlay;

            //Referencia al Overlay container de Ogre.
            Ogre::OverlayContainer* text_container;

            //Referencia a la instancia de text area donde se renderiza el texto.
            Ogre::TextAreaOverlayElement* text_area;

            //Referencia al Overlay Manager de Ogre
            Ogre::OverlayManager* overlay_mgr;

            //Nombre con el que se registra la instancia de OverlayElement.
            std::string text_name;

            //Nombre del font registrado en el .fontdef.
            std::string font_name;

            //Orden con el que se renderizan los Overlays.
            // Cu�nto m�s alto sea el n�mero m�s prioridad de renderizado tendr� el overlay.
            int z_order;

            //Tama�o de los car�cteres en relaci�n con el tama�o de la fuente establecido en el .fontdef
            float char_height;

            //Color del texto.
            Vector3 color;
            
            //Color de la parte superior del texto.
            Vector3 color_top;

            //Color de la parte inferior del texto.
            Vector3 color_bottom;

            //Texto que ser� renderizado.
            std::string text_caption;

            //Posici�n del sprite en la pantalla.
            // El (0,0) se encuentra en la esquina superior iozquierda de la pantalla.
            //La esquina inferior derecha de la pantalla representa la coordenada (1,1).
            VeryReal::Vector2 position;

            //Escala del sprite en pantalla.
            //Una escala de (1,1) representa que el sprite colocado en la coordenada (0,0) se ajusta a la altura y anchura de la pantalla.
            VeryReal::Vector2 scale;

            //Transform de UI asociado a este sprite.
            UITransformComponent* transform;
       
    };

}
#endif // UITEXTCOMPONENT
