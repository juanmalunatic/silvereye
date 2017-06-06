# Setup del SDK de OGRE3D para uso con Qt

Recurso principal: [Guía oficial de instalación del SDK de Ogre3D](http://www.ogre3d.org/tikiwiki/Installing+the+Ogre+SDK)

## Descarga de SDK precompilado y requisitos

Ogre3D tiene un SDK que contiene sus librerías etc.
Para facilitar la distribución de Ogre, un usuario _trusted_ de los foros oficiales compila periódicamente [varias versiones de dicho SDK](http://ogre3d.org/forums/viewtopic.php?t=69274).

Descargar el SDK evita tener que compilarlo pero restringe las versiones de todo el toolchain usado, pues se deben usar las herramientas con las que se compiló originalmente.
En mi caso, tuve que pasar de usar el compilador MingW x64 a Visual Studio 2013 x86 (vc120).

La librería boost de c++ también puede ser compilada o descargada (también es provista por el usuario previamente linkeada).

Las versiones usadas son:
- boost-1.61-vc120-x86-12.03.2016.7z
- OGRE-SDK-1.9.0-vc120-x86-12.03.2016.7z

Observar que es MSVC 2013 -- Visual C++ 12.0 x86.

Se descomprime el SDK en alguna carpeta donde se pueden poner todos los archivos de Ogre.
Se coloca el boost precompilado y renombrado (como /boost/) dentro de la carpeta del SDK descomprimido.

En mi caso tenía:

D:/OgreSDK/
	OGRE-SDK-1.9.0-vc120-x86-12.03.2016/
		boost/ <-- acá el boost descargado, renombrado a solo boost
	
	<A partir de acá otras cosas>
	DirectX_SDK_6_10/
	OGreCommandLineTools_1.7.2/
	OgreSDK_vc11_v1-9-0/ <-- esto fue un test creo
	OgreWikiTutorialFramework_1-9
	Utils
	
## Ajuste de Qt preexistente

Si ya se tiene un Qt instalado (como yo lo tenía)
- Se baja el compilador msvc2013 desde el Qt Manteinance Tool 
- Se baja [Visual Studio Community 2013](https://www.visualstudio.com/en-us/news/releasenotes/vs2013-community-vs), el cual es necesario para que QtCreator pueda usar mscv2013.
Al instalar VS2013 le puse las foundation classes porque ni idea, decía c++ :v 
- Se instalan las herramientas de debug para x86 usando el [Windows 10 SDK](https://developer.microsoft.com/en-us/windows/downloads/windows-10-sdk).
Importante solo seleccionar debugging tools.
Si hay problemas con que Qt lo detecte, ver [SO](http://stackoverflow.com/questions/9975949/how-to-configure-cdb-in-qt-creator).

Si el debugger no instaló, esto fueron otras cosas que probé.
Ya no sé que funcionó.

- Para tener debugger se instala el [VS SDK 2013](https://www.microsoft.com/en-us/download/details.aspx?id=40758).
Si ese archivo no instala el debugging, probar con el que está a continuación.
- [Microsoft Windows SDK for Windows 7 and .NET Framework 4](https://www.microsoft.com/en-us/download/details.aspx?id=8279), para Windows 7 (en este S.O. desarrollé originalmente la tésis).
Eso instala las x64 -.- seguir leyendo: 


## Otras vainas

OnScreen control de LG me outputea Anikash en el debugger de QT  
UltraLOL. Desactivarlo mientras.