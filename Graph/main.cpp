#include <iostream>
#include "Point.h"
#include "Graph.h"
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <string>
#include <algorithm>

using namespace std;


int main()
{
    int sommet,d,h,l;
    string nom;
    cout << "Entres le nombre de point \n";
    cin >> sommet;
    cout << "\nEntrez le diametre du disque \n";
    cin >> d;
    cout << "\nEntres la hauteur \n";
    cin >> h;
    cout << "\nEntres la longeur \n";
    cin >> l;
    Graph* g = new Graph(sommet,d,h,l);
    int inddegre = g->degremax();
    cout << "ESM : " << g->ESM(g,&g->stable) << endl;
    g->affichegraphe("graph.ps");
    //system("evince graph.ps");
    return 0;
}
