#include <allegro.h>
#include <time.h>

#define NACTEUR 1
#define SKATE 4
#define COURSE 4
#define NINJA 4
#define NSEQUENCE 3
#define BLOOD 8
#define SOUFFLE 4
#define MINEUR 4





typedef struct acteur
{
    // coordonn�e (du coin sup. gauche)
   ///LE DEPLACEMENT
    int posx, posy;

    // vecteur deplacement
    int depx, depy;

    // tailles : horizontal/vertical
    int tx,ty;


int chute;
int vith; //vitesse horizontale
int etat;
int etatprec;
int tmpimg;      // ralentir s�quence (image suivante 1 fois sur tmpimg)
int cptimg;
int x,y;         // position du coin sup. gauche
int dx;          // deplacement
int tmpdx;       // ralentir d�placements en x (1 pour ne pas ralentir)
int cptdx;


///ETATS DU PERSONNAGE

int pause;
int trous;//nombre de trous creus�s
int trousc;//menu creuser
int souffleur;//personnes dans le souffle pour ne pas avoir tous les acteurs en m�me temps
int vie;//mort vivant sert aussi � faire des �tats pour le souffle
int creuse; // �tat de creuser
int souffle; // soufle gauche droite haut
int points;// cjaque acteur a un nombre de points


   ///TOUS LES GRAPHISMES DU PROJET LIES A L'ACTEUR
char nomfichier[256];
char nomfichier1[256];
char nomfichier2[256];
char nomfichier3[256];
char nomfichier4[256];
char nomfichier5[256];
BITMAP *img[SKATE];
BITMAP *img1[COURSE];
BITMAP *img2[NINJA];
BITMAP *img3[BLOOD];
BITMAP *img4[SOUFFLE];
BITMAP *img5[MINEUR];
BITMAP * changeEtat;
BITMAP * creuser;
BITMAP * fleshsou;
BITMAP * capacite;
BITMAP * changeEtatBeau;
BITMAP *trou;
BITMAP *trougauche;
BITMAP *troudroit;
int imgcourante1;
int imgcourante2;
int imgcourante3;
int imgcourante4;
int imgcourante5;
int imgcourante6;





} t_acteur;







/// PROTOTYPE SOUS PROGRAMME


// Allouer et initialiser un acteur
t_acteur * creerActeur();

// Remplir un tableau avec des acteurs cr��s
void remplirTabActeurs(t_acteur * tab[NACTEUR]);


// Actualiser un acteur
void actualiserActeur(BITMAP *page,t_acteur *acteur, int k,BITMAP * cartecollision,int screenx);// le screenx car tout ce qu'on dessine � l'�cran doit etre r�adapte lors du scrollng.

// G�rer l'�volution de l'ensemble des acteurs
void actualiserTabActeurs(BITMAP * cartecollision,BITMAP *page, t_acteur * tab[NACTEUR],int screenx,int niveau,BITMAP* decor);

// Dessiner un acteur sur une bitmap page
void dessinerActeur(BITMAP *page, t_acteur *acteur,int screenx);

// Dessiner l'ensemble des acteurs sur une bitmap page
void dessinerTabActeurs(BITMAP *page,t_acteur * tab[NACTEUR],int screenx);
//p permet de savoir combien de menu sont affich� � la fois fonction permettant affichage d'un menu pour changer �tat de nos persos
void  changerEtat (BITMAP *cartecollision,BITMAP *page,t_acteur * acteur, int p,int screenx );
//m�me fonction pour p permet affichage menu pour creuser
void creuser (BITMAP * cartecollision,t_acteur * acteur,int p,BITMAP * page, BITMAP* decor );// Pour des raisons pratiques et une choix bien assum� la construction et la fonction creuser se feront dans le m�me �tat

// m�me fonction p permet affichage creuser
void souffleur (BITMAP * cartecollision ,t_acteur * acteur,int p); // on retourne au menu l'acteur pour qu boucle puisse s'occuper de dessiner les cercles



//dessine rectangle nos fonctions envoient diff�rents cas � dessine rectangle qui s'adapte selon le besoin les dessine sur la carte de collision
void dessineRectangle(BITMAP*cartecollision,t_acteur * acteur,int cas);
void dessinecercle (t_acteur *acteur, BITMAP *page,int screenx);//dessine des cercles

void chargementimageacteur(t_acteur*acteur);
void timingacteur(t_acteur * acteur);
void pente(BITMAP *cartecollision, t_acteur *acteur);
void dessinconstruction(BITMAP* page, t_acteur* acteur,int niveau);
void sauvegardeacteur(t_acteur *tab[NACTEUR]); // On arrive � sauvegarder les donner mais pas � les charger







