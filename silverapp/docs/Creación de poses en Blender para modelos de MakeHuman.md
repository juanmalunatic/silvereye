# Creación de poses en Blender para modelos de MakeHuman

## Guía:

Partiendo del skeleton default en MakeHuman, se sigue el tutorial: 
[Export your own MakeHuman pose from Blender](http://blender.stackexchange.com/questions/49768/can-i-set-my-pose-position-like-the-new-rest-position).

## Procedimiento

- Se parte del esqueleto default no toes 

- Se parte de la pose "sin pose"

- Se exporta al formato mhx2 

- Se importa desde blender 2.78 con el plugin Import-Runtime: [MakeHuman Exchange 2 (.mhx2) 0.27 de Thomas Larsson](https://bitbucket.org/Diffeomorphic/mhx2-makehuman-exchange) (recordar que para la compatibilidad con la exportación de Ogre se tiene un blender más antiguo) 

- Se edita el modelo: Click derecho pa seleccionar el bone, y rotarlo. Click con rueda del mouse para cambiar el eje cuando ya se le dio click derecho. 

- Se exporta el modelo editado como .bvh desde blender y se usa desde makehuman como indica la guía.

## Recomendaciones

Las instrucciones del tutorial no funcionaron para mi al principio, por lo que abrí un [issue en el bugtracker de MakeHuman](http://bugtracker.makehumancommunity.org/issues/1073). 
Resulta que es muy importante usar el esqueleto _Default no toes_ para que el proceso de creación de poses funcione (no sé si los otros esqueletos no funcionen, solo sé que _Cmu mb_ no se comporta según lo esperado).

## Notas

Respuesta de Yahoo para encontrar la modifier tab
https://answers.yahoo.com/question/index?qid=20111214115331AA8M6Z7 