#include <iostream>
#include <cmath>
#include <Grapic.h>
#include <stdlib.h>
#include <time.h>

using namespace grapic;
using namespace std;

const float G = 9.81f;
const int MAXW = 10000;
const int NMAX = 10000;         // nombre MAX de particules
const int DIMWY = 500;
const int DIMWX = 720;
const float  FRICTION = 0.8f;   // valeur d'absorbtion de la vitesse en cas de collision: 1=la particule repart aussi vite, 0=elle s'arrete

const float R = 5;         // rayon des cercles des particules

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


void print(Ball& b) ///Débug de la balle
{
    int i;
    cout<<i<<" POSITION =("<<b.p.x<<","<<b.p.y<<") VITESSE =("<<b.v.x<<","<<b.p.y<<") MASSE ="<<b.m<<endl;
}


struct AllImage ///Strcture qui créer les images
{
    Image im_five; ///Création de variable pour le dessin de ces scores
    Image im_ten; /// ...
    Image im_twenty; /// ..
};

struct World
{
    Wall tab[MAXW]; ///Tableau de murs pour initialisé généralement les murs
    int nbW; ///le nombre de murs dans le jeu
    Ball ba; ///10 balles max
    AllImage im; ///Pour les images
};

void initBall (Ball &ba) ///InitB
{
    {
        ba.p.x= rand()%(DIMWX-2)+1; ///valeur entre 1 - 717, pour évite que la balle générée aille en dehors de la fenêtre lors de la génération.
        ba.p.y= 530;//rand()%(DIMWY+10); ///valeur entre 1 et 510, pour ne pas qu'elle soit vue par le joueur.
    }
    {
        color(255,255,255); ///Couleur blanche.
        circle(ba.p.x, ba.p.y, ba.r); ///Création d'un cercle à partir des coordo définit précédement.
    }
    ba.m = 1.0;
    ba.f.x = 0;
    ba.f.y = 0;
}

void forceGravity(Ball &ba) ///Ajout de la gravité de la terre
{
    ba.f = ba.f + make_vec2(0, -ba.m * G);
}

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


void initTheWholeWorld (World &w, Ball &ba) ///Initialisation du monde
{
    initBall(ba);
    w.im.im_five = image("data/mines/mine.png");
    w.im.im_ten = image("data/mines/mine.png");
    w.im.im_twenty = image("data/mines/mine.png"); //"data/MINI_PROJET/"

    w.nbW = 0;
    {///MUR DE BASE
        ///Initialisation des murs du jeux (environement)
        AddWall(w, 250, 300, 150, 200); /// Droite / à gauche du milieu
        AddWall(w, 323, 130, DIMWX-323, 130); /// Droite _ en dessous du milieu
        AddWall(w, 360, 400, 360, 250); /// LA DROITE DU MILIEU |
        AddWall(w, 580, 200, 480, 300); /// DROITE / à droite du milieu
    }
    {///MEMBRANE COTE
        {///Nouvelle environement du jeu (membrane gauche)
            AddWall(w, 50, 460, 110, 400);/// segment \ en haut à gauche
            AddWall(w, 110, 400, 50, 360);/// segment / en haut à gauche
            AddWall(w, 50, 360, 80, 236);/// segment \ en dessous
            AddWall(w, 80, 236, 48, 222);/// segment / en dessous
            AddWall(w, 48, 222, 48, 172);/// segment | en dessous
            AddWall(w, 48, 172, 66, 150);/// segment \ en dessous
        }
        {
            ///Symétrique droit (membrane droite)
            AddWall(w, DIMWX-50, 460, DIMWX-110, 400);/// segment \ en haut à gauche
            AddWall(w, DIMWX-110, 400, DIMWX-50, 360);/// segment / en haut à gauche
            AddWall(w, DIMWX-50, 360, DIMWX-80, 236);/// segment \ en dessous
            AddWall(w, DIMWX-80, 236, DIMWX-48, 222);/// segment / en dessous
            AddWall(w, DIMWX-48, 222, DIMWX-48, 172);/// segment | en dessous
            AddWall(w, DIMWX-48, 172, DIMWX-66, 150);/// segment \ en dessous
        }
    }
    {///RAMPE
        {/// RAMPE EN HAUT A GAUCHE
            AddWall(w, 190, 440, 230, 470);
            AddWall(w, 230, 470, 288, 480);
            AddWall(w, 288, 480, 288, 500);
        }
        {
            ///SYMETRIQUE DE LA RAMPE
            AddWall(w, DIMWX-190, 440, DIMWX-230, 470);
            AddWall(w, DIMWX-230, 470, DIMWX- 288, 480);
            AddWall(w, DIMWX-288, 480, DIMWX-288, 500);
        }
    }
    {///PRISME
        {
            ///PRISME GAUCHE
            AddWall(w, 152, 377, 212, 377);
            AddWall(w, 212, 377, 232, 364);
            AddWall(w, 232, 364, 212, 347);
            AddWall(w, 212, 347, 152, 347);
            AddWall(w, 152, 347, 132, 362);
            AddWall(w, 152, 377, 132, 362);
        }
        {
            ///SYMETRIQUE DU PRISME GAUCHE
            AddWall(w, DIMWX-152, 377, DIMWX-212, 377);
            AddWall(w, DIMWX-212, 377, DIMWX-232, 364);
            AddWall(w, DIMWX-232, 364, DIMWX-212, 347);
            AddWall(w, DIMWX-212, 347, DIMWX-152, 347);
            AddWall(w, DIMWX-152, 347, DIMWX-132, 362);
            AddWall(w, DIMWX-152, 377, DIMWX-132, 362);
        }
    }
    {///TRIANGLE
        {
            /// TRIANGLE GAUCHE
            AddWall(w, 273, 262, 323, 262); ///x = 323, y = 262
            AddWall(w, 323, 262, 296, 222);
            AddWall(w, 296, 222, 273, 262);
        }
        {
            /// SYMETRIQUE TRIANGLE
            AddWall(w, DIMWX-273, 262, DIMWX-323, 262);
            AddWall(w, DIMWX-323, 262, DIMWX-296, 222);
            AddWall(w, DIMWX-296, 222, DIMWX-273, 262);
        }
    }

    {///SEGMENT PARTIE JEU
        {/// SEGMENT / en haut à droite
            AddWall(w, 578, 431, 538, 400);
        }
        {///SEGMENT SYMETRIQUE en haut à gauche
            AddWall(w, DIMWX-578, 431, DIMWX-538, 400);
        }
        {/// SEGMENT / vers ligne verticale
            AddWall(w, 325, 387, 281, 353);
        }
        {/// SEGMENT SYMETRIQUE \ vers ligne verticale
            AddWall(w, DIMWX-325, 387, DIMWX-281, 353);
        }
        {/// Segment entre
            AddWall(w, 263, 333, 283, 303);
        }
        {/// Segment symétrique entre
            AddWall(w, DIMWX-263, 333, DIMWX-283, 303);
        }
    }
    {///BOITE
        ///Initialisation des murs du jeux (boites)
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
    {///2 MUR FERMANT COTE LATERAL DES BOITES
        ///MUR FEMANT OUVERTURE
        {
            ///GAUCHE
            AddWall(w, 0, 80, 20, 50);
        }

        {
            ///DROITE
            AddWall(w, 700, 50, 720, 80);
        }
    }
    {/// MUR CREVASSE DES BOITES
        ///MUR FERMANT LES CREUX ENTRE LES BOITES
        AddWall(w, 70, 50, 91, 50);
        AddWall(w, 141, 50, 161, 50);
        AddWall(w, 211, 50, 231, 50);
        AddWall(w, 281, 50, 301, 50);
        AddWall(w, 351, 50, 371, 50);
        AddWall(w, 421, 50, 441, 50);
        AddWall(w, 491, 50, 511, 50);
        AddWall(w, 561, 50, 581, 50);
        AddWall(w, 631, 50, 651, 50);
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


void updateBall(Ball &ba) ///Mise à jour de la position de la balle à chaque pas de temps
{
    const float dt = 0.003;
    if (ba.m>0)
    {
        ba.v = ba.v + (dt/ba.m)*ba.f;     // mise à jour de la vitesse
        ba.p = ba.p + dt*ba.v;                   // mise à jour de la position
        ba.f.x = 0;
        ba.f.y = 0;
    }
}

void colisionWindow(Ball &b) ///Colision Balle Fenêtre seulement
{
    {
        ///Colision sur fenêtre
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
            b.v = FRICTION * b.v;
        }
    }

}

void drawB(Ball &ba) ///Dessine la balle
{
    color(255,0,0);
    circleFill(ba.p.x,ba.p.y, R);
}

void drawWall(World &wa) ///Dessine les murs
{
    int i;
    color(255,255,255);
    for (i= 0; i< wa.nbW ; i++)
    {
        line(wa.tab[i].minp.x,wa.tab[i].minp.y,wa.tab[i].maxp.x, wa.tab[i].maxp.y);
    }
}

bool CollisionDroite (const Wall &w, Ball &ba) ///Dis si il y colision avec segment (mur)
{
    Vec2 A = w.minp;
    Vec2 B = w.maxp;
    Vec2 C = ba.p;

    Vec2 u;
    u.x = B.x - A.x;
    u.y = B.y - A.y;

    Vec2 AC;
    AC.x = C.x - A.x;
    AC.y = C.y - A.y;

    float numerateur = u.x*AC.y - u.y*AC.x;   // norme du vecteur v

    if (numerateur <0)

        numerateur = -numerateur ;   // valeur absolue ; si c'est négatif, on prend l'opposé.

    float denominateur = sqrt(u.x*u.x + u.y*u.y);  // norme de u
    float CI = numerateur / denominateur;
    if (CI < R)
    {
        return true;
    }
    else
    {
        return false;
    }

}

bool isBallCollidingWithSegment(const Wall &wa, Ball &ba)
{
    Vec2 A = wa.minp; ///
    Vec2 B = wa.maxp;
    Vec2 C = ba.p;

    if (CollisionDroite(wa, ba) ==  false)
    {
        return false;
    }

    Vec2 AB,AC,BC;
    AB.x = B.x - A.x;
    AB.y = B.y - A.y;
    AC.x = C.x - A.x;
    AC.y = C.y - A.y;
    BC.x = C.x - B.x;
    BC.y = C.y - B.y;

    float pscal1 = AB.x*AC.x + AB.y*AC.y; ///produit scalaire
    float pscal2 = (-AB.x)*BC.x + (-AB.y)*BC.y; ///produit scalaire
    if (pscal1 >= 0 && pscal2 >= 0)
    {
        return true;
    }
    return false;

}

Vec2 ProjectionI(const Wall& wa,Ball &ba) ///Renvoie le point d'impact de la balle pour le calcul de la tragectoire de la balle pour le rebond
{
    Vec2 A = wa.minp;
    Vec2 B = wa.maxp;
    Vec2 C = ba.p;

    Vec2 u,AC;
    u.x = B.x - A.x;
    u.y = B.y - A.y;
    AC.x = C.x - A.x;
    AC.y = C.y - A.y;
    float ti = (u.x*AC.x + u.y*AC.y)/(u.x*u.x + u.y*u.y);
    Vec2 I;
    I.x = A.x + ti*u.x;
    I.y = A.y + ti*u.y;
    return I;
}

Vec2 GetNormale(const Wall& wa,Ball &ba) ///Calcul la norme
{
    Vec2 A = wa.minp;
    Vec2 B = wa.maxp;
    Vec2 C = ba.p;

    Vec2 AC,u,N;
    u.x = B.x - A.x;
    u.y = B.y - A.y;
    AC.x = C.x - A.x;
    AC.y = C.y - A.y;
    float parenthesis = u.x*AC.y-u.y*AC.x;  // calcul une fois pour les deux
    N.x = -u.y*(parenthesis);
    N.y = u.x*(parenthesis);
    // normalisons
    float norme = sqrt(N.x*N.x + N.y*N.y);
    N.x/=norme;
    N.y/=norme;
    return N;
}

Vec2 CalculerVecteurV2(Vec2 v,Vec2 N) /// v :le vecteur qui produit la colision, N : la Norm au vecteur de colision.
{
    Vec2 v2;
    float pscal = (v.x*N.x +  v.y*N.y);
    v2.x = v.x -2*pscal*N.x;
    v2.y = v.y -2*pscal*N.y;
    return v2; ///Vecteur de rebond
}


void checkForCollisionBetweenBallAndWall(Ball& ball, const Wall& w)
{
    if ((isBallCollidingWithSegment(w, ball)) == true)
    {
        Vec2 Norm = GetNormale(w, ball); ///Calcul de la norme
        Vec2 Imp = ProjectionI(w, ball); ///Le point d'impact
        Vec2 col = CalculerVecteurV2(ball.v, Norm);///Calcul de la nouvelle trajectoire

        ball.v = col;
        ///ball.p.x = ball.p.x + col.x;
        // ball.v.x = -ball.v.x;
        // ball.v.y = -ball.v.y;
        // ball.v = FRICTION * ball.v;
    }
}

void checkForCollisionsWithWorld(Ball& ball, const World& world) ///Boucle qui répète pour chaque mur si il y a colision avec la balle
{
    // Pour chaque mur du monde...
    for (const auto& wall : world.tab)
    {
        // On résoud une potentielle collision avec la balle.
        checkForCollisionBetweenBallAndWall(ball, wall);
    }
}
//avec l'aide de la page : https://openclassrooms.com/fr/courses/1374826-theorie-des-collisions/1375352-formes-plus-complexes

void updateOnearth(Ball& ba)///Met à jour la balle en fonction des propriétés de la terre énoncé dans la procédure précédante
{
    colisionWindow(ba);
    updateBall(ba);
    forceGravity(ba);
}
void DrawImage(int i, int x,int y,World &w) ///Procédure qui affiche pour un i donné soit l'image du 5, 10 ou 20 aux coordonnées x et y entré
{
    ///World &w;
    switch(i)
    {
    case 5 :
        image_draw(w.im.im_five, x, y, 30, 30);
        break;
    case 10 :
        image_draw(w.im.im_ten, x, y, 30, 30);
        break;
    case 20 :
        image_draw(w.im.im_five, x, y, 30, 30);
        break;
    default :
        break;
    }
}

void updateScore(int &i) ///Incrémentation du score 0
{
    color(255,255,255);
    print (360,460, i);
}

void AllScoreInTheBox(World &w) ///Ajout de toutes les images de score
{
    {
        //Images des 5 points
        DrawImage(5, 665, 5,w); ///dessine 5 aux coordonnées x = 360 et y = 5
        DrawImage(5, 35, 5,w); ///dessine 5 aux coordonnées x = 360 et y = 5
        DrawImage(5, 360, 5,w); ///dessine 5 aux coordonnées x = 360 et y = 5
        DrawImage(5, 360, 5,w); ///dessine 5 aux coordonnées x = 360 et y = 5
    }
    {
        //Images des 10 points
        DrawImage(10, 360, 5,w); ///dessine 10 aux coordonnées x = 360 et y = 5
        DrawImage(10, 360, 5,w); ///dessine 10 aux coordonnées x = 360 et y = 5
        DrawImage(10, 360, 5,w); ///dessine 10 aux coordonnées x = 360 et y = 5
        DrawImage(10, 360, 5,w); ///dessine 10 aux coordonnées x = 360 et y = 5
    }
    {
        //Images des 20 points
        DrawImage(20, 360, 5,w); ///dessine 20 aux coordonnées x = 360 et y = 5
        DrawImage(20, 350, 5,w); ///dessine 20 aux coordonnées x = 50 et y = 5
    }

}

void drawAll (World &w, Ball &ba) ///Procédure qui englobe les autres draw
{
    drawWall(w);
    drawB(ba);
    AllScoreInTheBox(w);
}



int main(int, char** )
{
    srand(time(NULL));
    Ball ba;
    World w;
    Menu m;
    winInit("Dans la boite", DIMWX, DIMWY);
    backgroundColor( 0, 0, 0);
    initTheWholeWorld(w, ba);
    print(ba);
    bool stop=false;
    menu_add( m, "20 POINTS");
    menu_add( m, "10 POINTS");
    menu_add( m, "5 POINTS");
    while( !stop )
    {
        winClear();
        menu_draw(m, 10,70, 100, 102);
        /*switch(menu_select(m))
        {
            case 0 : ///*on met ici le cas où si balle dans boite alors score + 20 * 5; draw(b); break;
            case 1 : ; draw(dat); break;
            case 2 : ; draw(dat); break;
            default: ; draw(jeu); break; ///jeu : Pas d'action donc jeu bouge pas
        }
        */
        int i = 0; ///INCREMENTATION A FAIRE
        print (295,461, "score :"); ///REMPLACER PAR UN IMAGE_DRAW
        updateScore(i);
        /*if (isKeyPressed(SDLK_SPACE))
        {
            initBall(ba);
        }
        */
        updateOnearth(ba);
        checkForCollisionsWithWorld(ba,w);
        ///DebugCol(w,ba);
        drawAll(w,ba);
        ///Pour avoir des coordonnées plus facilement
        if(isMousePressed(SDL_BUTTON_LEFT))
        {
            int x,y;
            mousePos(x,y);
            cout << "X est : " << x << " et Y est : " << y << endl;
        }
        ///
        stop = winDisplay();
    }
    winQuit();
    return 0;
}

