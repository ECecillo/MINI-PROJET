#include <iostream>
#include <cmath>
#include <Grapic.h>
#include <stdlib.h>
#include <time.h>


using namespace grapic;
const int MAXW = 50;
const int NMAX = 10000;         // nombre MAX de particules
const int DIMWY = 500;
const int DIMWX = 720;
const float  FRICTION = 0.2f;   // valeur d'absorbtion de la vitesse en cas de collision: 1=la particule repart aussi vite, 0=elle s'arrete
const float RADIUS = 5;         // rayon des cercles des particules

struct Color
{
    int r;		// Des int pour pouvoir depasser 255 lors des additions mais ce n'est pas très joli, ni conventionnelle
    int g;
    int b;
};

struct Vec2
{
	float x, y;
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

float norm(const Vec2 v) ///Calculs de l'hypo.
{
	return sqrt(v.x*v.x + v.y*v.y);
}


struct Wall ///Création des murs du Jeu
{
    Vec2 minp; ///Coordonnées pour les rectangles
    Vec2 maxp; ///Coordonnées pour les rectangles
};

struct Ball
{
    Vec2 p;        // postion de la Balle
    Vec2 v;        // vitesse
    Vec2 f;        // force
    float m;        // masse
};

void print(Ball& b) ///Débug de la balle
{
    int i;
    cout<<i<<" b=("<<b.p.x<<","<<b.p.y<<") v=("<<b.v.x<<","<<b.p.y<<") m="<<b.m<<endl;
}

struct World
{
    int nbW; ///le nombre de murs dans le jeu
    Wall tab[MAXW]; ///Tableau de murs pour initialisé généralement les murs
};

void initWall (World &w, float xmin, float ymin, float xmax, float ymax) ///Propriété générale des murs
{
    int i;
    w.nbW= 26;

    w.minp.x = xmin; ///Init x min pour rectangle qui formera mur
    w.minp.y = ymin; /// ...
    w.maxp.x = xmax; /// ...
    w.maxp.y = ymax; /// ...
    for (i=0; i< MAXW; i++)
    {
        color(255,255,255); ///couleur du mur ( rectangle ).
        rectangle(w.minp.x, w.minp.y, w.maxp.x, w.maxp.y);
    }
}

/*struct World ///Création des murs du Jeu
{


};*/

void initBall (Ball &b)
{
    b.p.x= rand()%(DIMWX-2)+1; ///valeur entre 1 - 717, pour évite que la balle générée aille en dehors de la fenêtre lors de la génération.
    b.p.y= rand()%(DIMWY+10)+1; ///valeur entre 1 et 510, pour ne pas qu'elle soit vue par le joueur.
    color(255,255,255); ///Couleur blanche.
    circle(b.p.x, b.p.y, 3); ///Création d'un cercle à partir des coordo définit précédement.
}

void initWorld (World &w)
{
    w.nbW = 26; ///26 murs en tout dans le jeu


}

void updateParticle(Balle& b)		// advect
{
    const float dt = 0.1;
    if (b.m>0)
    {
        b.v = b.v + (dt/b.m)*b.f;     // mise à jour de la vitesse
        b.p = b.p + dt*b.v;                   // mise à jour de la position
        b.f.x = 0;
        b.f.y = 0;
    }
}

void colisionWindow(Ball &b, Wall &wa) /// Colision pour une seule balle pour l'instant,
{
  {///Colision sur fenêtre
    if (b.p.x < 0)
    {
        b.p.x = -b.p.x;
        b.v.x = -b.v.x;
        b.v = FRICTION * b.v;
    }
    if (b.p.y < 0)
    {
        b.p.y = b.p.y;
        b.v.y = -b.v.y;
        b.v = FRICTION * b.v;
    }
    if (b.p.x >= DIMWX)
    {
        b.p.x = DIMWX-(b.p.x-DIMWX);
        b.v.x = -b.v.x;
        b.v = FRICTION * b.v;
    }
    if (b.p.y >= DIMWY)
    {
        b.p.y = DIMWY-(b.p.y-DIMWY);
        b.v.y = -b.v.y;
        b.v = FRICTION * b.v
    }
  }
  {
    M1 = ;
    M2 = ;

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

void drawW(World& d)
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
    srand(time(NULL));
    Ball b;
    initBall(b);
    World dat;
    Menu m;
    bool stop=false;
	winInit("Dans la boite", DIMWX, DIMWY);
	init(dat);
    backgroundColor( 0, 0, 0);

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

