// ******** D�claration des prototypes ********
  char appuiLong(char ledC);
  char appuiCourt(char ledC);
  char appuiTresLong();

void main()
{
// ********  D�claration des variables ********
char longPress = 0;      //Ici , on choisis des char pour ne pas allouer des espaces m�moires inutiles
char tresLongPress = 0;
int compteur = 0;
char led = 1;
char courtPress = 0;

TRISA = 0b00000011 ;  // port A en sortie sauf  RA0 et RA1
PORTA = 0;            // mettre les sorties � z�ro
TRISB = 0b00000000;      // Port B en sortie
PORTB = 0;            // mettre les sorties � z�ro
pcon.OSCF = 1;         // configure le bit 3 du registre pcon  pour 4 mhz
CMCON = 0b00000111;

        RA3_bit = 0;  // On allume la premi�re led par d�fault pour savoir si c'est bien aliment�
        RA6_bit = 1;
        RA7_bit = 1;
          while(1)
          {
             while(RA0_bit==0)    // Tant qu'on presse le bouton
             {
               compteur++;        // On va incr�menter un compteur pour d�terminer ensuite le type d'appui
               delay_ms(50);
             }
             
// ******** On va d�terminer le type d'appui ********

              if(compteur >= 1 && compteur < 15)   //si compteur est entre 1 et 15
               {
                //On configure les param�tres pour un appui court
                longPress = 0;
                tresLongPress = 0;
                courtPress = 1;
               }
               else if (compteur >= 15 && compteur <25)
               {
                  //On configure les param�tres pour un appui long
                  longpress = 1;
                  treslongpress = 0;
               }
               else if (compteur >= 25)
               {
                  //On configure les param�tres pour un appui tr�s long
                  treslongpress = 1;
                  longpress =0;
               }
               
// ******** On effectue les actions en fonction du type d'appui ********

              if(courtPress == 1)  //Si c'est un appuie court
              {
                    RA3_bit = 0;  //Allumage led mode 1
                    RA6_bit = 1;
                    RA7_bit = 1;

                    led = appuiCourt(led);  //Appel fonction pour un appui court, la led va retenir la position et va devoir prendre une de ces valeurs: 1-2-4-8-16-32-64-128
                    courtPress = 0;
                    compteur = 0;
              }
              else if (longpress == 1)   //Si on est dans un appuie long
              {
                 RA3_bit = 1;   //Allumage led mode 2
                 RA6_bit = 0;
                 RA7_bit = 1;

                 led=appuiLong(led); //Appel fonction appui long
                 compteur = 0;
              }
              else if (treslongpress == 1) // Appui tr�s long
              {
                 RA3_bit = 1; //Allumage led mode 3
                 RA6_bit = 1;
                 RA7_bit = 0;
                 
                 led=appuiTresLong(void); //appel fonction mode 1khz
                 compteur = 0;
              }
      }
}

// ******** Sous- programmes ********

 char appuiCourt(char ledC)    //Appui simple
 {
   PORTB = ledC;  //On allume la led correspondante
   ledC = (ledC *2)%255;  //On met � jour cette led pour la faire correspondre � la led suivante
                          //On fait donc *2 pour "d�caler" un bit vers la droite et ainsi passer � la suivant
                        // et %255 pour retourner � la premi�re si on est a 256
 }
 
 char appuiLong(char ledC)  //Appui long
{
   int cpt =0;
   for(cpt = 0; RA0_bit == 1; cpt++)   //Tant qu'on appui pas
   {
      if(cpt>=20)      // On incr�mente un compteur pour d�terminer le temps entre chaque led allum�
      {
         PORTB = ledC;
         ledC = (ledC *2)%255;
         cpt=0;
      }
      delay_ms(15);
   }
   if (ledC == 1)  //On g�re ce cas pour �viter d'avoir ledC = 256 = 1 et 1/2 = 0
   {
      return 128;   //La derni�re led s'allume
   }
   return ledC/2;      //Si on relache on divise par 2 pour avoir la led courante car on a d�j� pass� � la suivante
}

 char appuiTresLong()      //Appui tr�s long
 {
   char led = 1;
   while(RA0_bit==1)  // Tant qu'on appui pas
   {
     PORTB = led;
     led = (led *2)%255;
     delay_ms(1);
   }
   PORTB = 0;   //si on r�appuie, on allume d'office la premi�re led
   return 1;
 }