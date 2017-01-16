#include <allegro.h>



int menu ()
{
BITMAP *page ;
BITMAP *decor;
BITMAP *play;
BITMAP *quit;
BITMAP *titre;
BITMAP *continuer;
BITMAP *skate;
SAMPLE *music;
int sortie=0;

page=create_bitmap(SCREEN_W,SCREEN_H);
clear_bitmap(page);
skate=load_bitmap("Projet info/imagemenu.bmp",NULL);
    if (!skate)
    {
      allegro_message("pas pu trouver imagemenu.bmp");
      exit(EXIT_FAILURE);
    }

titre=load_bitmap("menu projet/fatboy.bmp",NULL);
    if (!titre)
    {
        allegro_message("pas pu trouver Images/fatboy.bmp");
        exit(EXIT_FAILURE);
    }
continuer=load_bitmap("menu projet/continuer.bmp",NULL);
    if (!titre)
    {
        allegro_message("pas pu trouver Images/continuer.bmp");
        exit(EXIT_FAILURE);
    }
decor=load_bitmap("menu projet/fond.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver Images/fond.bmp");
        exit(EXIT_FAILURE);
    }
play=load_bitmap("menu projet/play2.bmp",NULL);
    if (!play)
    {
        allegro_message("pas pu trouver Images/play.bmp");
        exit(EXIT_FAILURE);
    }
quit=load_bitmap("menu projet/quit.bmp",NULL);
    if (!quit)
    {
        allegro_message("pas pu trouver Images/quit.bmp");
        exit(EXIT_FAILURE);
    }


      music = load_sample("Girls Just Want to Have Fun (1979) by Robert Hazard, Cyndi Lauper.wav");
      if (!music)
       printf("ne pouvez pas charger la musique!");
     else
        printf("chargement réussi");
play_sample(music,  255, 255, 2000, 1);
    while (sortie==0)
    {

     blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
	blit(play,page, 0, 0, 370, 280, 323, 32);
	blit(continuer,page, 0, 0, 370,400 , 323,32);
	blit(quit, page, 0, 0,370,520,323,32);
	draw_sprite(page,titre,315,65);
	draw_sprite(page,skate,139,542);
	blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

	if (mouse_b&2 && mouse_x<=693 && mouse_x>=370 && mouse_y<=300 && mouse_y>=280)//nouvelle partie
    {
        sortie=3;
    }
    	  if  (mouse_b&2 && mouse_x<=693 && mouse_x>=370 && mouse_y<=552 && mouse_y>=520)//continuer
    {
sortie =2;
    }
     if(mouse_b&2 && mouse_x<=693 && mouse_x>=370 && mouse_y<=426 && mouse_y>=400)//quitter
  {
        sortie=4;

   }
}

return sortie;

}



int menupause(BITMAP *page)
{


BITMAP *menu;
int sortie=0;

menu=load_bitmap("menupause.bmp",NULL);
    if (!menu)
    {
      allegro_message("pas pu trouver menupause.bmp");
      exit(EXIT_FAILURE);
    }
if (key [KEY_ESC])
{

    while ( sortie==0)
    {
	draw_sprite(page,menu,170,175);
	blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);

	  if (mouse_b&1 && mouse_x<=610 && mouse_x>=430 && mouse_y<=400 && mouse_y>=360)
    {
sortie=3; //reprend
    }

     if (mouse_b&1 && mouse_x<=610 && mouse_x>=430 && mouse_y<=485 && mouse_y>=445)
    {
        sortie=2; // recommence
    }

     if (mouse_b&1 && mouse_x<=610 && mouse_x>=430 && mouse_y<=565 && mouse_y>=525)
    {
      sortie=1; // quitte vers menu
    }

    }


return sortie;

}


}

int scrolling(int screenx)
{
    if (key[KEY_RIGHT])   screenx+=5;
    if (key[KEY_LEFT] )   screenx-=5;
    return screenx;
}




int rythmedejeu()
{
    int rythme=0;
    if (key[KEY_F10])
        // on ralentit
        rythme+=5;
    if (key[KEY_F11])
        // on accelere
        rythme-=5;
return rythme;
}
int menuscore(int niveauscore1, int niveauscore2, int niveauscore3)
{
BITMAP *page ;
BITMAP *decor;
BITMAP *score;
BITMAP *map1;
BITMAP *map2;
BITMAP *map3;
BITMAP *quit;
int sortie=0;

page=create_bitmap(SCREEN_W,SCREEN_H);
clear_bitmap(page);

score=load_bitmap("menu des scores/highscores.bmp",NULL);
    if (!score)
    {
        allegro_message("pas pu trouver ");
        exit(EXIT_FAILURE);
    }

decor=load_bitmap("fond.bmp",NULL);
    if (!decor)
    {
        allegro_message("pas pu trouver Images/fond.bmp");
        exit(EXIT_FAILURE);
    }
map1=load_bitmap("menu des scores/1min.bmp",NULL);
    if (!map1)
    {
        allegro_message("pas pu trouver");
        exit(EXIT_FAILURE);
    }

map2=load_bitmap("menu des scores/2min.bmp",NULL);
    if (!map2)
    {
        allegro_message("pas pu trouver");
        exit(EXIT_FAILURE);
    }

map3=load_bitmap("menu des scores/3min.bmp",NULL);
    if (!map3)
    {
        allegro_message("pas pu trouver");
        exit(EXIT_FAILURE);
    }

quit=load_bitmap("menu des scores/menu-back.bmp",NULL);
    if (!quit)
    {
        allegro_message("pas pu trouver Images/quit.bmp");
        exit(EXIT_FAILURE);
    }


    while ( sortie!=1)
    {
    blit(decor,page,0,0,0,0,SCREEN_W,SCREEN_H);
	draw_sprite(page,quit,800,600);
	draw_sprite(page,score,200,65);
	draw_sprite(page,map1,150,200);
	draw_sprite(page,map2,150,400);
	draw_sprite(page,map3,150,600);
	blit(page,screen,0,0,0,0,SCREEN_W,SCREEN_H);
    // afficher des scores

    textprintf_ex(decor,font,350,268,makecol(255,0,0),-1,"SCORE:%d",niveauscore1);
    textprintf_ex(decor,font,350,468,makecol(255,0,0),-1,"SCORE::%d",niveauscore2);
    textprintf_ex(decor,font,350,668,makecol(255,0,0),-1,"SCORE::%d",niveauscore3);

	  if (mouse_b&1 && mouse_x<=963 && mouse_x>=800 && mouse_y<=665 && mouse_y>=600)
    {
     sortie=1;
    }

    }

return sortie;





















}



