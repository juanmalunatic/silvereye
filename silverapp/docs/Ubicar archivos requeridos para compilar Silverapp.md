# Archivos necesarios para compilar Silverapp

Para que Ogre pueda acceder al modelo 3D, sus texturas, etc, se debe copiar el contenido de /thesis_resources/ como si fuera un "crack", sobre la raíz de OgreSDK.

Como se sobreescriben las configuraciones por defecto de Ogre, mejor hacer baks.

Se lista la idea para la estructura de archivos:

```
X:/OgreSDK-blabla/
	boost/
	media/
		human_project/ç
			[etc]
	bin/
		Debug/
			plugins_d.cfg   <- estos no son tan importantes pues la tesi se compila
			resources_d.cfg    en modo release
		Release/
			plugins.cfg    
			resources.cfg
```



