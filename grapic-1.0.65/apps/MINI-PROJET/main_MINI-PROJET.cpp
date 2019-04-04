#include <iostream>
#include <cmath>
#include <Grapic.h>

using namespace grapic;
const int NMAX = 10000;         // nombre MAX de particules
const int DIMW = 500;
const float  FRICTION = 0.2f;   // valeur d'absorbtion de la vitesse en cas de collision: 1=la particule repart aussi vite, 0=elle s'arrete
const float RADIUS = 5;         // rayon des cercles des particules

struct Vec2
{
	float x, y;
};

struct Balle
{
    Vec2 p;        // postion de la Balle
    Vec2 v;        // vitesse
    Vec2 f;        // force
    float m;        // masse
};

struct World
{
    Particle part[NMAX];        // tableau de particules
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

void init(World& d)
{
    d.n = 10;
}

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

		if (d.part[i].p.x >= DIMW)
		{
			d.part[i].p.x = DIMW-(d.part[i].p.x-DIMW);
			d.part[i].v.x = -d.part[i].v.x;
			d.part[i].v = FRICTION * d.part[i].v;
		}

		if (d.part[i].p.y >= DIMW)
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
    d.n ++;
    for(i=0;i<d.n;i++)
    {
        color(20*i, 255-20*i, 128);
        rectangle( DIMW/2 - 10*i, DIMW/2 - 10*i, DIMW/2 + 10*i, DIMW/2 + 10*i);
    }
}

int main(int , char** )
{
    World dat;
    bool stop=false;
	winInit("MyProg", DIMW, DIMW);
	init(dat);
    backgroundColor( 100, 50, 200 );
	while( !stop )
    {
        winClear();
        draw(dat);
        stop = winDisplay();
    }
    winQuit();
	return 0;
}

