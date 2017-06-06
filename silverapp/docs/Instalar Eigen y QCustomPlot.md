# Instalar Eigen y QCustomPlot

## Eigen  

Se baja el último source code y se copia solo la carpeta /Eigen.
Agrego la linea a libversions.txt.

Getting started: http://eigen.tuxfamily.org/dox/GettingStarted.html 

Instalo la carpeta unsupported (que dentro tiene /Eigen) para usar un mejor módulo de [EulerAngles](http://eigen.tuxfamily.org/dox-devel/unsupported/group__EulerAngles__Module.html#title0) 

Ojo, la unsupported es de 3.3 y eigen es 3.2.algo

## QCustomPlot 

Copio qcustomplot.cpp y .h a la carpeta del proyecto.
Agrego la linea a libversions.txt.

Getting started: http://www.qcustomplot.com/index.php/tutorials/settingup 

## Ambos en un proyecto

Se crea un proyecto nuevo con Qt Creator.
Se agrega Eigen.
Se copia /Eigen al folder del .pro 
Editar el pro file:

    INCLUDEPATH += $$PWD/Eigen 

Y listo. Se incluye #include <Eigen/Dense> o lo que se nite y se corre. 

Se agrega QcustomPlot 
Se copian los dos archivos .cpp y .h al folder del .pro 
Editar el pro file 

    QT+=widgets printsupport 
	
Incluir .cpp en SOURCES y .h en HEADERS 

Se hacen los getting started de ambos. Funcionan.