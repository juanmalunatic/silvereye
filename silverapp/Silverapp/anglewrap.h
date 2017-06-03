#ifndef ANGLEWRAP_H
#define ANGLEWRAP_H

//#define _USE_MATH_DEFINES

//#include <cmath>
#include <math.h>
#include <QDebug>

#ifndef M_PI
#define M_PI  3.14159265358979323846264338327950288
#endif

#ifndef M_2PI
#define M_2PI  6.28318530717958647692528676655900576
#endif

//https://stackoverflow.com/a/15651444

//Normalize to [-180,180):
inline double constrainAngle(double x)
{
    x = fmod(x + M_PI,M_2PI);
    if (x < 0)
        x += M_2PI;
    return x - M_PI;
}

// convert to [-360,360]
inline double angleConv(double angle)
{
    return fmod(constrainAngle(angle),M_2PI);
}

inline double angleDiff(double a,double b)
{
    double dif = fmod(b - a + M_PI,M_2PI);
    if (dif < 0)
        dif += M_2PI;
    return dif - M_PI;
}
inline double angleUnwrap(double previousAngle,double newAngle)
{
    return previousAngle - angleDiff(newAngle,angleConv(previousAngle));
}



int updateAngleMode(int prevAngleMode, double prevAngle, double newAngle)
{
    double angleDifference = angleDiff(prevAngle, newAngle);

    /*
    if( angleDifference > 1.57 )
    {
        qDebug() << angleDifference;
    }
    */

    if( angleDifference >= ( M_PI-(M_PI/180*0.5) ) )
    {
        if( prevAngle > newAngle )
        {
            return 1; // lastjumpy > jumpy, add nothing
        }
        else
        {
            return 0; // return mode 0
        }
    }

    return prevAngleMode;
}








#endif // ANGLEWRAP_H
