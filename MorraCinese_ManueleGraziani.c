#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <errno.h>

#define Sasso   0
#define Carta   1
#define Forbici 2


//Dichiarazione delle funzioni
short int User_Input();
void PrintRules();
void Play(unsigned short int);


typedef struct {

        unsigned short int UserWins;
        unsigned short int PCWins;

}scores;



int main(){

        unsigned short int Shots_Number = 3;
        short int User_Choice = -1;

        printf("MORRA CINESE \n");
        printf("Developed by Manuele Graziani \n\n");



        do{


                do{
                        printf("Premere 1: per giocare \nPremere 2: per impostare il numero dei tiri per vincere  \n");
                        printf("Premere 3: per visualizzare le regole \nPremere 0: per uscire dal gioco\n");

                        User_Choice = User_Input();

                        if( User_Choice < 0 || User_Choice > 3){

                                system("clear");
                                User_Choice = -1;
                                printf("\nValore inserito non valido, riprovare \n\n");
                        }

                }while(User_Choice == -1);


                switch(User_Choice)
                {

                        case 1:Play(Shots_Number);break;

                        case 2:printf("Inserire il numero dei tiri da compiere per determianre il vincitore (Max 3 caratteri):  ");
                               Shots_Number = User_Input();
                               printf("\n");break;

                        case 3:PrintRules();break;

                }



        }while(User_Choice != 0);

        printf("Chiusura del programma\n");

        return 0;

}



//Implementazione delle funzioni

void PrintRules(){

        system("clear");
        printf("Lo scopo è sconfiggere l'avversario 'di nome Processore' scegliendo un segno in grado di battere quello dell'avversario, secondo le seguenti regole:\n");
        printf("- Il sasso rompe le forbici\n- Le forbici tagliano la carta\n- La carta cattura il sasso\n");
        printf("\nInoltre si può scegliere quante volte ripetere il gioco per determinare il vincitore (Default 3 tiri)\n\n");

}


short int User_Input(){ 

        short int User_Choice = -1;
        char Buffer[3], *endptr = NULL;

        do{

                scanf("%3s",Buffer);/*Legge solamente i primi due caratteri inseriti 
                                      dall'utente impendendo overflow del Buffer*/
		if(getchar() == '\n'){
		
		       	errno = 0;
        	        User_Choice = (short int) strtol (Buffer,&endptr, 10);
			//printf("Valore U: %d \n", User_Choice);


	                //Controllo sui possibili errori
               		if(errno != 0){
                        	printf("Error: strtol %d",errno);
                        	exit(EXIT_FAILURE);
                	}


               		if(*endptr != '\0'){
                        	printf("Per favore inserire valori appartenenti all'insieme N\n\n");
                        	User_Choice = -1;
                	}
		
		
		
		}else{

			printf("Errore, valore inserito superiore alla dimensione massima consentita. Riprovare!!\n");
			while(getchar() != '\n');/*Nell’eventualità di un input di dimensioni maggiori di due caratteri, i caratteri 
                           			   in eccesso verranno cancellati fino al raggiungimento dell’carattere terminazione*/

			User_Choice = -1;

		}


               

        }while(User_Choice == -1);

        return User_Choice;
}


void Play(unsigned short int Shots_Number){


        short int Pc_Choice = -1, User_Choice = -1;
        int t = 0;
        char **array;//Array utilizzato per stampare la mossa corrispondente al numero generato 
        scores Scores;

        if( (array = malloc(sizeof (char*)*3)) == NULL)
                exit(EXIT_FAILURE);

        array[0] = "Sasso";
        array[1] = "Carta";
        array[2] = "Forbici";

        Scores.UserWins = 0;
        Scores.PCWins = 0;

        system("clear");
	

	t = time(NULL);
	srand(t);

        for(int i = 0; i < Shots_Number; i++){



                do{

                        printf("Premere 0: Per scegliere sasso \nPremere 1: Per scegliere carta  \n");
                        printf("Premere 2: Per scegliere forbici\n");

                        User_Choice = User_Input();

                        //Esegue il controllo sul valore inserito dall'utente
                        if( User_Choice < 0 || User_Choice > 2){

                                system("clear");

                                User_Choice = -1;
                                printf("\nValore inserito non valido, riprovare %d \n\n", User_Choice);
                        }

                }while(User_Choice == -1);

                Pc_Choice = rand() % 3;


                printf("Scelta Processore: %s \n",array[Pc_Choice]);

                //Confronta la scelta dell'utente a quella del PC per determinare il vincitore
                switch(User_Choice){

                        case Sasso:
                                switch(Pc_Choice){
                                            case Sasso: printf("Pari\n\n"); break;
                                            case Carta: printf("Hai perso una battaglia, ma non la guerra \n\n");Scores.PCWins++;break;
                                            case Forbici: printf("Hai vinto\n\n"); Scores.UserWins++; break;
                                }

                                break;



                        case Carta:
                                switch(Pc_Choice){
                                            case Sasso: printf("Hai vinto\n\n"); Scores.UserWins++; break;
                                            case Carta: printf("Pari\n\n"); break;
                                            case Forbici:printf("Hai perso una battaglia, ma non la guerra\n\n");Scores.PCWins++;break;
                                }

                                break;

                        case Forbici:
                                switch(Pc_Choice){
                                            case Sasso: printf("Hai perso una battaglia, ma non la guerra \n\n");Scores.PCWins++;break;
                                            case Carta: printf("Hai vinto\n\n"); Scores.UserWins++; break;
                                            case Forbici: printf("Pari\n\n"); break;
                                 }

                                break;


                }



        }

	free(array);	

        if(Scores.UserWins > Scores.PCWins)
                printf("***HAI VINTO***\n");
        else if(Scores.UserWins < Scores.PCWins)
                printf("***HAI PERSO***\n");
        else
                printf("***PARITA'***\n");


}
