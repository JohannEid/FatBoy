#include <allegro.h>
#include <time.h>
#include "acteur.h"
#include "interface.h"
#define NACTEUR 10
#define SKATE 4
#define COURSE 4
#define NINJA 4
#define NSEQUENCE 3
#define BLOOD 8
#define SOUFFLE 4
#define MINEUR 4




///PRECISIONS UTILES :
//SCROLLING : (juste au dernier niveau fleche gauche fleche droite)
//RYHTMES DE JEU : F10 et F11
//CLIQUE DROIT DANS LE MENU PRINCIPAL LES AUTRES SERONT AVEC CLIQUE GAUCHE
// beaucoup de temps a été consacré a mettre la musique celle ci est en théorie facile à mettre je ne sais pas qu'elle étape j'ai raté elle ne veut juste pas marcher





int main()
{
    ///DECLARATION VARIABLES
    // Le tableau regroupant tous les acteurs
    // c'est un tableau de pointeurs sur structures t_acteurs
    t_acteur * mesActeurs[NACTEUR];


    // BITMAP servant de buffer d'affichage (double buffer)
    BITMAP *page;
    BITMAP *pagescrolling;
    BITMAP *cartecollision;
    BITMAP *decor;

    int p =1;
    int sortie=0;
    int nvpartie=0;// permet de recommencer le jeu
    int screenx=0;
    int sc=1;
    int res=0; //boléen pour boucle
    BITMAP * save;
    int delai =0;
    int rythme =25;
    int niveau=0; // on peut ainsi repérer les niveaux
    int scoreniveau1=0;
    int scoreniveau2=0;
    int scoreniveau3=0;
    int s =1;








///INITIALISATION ALLEGRO
    // Lancer allegro et le mode graphique
    allegro_init();
    install_keyboard();
    install_mouse();
    set_color_depth(desktop_color_depth());
    if (set_gfx_mode(GFX_AUTODETECT_WINDOWED,1024,768,0,0)!=0)
    {
        allegro_message("prb gfx mode");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
      show_mouse(screen);

    // On utilise aléatoire
srand(time(NULL));

    page=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);
    pagescrolling=create_bitmap(SCREEN_W,SCREEN_H);
    clear_bitmap(page);

///CHARGEMENT IMAGES
    cartecollision=load_bitmap("niveau_test.bmp",NULL);
    if(!cartecollision)
    {
        allegro_message("pb chargement niveau_test.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

  decor=load_bitmap("decor.bmp",NULL);
     if(!decor)
    {
        allegro_message("pb chargement decor.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


    ///COMMENCE TRAITEMENT
    // remplir le tableau avec des acteurs alloués et initialisés
    //on commence par appeler notre menu de jeu


while(nvpartie!=2)
{
if(p==1)
nvpartie=menu(); //par défaut p est à 1 pour permettre d'afficher le menu au moins une fois
if(nvpartie==3)
{
    niveau=0;
    nvpartie=1;//si on a appuyé sur nouvelle partie dans le menu on revient au premier niveau
}
if(nvpartie==1)
{
 if(niveau==0)// on charge niveau 1
   {
       remplirTabActeurs(mesActeurs); // si le menu envoie nouvelle partie on recommence la boucle de jeu
     cartecollision=load_bitmap("niveau_test.bmp",NULL);
    if(!cartecollision)
    {
        allegro_message("pb chargement niveau_test.bmp");
        allegro_exit();
        exit(EXIT_FAILURE); // si on recommence le niveau on recharge la carte de collision
    }
    decor=load_bitmap("decor.bmp",NULL);
     if(!decor)
    {
        allegro_message("pb chargement decor.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
   }
 if(niveau==2)
     {
       remplirTabActeurs(mesActeurs); // si le menu envoie nouvelle partie on recommence la boucle de jeu
     cartecollision=load_bitmap("niveau_test2.bmp",NULL);
    if(!cartecollision)
    {
        allegro_message("pb chargement niveau_test2.bmp");
        allegro_exit();
        exit(EXIT_FAILURE); // si on recommence le niveau on recharge la carte de collision
    }
    decor=load_bitmap("decor2.bmp",NULL);
     if(!decor)
    {
        allegro_message("pb chargement decor2.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
   }
 if(niveau==3)
     {
       remplirTabActeurs(mesActeurs); // si le menu envoie nouvelle partie on recommence la boucle de jeu
     cartecollision=load_bitmap("niveau_test3.bmp",NULL);
    if(!cartecollision)
    {
        allegro_message("pb chargement niveau_test3.bmp");
        allegro_exit();
        exit(EXIT_FAILURE); // si on recommence le niveau on recharge la carte de collision
    }
    decor=load_bitmap("decor3.bmp",NULL);
     if(!decor)
    {
        allegro_message("pb chargement decor3.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }
   }


sc=1; // on remet le score normale pour revenir à la boucle
//sauvegardeacteur(mesActeurs);
}
 else if(nvpartie==2)    //si le menu envoie quitter on quitte...
{
exit(EXIT_FAILURE);
}
else if (nvpartie==4)
{

sc=1; //si on continue la partie alors on recharge naturellement la bitmap sauvée
 cartecollision=load_bitmap("save.bmp",NULL);
 if(!cartecollision)
    {
        allegro_message("pb chargement save.bmp");
        allegro_exit();
        exit(EXIT_FAILURE); // si on recommence le niveau on recharge la carte de collision
    }


}

    /// BOUCLE DE JEU ESPACE POUR NIVEAU 2 ENTER POUR NIVEAU 3
    while ((!key[KEY_ESC])&&(sc==1)&&(!key[KEY_SPACE])&&(!key[KEY_ENTER])&&(s==1))// on met s qui entre en jeu quand on a le menu des scores
    {

        clear_bitmap(page);

        screenx = scrolling( screenx);
        if(screenx<0)//on ne peut pas dépasser le décor
            screenx=0;
        if(screenx>decor->w - SCREEN_W)
         screenx=decor->w - SCREEN_W;



        blit(decor,page,screenx,0,0,0,decor->w,decor->h);


        actualiserTabActeurs(cartecollision,page,mesActeurs,screenx,niveau,decor);

        dessinerTabActeurs(page,mesActeurs,screenx);

        blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

        delai =rythmedejeu();
        if ((rythme ==5)&&(delai<0))
        rythme = rythme;
        // on empeche la pause d'atteindre 0
        else rythme +=delai;


        rest( rythme ); // on permet au jour de ralentir ou accéler le jeu

        sc =score(mesActeurs);


    }

/// CE QUI CONCERNE L ENCHAINEMENT DES NIVEAUX
if(niveau==0)
   scoreniveau1 =sc;//on mémorise les score du niveau 1 2 et 3
if(niveau==2)
     scoreniveau2=sc;
if(niveau==3)
scoreniveau3=sc;
if ((key[KEY_SPACE])||((scoreniveau1>=50)&&(niveau==0)))//si on a fait survivre 5 personnages au moins
{
  remplirTabActeurs(mesActeurs);

     cartecollision=load_bitmap("niveau_test2.bmp",NULL);
    if(!cartecollision)
    {
        allegro_message("pb chargement niveau_test2.bmp");
        allegro_exit();
        exit(EXIT_FAILURE); // on passe au niveau suivant
    }
 decor=load_bitmap("decor2.bmp",NULL);
     if(!decor)
    {
        allegro_message("pb chargement decor.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }

p=0;
sc=1;
nvpartie=0; // on met à 0 pour ne pas avoir à passer par le menu
niveau=2;
}
else if (((scoreniveau1<=50)&&(niveau==0)&&(sc!=1)))//si on a raté on recommence
          {
    remplirTabActeurs(mesActeurs);
    sc=1;
    nvpartie=0;// on remet à 0 pour recommencer sans passer par le menu
    p=0;
   cartecollision=load_bitmap("niveau_test.bmp",NULL);
    if(!cartecollision)
    {
        allegro_message("pb chargement niveau_test2.bmp");
        allegro_exit();
        exit(EXIT_FAILURE); // on passe au niveau suivant
    }
          }
if((key[KEY_ENTER])||(scoreniveau2>=30)&&(niveau==2))//on vérifie qu'avance de passer au 3 ème niveau, le 2 eme est bien chargé vu la difficulté on se permet de réussir avec juste 3 persos
{

  remplirTabActeurs(mesActeurs);

     cartecollision=load_bitmap("niveau_test3.bmp",NULL);
    if(!cartecollision)
    {
        allegro_message("pb chargement niveau_test3.bmp");
        allegro_exit();
        exit(EXIT_FAILURE); // on passe au niveau suivant
    }
 decor=load_bitmap("decor3.bmp",NULL);
     if(!decor)
    {
        allegro_message("pb chargement decor.bmp");
        allegro_exit();
        exit(EXIT_FAILURE);
    }


p=0;
sc=1;
nvpartie=0;
niveau=3; // on arrive donc au 3eme niveau
}
    else if (((scoreniveau2<=30)&&(niveau==2)&&(sc!=1)))//si on a raté on recommence
          {
    remplirTabActeurs(mesActeurs);
    sc=1;
    nvpartie=0;// on remet à 0 pour recommencer sans passer par le menu
    p=0;
   cartecollision=load_bitmap("niveau_test2.bmp",NULL);
    if(!cartecollision)
    {
        allegro_message("pb chargement niveau_test2.bmp");
        allegro_exit();
        exit(EXIT_FAILURE); // on passe au niveau suivant
    }


          }

if((niveau==3)&&(scoreniveau3>=20))//si on arrive au troisième niveau qu'on a gagné on se permet de réussir avec juste 2 persos
{
sc=1;
s=0;


s=menuscore(scoreniveau1,scoreniveau2,scoreniveau3);//on va faire comme pour pause une sortie vers menu

if (s==1)
{
    p=1;//on affiche le menu
    nvpartie=0;//valeur neutre

    niveau=0;
    scoreniveau1=0;
    scoreniveau2=0;
    scoreniveau3=0; // on réinitialise toutes nos valeurs

}

}
 if (((scoreniveau3<=20)&&(niveau==3))&&(sc!=1))//si on a raté on recommence
          {
    remplirTabActeurs(mesActeurs);
    sc=1;
    nvpartie=0;// on remet à 0 pour recommencer sans passer par le menu
    p=0;
   cartecollision=load_bitmap("niveau_test3.bmp",NULL);
    if(!cartecollision)
    {
        allegro_message("pb chargement niveau_test2.bmp");
        allegro_exit();
        exit(EXIT_FAILURE); // on passe au niveau suivant
    }


          }

///TOUT CE QUI CONCERNE LE MENU PAUSE
if (key[KEY_ESC])//on affiche le menu pause
{p=menupause(page);
 // on récolte l'information du menupause
if(p==1)
{

    sortie=menu();
    save_bitmap("save.bmp",cartecollision,NULL);
     if (save_bitmap("save.bmp",cartecollision,NULL)==0)
     {
         printf("sauvegarde reussie!");
     }
else
    exit(EXIT_FAILURE);

          //on quitte vers le menu si le menu pause demande en sauvant notre carte de collision
}
else if (p==2)
{
    nvpartie=1;// on recommence le niveau
}else if (p==3)
{
    nvpartie=5; //nvpartie a une valeur qui ne correspond à rien pour reprend le niveau sans rien de changer
}
 }
}


    return 0;
}
END_OF_MAIN();







