#include "Graph.h"
#include "Point.h"
#include <iostream>
#include <stdlib.h>     /* srand, rand */
#include <time.h>       /* time */
#include <fstream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;
Graph::Graph(int n, int d, int h, int l)
{
    this->sommet = n;
    this->dmax = d;
    this->length = l;
    this->height = h;
    srand(time(NULL));
    for(int i=0;i<n;i++)
    {
        Point* p = new Point();
        p->Setx(rand()%length);
        p->Sety(rand()%height);
       //x=rand()%612; y=rand()%792;
        //p->Setx(rand()%612);
        //p->Sety(rand()%792);
        liste.push_back(p);
    }
    this->voisin.resize(n);
    initvoisin();
    this->degre = new vector<int>;
    initdegre();
}

Graph::Graph()
{

}

void Graph::affiche()
{
    cout << "Le graph:" << endl;
    cout << liste.size() << endl;
    for (vector<Point*>::iterator it=liste.begin(); it != liste.end(); it++)
    {
        (*it)->affiche();
        cout << "toto";
    }

}

int Graph::distanceCarre(Point* p1, Point* p2)
{
    int distx = p1->Getx() - p2->Getx();
    distx = distx*distx;
    int disty = p1->Gety() - p2->Gety();
    disty = disty * disty;
    return (distx +disty);
}

bool Graph::testvoisin(Point* p1, Point* p2)
{
    if(distanceCarre(p1,p2) < (this->dmax * this->dmax *4))
        return true;
    else
        return false;
}

void Graph::initvoisin()
{
    for(int i=0; i<this->sommet; i++)
    {
        for(int j=0;j<this->sommet;j++)
        {
            if ((i!=j) && (distanceCarre(liste[i],liste[j]) < dmax*dmax*4))
            {
                voisin[i].push_back(j);
            }
        }
    }
}

void Graph::initdegre()
{
    for(int i=0; i<this->sommet; i++)
		degre->push_back(voisin[i].size());
}

int Graph::degremax()
{
    int indice=-1;
    int max =-2;
    int i=0;
    for (vector<int>::iterator it = degre->begin() ; it != degre->end(); ++it,i++)
    {
        if((*it)>max)
        {
            max = (*it);
            indice = i;
        }
    }
    return indice;
}

void Graph::affichevoisin()
{
    cout << "Les voisin sont: " << endl;
    for(int i=0;i<sommet;i++)
    {
        cout <<" le sommet " << i <<" a pour voisin:  ";
        for(int j=0;j<this->voisin[i].size();j++)
        {
             cout << " " << voisin[i][j] << " ";
        }
        cout << endl;
    }
}

Graph* Graph::enlevePoint(int indice)
{
    Graph* g = new Graph();
    g->sommet = this->sommet-1;
    g->liste = this->liste;
    g->liste.erase(g->liste.begin() + indice);
    g->dmax = this->dmax;
    g->voisin.resize(g->sommet);
    g->initvoisin();
    g->degre = new vector<int>;
    g->initdegre();

    return g;
}

Graph* Graph::enleveVoisin(int indice)
{
    Graph* g = new Graph();

    g->liste = this->liste;
    vector<int> row = this->voisin[indice];
    g->sommet = this->sommet - row.size()-1;
    g->dmax = this->dmax;
    int cmpt=0;
    for(int i=0;i<row.size();i++)
    {
            if(row[i]< indice)
                cmpt++;
            g->liste.erase(g->liste.begin() + (row[i] - (i)));
    }

    if((indice - cmpt )<=0)
        g->liste.erase(g->liste.begin()+0);
    else
        g->liste.erase(g->liste.begin() + (indice-cmpt));

    g->voisin.resize(g->sommet);
    g->initvoisin();
    g->degre = new vector<int>;
    g->initdegre();
    return g;
}

void Graph::affichedegre()
{
    cout << "Les degres :" << endl;
    int i=0;
    for (vector<int>::iterator it = degre->begin() ; it != degre->end(); ++it,i++)
        cout << "Le sommet " << i << " a " << (*it) << endl;
}

void Graph::affichegraphe(char* s)
{
    ofstream output;             // Cree le fichier Graphe.ps qui affiche le graphe.
    output.open(s,ios::out);
    output << "%!PS-Adobe-3.0" << endl;
    output << endl;

    output << "/Times-Roman findfont" << endl;
    output << "8 scalefont" << endl;
    output << "setfont" << endl;
    output << endl;
    for(int i=0;i<sommet;i++)
    {
        output << liste[i]->Getx() << " " << liste[i]->Gety() << " 3 0 360 arc" <<endl;
        output << "0 1 1 setrgbcolor " <<endl;

        output << "fill" <<endl;
        output << "stroke"<<endl;
        output << endl;

        output << liste[i]->Getx() << " " << liste[i]->Gety() << " " << this->dmax << " " << "0 360 arc" <<endl;
        output << "0 0 1 setrgbcolor " <<endl;
        output << "stroke"<<endl;
        output << endl;

    }

    //sort( stable.begin(), stable.end() );
    stable.erase( unique( stable.begin(), stable.end() ), stable.end() );

    cout <<"size-1 :" << this->stable.size() << endl;

    int size = stable.size();
    int i=0;
    while(i<size-1)
    {
        if(i<size-1)
        {
            int j=i+1;
            while(j<size)
            {
                if(j<size)
                {
                    if (distanceCarre(stable[i],stable[j]) > dmax*dmax*4)
                    {
                        output << stable[i]->Getx() << " " << stable[i]->Gety() << " 7 0 360 arc" <<endl;
                        output << "1 0 0 setrgbcolor " <<endl;

                        output << "fill" <<endl;
                        output << "stroke"<<endl;
                        output << endl;
                        j++;
                    }
                    else
                    {
                        stable.erase(stable.begin()+j);
                        size--;
                    }
                }
        }
        i++;
    }
    }

    output << stable.back()->Getx() << " " << stable.back()->Gety() << " 10 0 360 arc" <<endl;
                        output << "1 0 0 setrgbcolor " <<endl;

                        output << "fill" <<endl;
                        output << "stroke"<<endl;
                        output << endl;

    cout <<"size :" << this->stable.size() << endl;

    output << endl;

    for(int i=0;i<sommet-1;i++)
    {
        for (int j=i+1 ;j<sommet;j++)
        {
            if (distanceCarre(liste[i],liste[j]) < dmax*dmax*4)
            {
                output << "0 1 1 setrgbcolor " <<endl;
                output << liste[i]->Getx() << " " << liste[i]->Gety() << " moveto" << endl;
                output << liste[j]->Getx() << " " << liste[j]->Gety() << " lineto" << endl;
                output << "stroke" << endl;
                output << endl;
            }
        }

        output << "1 1 1 setrgbcolor " <<endl;
        output << "newpath" << endl;
        output << liste[i]->Getx() << " " << liste[i]->Gety()+10 << " moveto" << endl;
        output << "(" << i << ")" << " show" << endl;
        output << endl;

      }
      output << "1 1 1 setrgbcolor " <<endl;
      output << "newpath" << endl;
      output << liste[sommet-1]->Getx() << " " << liste[sommet-1]->Gety()+10 << " moveto" << endl;
      output << "(" <<sommet-1 << ")" << " show" << endl;
      output << endl;
}

int Graph::ESM(Graph *g,vector<Point*>* s)
{
    if(g->sommet == 1)
    {
        s->push_back(g->liste[0]);
        return 1;
    }
    else if(g->sommet ==0)
        return 0;
    else
    {
        int inddegre =g->degremax();
        return maxi( ESM(g->enlevePoint(inddegre),s) , (ESM((g->enleveVoisin(inddegre)),s)+1) , inddegre,s,g);
    }

}

int Graph::maxi(int a, int b, int inddegre, vector<Point*>* s, Graph *g)
{

    if(a>b)
    {
        return a;
    }
    else
    {
        s->push_back(g->liste[inddegre]);
        return b;
    }
}

