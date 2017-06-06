# Crear un modelo de humano con MakeHuman

Exportar desde MakeHuman hacia Ogre usando la exportación nativa (usando MakeHuman 1.1.0).
Escoger metros (no decimeters) para la escala 1 ogre unit = 1 metro 

## Renombrado de archivos

Esta sección usa Notepad++ y las OgreCommandLineTools

```
El archivo queda llamandose nombre.mesh.mesh.xml 
   Renombrar a nombre.mesh.xml 
   Editar nombre.mesh.skeleton.xml a nombre.skeleton.xml 
   Renombrar nombre.mesh.material a nombre.material

Editar el archivo mesh.xml post renombrado (nombre.mesh.xml) 
  Buscar y reemplazar nombre.mesh_ por nombre_ para arreglar los materiales 
  Buscar en la parte de abajo el link de skeleton, quitarle el "mesh." 

Paso los xml (skeleton y mesh) por el ogrexml converter 
Euego los paso por el upgrader (asegurandome que todo esté bien) 
```

## Rotado del modelo para hacerlo ISB

El proceso hasta aquí funciona pero el humano mira hacia el eje equivocado cuando está hacia adelante. 
Para que el sistema coordenado de la persona cumpla con las convenciones de la ISB, el muñeco se rota con las OgreCommandLineTools: 

### PARA TYPICAL (z arriba, x adelante) 
OgreMeshMagick.exe transform -rotate=90/1/0/0 humano.mesh 
OgreMeshMagick.exe transform -rotate=90/0/0/1 humano.mesh 

### PARA ISB (y arriba, x adelante) 
OgreMeshMagick.exe transform -rotate=90/0/1/0 humano.mesh 

## Notas

Los p*tos ojos: entré al material y depth_write on en ojos y short02 (pelo) 
Y SHADOWTYPE_TEXTURE_MODULATIVE 

Varias ediciones al material!!! Documentado en bak de materials 

Alternativa para exportarlo al modelo low poly: 
http://www.makehumancommunity.org/forum/viewtopic.php?f=6&t=2508 