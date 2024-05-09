# MOTOR VERYREAL - Proyecto 3
![Logo](VeryRealSolucion\bin\logo.png)


## Autores

- [Cristina Mora Velasco](https://github.com/CristinaMora)
- [Francisco Miguel Galvan Muñoz](https://github.com/CiscoGalvan)
- [Sheila Julvez Lopez](https://github.com/sheilajulvez)
- [Pablo Martínez Quesada ](https://github.com/Ares75643)
- [Alfonso Jaime Rodulfo Guío](https://github.com/ARodulfo)
- [Pablo Cerrada Vega](https://github.com/PabloCerrada)
- [Jose Moreno Barbero](https://github.com/JoseMorenob)
- [Jose E. Robles Roca](https://github.com/josepk01)
- [Agustín Castro De Troya](https://github.com/AgusCDT)
- [Manuel Prada Mínguez](https://github.com/manuelpr07)
<br>

## Guia de estilos
 Nuestra quia de estilos se muestra al completo en el pdf: [Guia_de_Estilos.pdf](VeryRealSolucion\bin\Guia_de_Estilo.pdf)


## Compilación del motor

Clona el repositorio

```bash
  git clone https://github.com/UCM-FDI-DISIA/VeryReal.git
```

Abre el directorio correspondiente
```bash
  cd tu ruta de descarga + VeryReal\VeryRealSolucion\dependencias\cMake\
```
Descarga las  dependencias

```bash
 All.bat
```

## Estructura del Motor:
Contamos con 1 solución con varios Proyectos en ella. Estos están definidos uno por cada módulo o parte diferenciada en el motor:

<br>

### AudioLeon
Audio leon es el proyecto encargado de la  parte de sonidos. Utiliza como libreria FMOD
<br>



### GuilleElArquitecto

Guille el  arquitecto es el proyecto encargado en definir toda nuestra arquitectura básica. Sin tener dependencia de ningún modulo. 
<br>
.
.
.


### LuaLuengo
<br>


### PedroBullet
<br>


### RomeRender
RomeRender es el proyecto encargado de toda la parte de renderizado del motor (3D como 2D), esto lo hace mediante Ogre. Para ello esta formado por una serie de clases que tienen las siguientes
funcionalidades:

        -AnimatorComponent: Componente que se enacarga del cargado y uso de animaciones, además de su gestión.
        Para guardar las animaciones se utiliza un unordered_map que nos  permite guardarlas, actualizarlas y borrarlas eficazmente.

        -CameraComponent: Componente que añade una camará al escenario, a su vez funciona como wrapper de la cámara de ogre. Tiene funcionalidades como: 
                - pitch
                - roll
                - desactivate
                - setviewportbackground

        - conversorvectores: puesto que utilizamos nuestros propios vectores, los de ogre deben quedar ocultos para el resto de proyectos. Para facilitar la tarea de conversiones hemos creado unos métodos dentro del namespace de VeryReal que nos facilitan esa conversió. 
        
        - RenderManager: Manager que se encarga de la inicialización de Ogre a partir de los archivos .cfgs, también se encarga del renderizado de cada frame en su Update y de la carga de
        shaders y recursos. Para finalizar, se encarga de la creación de nodos para dar al usuario una interfaz desde la que gestionar estos.

        - Window: Clase creada para gestionar la funcionalidad de la pantalla, esta es creada con SDL externamente y pasada a Ogre como ventana externa.

        -LightComponet: Componente que funciona como wrapper de la luz de ogre.

         -MeshRenderComponent: Componente encargada de crear el .mesh de cada entidad asi como de asignar su material. 

        - exportRomeRender: metodo para exportar unicamente el modulo de render.

  UI:

        - UIButtomComponent: clase base de boton, que detecta cuando el ratón está dentro de su transform y llama a una funcion si se pincha sobre ella. La funcion Action() esta vacia ya que cada boton tiene que tener una fucionalidad distinta

        - UIProgressBar: clase que nos permite crear una barra de carga por medio de overlay element.

        -UISpriteRenderComponent: Este componente renderiza imagenes 2D segun el transform que tenga 

        -UITextComponent: Permite poder escribir textos en pantalla asi como cargar distintas fuentes de letra.

        -UITransformComponent: Componente que sirve para indicar la posicion y escala de un objeto. Cogiendo posiciones entre 0 y 1 
 
<br>

<br>


### TonInput <br>

TonInput es el proyecto encargado del input del motor a través de SDL. Para ello se vale de un manager con funciones y variables para manejar los eventos tanto de teclado, ratón como de mando. Clases implicadas:

        - InputManager: manager que se encarga de actualizar los estados del ratón, teclado y mando. En el método Update compruebará si se ha dado algún tipo de evento y lo gestiona en caso de que se haya dado. 

        - TonMapeo: clase que contiene enums para el parseo entre variables de SDL y nuestras propias variables.



<br>


