# Proyecto 3 - MOTOR VERYREAL
<br>

## Estructura del Motor:
Contamos con 1 solución con varios Proyectos en ella. Estos están definidos uno por cada módulo o parte diferenciada en el motor:

<br>

### AudioLeon
<br>



### GuilleElArquitecto
<br>
.
.
.


### LuaLuengo
<br>


### PedroBullet
<br>


### RomeRender
RomeRender es el proyecto encargado de toda la parte de renderizado del motor, esto lo hace mediante Ogre. Para ello esta formado por una serie de clases que tienen las siguientes
funcionalidades:
        - RenderManager: Manager que se encarga de la inicialización de Ogre a partir de los archivos .cfgs, también se encarga del renderizado de cada frame en su Update y de la carga de
        shaders y recursos. Para finalizar, se encarga también de la creación de nodos para dar al usuario una interfaz desde la que gestionar estos.

        - Window: Clase creada para gestionar la funcionalidad de la pantalla, esta es creada con SDL externamente y pasada a Ogre como ventana externa.

        También contamos con una serie de componentes que nos darán distintas funcionalidades bases y esenciales para el desarrollo de juegos:

        -LightComponet_: Componente que funciona como wrapper de la luz de ogre.

        -AnimatorComponent: Componente que se enacarga del cargado y uso de animaciones, además de su gestión.

        -CameraComponent: Componente que añade una camará al escenario, también funciona como wrapper de la cámara de ogre.

        -MeshRendererComponent: Componente encargado del renderizados de los .mesh y materiales de las entidades.


<br>



### TonInput <br>

TonInput es el proyecto encargado del input del motor a través de SDL. Para ello se vale de un manager con funciones y variables para manejar los eventos tanto de teclado, ratón como de mando. Clases implicadas:

        - InputManager: manager que se encarga de actualizar los estados del ratón, teclado y mando. En el método Update compruebará si se ha dado algún tipo de evento y lo gestiona en caso de que se haya dado. 

        - TonMapeo: clase que contiene enums para el parseo entre variables de SDL y nuestras propias variables.



<br>

Actualmente también contamos con 2 Proyectos por Módulo:
· El proyecto en si que es la biblioteca
· El proyecto llamado "modulo_test" que nos sirve temporalmente para hacer pruebas de ese módulo




## Autores
<br>

- [Pablo Cao](https://github.com/Cao33).
- [ Agustín Castro](https://github.com/AgusCDT).
- [Pablo Cerrada](https://github.com/PabloCerrada).
- [ Francisco Miguel Galván](https://github.com/CiscoGalvan).
- [ Pablo Martinez](https://github.com/Ares75643).
- [Jose Moreno](https://github.com/JoseMorenob).
- [Cristina Mora](https://github.com/CristinaMora).
- [Manuel Prada](https://github.com/manuelpr07).
- [Sheila Julvez](https://github.com/sheilajulvez).
- [Jose Eduardo Robles](https://github.com/josepk01).
- [Alfonso Jaime Rodulfo](https://github.com/ARodulfo).

