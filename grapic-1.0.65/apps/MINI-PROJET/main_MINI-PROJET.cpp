#include <iostream>
#include <cmath>
#include <Grapic.h>
#include <stdlib.h>
#include <time.h>

using namespace grapic;
using namespace std;

const float G = 9.81f;
const int MAXW = 28;
const int NMAX = 10000;         // nombre MAX de particules
const int DIMWY = 500;
const int DIMWX = 720;
const float  FRICTION = 0.02f;   // valeur d'absorbtion de la vitesse en cas de collision: 1=la particule repart aussi vite, 0=elle s'arrete
const float R = 3;         // rayon des cercles des particules

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
    Vec2 minp; ///Coordonnées pour les lignes : x
    Vec2 maxp; ///Coordonnées pour les lignes : y
};

struct Ball
{
    Vec2 p;        // postion de la Balle
    Vec2 v;        // vitesse
    Vec2 f;        // force
    float m;        // masse
    float r;
};

/*void print(Ball& b) ///Débug de la balle
{
    int i;
    cout<<i<<" b=("<<b.p.x<<","<<b.p.y<<") v=("<<b.v.x<<","<<b.p.y<<") m="<<b.m<<endl;
}*/

struct World
{
    Wall tab[MAXW]; ///Tableau de murs pour initialisé généralement les murs
    int nbW; ///le nombre de murs dans le jeu
    Ball ba;

};

void AddWall(World &w, float xmin, float ymin,float xmax, float ymax) ///Permet d'ajouter chaque mur à des coordonnées différentes
{
    //for (w.nbW = 0; w.nbW < nb; w.nbW++)
    //{

        w.tab[w.nbW].minp.x = xmin;
        w.tab[w.nbW].minp.y = ymin;
        w.tab[w.nbW].maxp.x = xmax;
        w.tab[w.nbW].maxp.y = ymax;
        w.nbW++;
    //}

}

void initBall (Ball &b) ///InitB
{
    {
        b.p.x= rand()%(DIMWX-2)+1; ///valeur entre 1 - 717, pour évite que la balle générée aille en dehors de la fenêtre lors de la génération.
        b.p.y= 530;//rand()%(DIMWY+10); ///valeur entre 1 et 510, pour ne pas qu'elle soit vue par le joueur.
    }
    {
        color(255,255,255); ///Couleur blanche.
        circle(b.p.x, b.p.y, b.r); ///Création d'un cercle à partir des coordo définit précédement.
    }
    b.m = 1.0;
    b.f.x = 0;
    b.f.y = 0;
}

void forceGravity(Ball &ba) ///Ajout de la gravité de la terre
{
	ba.f = ba.f + make_vec2(0, -ba.m * G);
}

void initTheWholeWorld (World &w, Ball &ba) ///Initialisation de la balle dans le monde et de tous les murs du jeu
{
    initBall(ba);
    w.nbW = 0;
    { ///Initialisation des murs du jeux (environement)

        AddWall(w, 50, 450, 150, 350);  ///Droite \ en haut à gauche
        AddWall(w, 250, 300, 150, 200); /// Droite / à gauche du milieu
        AddWall(w, 310, 150, 410, 150); /// Droite en dessous du milieu
        AddWall(w, 360, 400, 360, 250); /// LA DROITE DU MILIEU
        AddWall(w, 675, 450, 580, 350); /// DROITE / en haut à droite
        AddWall(w, 580, 200, 480, 300); /// DROITE / à droite du milieu
    }
    { ///Initialisation des murs du jeux (boites)
        {
            AddWall(w, 20, 0, 20, 50);
            AddWall(w, 70, 0, 70, 50);
        }

        {
            AddWall(w, 90, 0, 90, 50);
            AddWall(w, 140, 0, 140, 50);
        }

        {
            AddWall(w, 160, 0, 160, 50);
            AddWall(w, 210, 0, 210, 50);
        }

        {
            AddWall(w, 230, 0, 230, 50);
            AddWall(w, 280, 0, 280, 50);
        }

        {
            AddWall(w, 300, 0, 300, 50);
            AddWall(w, 350, 0, 350, 50);
        }

        {
            AddWall(w, 370, 0, 370, 50);
            AddWall(w, 420, 0, 420, 50);
        }
        {
            AddWall(w, 440, 0, 440, 50);
            AddWall(w, 490, 0, 490, 50);
        }

        {
            AddWall(w, 510, 0, 510, 50);
            AddWall(w, 560, 0, 560, 50);
        }

        {
            AddWall(w, 580, 0, 580, 50);
            AddWall(w, 630, 0, 630, 50);
        }

        {
            AddWall(w, 650, 0, 650, 50);
            AddWall(w, 700, 0, 700, 50);
        }
    }
    { ///MUR FEMANT OUVERTURE
        { ///GAUCHE
            AddWall(w, 0, 80, 20, 50);
        }

        { ///DROITE
            AddWall(w, 700, 50, 720, 80);
        }
    }
}

/*void initWorldW (World &w)
{
    w.nbW = 26; ///26 murs en tout dans le jeu
    int i;
    for (i=0; i< w.nbW; i++)
    {
        w.tab[i].CoulW = color(255,255,255);
    }
}
*/


void updateBall(Ball& b)		// advect
{
    const float dt = 0.002;
    if (b.m>0)
    {
        b.v = b.v + (dt/b.m)*b.f;     // mise à jour de la vitesse
        b.p = b.p + dt*b.v;                   // mise à jour de la position
        b.f.x = 0;
        b.f.y = 0;
    }
}

void colisionWindow(Ball &b)
{
  {///Colision sur fenêtre
    if (b.p.x < 0)  ///colision bas de fenêtre
    {
        b.p.x = -b.p.x;
        b.v.x = -b.v.x;
        b.v = FRICTION * b.v;
    }
    if (b.p.y < 0)  ///colision fenêtre
    {
        b.p.y = -b.p.y;
        b.v.y = -b.v.y;
        b.v = FRICTION * b.v;
    }
    /*if (b.p.x >= DIMWX)
    {
        b.p.x = DIMWX-(b.p.x-DIMWX);
        b.v.x = -b.v.x;
        b.v = FRICTION * b.v;
    } HAUT DE LA FENETRE */
    if (b.p.y >= DIMWY)
    {
        b.p.y = DIMWY-(b.p.y-DIMWY);
        b.v.y = -b.v.y;
        b.v = FRICTION * b.v;
    }
  }

}

void drawB(Ball &ba)
{
    color(255,0,0);
    circleFill(ba.p.x,ba.p.y, R);
}

void drawWall(World &wa)
{
    int i;
    color(255,255,255);
    for (i= 0; i< wa.nbW ; i++)
    {
        line(wa.tab[i].minp.x,wa.tab[i].minp.y,wa.tab[i].maxp.x, wa.tab[i].maxp.y);
    }
}

void drawAll (World &w, Ball &ba)
{
    drawWall(w);
    drawB(ba);
}

bool CollisionDroite (World &w, Ball &ba) ///Dis si il y colision avec segment (mur)
{
    int i;
    for (i=0; i < w.nbW; i++)
    {
        Vec2 u = w.tab[i].maxp-w.tab[i].minp; //, w.tab[i].maxp.y-w.tab[i].minp.y);
       // Vec2 u = make_vec2(w.tab[i].maxp.x-w.tab[i].minp.x, w.tab[i].maxp.y-w.tab[i].minp.y);
        Vec2 WallCer = make_vec2(ba.p.x - w.tab[i].minp.x,ba.p.y - w.tab[i].minp.y );   ///


    float numerateur = u.x*WallCer.y-u.y*WallCer.x;
    if (numerateur<0)
    {
        numerateur = -numerateur;
    }
    float denominateur = norm(u);
    float CI = numerateur/denominateur;


    if (CI < R)
    {
        return true;
    }
    else
    {
        return false;
    }
    }

}

bool UpdateBlocParticle(World& wa, Ball ba)
{
    int i;
    for (i=0; i< wa.nbW; i++)
    {
            if (CollisionDroite(wa, ba) ==  false)
            {
                return false;
            }
    Vec2 Min = wa.tab[i].minp;
    Vec2 Max = wa.tab[i].maxp;

    Vec2 C = ba.p;

    Vec2 XY, XC, YC; ///XC = X à la balle, XY = segment, YC = Y à la balle
    XY.x = Max.x - Min.x;
    XY.y = Max.y - Min.y;
    XC.x = C.x - Min.x;
    XC.y = C.y - Min.y;
    YC.x = C.x - Max.x;
    YC.y = C.y - Max.y;

    float pscal1 = XY.x*XC.x + XY.y*XY.y; ///produit scalaire
    float pscal2 = (-XY.x)*YC.x + (-XY.y)*YC.y; ///produit scalaire
    if (pscal1 >= 0 && pscal2 >= 0)
    {
        ba.v.x = -ba.v.x;
    }
    return true;
    }

}


void updateOnearth(Ball& ba)
{
    forceGravity(ba);
    updateBall(ba);
    colisionWindow(ba);
}


int main(int , char** )
{
    srand(time(NULL));
    World w;
    Ball ba;
    Menu m;
    winInit("Dans la boite", DIMWX, DIMWY);
    backgroundColor( 0, 0, 0);
    initTheWholeWorld(w, ba);
    bool stop=false;
    menu_add( m, "20 POINTS");
    menu_add( m, "10 POINTS");
    menu_add( m, "5 POINTS");
	while( !stop )
    {
        winClear();
        /*menu_draw(m, 5,5, 100, 102);
        switch(menu_select(m))
        {
            case 0 : ///*on met ici le cas où si balle dans boite alors score + 20 * 5; draw(b); break;
            case 1 : ; draw(dat); break;
            case 2 : ; draw(dat); break;
            default: ; draw(jeu); break; ///jeu : Pas d'action donc jeu bouge pas
        }
    */
        updateOnearth(ba);
        drawAll(w,ba);
        CollisionDroite(w, ba);
        UpdateBlocParticle(w, ba);
        cout << CollisionDroite(w, ba);
        stop = winDisplay();

    }
    winQuit();
	return 0;
}

