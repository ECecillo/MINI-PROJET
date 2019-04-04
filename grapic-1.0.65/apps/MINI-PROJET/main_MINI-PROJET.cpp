#include <iostream>
#include <cmath>
#include <Grapic.h>

using namespace grapic;
const int NMAX = 10000;         // nombre MAX de particules
const int DIMWY = 500;
const int DIMWX = 720;
const float  FRICTION = 0.2f;   // valeur d'absorbtion de la vitesse en cas de collision: 1=la particule repart aussi vite, 0=elle s'arrete
const float RADIUS = 5;         // rayon des cercles des particules

struct Vec2
{
	float x, y;
};

struct Bucket
{

};

struct Balle
{
    Vec2 p;        // postion de la Balle
    Vec2 v;        // vitesse
    Vec2 f;        // force
    float m;        // masse
};

struct TerrM ///Création des murs du Jeu
{
    int x,y;

};

struct World
{
    Balle ba[NMAX];        // tableau de particules
	int np;                     // nombre de particules
};

Vec2 operator+(const Vec2& a, const Vec2& b)
{
	Vec2 r;
	r.x = a.x + b.x;
	r.y = a.y + b.y;
	return r;
}

Vec2 operator-(const Vec2& a, const Vec2& b)
{
	Vec2 r;
	r.x = a.x - b.x;
	r.y = a.y - b.y;
	return r;
}

Vec2 operator+=(Vec2& a, const Vec2& b)
{
	a.x += b.x;
	a.y += b.y;
	return a;
}

Vec2 operator*(float a, const Vec2& b)
{
	Vec2 r;
	r.x = a * b.x;
	r.y = a * b.y;
	return r;
}

Vec2 make_vec2(float x, float y)
{
    Vec2 r;
    r.x = x;
    r.y = y;
    return r;
}

/*void init(World& d)
{
    d.n = 10;
}
*/
void collision(World& d)
{
	int i;
	for (i = 0; i < d.np; ++i)
	{
		if (d.part[i].p.x < 0)
		{
			d.part[i].p.x = -d.part[i].p.x;
			d.part[i].v.x = -d.part[i].v.x;
			d.part[i].v = FRICTION * d.part[i].v;
		}

		if (d.part[i].p.y < 0)
		{
			d.part[i].p.y = -d.part[i].p.y;
			d.part[i].v.y = -d.part[i].v.y;
			d.part[i].v = FRICTION * d.part[i].v;
		}

		if (d.part[i].p.x >= DIMWX)
		{
			d.part[i].p.x = DIMW-(d.part[i].p.x-DIMW);
			d.part[i].v.x = -d.part[i].v.x;
			d.part[i].v = FRICTION * d.part[i].v;
		}

		if (d.part[i].p.y >= DIMWY)
		{
			d.part[i].p.y = DIMW - (d.part[i].p.y - DIMW);
			d.part[i].v.y = -d.part[i].v.y;
			d.part[i].v = FRICTION * d.part[i].v;
		}
	}
}

void forceGravity(World& d)
{
	int i,j;
	const float G = 9.81f;
	for (i = 0; i < d.np; ++i)
	{
        d.part[i].f.x = 0;
        d.part[i].f.y = -d.part[i].m * G;
	}
}

void draw(World& d)
{
    int i;
    d. ++;
    for(i=0;i<d.n;i++)
    {
        color(20*i, 255-20*i, 128);
        rectangle( DIMW/2 - 10*i, DIMW/2 - 10*i, DIMW/2 + 10*i, DIMW/2 + 10*i);
    }
}

int main(int , char** )
{
    World dat;
    Menu m;
    bool stop=false;
	winInit("Lucky Ball", DIMWX, DIMWY);
	init(dat);
    backgroundColor( 100, 50, 200 );

    menu_add( m, "20 POINTS");
    menu_add( m, "10 POINTS");
    menu_add( m, "5 POINTS");

	while( !stop )
    {
        winClear();
        menu_draw(m, 5,5, 100, 102);
        switch(menu_select(m))
        {
            case 0 : /*on met ici le cas où si balle dans boite alors score + 20 * 5*/; draw(dat); break;
            case 1 : ; draw(dat); break;
            case 2 : ; draw(dat); break;
            default: ; draw(jeu); break; ///jeu : Pas d'action donc jeu bouge pas
        }
        stop = winDisplay();
    }
    winQuit();
	return 0;
}

