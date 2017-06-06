# Mesh para OGRE3D a partir de Blender

## Blender exporter

Para convertir un modelo cualquiera de Blender a .mesh se usa [_Blender Exporter_](http://www.ogre3d.org/download/tools).  

Cuando se realizó el trabajo de grado (Q4 2016), Blender Exporter (BE) estaba en un estado de medio _abandonware_, pues su última actualización había sido el 10 de septiembre de 2012.

En el momento de redactar este documento (Q2 2017), los links a la versión usada están caídos (gracias google code). El instalador de la versión usada de BE se puede encontrar gracias al Internet Archive: [blender2ogre-0.5.8.exe](https://web.archive.org/web/20160924082243/https://storage.googleapis.com/google-code-archive-downloads/v2/code.google.com/blender2ogre/blender2ogre-0.5.8.exe).
La versión de Blender que es compatible con ese plugin es la 2.63. 

[Otras versiones antiguas de Blender Exporter](https://web.archive.org/web/20160924012612/https://code.google.com/archive/p/blender2ogre/downloads)

[Repositorio actual (2017) de la herramienta blender2ogre](https://github.com/OGRECave/blender2ogre)


## En Blender  

Para revisar que el plugin está instalado, buscarlo en el panel de plugins de Blender (buscarlo con keyword "ogre").

- Se usa Blender 2.63 para tener compatibilidad con el plugin de exportación antiguo.
- Se crea el modelo deseado
- Se le hace _Join_ para exportar un solo mesh 
- Se usa _Apply transforms_ para que guarde cambios a mesh. El modelo se exporta como un plano (aplastado) si uno no aplica las transforms al mesh con Ctrl+A !!
- Se puede seleccionar unir los materiales y exportar solo mesh (no scene) 
- Usar configuracion XYZ 

## Ogre Command-line Tools

Exportar por medio del plugin genera un archivo _.mesh.xml_. Una vez se tiene este archivo, este se transforma con las [Ogre Command-line Tools](https://sourceforge.net/projects/ogre/files/ogre-tools/1.7.2/OgreCommandLineTools_1.7.2.zip/download).

Se puede drag&drop el .mesh.xml al OgreXMLconverter, o se pueden usar las herramientas desde la línea de comandos si se desea realizar más ajustes (escala, rotar el modelo, etc).

## Revisión del mesh

Una vez se tiene el archivo _.mesh_, se puede usar el software [OgreMeshy](https://sourceforge.net/projects/ogremeshy/) para verificar que la exportación desde Blender fue correcta. Revisar tanto el esqueleto como el eje coordenado.


## Uso del mesh en OGRE
  
Pongo Axes.mesh en media/models/ (En la carpeta del SDK de Ogre)

Pongo Axes.material en media/materials/scripts (renombro el .material que genera auto) 