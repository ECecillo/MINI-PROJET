#include <Grapic.h>

using namespace grapic;

const int MAX= 100;

const int DIMW = 500;

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

float norm(const Vec2 v)
{
	return sqrt(v.x*v.x + v.y*v.y);
}

struct Couleur
{
    int r;
    int g;
    int b;
};

struct Marchand
{
    Vec2 p;
    float prix;
    Couleur col;
    int nbc;
};
struct LesMarchands
{
    Marchand tab[MAX];
    int n;
};

void init (LesMarchands &lm, int nm)
{
    int i;
    lm.n= nm;
    for (i=0; i<lm.n; i++)
    {
        lm.tab[i].p= make_vec2(rand()%DIMW,rand()%DIMW);
        lm.tab[i].prix = 2 + rand()%5;
        lm.tab[i].col.r = 2 + rand()%255;
        lm.tab[i].col.g = 2 + rand()%255;
        lm.tab[i].col.b = 2 + rand()%255;
    }
}

void drawMarchand (LesMarchands lm)
{
    int i;
    color(255,0,0);
    for (i=0; i<lm.n; i++)
    {
        circleFill(lm.tab[i].p.x,lm.tab[i].p.y, 2);
    }
}

int ChoixMarchand (int i, int j, LesMarchands lm)
{
    int im= 0;
    float prix, prix_l;
    Vec2 pos = make_vec2(i, j);
    prix= lm.tab[0].prix + norm(pos-lm.tab[0].p);
    int l;
    for (l=1; l<lm.n; l++)
    {
        prix_l = lm.tab[l].prix + norm(pos - lm.tab[l].p);///nouveau prix issue du calcul de la distance
        if (prix_l < prix)
        {
            im = l;
            prix= prix_l;
        }
    }
    return im;
}

void vente (LesMarchands &lm, bool aff)
{
    int i, j, im;
    for (i=0; i<lm.n; i++)
    {
        lm.tab[i].nbc= 0;
        for (i=0; i<DIMW; i++)
        {
            for (j=0; j<DIMW; j++)
            {
                im= ChoixMarchand (i, j, lm);
                ///renvoie le n° du marchand
                lm.tab[im].nbc++;
                if (aff)
                {
                    put_pixel (i,j,lm.tab[im].col.r,lm.tab[im].col.g,lm.tab[im].col.b);
                }
            }
        }
    }
}

void MiseAjour (LesMarchands &lm)
{
    float revenu;
    float revenu_mv;
    Vec2 pos;
    float prix;
    LesMarchands lmav, lmap = lm; ///lmav : les marchands avant, lmap : les marchands après.
    int j, i;
    Vec2 dp[4]= {make_vec2(-1,0),make_vec2(1,0),make_vec2(0,1),make_vec2(0,-1)};
    for(i=0; i<lm.n ; i++)
    {
        revenu = lmav.tab[i].prix*lmav.tab[i].nbc;
        pos = lmav.tab[i].p;
        for (j=0; j < 4; j++)
        {
            lm= lmav;
            lm.tab[i].p = lm.tab[i].p + dp[j];
            vente (lm, false);
            revenu_mv = lm.tab[i].nbc*lm.tab[i].prix;
            if (revenu_mv > revenu)
            {
                revenu = revenu_mv;
                pos = lm.tab[i].p;
            }
            lm.tab[i].p = pos;
        }

        revenu = lm.tab[i].nbc*lm.tab[i].prix;
        vente (lm, false);
        prix = lm.tab[i].prix;
        for (j=-1; j<= 1; j++)
        {
            lm= lmav;
            lm.tab[i].prix +=j;
            vente (lm, false);
            revenu_mv = lm.tab[i].nbc*lm.tab[i].prix;
            if (revenu_mv > revenu)
            {
                revenu = revenu_mv;
                prix = lm.tab[i].prix;
            }
        }
        lmap.tab[i].prix= prix;
    }
    lm= lmap;
}

int main(int , char** )
{
    srand(time(NULL));
    LesMarchands lm;
    init(lm, 6);
    bool stop=false;
	winInit("IceScream", DIMW, DIMW);
	bool fin = false;
    backgroundColor( 100, 50, 200 );
	while( !stop )
    {
        winClear();
        vente (lm, true);
        drawMarchand(lm);
        MiseAjour(lm);
        stop = winDisplay();
    }
    winQuit();
	return 0;
}

