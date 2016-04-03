#ifndef GRAPH_H
#define GRAPH_H
#include "Point.h"
#include <vector>
#include <string>
using namespace std;

class Graph
{
    public:
        Graph(int n,int d, int h, int l);
        Graph();
        vector<Point*> Getliste() { return liste; }
        void Setliste(vector <Point*> val) { liste = val; }
        int distanceCarre(Point* p1, Point* p2);
        bool testvoisin(Point* p1,Point* p2);
        void affiche();
        void initvoisin();
        void initdegre();
        int degremax();
        Graph* enlevePoint(int indice);
        Graph* enleveVoisin(int indice);
        void affichevoisin();
        void affichegraphe(char* s);
        void affichedegre();
        int ESM(Graph* g,vector<Point*>* s);
        int maxi(int a, int b, int inddegre, vector<Point*>* s, Graph *g);
        vector<Point*> stable;
        int sommet;
    protected:
    private:
        int height;
        int length;
        vector<Point*> liste;
        int dmax;
        vector<vector<int> > voisin;
        vector<int>* degre;

};

#endif // GRAPH_H
