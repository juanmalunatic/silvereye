# Usar Ogre3D en QtCreator

## Instalación de requisitos

Ver "Install the Ogre3D SDK to use it with Qt.md"

## Ajustes previos

Guía: [Tutorial de Ogre acerca de como instalar su SDK](http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Installing+the+Ogre+SDK), (saved_websites/Installing the Ogre SDK.pdf)

- Instalar el redist de DirectX, [directx_Jun2010_redist.exe](http://www.microsoft.com/en-au/download/details.aspx?id=8109).
- Setear el path de OGRE según la guía (en saved_websites/) 

## Setup de un proyecto de Ogre3D en QtCreator

Guía: [Setupear una aplicación con QtCreator](http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Setting+Up+An+Application+-+QtCreator), también en saved_websites/Setting Up...


Notar que la pinche cosa apendea una d al nombre del .exe (solo en modo debug) 

 
Por último para que el tutorial funcione (poder usar OpenGL): 
De acuerdo a una [consulta en el foro](http://www.ogre3d.org/forums/viewtopic.php?f=2&t=85562), en /Debug o /Release de %ogre_sdk_dir% hay un archivo resource_d.cfg.
Hay que añadirle el path  
    FileSystem=../../Media/materials/programs/GLSL 


[Foro: Tutorial no funciona en DX11](http://www.ogre3d.org/forums/viewtopic.php?f=2&t=81280)

