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


.

<br>

Actualmente también contamos con 2 Proyectos por Módulo:
· El proyecto en si que es la biblioteca
· El proyecto llamado "modulo_test" que nos sirve temporalmente para hacer pruebas de ese módulo




## Autores
<br>
<li> Pablo Cao
<li> Agustín Castro
<li> Pablo Cerrada
<li> Francisco Miguel Galván
<li> Sheila Julvez
<li> Pablo Martinez
<li> Jose Moreno
<li> Cristina Mora
<li> Manuel Prada
<li> Jose Eduardo Robles
<li> Alfonso Jaime Rodulfo


