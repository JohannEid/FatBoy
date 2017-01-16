#include <allegro.h>
#include <time.h>
#include "acteur.h"


#define NACTEUR 10
#define SKATE 4
#define COURSE 4
#define NINJA 4
#define NSEQUENCE 3
#define BLOOD 8
#define SOUFFLE 4
#define MINEUR 4

t_acteur * creerActeur()
{

    t_acteur *acteur;


    acteur = (t_acteur *)malloc(sizeof(t_acteur)); // allocation
    // on appelle le programme du chargement des bmp acteurs
     chargementimageacteur(acteur);

    // Initialisation
    acteur->creuse=0;
acteur->souffleur=0;
acteur->pause =0;

acteur->posx = 140;
acteur->posy = rand()%1000-1000; //hauteur aleatoire au dessus du trou dans le toit pour donner une impression de chute d'acteurs multiples

acteur->chute=5;
acteur->vith=5;
  acteur ->cptdx=0;
    acteur ->tmpdx=1;
acteur ->cptimg=0;
    acteur ->tmpimg=5;
acteur->imgcourante1=0;
acteur->imgcourante2=0;
acteur->imgcourante3=0;
acteur->imgcourante4=0;
acteur->imgcourante5=0;
acteur->imgcourante6=0;
acteur->vie =1;
acteur->etat=2;
acteur->trous=0;
acteur->trousc=0;
acteur->points=0;

acteur->tx =acteur->img5[0]->w;
acteur->ty =acteur->img5[0]->h;



    return acteur;
}
void chargementimageacteur(t_acteur*acteur)
{
int i,j,p,k,r,l;
   ///CHARGEMENT DE NOS ANIMATIONS
        for (r=0;r<SOUFFLE;r++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf( acteur->nomfichier4,"souffle/image%d.bmp",r);

        acteur->img4[r] = load_bitmap(acteur->nomfichier4,NULL);
        if (! acteur->img4[r]){
            allegro_message("pas pu trouver %s",acteur->nomfichier4);
            exit(EXIT_FAILURE);
        }
    }
     for (l=0;l<MINEUR;l++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf( acteur->nomfichier5,"mineur/image%d.bmp",l);

        acteur->img5[l] = load_bitmap(acteur->nomfichier5,NULL);
        if (! acteur->img5[l]){
            allegro_message("pas pu trouver %s",acteur->nomfichier5);
            exit(EXIT_FAILURE);
        }

    }

       for (i=0;i<SKATE;i++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf( acteur->nomfichier,"skate/image%d.bmp",i);

        acteur->img[i] = load_bitmap(acteur->nomfichier,NULL);
        if (! acteur->img[i]){
            allegro_message("pas pu trouver %s",acteur->nomfichier);
            exit(EXIT_FAILURE);
        }
    }
      for (j=0;j<COURSE;j++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(acteur->nomfichier1,"course/image%d.bmp",j);

        acteur->img1[j] = load_bitmap(acteur->nomfichier1,NULL);
        if (! acteur->img1[j]){
            allegro_message("pas pu trouver %s",acteur->nomfichier1);
            exit(EXIT_FAILURE);
        }
    }

           for (p=0;p<NINJA;p++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf(acteur->nomfichier2,"ninja/image%d.bmp",p);

        acteur->img2[p] = load_bitmap(acteur->nomfichier2,NULL);
        if (! acteur->img2[p]){
            allegro_message("pas pu trouver %s",acteur->nomfichier2);
            exit(EXIT_FAILURE);

    }
    }

        for (k=0;k<BLOOD;k++)
    {
        // sprintf permet de faire un printf dans une chaine
        sprintf( acteur->nomfichier3,"blood/sang%d.bmp",k);

        acteur->img3[k] = load_bitmap(acteur->nomfichier3,NULL);
        if (! acteur->img3[k]){
            allegro_message("pas pu trouver %s",acteur->nomfichier3);
            exit(EXIT_FAILURE);
        }

    }

    acteur->changeEtat=load_bitmap("menuchange.bmp",NULL);

    if(!acteur->changeEtat)
    {
        allegro_message("pb chargement menuchange.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
   acteur->creuser=load_bitmap("fleches.bmp",NULL);

    if(!acteur->creuser)
    {
        allegro_message("pb chargement fleches.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
acteur->fleshsou=load_bitmap("flechesou.bmp",NULL);

    if(!acteur->fleshsou)
    {
        allegro_message("pb chargement flechesou.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


acteur->trou=load_bitmap("trou.bmp",NULL);
     if(!acteur->trou)
    {
        allegro_message("pb chargement trou.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
acteur->trougauche=load_bitmap("trougauche.bmp",NULL);
     if(!acteur->trou)
    {
        allegro_message("pb chargement trougauche.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
acteur->troudroit=load_bitmap("troudroit.bmp",NULL);
     if(!acteur->trou)
    {
        allegro_message("pb chargement troudroit.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

}



void remplirTabActeurs(t_acteur * tab[NACTEUR]) // remplir un tableau avec des (pointeurs sur) les acteurs créés
{
    int i;

    for (i=0;i<NACTEUR;i++)
        tab[i]=creerActeur();
}


// Actualiser un acteur
void actualiserActeur(BITMAP *page, t_acteur *acteur,int k,BITMAP*cartecollision,int screenx )
{
pente(cartecollision, acteur);
    //on mémorise l'état
    if(acteur->etat!=3)
    acteur->etatprec=acteur->etat;

if ((acteur->pause==0)&&(acteur->vie!=0)&&(acteur->vie!=3)&&(acteur->vie!=4))//etat normal fonctionne tant qu'on est pas dans le souffle et qu'aucun menu n'est activé
{

    acteur->depx=0; //vitesse verticale nulle
    acteur->depy=acteur->chute;

if((getpixel(cartecollision,acteur->posx+acteur->tx/2,acteur->posy+acteur->ty)==makecol(255,255,255)) ||
    (getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy+acteur->ty)==makecol(255,255,255)) ||
       (getpixel(cartecollision,acteur->posx,acteur->posy+acteur->ty)==makecol(255,255,255))&&(acteur->vie==1)) //si il y a du blanc a gauche/au milieu/a droite de la base du rectangle
    {
        acteur->depy=0;         //on arrete le mvt vertical
        acteur->depx=acteur->vith;  //son vecteur deplacement prend la valeur de la vitesse
    }


     if(getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy+acteur->ty/4)==makecol(255,255,255)&&(acteur->vie==1)) //si le milieu de son cote droit touche un pixel blanc
        {
            acteur->vith=-acteur->vith; //on inverse la vitesse
            acteur->depx=acteur->vith;  //son deplacement horizontal prend la valeur de la vitesse maintenant inversee
        }

    if(getpixel(cartecollision,acteur->posx,acteur->posy+acteur->ty/4)==makecol(255,255,255)&&(acteur->vie==1)) //milieu du cote gauche
        {
            acteur->vith=-acteur->vith;
            acteur->depx=acteur->vith;
        }



///ON REPERE LES GAGNANTS
  if(((getpixel(cartecollision,acteur->posx+acteur->tx/2,acteur->posy+acteur->ty)==makecol(0,255,255)) ||
        (getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy+acteur->ty)==makecol(0,255,255)) ||
       (getpixel(cartecollision,acteur->posx,acteur->posy+acteur->ty)==makecol(0,255,255)))&&(acteur->vie!=0))

       {
           acteur->vie=0;
           acteur->points=10;
       }



///ON REPERE LES SOUFFLES
if(getpixel(cartecollision,acteur->posx+(acteur->tx)/2,acteur->posy-(acteur->ty))==makecol(255,130,180)&&(k==0)&&(acteur->depy==0))// souffle vers le haut variable k permet d'assurer pas plus d'un personnage dans le souffle à la fois
{

acteur->vie=2;
}
if(getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy+acteur->ty/2)==makecol(255,70,120)&&(k==0)&&(acteur->depy==0)) //souffle vers droite on ne peut pas monter lors d'une chute
        {
acteur->vie=3;
        }


    if(getpixel(cartecollision,acteur->posx,acteur->posy+acteur->ty/2)==makecol(255,100,150)&&(acteur->vie==1)&&(acteur->depy==0)) //souffle gauche
        {
          acteur->vie=4;
        }
if ((getpixel(cartecollision,acteur->posx,acteur->posy+acteur->ty/2)==makecol(255,70,120))&&(getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy+acteur->ty/2)==makecol(0,0,0)) &&(acteur->depx<0)&&(acteur->vie==1)) // si le personage prend le souffle dans le mauvais sens il explose...
{
    acteur->vie=7;
}
if ((getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy+acteur->ty/2)==makecol(255,100,150))&&(getpixel(cartecollision,acteur->posx,acteur->posy+acteur->ty/2)==makecol(0,0,0)) &&(acteur->depx>0)&&(acteur->vie==1)) // si le personage prend le souffle dans le mauvais sens il explose...
{
    acteur->vie=7;
}
///ON GERE CREUSER
if ((getpixel(cartecollision,acteur->posx+(acteur->tx),acteur->posy+(acteur->ty)/2)==makecol(150,70,255))&&(acteur->etat==6))
{
acteur->creuse=1;
}
if((getpixel(cartecollision,acteur->posx,acteur->posy+(acteur->ty)/2)==makecol(180,100,255))&&(acteur->etat==6))
{
acteur->creuse=2;
}

if(((getpixel(cartecollision,acteur->posx+acteur->tx/2,acteur->posy+acteur->ty)==makecol(120,40,255)) ||
        (getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy+acteur->ty)==makecol(120,40,255)) ||
       (getpixel(cartecollision,acteur->posx,acteur->posy+acteur->ty)==makecol(120,40,255)))&&(acteur->etat==6))//le +5 car parfois marge d'erreur
    {
       acteur->creuse=3;
    }
if(getpixel(cartecollision,acteur->posx+(acteur->tx)+50,acteur->posy+(acteur->ty)/2)==makecol(0,0,0)&&(acteur->creuse==1))
{
acteur->trousc=0;
acteur->creuse=0;
acteur->etat=2;
acteur->etatprec=2;
}

if((getpixel(cartecollision,acteur->posx-50,acteur->posy+(acteur->ty)/2==makecol(0,0,0))&&(acteur->creuse==2))&&(acteur->trous>1))
   {
acteur->trousc=0;
acteur->creuse=0;
acteur->etat=2;
acteur->etatprec=2;

   }
if((getpixel(cartecollision,acteur->posx+(acteur->tx)/2,acteur->posy+(acteur->ty)+15)==makecol(0,0,0))&&(acteur->creuse==3)&&(acteur->trous>1))
   {
acteur->trousc=0;
acteur->creuse=0;
acteur->etat=2;
acteur->etatprec=2;
   }
if((getpixel(cartecollision,acteur->posx+(acteur->tx),acteur->posy+(acteur->ty)/2)==makecol(150,70,255)&&(acteur->etat==6)))//si on repère un trou vers la droite le mineur va vers lui

{
    acteur->depx=5;
}
if((getpixel(cartecollision,acteur->posx+(acteur->tx),acteur->posy+(acteur->ty)/2)==makecol(180,100,255)&&(acteur->etat==6)))//si on repère un trou vers la gauche le mineur va vers lui

{
    acteur->depx=-5;
}
/*if((acteur->depx==0)&&(acteur->etat!=6)&&(acteur->etat!=4)&&((getpixel(cartecollision,acteur->posx+acteur->tx/2,acteur->posy+acteur->ty+50)!=makecol(255,255,255)) ||
        (getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy+acteur->ty+50)==makecol(255,255,255)) ||
       (getpixel(cartecollision,acteur->posx,acteur->posy+acteur->ty+50)==makecol(255,25,255)))) //su pas de déplacement horizontale notre perso prend un skate!
{
    acteur->etat=3;
}*/
else
{acteur->etat=acteur->etatprec;}

    acteur->posx = acteur->posx + acteur->depx; //on actualise le mvt
    acteur->posy = acteur->posy + acteur->depy;


}

  timingacteur(acteur);


 if ((acteur->pause==1)&&(acteur->vie==1))
{
acteur->depx =0;
acteur -> depy =0;
draw_sprite(page,acteur->changeEtat,acteur->posx+50-screenx,acteur->posy+50);//permet de changer d'état
/*draw_sprite(page,acteur->changeEtatBeau,acteur->posx+50,acteur->posy+50);*/

}
else if ((acteur->pause==2)&&(acteur->vie==1))
{
acteur->depx =0;
acteur -> depy =0;
draw_sprite(page,acteur->creuser,acteur->posx-screenx,acteur->posy+80);//on dessine les fleches pour creuser

}


else if ((acteur->pause==6)&&(acteur->vie==1))

{

acteur->depx=0;
acteur->depy=0;


draw_sprite(page,acteur->fleshsou,acteur->posx+(acteur->tx/2)-screenx,acteur->posy-30);// on dessine les fleches de souffles

}
if(acteur->vie==0)//mort
{
acteur->pause=60;
acteur->souffleur=0; // parfois les personnes arriva
}

if(acteur->vie==2)//inertie
{

if(acteur->etat!=3)   // stocke etat
{acteur->etatprec=acteur->etat;
acteur->etat=3;}
acteur->depx=0;
acteur->depy=-20; // si on repère le souffle on va vers le haut
acteur->souffleur++;

    acteur->posx = acteur->posx + acteur->depx; //on actualise le mvt
    acteur->posy = acteur->posy + acteur->depy;
 if(((getpixel(cartecollision,acteur->posx+acteur->tx/2,acteur->posy+acteur->ty)==makecol(255,255,255)) ||
        (getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy+acteur->ty)==makecol(255,255,255)) ||
       (getpixel(cartecollision,acteur->posx,acteur->posy+acteur->ty)==makecol(255,255,255))&&(acteur->vie==1))&&(getpixel(cartecollision,acteur->posx,acteur->posy+(acteur->ty)/2+20)==makecol(0,0,0)))
        // on arrete une fois qu'on touche un sol blanc et qu'on a du noir en haut


   {
    acteur->vie=1; // fin de l'inertie retour à la vie normale :)
    acteur->souffleur=0; // remet trous à 0
    //remet etat avant souffle
   if(acteur->etatprec!=3)
    acteur->etat = acteur->etatprec;
   }
// si on sort du niveau si le joueur a active le souffle sans qu'il y ait de passerelle en haut

if((getpixel(cartecollision,acteur->posx+acteur->tx/2,acteur->posy)==makecol(254,0,0)) ||
        (getpixel(cartecollision,acteur->posx,acteur->posy)==makecol(254,0,0)) ||
       (getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy)==makecol(254,0,0)))
    {


        acteur->vie=7;
        acteur->souffleur=0;
    }

}

/// DIFFERENTS ETATS AVEC LE SOUFFLE
if (acteur->vie==3)

{
if(acteur->etat!=3)
{acteur->etatprec=acteur->etat;
acteur->etat=3;}
acteur->depx=20; // on va vers la droite
acteur->depy=0;

acteur->souffleur++;
 acteur->posx = acteur->posx + acteur->depx; //on actualise le mvt
acteur->posy = acteur->posy + acteur->depy;
if((getpixel(cartecollision,acteur->posx+acteur->tx/2,acteur->posy+acteur->ty+20)==makecol(255,255,255)) ||
        (getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy+acteur->ty+20)==makecol(255,255,255)) ||// si on toucbe une passerelle on s'arrete
       (getpixel(cartecollision,acteur->posx,acteur->posy+acteur->ty+20)==makecol(255,255,255)))
       {
            acteur->vie=1; // fin de l'inertie retour à la vie normale :)
    acteur->souffleur=0;

    if(acteur->etatprec!=3)
    acteur->etat = acteur->etatprec;
       }
// si on prend un mur blanc on meurt
if ((getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy)==makecol(255,255,255)))
{

acteur->vie=7;
acteur->souffleur=0;

}


       }


if (acteur->vie==4)
{

if(acteur->etat!=3)   // stocke etat
{acteur->etatprec=acteur->etat;
acteur->etat=3;}
acteur->depx=-20;
acteur->depy=0;

acteur->souffleur++;
 acteur->posx = acteur->posx + acteur->depx; //on actualise le mvt
acteur->posy = acteur->posy + acteur->depy;
if((getpixel(cartecollision,acteur->posx+acteur->tx/2,acteur->posy+acteur->ty)==makecol(255,255,255)) ||
        (getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy+acteur->ty)==makecol(255,255,255)) ||
       (getpixel(cartecollision,acteur->posx,acteur->posy+acteur->ty)==makecol(255,255,255)))
       {
            acteur->vie=1; // fin de l'inertie retour à la vie normale :)
      acteur->souffleur=0;
      if(acteur->etatprec!=3)
      acteur->etat = acteur->etatprec;
       }

}

if((getpixel(cartecollision,acteur->posx,acteur->posy-(acteur->ty/2))==makecol(255,255,255))&&(acteur->vie==4)) // si on se prend un mur vers la gauche alors qu'il y a le souffle
{
acteur->vie=7;
acteur->souffleur=0;
}
///ZONES DE MORT
if((getpixel(cartecollision,acteur->posx+acteur->tx/2,acteur->posy+acteur->ty)==makecol(255,0,0)) ||
        (getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy+acteur->ty)==makecol(255,0,0)) ||// si on toucbe une zone mortelle
       (getpixel(cartecollision,acteur->posx,acteur->posy+acteur->ty)==makecol(255,0,0)))
       {
           acteur->vie=7;
       }

if(acteur->vie==7)
{
    acteur->depx=0;
    acteur->depy=0;
    acteur->etat=4;
}
if(acteur->vie==8)
{
    acteur->depx=0;
    acteur->depy=0;
    acteur->etat=5;
}

if(acteur->vie==10)
{

    acteur->etat=4;

}


}
void pente(BITMAP *cartecollision, t_acteur *acteur)
{
    // Pente vers la droite
if( (getpixel(cartecollision, acteur->posx+acteur->tx-20,acteur->posy+acteur->ty)==makecol(255,255,255)) &&
    (getpixel(cartecollision, acteur->posx+acteur->tx-20, acteur->posy+acteur->ty-5) == makecol(255,255,255))
    && acteur->depx>0) //Si le deplacement en x>0 et que les pixels au pied du joueur et devant lui sont blancs
{
    acteur->posy=acteur->posy-5; //on incremente la position en y
}

// pente vers la gauche
if( (getpixel(cartecollision, acteur->posx+20,acteur->posy+acteur->ty)==makecol(255,255,255)) &&
    (getpixel(cartecollision, acteur->posx+20, acteur->posy+acteur->ty-5) == makecol(255,255,255))
    && acteur->depx<0)
{
    acteur->posy=acteur->posy-5;
}
}
void timingacteur(t_acteur * acteur)
{
     ///ON GERE LE TIMING
      acteur->cptdx++;
    if (acteur->cptdx >= acteur->tmpdx){
        acteur->cptdx=0;
        acteur->x = acteur->x + acteur->dx;
    }

    // gestion enchainement des images
    // incrémenter imgcourante une fois sur tmpimg
    acteur->cptimg++;

    if (acteur->cptimg >= acteur->tmpimg){
        acteur->cptimg=0;


            if (acteur->etat ==1)
            acteur->imgcourante1++;
         if (acteur->etat ==2)
            acteur->imgcourante2++;
      if (acteur->etat ==3)
            acteur->imgcourante3++;
            if(acteur->etat==4)
                acteur->imgcourante4++;
      if(acteur->etat==5)
                acteur->imgcourante5++;
         if (acteur->etat==6)
        acteur->imgcourante6++;

      acteur->cptdx++;
    if (acteur->cptdx >= acteur->tmpdx){
        acteur->cptdx=0;
        acteur->x = acteur->x + acteur->dx;
    }

    // gestion enchainement des images
    // incrémenter imgcourante une fois sur tmpimg
    acteur->cptimg++;

    if (acteur->cptimg >= acteur->tmpimg){
        acteur->cptimg=0;





        if ( acteur->imgcourante1 >= SKATE )


            {
               acteur->imgcourante1=0;
            }
        if( acteur->imgcourante2 >= COURSE )
        {
               acteur->imgcourante2=0;

        }


        if(acteur->imgcourante3 >= NINJA )
            {
                   acteur->imgcourante3=0;
            }
  if(acteur->imgcourante4 >= BLOOD )
            {
                   acteur->vie=0;
            }
  if(acteur->imgcourante5 >= SOUFFLE )
            {
                   acteur->imgcourante5=0;
            }

    }


        if ( acteur->imgcourante1 >= SKATE )


            {
               acteur->imgcourante1=0;
            }
        if( acteur->imgcourante2 >= COURSE )
        {
               acteur->imgcourante2=0;

        }


        if(acteur->imgcourante3 >= NINJA )
            {
                   acteur->imgcourante3=0;
            }
  if(acteur->imgcourante4 >= BLOOD )
            {
                   acteur->vie=0;
            }
  if(acteur->imgcourante5 >= SOUFFLE )
            {
                   acteur->imgcourante5=0;
            }
if(acteur->imgcourante6 >= MINEUR)
{
    acteur->imgcourante6=0;
}
    }

}













// Gérer l'évolution de l'ensemble des acteurs
void actualiserTabActeurs(BITMAP * cartecollision,BITMAP *page,t_acteur * tab[NACTEUR],int screenx,int niveau,BITMAP* decor)
{
    int i;
    int p=0;
    int j;
    int k=0;


    for (j=0;j<NACTEUR;j++)
    {

   if(tab[j]->trousc!=0)
   p++;
    if(tab[j]->souffleur!=0)
   k++;
    }

    for (i=0;i<NACTEUR;i++)
        {

   actualiserActeur(page,tab[i],k,cartecollision,screenx);
   changerEtat(cartecollision,page,tab[i],p,screenx);
   creuser (cartecollision ,tab[i],p,page,decor);
   souffleur ( cartecollision ,tab[i], p);
   if (tab[i]->etat==5)
   {
    dessinecercle (tab[i], page,screenx);
   }
     if(tab[i]->etat==6)
   {
       dessinconstruction(page,tab[i],niveau); //dessiner les pentes issues de la construction
   }
        }

// on gère le scrolling car cette fonction permet de vérifier l'état de chaque acteur


}

// Dessiner un acteur sur le buffer
void dessinerActeur(BITMAP *page, t_acteur *acteur,int screenx)
{

 if ((acteur->etat ==1)&&(acteur->vie!=0))
     {if (acteur->depx>=0)
            draw_sprite(page,acteur->img[acteur->imgcourante1],acteur->posx-screenx,acteur->posy);
        else
            draw_sprite_h_flip(page,acteur->img[acteur->imgcourante1],acteur->posx-screenx,acteur->posy);}


 if ((acteur->etat ==2)&&(acteur->vie!=0))
     {if (acteur->depx>=0)

            draw_sprite(page,acteur->img1[acteur->imgcourante2],acteur->posx-screenx,acteur->posy);

        else
            draw_sprite_h_flip(page,acteur->img1[acteur->imgcourante2],acteur->posx-screenx,acteur->posy);}


 if ((acteur->etat ==3)&&(acteur->vie!=0))
     {if (acteur->depx>=0)
            draw_sprite(page,acteur->img2[acteur->imgcourante3],acteur->posx-screenx,acteur->posy);
        else
            draw_sprite_h_flip(page,acteur->img2[acteur->imgcourante3],acteur->posx-screenx,acteur->posy);}

 if ((acteur->etat ==4)&&(acteur->vie!=0))
 {
          {draw_sprite(page,acteur->img3[acteur->imgcourante4],acteur->posx-screenx,acteur->posy);}
 }
 if ((acteur->etat ==5)&&(acteur->vie!=0))
 {
          {draw_sprite(page,acteur->img4[acteur->imgcourante5],acteur->posx-screenx,acteur->posy);}
 }

 if ((acteur->etat ==6)&&(acteur->vie!=0))
     {if (acteur->depx>=0)
            draw_sprite(page,acteur->img5[acteur->imgcourante6],acteur->posx-screenx,acteur->posy);
        else
            draw_sprite_h_flip(page,acteur->img5[acteur->imgcourante6],acteur->posx-screenx,acteur->posy);}


}




// Dessiner sur une bitmap l'ensemble des acteurs
void dessinerTabActeurs(BITMAP *page,t_acteur * tab[NACTEUR],int screenx)
{
int i=0;
    int tempo=1;// on fait en sorte que tous les acteurs ne spawn pas en meme temps



    while(i<NACTEUR)

        {
            if((rand()%100<tempo))
            {
                dessinerActeur(page,tab[i],screenx);
                i++;
            }


        }
}


void  changerEtat(BITMAP *cartecollision ,BITMAP *page,t_acteur * acteur,int p,int screenx)

{


if ((mouse_b&1) && ((mouse_x>=acteur->posx-screenx )&& (mouse_x<=acteur->posx +acteur->tx-screenx)) && ((mouse_y>=acteur->posy) && (mouse_y<=acteur->posy +acteur->ty))&&(acteur->etat==2)&&(p==0))


{

acteur->pause=1; // état ou on draw sprite notre menu changement état et acteur s'arrete
acteur->trousc++;

}


if ((mouse_b&1)&&(getpixel(page,mouse_x,mouse_y)==makecol(255,0,0))&&(acteur->pause==1))
{

acteur->etat=1;
acteur->pause=6;
acteur->trousc=0;

}

 if((mouse_b&1)&&(getpixel(page,mouse_x,mouse_y)==makecol(0,255,0))&&(acteur->pause==1))
{
  acteur->etat=2;
  acteur->pause=0;
  acteur->trousc=0;


}

 if((mouse_b&1)&&(getpixel(page,mouse_x,mouse_y)==makecol(0,0,255))&&(acteur->pause==1))
 {

  acteur->etat=6;
  acteur->pause=2;
  acteur->trousc=0;

}



}


void creuser (BITMAP * cartecollision ,t_acteur * acteur,int p,BITMAP* page,BITMAP *decor)// creuser servira aussi pour construire
{
int cas=0;
int i ;

if(acteur->creuse==1)// si notre état dans actualiser acteur a était mis à 1 on peut creuser!
{
cas =2;
dessineRectangle(cartecollision,acteur,cas);

acteur->trous++;}

if(acteur->creuse==2)// si notre état dans actualiser acteur a était mis à 1 on peut creuser!
{
 cas =3;
dessineRectangle(cartecollision,acteur,cas);
acteur->trous++;


}
if(acteur->creuse==3)// si notre état dans actualiser acteur a était mis à 1 on peut creuser!
{
cas =1;
dessineRectangle(cartecollision,acteur,cas);
acteur->trous++;

}





 if((mouse_b&1)&&(getpixel(screen,mouse_x,mouse_y)==makecol(0,255,64))&&(acteur->pause==2))// si on creuse vers le bas
{

    if((getpixel(cartecollision,acteur->posx+acteur->tx/2,acteur->posy+acteur->ty)==makecol(255,255,255)) ||//si on repère du blanc en dessous on peut creuser
        (getpixel(cartecollision,acteur->posx+acteur->tx,acteur->posy+acteur->ty)==makecol(255,255,255)) ||
       (getpixel(cartecollision,acteur->posx,acteur->posy+acteur->ty)==makecol(255,255,255)))
       {

cas =1;
dessineRectangle(cartecollision,acteur,cas);
draw_sprite(decor,acteur->trou,acteur->posx,acteur->posy+acteur->ty-20); // on dessine le trou
acteur->trous++;
acteur->trousc=0;// plus de menu
acteur->pause=0;

       }
else
    {acteur->pause=0;
    acteur->etat=2;
    acteur->trousc=0;}

}
else if((mouse_b&1)&&(getpixel(screen,mouse_x,mouse_y)==makecol(255,0,128))&&(acteur->pause==2))//si on creuse à droite
{

if (((getpixel(cartecollision,acteur->posx+(acteur->tx)+30,acteur->posy+(acteur->ty)/2)==makecol(255,255,255))))// si on repère du blanc à droite on peut creuser
{
cas =2;
dessineRectangle(cartecollision,acteur,cas);
draw_sprite(decor,acteur->troudroit,acteur->posx,acteur->posy);
acteur->trous++;
acteur->trousc=0;
acteur->pause=0;// plus de menu

}

else
{
    acteur->pause=0;
    acteur->etat=2;
    acteur->trousc=0;
}

}



else  if((mouse_b&1)&&(getpixel(screen,mouse_x,mouse_y)==makecol(255,128,0))&&(acteur->pause==2))
{
if (((getpixel(cartecollision,acteur->posx-30,acteur->posy+(acteur->ty)/2)==makecol(255,255,255))))//si on repère du blanc à gauche on peut creuser sinon non
{

cas =3;
dessineRectangle(cartecollision,acteur,cas);
draw_sprite(decor,acteur->trougauche,acteur->posx,acteur->posy);
acteur->trous++;
acteur->trousc=0;
acteur->pause=0;// plus de menu
}


else
{
    acteur->pause=0;
    acteur->etat=2;
    acteur->trousc=0;
}
}
///POUR LA CONSTRUCTION
else if((mouse_b&1)&&(getpixel(screen,mouse_x,mouse_y)==makecol(128,0,128))&&(acteur->pause==2))//diagonale gauche
{
    cas=7;
    dessineRectangle(cartecollision , acteur, cas);
    acteur->creuse=10;




}
else if((mouse_b&1)&&(getpixel(screen,mouse_x,mouse_y)==makecol(128,0,0))&&(acteur->pause==2))//diagonale droite
{
    cas=8;
    dessineRectangle(cartecollision , acteur, cas);
        acteur->creuse=11;
}



else  if((mouse_b&1)&&(getpixel(screen,mouse_x,mouse_y)==makecol(255,255,0))&&(acteur->pause==2)) // on le tue
{
acteur->vie=0;
acteur->trousc=0;
}


}



void souffleur (BITMAP * cartecollision ,t_acteur * acteur,int p)
{
int cas=0;

if((mouse_b&1)&&(getpixel(screen,mouse_x,mouse_y)==makecol(0,125,255))&&(acteur->pause==6)&&(acteur->etat==1))//vers droite
{
cas=4;
dessineRectangle(cartecollision , acteur, cas);
acteur->souffle =1;


acteur->vie=8;//une fois qu'on fait le souffle alors on a l'animation

}

else  if((mouse_b&1)&&(getpixel(screen,mouse_x,mouse_y)==makecol(255,125,0))&&(acteur->pause==6)&&(acteur->etat==1))//vers gauche
{
cas=5;
dessineRectangle(cartecollision , acteur, cas);
acteur->souffle =2;

acteur->vie=8;
}
else  if((mouse_b&1)&&(getpixel(screen,mouse_x,mouse_y)==makecol(125,255,255))&&(acteur->pause==6)&&(acteur->etat==1))//vers haut
{
cas=6;
dessineRectangle(cartecollision , acteur, cas);
acteur->souffle =3;

acteur->vie=8;
}


else  if((mouse_b&1)&&(getpixel(screen,mouse_x,mouse_y)==makecol(180,180,0))&&(acteur->pause==6)&&(acteur->etat==1))
{

acteur->vie=0;
}

}




void dessineRectangle(BITMAP *cartecollision ,t_acteur * acteur,int cas)
///TROUS
{
if(cas==1)//creuse vers le bas
{
rectfill(cartecollision,acteur->posx-3, acteur->posy+(acteur->ty)-3, acteur->posx +(acteur->tx)+10, acteur->posy+(acteur->ty)+13, makecol(120,40,255));

}
else if(cas==2) // creuse à droite
{
rectfill(cartecollision,acteur->posx +(acteur->tx), acteur->posy, acteur->posx +(acteur->tx)+46, acteur->posy +(acteur->ty), makecol(150,70,255));
}

else if(cas==3) // creuse à gauche
{
rectfill(cartecollision,acteur->posx-(acteur->tx)-46, acteur->posy, acteur->posx , acteur->posy +(acteur->ty), makecol(180,100,255));
}
///CREUSE
else if(cas==4) // souffle vers la droite
{
rectfill(cartecollision,acteur->posx +(acteur->tx), acteur->posy, acteur->posx +(acteur->tx)*3, acteur->posy +(acteur->ty), makecol(255,70,120));
}

else if(cas==5) // souffle vers la gauche
{
rectfill(cartecollision,acteur->posx-(acteur->tx)*3, acteur->posy, acteur->posx , acteur->posy +(acteur->ty), makecol(255,100,150));
}
else if(cas==6) // souffle vers le haut
{
 rectfill(cartecollision,acteur->posx, acteur->posy-(acteur->ty)*2, acteur->posx +(acteur->tx), acteur->posy , makecol(255,130,180));

}
else if(cas==7) //constructoin en vers la gauche
{
    int i;
    for(i=0;i<30;i++) //epaisseur de la pente de 30px
    {
        line(cartecollision,acteur->posx-i,acteur->posy+acteur->ty+50,acteur->posx-250-i,acteur->posy+acteur->ty-150,makecol(255,255,255));
        acteur->vie=0;//le perso se transforme en escalier et disparait
    }
}

else if(cas==8) //construction vers la droite
{
    int i;
    for(i=0;i<30;i++)
    {
        line(cartecollision,acteur->posx+acteur->tx+i,acteur->posy+acteur->ty+50,acteur->posx+acteur->tx+250+i,acteur->posy+acteur->ty-150,makecol(255,255,255));
        acteur->vie=0;
    }
}
}
 void dessinecercle (t_acteur *acteur, BITMAP *page,int screenx)
 {
     int i;

    int color1 = makecol(255,127,39);
    int color2 = makecol(255,242,0);
    int color3 = makecol(163,73,164);
    int radius =5;
     int positionx=0;
    int positiony=0;
    int couleur=0;

 if (acteur->souffle==1)//permet de savoir la direction du souffle
   for(i=0;i<(rand()%60)+10;i++)
       {
           positionx= acteur->posx+ acteur->tx +rand()% (acteur->tx)*2;
           positiony= acteur->posy + rand()% acteur->ty;     // prend une couleur et position aléatoire pour chaque cercle
        couleur=(rand()%3)+1;
        if(couleur==1)
            couleur=color1;
              if(couleur==2)
            couleur=color2;
                  if(couleur==3)
            couleur=color3;
    circlefill(page,positionx-screenx,positiony,radius,couleur);// position aléatoire sur la bmp au niveau de l'acteur
     }

if (acteur->souffle==2)//permet de savoir la direction du souffle
   for(i=0;i<(rand()%60)+10;i++)
       {
           positionx= acteur->posx - rand()% (acteur->tx)*2;
           positiony= acteur->posy + rand()%acteur->ty;    // prend une couleur et position aléatoire pour chaque cercle
        couleur=(rand()%3)+1;
        if(couleur==1)
            couleur=color1;
              if(couleur==2)
            couleur=color2;
                  if(couleur==3)
            couleur=color3;
    circlefill(page,positionx-screenx,positiony,radius,couleur);// position aléatoire sur la bmp au niveau de l'acteur
     }


if (acteur->souffle==3)//permet de savoir la direction du souffle
   for(i=0;i<(rand()%60)+10;i++)
       {
           positionx= acteur->posx + rand()% (acteur->tx);
           positiony= acteur->posy - rand()% (acteur->ty)*2;     // prend une couleur et position aléatoire pour chaque cercle
        couleur=(rand()%3)+1;
        if(couleur==1)
            couleur=color1;
              if(couleur==2)
            couleur=color2;
                  if(couleur==3)
            couleur=color3;
    circlefill(page,positionx-screenx,positiony,radius,couleur);// position aléatoire sur la bmp au niveau de l'acteur
     }





 }

int score (t_acteur * tab[NACTEUR]) //cette fonction va faire le tour des acteur voir quand il'n'y a plus de vivants si plus aucun est vivant fin du niveau on compte les points.

 {
int i;
int c=0;
int j;
int score=0;
for (i=0;i<NACTEUR;i++)
{
    if (tab [i]->vie==0 ||tab [i]->vie==8)//on compte le nombre d'acteurs
    {
        c++;
    }
}
if (c  == NACTEUR)//si tous les acteurs sont "out"
{
 for (j=0;j<NACTEUR;j++)// on compte les points si niveau fini
{
  score = score + tab[j]->points +tab[j++]->points;
}
return score;
 }
else
return 1;
 }

 void dessinconstruction(BITMAP * page, t_acteur * acteur,int niveau)
{
    int i;

    if(acteur->creuse==10)
    {
        for(i=0;i<30;i++)
        {
            if(niveau==0)// on change la couleur en fonction du niveau
            line(page,acteur->posx-i,acteur->posy+acteur->ty+50,acteur->posx-250-i,acteur->posy+acteur->ty-150,makecol(128,128,128));
            else if (niveau==2)
            line(page,acteur->posx-i,acteur->posy+acteur->ty+50,acteur->posx-250-i,acteur->posy+acteur->ty-150,makecol(0,255,64));
            else if (niveau==3)
            line(page,acteur->posx-i,acteur->posy+acteur->ty+50,acteur->posx-250-i,acteur->posy+acteur->ty-150,makecol(255,128,0));
        }
    }

    if(acteur->creuse==11)
    {

        for(i=0;i<30;i++)
        {        if(niveau==0)
                line(page,acteur->posx+acteur->tx+i,acteur->posy+acteur->ty+50,acteur->posx+acteur->tx+250+i,acteur->posy+acteur->ty-150,makecol(128,128,128));
                  else if (niveau==2)
                     line(page,acteur->posx+acteur->tx+i,acteur->posy+acteur->ty+50,acteur->posx+acteur->tx+250+i,acteur->posy+acteur->ty-150,makecol(0,255,64));
                      else if (niveau==3)
                     line(page,acteur->posx+acteur->tx+i,acteur->posy+acteur->ty+50,acteur->posx+acteur->tx+250+i,acteur->posy+acteur->ty-150,makecol(255,128,0));
                //line(page,acteur->posx+acteur->tx+100+i,acteur->posy+acteur->ty-i,acteur->posx+acteur->tx+100+30+i,acteur->posy+acteur->ty-i,couleur);
        }
    }
/*
    if(acteur->creuse==12)
    {
        rectfill(page,acteur->posx,acteur->posy+acteur->ty,acteur->posx+acteur->tx,acteur->posy+2*acteur->ty,makecol(0,0,0));
    }
*/
}
/// la sauvegarde marche pas
/*
void sauvegardeacteur(t_acteur *tab[NACTEUR])
 {
     int i;
    FILE* fichier= NULL;

    fichier=fopen("sauvegarde.txt","w+");


        if (fichier != NULL)
    {

        for(i=0;i<NACTEUR;i++)
        {
            fprintf(fichier,"%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n%d\n",
            tab[i]->posx,
            tab[i]->posy,
            tab[i]->depx,
            tab[i]->depy,
            tab[i]->etat,
            tab[i]->etatprec,
            tab[i]->tmpimg,
            tab[i]->cptimg,
            tab[i]->x,
            tab[i]->y,
            tab[i]->dx,
            tab[i]->tmpdx,
            tab[i]->cptdx,
            tab[i]->pause,
            tab[i]->trous,
            tab[i]->trousc,
            tab[i]->souffleur,
            tab[i]->vie,
            tab[i]->creuse,
            tab[i]->souffle,
            tab[i]->points);
        }


    }
    else
    {
        // On affiche un message d'erreur si on veut
        printf("Impossible d'ouvrir le fichier sauvegarde.txt");
    }






 }

*/
