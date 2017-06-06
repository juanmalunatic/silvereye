# Deployment de la aplicación

No se ha hecho un deployment final pues aún se arreglan cosas sobre la marcha.

## Guía

Se siguen las [instrucciones oficiales de Qt5 para deployment]( http://doc.qt.io/qt-5/windows-deployment.html)
Si estas no funcionan, existe un [artículo en la Wiki de Qt sobre deployment](https://wiki.qt.io/Deploy_an_Application_on_Windows)

Se deben tener además unas [consideraciones para el deployment de Ogre3D en Windows](http://www.ogre3d.org/forums/viewtopic.php?f=2&t=70897&p=463127&hilit=deploy+ogre3d#p463127).
En el foro oficial se recomienda copiar algunos dll de Ogre y los archivos de materiales e incluir un paquete redistribuible de M$.
En [Troubleshooting de Ogre 3D](http://www.ogre3d.org/tikiwiki/tiki-index.php?page=Troubleshooting) hay hints si algo falla.

## Deployment tentativo antiguo

Seguí un articulo para [vcvarsall](https://msdn.microsoft.com/en-us/library/f2ccy3wt.aspx)

 Abrí la consola de msvc2013sv 

Navegué con CD hasta la carpeta /compicombo/release que habia compilado en creator (donde esté el .exe, habiendo seleccionado release) 

Corrí windeployqt en el .exe 
Probando en el portátil -> success. 