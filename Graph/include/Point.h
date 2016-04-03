#ifndef POINT_H
#define POINT_H


class Point
{
    public:
        Point();
        virtual ~Point();
        int Getx() { return x; }
        void Setx(int val) { x = val; }
        int Gety() { return y; }
        void Sety(int val) { y = val; }
        void affiche();
        bool egale(Point* p);
    protected:
    private:
        int x;
        int y;
};

#endif // POINT_H
