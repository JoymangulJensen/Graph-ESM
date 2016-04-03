#include "Point.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */

using namespace std;

Point::Point()
{

}

Point::~Point()
{
    //dtor
}


void Point::affiche()
{
    cout << "x: " << this->Getx() << " y: " << this->Gety() << endl;
}

bool Point::egale(Point* p)
{
    if(p->Getx() == this->Getx() && p->Gety() == this->Gety())
        return true;
    return false;
}
