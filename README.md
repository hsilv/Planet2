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
