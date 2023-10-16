# Planet2
# Shaders
## Shaders de Rocosos
![](https://github.com/hsilv/Planet2/blob/main/Earth%20(2).gif)

## Shaders de Soles
![](https://github.com/hsilv/Planet2/blob/main/Sun.gif)

## Shaders de Gaseosos
![](https://github.com/hsilv/Planet2/blob/main/Jupiter.gif)

# Planetario

Para poder correr esto, es necesario ejecutar los scripts de Bash en cualquier sistema operativo que lo soporte, asimismo, poseer instalado TBB, SDL y GLM de forma global en el sistema operativo, agregado al Path.
Solo hace falta colocar en consola `run.sh`

Esto fue programado en un entorno Linux basado en Debian

![](https://github.com/hsilv/Planet2/blob/main/Planetarium.gif)

## Selección de planetas

Para seleccionar planetas (no satélites) se establecieron los siguientes controles:

| Comando | Acción |
| :-----: | :----: |
| Suma del Numpad | Sube en el índice del planeta y todo actúa en relación al nuevo planeta centrado |
| Resta del Numpad | Baja en el índice del planeta y todo actúa en relación al nuevo planeta centrado |

Cabe destacar que el primer índice es el Sol

Muestra de selección y Warping a los planetas:

![](https://github.com/hsilv/Planet2/blob/main/Select.gif)

Perspectiva de un objeto centrado con respecto a su sistema

![](https://github.com/hsilv/Planet2/blob/main/Perspective.gif)

## Control de Cámara

### Modo Cangrejo

Para mover la cámara existen diferentes formas, la primera es en "modo cangrejo" que mueve a la cámara directamente en una dirección sin "aparentemente" cambiar hacia dónde mira ni seguir un objeto en especial:

| Comando | Acción |
| :-----: | :----: |
| Flecha Arriba | Mueve la cámara hacia delante |
| Flecha Abajo | Mueve la cámara hacia atrás |
| Flecha Derecha | Mueve la cámara a la derecha |
| Flecha Izquierda | Mueve la cámara a la izquierda |
| Page Up o Av Pág | Mueve la cámara hacia arriba en el eje Y |
| Page Down o Re Pág | Mueve la cámara hacia abajo en el eje Y |

Cabe destacar que la vista por defecto es un Bird's Eye. Por otro lado, el movimiento de la cámara en Y no mueve su centro, es decir, mantiene en centro al mismo objeto, por lo cual, pueden surgir diferentes efectos (ninguno desagradable) según la posición de la cámara

![](https://github.com/hsilv/Planet2/blob/main/Crab.gif)

### Modo Libre

El "modo libre" está habilitado únicamente en el eje z, es decir se mueve hacia delante o hacia atrás orbitando al objeto, manteniéndolo siempre centrado, esto es principalmente usado para brindar inclinación y perspectiva a las cosas.

| Comando | Acción |
| :-----: | :----: |
| W | Mueve la cámara hacia delante en una órbita relacionada al objeto enfocado |
| S | Mueve la cámara hacia atrás en una órbita relacionada al objeto enfocado |

También posee un comportamiento especial, una vez pasado cierto umbral en coordenadas 0's en z, la perspectiva se reajustará para mantener la orientación de la cámara en relación a su vector de dirección hacia arriba.

![](https://github.com/hsilv/Planet2/blob/main/Free.gif)

# Aspectos Importantes

### Clip de objetos cercanos

Se añadió una condición que no evita el acercamiento de la cámara a los objetos, si no los considera de una forma especial, siendo capaces estos de ser atravesados sin afectar demasiado el rendimiento, se hizo un clip trasero a la cámara con distancia de 1.5f desde adelante hacia atrás, es decir cualquier vértice que esté desde 1.5f hacia atrás de la cámara, no se renderizará.

Por otro lado, las órbitas se borran al cambiar de perspectiva de cámara, esto debido a que se debe limpiar la órbita anterior para que no parezca sucio.

### Rendimiento

Debido a la calidad de keyframes de los GIF's no se muestra su rendimiento real, el cual es un aproximado de 30fps hacia arriba a distancia media y 10fps cerca de los objetos.

![](https://github.com/hsilv/Planet2/blob/main/FPS.png)

