#include<Grapic.h>

using namespace grapic;

const int NB_INSECTS = 50;
const int DIMW = 500;

struct Vec2
{
    float x, y;
};

Vec2 make_Vec2(float x, float y)
{
    Vec2 v;
    v.x = x;
    v.y = y;
    return v;
}

float distance(Vec2 a, Vec2 b)
{
    return sqrt((b.x-a.x)*(b.x-a.x) + (b.y-a.y)*(b.y-a.y));
}

struct Color
{
    int r;
    int g;
    int b;
};

Color make_Color(int r, int g, int b)
{
    Color c;
    c.r = r;
    c.g = g;
    c.b = b;
    return c;
}

struct insect
{
    Vec2 p;
    Color c;
    float t;
    float duree;
};

struct popInsect
{
    insect T[NB_INSECTS];
    int nbi;
    Color good;
    int range;
    Image im_fond;
};

void init_Insect(insect& ins, Color good, int range)
{
    ins.p = make_Vec2(rand()%DIMW, rand()%DIMW);
    ins.c = make_Color(good.r + (rand()%(2*range+1)-range),
                       good.g + (rand()%(2*range+1)-range),
                       good.b + (rand()%(2*range+1)-range));
    // Clamp des couleurs entre 0 et 255
    if(ins.c.r < 0) ins.c.r = 0; if(ins.c.r > 255) ins.c.r = 255;
    if(ins.c.g < 0) ins.c.g = 0; if(ins.c.g > 255) ins.c.g = 255;
    if(ins.c.b < 0) ins.c.b = 0; if(ins.c.b > 255) ins.c.b = 255;
    ins.t = elapsedTime();
    ins.duree = -1;
}

void Init(popInsect& pop)
{
    pop.nbi = NB_INSECTS;
    pop.good = make_Color(127, 127, 127);
    pop.range = 127;
    pop.im_fond = image("data/tournesol.jpg");
    for(int i = 0; i < pop.nbi; i++)
    {
        init_Insect(pop.T[i], pop.good, pop.range);
    }
}

void minMaxLifeDuration(popInsect pop, float& mini, float& maxi)
{
    // Trouver le premier insecte mort (duree != -1)
    int first = -1;
    for(int i = 0; i < pop.nbi; i++)
    {
        if(pop.T[i].duree != -1)
        {
            first = i;
            break;
        }
    }
    
    if(first == -1)
    {
        mini = 0;
        maxi = 0;
        return;
    }
    
    mini = pop.T[first].duree;
    maxi = pop.T[first].duree;
    
    for(int i = 0; i < pop.nbi; i++)
    {
        if(pop.T[i].duree != -1)
        {
            if(pop.T[i].duree < mini) mini = pop.T[i].duree;
            if(pop.T[i].duree > maxi) maxi = pop.T[i].duree;
        }
    }
}

Color averageColorOfGoodInsect(popInsect pop, float duree_limite)
{
    int nb = 0;
    Color c = make_Color(0,0,0);
    for(int i = 0; i < pop.nbi; i++)
    {
        if(pop.T[i].duree > duree_limite && pop.T[i].duree != -1)
        {
            c.r += pop.T[i].c.r;
            c.g += pop.T[i].c.g;
            c.b += pop.T[i].c.b;
            nb ++;
        }
    }
    if(nb == 0)
    {
        return make_Color(127,127,127);
    }
    else
    {
        c.r = c.r / nb;
        c.g = c.g / nb;
        c.b = c.b / nb;
        return c;
    }
}

void draw(popInsect pop)
{
    int cpt = 0;
    int x, y;
    mousePos(x,y);
    
    if(pop.im_fond.id != -1)
        image_draw(pop.im_fond, 0, 0, DIMW, DIMW);
    else
        backgroundColor(240,230,255);
    
    for(int i = 0; i < pop.nbi; i++)
    {
        if(pop.T[i].duree == -1)
        {
            color(pop.T[i].c.r, pop.T[i].c.g, pop.T[i].c.b);
            circleFill(pop.T[i].p.x, pop.T[i].p.y, 3);
            cpt++;
        }
    }
    
    color(pop.good.r, pop.good.g, pop.good.b);
    rectangleFill(10, DIMW - 40, 30, DIMW - 20);
    color(0,0,0);
    print(DIMW - 40, DIMW - 40, cpt);
    circle(x, y, 20);
}

void Update(popInsect& pop)
{
    int x, y, nbviv = 0;
    float d, m, M, milieu;
    Color best;
    Vec2 mouse;
    mousePos(x,y);
    mouse = make_Vec2(x, y);
    
    for(int i = 0; i < pop.nbi; i++)
    {
        d = distance(mouse, pop.T[i].p);
        if(d < 20 && pop.T[i].duree == -1)
        {
            pop.T[i].duree = elapsedTime() - pop.T[i].t;
        }
        else if(pop.T[i].duree == -1)
        {
            nbviv ++;
        }
    }
    
    if(nbviv == 0)
    {
        minMaxLifeDuration(pop, m, M);
        milieu = m + 0.8 * (M - m);
        best = averageColorOfGoodInsect(pop, milieu);
        pop.good = best;
        for(int i = 0; i < pop.nbi; i++)
        {
            init_Insect(pop.T[i], best, pop.range);
        }
    }
}

int main(int, char**)
{
    srand(time(NULL));
    winInit("Evolution des insectes - Camouflage", DIMW, DIMW);
    backgroundColor(240, 230, 255);
    
    popInsect li;
    Init(li);
    
    bool stop = false;
    while(!stop)
    {
        winClear();
        
        draw(li);
        Update(li);
        
        stop = winDisplay();
    }
    winQuit();
    return 0;
}