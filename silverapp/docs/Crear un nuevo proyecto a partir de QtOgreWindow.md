#Instalación de QTOgreWindow

Guía: [Integración de Ogre en Qt5](http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Integrating+Ogre+into+QT5 )


# Desde cero:

Creo una carpeta Qt_QTOgreWindow para el proyecto 

## Estructura de Qmake (.pro)

Se crea un proyecto de qmake vacío, puede ser como lo dice [esta guía de StackOverflow](https://stackoverflow.com/questions/6594146/how-to-create-main-cpp-when-using-qt-designer).

El setup básico de Ogre3d involucra: 

1. Añadirle al Qmake (.pro) los paths al folder de Ogre3d como sugiere la [info oficial de ogre3d para qt creator](http://www.ogre3d.org/tikiwiki/Setting+Up+An+Application+-+QtCreato) (ver /saved_websites si offline).

Sin embargo le dejo varias cosas que Qt necesita para funcionar normalmente como  
```
QT       += core gui 
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets 
```
Es decir, modificar los requerimientos e includes, lo importante son los fragmentos encerrados en {}

## Estructura de folders 

Como se creó el proyecto vacío se agrega un main.cpp 

Se descargan los tres archivos de QTOgreWindow (.cpp, .h y SdkQtCameraMan.h) los cuales están en texto plano en la pág anteriormente mencionada. 
Se agregan al proyecto. 

## Mover a carpeta de OgreSDK 

Al haber compilado, se deben copiar los exe generados (tanto en debug como en release) a la carpeta del sdk del ogre pues para ejecución se necesita de los dll que están allá. Si no, la app crashea asi no se instancie QTOgreWindow (solo con incluirlos en el pro). 

Para hacer esto automáticamente, se siguen los pasos de "Setting Up an application with Qt Creator", la parte de cmd y copy (Desde Build Settings hasta llegar al titulote de Tutorial Framework). 