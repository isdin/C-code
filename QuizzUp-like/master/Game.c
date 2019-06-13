#include "index.h"

void createAnswersFile(char *fileName)
{
    FILE * fichier = NULL;

    fichier=fopen(fileName,"rb");
    if (fichier==NULL)
    {
        fichier=fopen(fileName,"wb");
        
    }
    fclose(fichier);
}

void LaunchGame(profil *User)
{
    long IndexPosQuestion[5]; 
    short totalscore = 0;
    memset(IndexPosQuestion,0,sizeof(long)*5);
    srand(time(NULL));
    CLEAR
    printf("Bonjour %s\n",User->nom);
    char selected[144]; 
    printf("\n"); 
    printf("Choisissez un theme : ");
    Index *Themes = NULL; 
    Index *Tquestion = NULL;
    Partie partie;
    memset(&partie,0,sizeof(Partie));
    long nquestion = 0;
    long size = allocate_Index(QUESTFILE);
    Themes = (Index *) malloc(sizeof(Index)*size);
    memset(Themes,0,sizeof(Index)*size);
    Tquestion = (Index *) malloc(sizeof(Index)*size);
    memset(Tquestion,0,sizeof(Index)*size);
    Fill_index(QUESTFILE,Themes); 
    MakeIndex(QUESTFILE,Themes,size);
    
    SortIndexTheme(QUESTFILE,Themes,size);
    printf("|Saisissez TOUS pour tous les themes.|\n");
    PrintByTheme_MEMORY("inutile",Themes,size);
    
    printf("\nVotre choix (sensible a la casse) > ");
    memset(selected,0,144);
    fgets(selected,144,stdin);
    selected[strlen(selected)-1]=0;
    
    if(strcmp(selected,"TOUS")!=0)
    {
        
        for(long x=0;x<size;x++)
        {
        
                if(strcmp((Themes+x)->theme,selected)==0)
                {
                    memcpy((Tquestion+nquestion),(Themes+x),sizeof(Index));
                    strcpy(partie.theme,selected);
                    nquestion++;
                }
        
        }

        if(!nquestion)
        {
            printf("Aucun Theme correspondant a \"%s\" n'a ete trouve",selected);
            free(Tquestion);
            free(Themes);
            getchar();
            return;
        }
    }
    else
    {
        for(long x=0;x<size;x++)
        {
        

                    memcpy((Tquestion+nquestion),(Themes+x),sizeof(Index));
                    strcpy(partie.theme,(Themes+x)->theme);
                    nquestion++;
                
        
        }


    }
    
    
    if(nquestion<5)
        {
            printf("Il n'y a pas assez de question dans ce theme !\n");
            free(Tquestion);
            free(Themes);
            getchar();
            return;
        }
    



        for(long i = 0; i < 5; i++)
        {
            IndexPosQuestion[i] = rand()%nquestion;
            for(long j = i-1;j>=0;j--)
                {
                    if(IndexPosQuestion[i]==IndexPosQuestion[j])
                    {
                        i--;
                        j=-1;
                    }
                }
        }
        partie.IdProfil = User->iDProfil;
        partie.IdPartie = set_id(1);
        for(short i=0;i<5;i++)
        {
            partie.IdQestion[i] = (Tquestion+IndexPosQuestion[i])->idQuestion;
        }
        

        totalscore = QandA(Tquestion,IndexPosQuestion,User,&partie);

        partie.scoreTotal = totalscore;
        WritePartie(&partie); 
        free(Themes);
        free(Tquestion);
        printf("Votre score : %hd",totalscore);
        getchar();

}

short QandA(Index *question, long *index,profil *User,Partie *partie)
{
    short score = 0;
    short choix = 0;
    time_t start, end, duration; 
    bool GoodAnswer = false;
    bool interupt = false;
    
    reponse donnee; 
    
    

    

    for(int i = 0;i<5;i++)
    {
        memset(&donnee,0,sizeof(reponse));
        GoodAnswer = false;
        interupt = false;
        CLEAR
        printf("Saisissez votre reponse (1 a 3) ou -1 pour quitter\n");
        start = time (0);
        printf("QUESTION %d : \n",i+1);
        printf("Theme : "); 
        puts((question+*(index+i))->theme);
        puts((question+*(index+i))->libelle);
        printf("1. ");
        puts((question+*(index+i))->distracteur1);
        printf("2. ");
        puts((question+*(index+i))->distracteur2);
        printf("3. ");
        puts((question+*(index+i))->distracteur3);
        printf("Votre choix > ");
        scanf("%hd",&choix);
        getchar();
        end = time(0);
        duration = end - start;
        donnee.idProfil = User->iDProfil;
        donnee.idPartie = set_id(1);
        donnee.idQuestion = (question+*(index+i))->idQuestion;
        
        if(choix==-1)
        {
            interupt = true;
        }
        donnee.timestamp = duration;
        donnee.reponseDonnee = choix;
        if(choix==-1)
            donnee.reponseDonnee = 0;
        switch (choix)
        {
            case 1 : 
                        if(strcmp((question+*(index+i))->distracteur1,(question+*(index+i))->correctAnswer)==0)
                            {
                                GoodAnswer = true;
                                donnee.points = GiveScore(duration);
                            }
                break;
            case 2 : 
                        if(strcmp((question+*(index+i))->distracteur2,(question+*(index+i))->correctAnswer)==0)
                            {
                                GoodAnswer = true;
                                donnee.points = GiveScore(duration);
                            }
                break;
            case 3 : 
                        if(strcmp((question+*(index+i))->distracteur3,(question+*(index+i))->correctAnswer)==0)
                            {
                                GoodAnswer = true;
                                donnee.points = GiveScore(duration);
                            }
                break;
            case -1 : 
                score+=0;
                for(int x=i;x<5;x++)
                    partie->IdQestion[x] = 0;
                break;

            default: 
                    score += 0;
                    donnee.points = 0;
                break;
        }

        if(GoodAnswer && interupt==false)
        {
            score+=GiveScore(duration);
            
        }
        if(interupt == true)
        {
            donnee.points = 0;
            return score;
        }

        WriteAnswer(&donnee);

    }

    
    return score; 
}

short GiveScore(time_t input)
{
    switch ((short)input)
        {
                case 0:
                case 1: return 10;
                    break;
                case 2: return 9;
                    break;
                case 3: return 8;
                break;
                case 4:return 7;
                    break;
                case 5: return 6;
                break;
                case 6: return 5;
                    break;
                case 7: return 4;
                break;
                case 8: return 3;
                    break;
                case 9: return 2;
                break;
                case 10: return 1;
                    break;
                default: return 0;
                    break;
            
        }

        return 0;
}

void WriteAnswer(reponse *input)
{
    FILE *stream = NULL; 

    stream = fopen(ANSWFILE,"ab");
    fwrite(input,sizeof(reponse),1,stream);
    fclose(stream);

}

long Size_Of_Reponse()
{
    FILE *stream = fopen(ANSWFILE,"ab");
    long size = ftell(stream);
    fclose(stream);

    size/=sizeof(reponse);

    return size;
}

void createFilePartie(char *fileName)
{
    FILE * fichier = NULL;
    
    
    

    fichier=fopen(fileName,"rb");
    if (fichier==NULL)
    {
        fichier=fopen(fileName,"wb");
        
    }
    fclose(fichier);
}

void WritePartie(Partie *input)
{
    FILE *stream = NULL; 
    stream = fopen("partie.dat","ab");
    fwrite(input,sizeof(Partie),1,stream); 
    fclose(stream);
}
long PartieSize()
{
    FILE *stream = NULL; 
    stream = fopen("partie.dat","ab");
    long size = ftell(stream);
    size/=sizeof(Partie); 
    fclose(stream);

    return size;
}

void ReadAnswer(long ID,bool OnlyMe)
{
    CLEAR
    reponse *data = NULL;
    FILE *stream = NULL;
    data = (reponse *) malloc(sizeof(reponse));
    long o = 0;
    memset(data,0,sizeof(reponse));
    
    
    stream = fopen(ANSWFILE,"rb");
    if(OnlyMe == false)
    {
        while(fread(data,sizeof(reponse),1,stream)>=1)
        {
            
            printf("\n---------------------------\n");
            printf("IdProfil : %s\n",ReturnNameById(data->idProfil));
            printf("IdPartie : %ld\n",data->idPartie);
            printf("IdQuestion : %ld\n",data->idQuestion);
            printf("Points : %hd\n",data->points);
            printf("Reponse : %hd\n",data->reponseDonnee);
            printf("Time_Stamp : %d\n",(int)data->timestamp);
            printf("\n---------------------------\n");
            memset(data,0,sizeof(reponse));
            o++;
        }
    }

    else
    {
        while(fread(data,sizeof(reponse),1,stream)>=1)
        {
            //if(data->idProfil==ID)
            if(strcmp(ReturnNameById(data->idProfil),ReturnNameById(ID))==0)
            {
                printf("\n---------------------------\n");
                printf("IdProfil : %s\n",ReturnNameById(data->idProfil));
                printf("IdPartie : %ld\n",data->idPartie);
                printf("IdQuestion : %ld\n",data->idQuestion);
                printf("Points : %hd\n",data->points);
                printf("Reponse : %hd\n",data->reponseDonnee);
                printf("Time_Stamp : %d\n",(int)data->timestamp);
                printf("\n---------------------------\n");
                memset(data,0,sizeof(reponse));
                o++;
            }
        }
    }
    
    printf("--- %s a %ld reponses ---\n\n",ReturnNameById(ID),o);
    fclose(stream);
    free(data);
    data=NULL;

    printf("\n-----------PRESS ENTER-----------------");
    getchar();


}
void ReadPartie()
{
    Partie *data = NULL;
    FILE *stream = NULL;
    data = (Partie *) malloc(sizeof(Partie));
    memset(data,0,sizeof(Partie));
    
    stream = fopen("partie.dat","rb");
    

    while(fread(data,sizeof(Partie),1,stream)>=1)
    {
        printf("\n---------------------------\n");
        printf("IdProfile : %ld\n",data->IdProfil);
        printf("IdPartie : %ld\n",data->IdPartie);
        printf("Theme  : %s\n",data->theme);
        printf("ID des questions posee : ");
        for(int w = 0;w<5;w++)
        {
            if(data->IdQestion[w])
                printf(" %ld",data->IdQestion[w]);
        }
        printf("\n");
        printf("Points : %hd\n",data->scoreTotal);

        printf("\n---------------------------\n");
        memset(data,0,sizeof(Partie));
    }
    fclose(stream);
    free(data);
    data=NULL;
}

void GetMyGames(profil *user,bool myself)
{
	CLEAR
    MyGames *Stack= NULL;
    MyGames *stamp = NULL;
    Partie *data = NULL;
    FILE *stream = NULL;
    profil temp;
    long i=0;
    char str[144]; 
    if(!myself)
    {
    	printf("Quel utilisateur vous interesse ?"); 
    	fgets(str,144,stdin);
    
    	str[strlen(str)-1]=0;
    	str[0] = toupper(str[0]);
    	i = Seek_User(USERFILE,str,&temp);
    	if(i<=0)
        	return;
    	i=0;

    }
    else
    	temp = *user;
    stream = fopen("partie.dat","rb");
    
    data = (Partie *)malloc(sizeof(Partie));

    while(fread(data,sizeof(Partie),1,stream)>=1)
    {
        if(strcmp(ReturnNameById(data->IdProfil),temp.nom)==0 && data->IdProfil == temp.iDProfil)
        {
            stamp = (MyGames *) malloc(sizeof(MyGames));
            stamp->Next = Stack;
            stamp->data = data; 
            Stack = stamp;
        }
    data = (Partie *)malloc(sizeof(Partie));
    }
    fclose(stream);

    while(Stack!=NULL)
    {
        printf("\n---------------------------\n");
        printf("Profile : %s\n",ReturnNameById(Stack->data->IdProfil));
        printf("IdPartie : %ld\n",Stack->data->IdPartie);
        printf("Theme  : %s\n",Stack->data->theme);
        printf("ID des questions posee : ");
        for(int w = 0;w<5;w++)
        {
            if(Stack->data->IdQestion[w])
                printf(" %ld",Stack->data->IdQestion[w]);
            else
                printf(" NON REPONDU ");
        }
        printf("\n");
        printf("Points : %hd\n",Stack->data->scoreTotal);

        printf("\n---------------------------\n");
        i++;
        Stack = Stack->Next;
    }

    printf("\n------ %ld Parties on ete jouee par %s ---------\n",i,temp.nom);
    printf("\n---------------PRESS ENTER---------------\n");
    getchar();
    free(data);
    free(stamp);
}

void Check_Integrity()
{

	return;

}

void delete_ForIntegrity(long ID)
{
    long i;
    
    long sizeofFile = Size_Of_Reponse();
    FILE *stream = fopen(ANSWFILE,"r+b");
    FILE *second = NULL; 
    second = fopen("buffer.dat","w+b");

    reponse *data = NULL;
    data = (reponse *) malloc(sizeof(reponse));



    for(i=0;i<sizeofFile;i++)
    {
        memset(data,0,sizeof(reponse));
        fread(data,sizeof(reponse),1,stream);
        if(data->idProfil!=ID)
        {
            fwrite(data,sizeof(reponse),1,second);
        }
        
    }

    fclose(stream); 
    fclose(second);
    remove(ANSWFILE); 
    rename("buffer.dat",ANSWFILE);
    free(data);
    delete_ForIntegrity_partie(ID);
    delete_ForIntegrity_Answers(ID);
}
void delete_ForIntegrity_partie(long ID)
{
    long i;
    
    long sizeofFile = PartieSize();
    FILE *stream = fopen("partie.dat","r+b");
    FILE *second = NULL; 
    second = fopen("buffer.dat","w+b");

    Partie *data = NULL;
    data = (Partie *) malloc(sizeof(Partie));



    for(i=0;i<sizeofFile;i++)
    {
        memset(data,0,sizeof(Partie));
        fread(data,sizeof(Partie),1,stream);
        if(data->IdProfil!=ID)
        {
            fwrite(data,sizeof(Partie),1,second);
        }
        
    }

    fclose(stream); 
    fclose(second);
    remove("partie.dat"); 
    rename("buffer.dat","partie.dat");
    free(data);
}

void Teacher_Quote()
{
        
        printf("127 est le meilleur nombre au monde.\n");
        printf("\t\t\tMonsieur P. Quettier 2018-2019\n\n");
        printf("Dire que je suis payez a vous regarder.\n");
        printf("\t\t\tMonsieur P. Quettier 2018-2019\n\n");
        printf("Oh merde, il y a un mandat contre Dodo la Saumure.\n");
        printf("\t\t\tMonsieur P. Quettier 2018-2019\n\n");
        printf("En tant que votre meilleur prof je ....\n");
        printf("\t\t\tMonsieur P. Quettier 2018-2019\n\n");
        printf("Que t'es con Isdin.\n");
        printf("\t\t\tMonsieur P. Quettier 2018-2019\n\n");
        printf("[Explications sur les piles] Quand votre queue est au maximum,...Vous etes degueulasse\n");
        printf("\t\t\tMonsieur P. Quettier 2018-2019\n\n");
        printf("Si vous n'y arrivez pas, vous pouvez aller en Infographie.\n");
        printf("\t\t\tMonsieur H. Vanstapel 2018-2019\n\n");
        printf("Je m'enfou, tant que ça marche.\n");
        printf("\t\t\tMonsieur S. Calmant 2018-2019\n\n");
        printf("Reflechis un peu !\n");
        printf("\t\t\tMonsieur S. Calmant 2018-2019\n\n");
        printf("Un homme de la rue pourrait pirater votre reseau.\n");
        printf("\t\t\tMonsieur P. Defooz 2018-2019\n\n");
        printf("Vous voulez voir une huitre ?\n");
        printf("\t\t\tMonsieur P. Sagot 2018-2019\n\n");
        printf("Je me suis casse une cote au Karting\n");
        printf("\t\t\tMonsieur P. Sagot 2018-2019\n\n");
        printf("A 40 etudiants, Isdin fait sauter l'amphi\n");
        printf("\t\t\tMonsieur P. Sagot 2018-2019\n\n");
        printf("Je suis ne un 14 Avril, un dimanche en 79, je suis une cloche.\n");
        printf("\t\t\tMonsieur P. Sagot 2018-2019\n\n");
}
void Help()
{
        printf("1. Vos parties/score/reponses se trouve dans : Menu profil --> Mon profil --> Mes parties\n");
        printf("2. Vous pouvez modifier toute vos donnees sauf votre Username\n");
        printf("3. Tout les fichiers necessaire a l'app sont cree au lancement.\n");
        printf("4. Easter Egg : ./main -127\n");
}

void PointbyTheme()
{
    

    FILE *stream = NULL;

    profil fetched;


    reponse *rep = NULL;
    reponse TempR;
    Question *questions = NULL;
    Question tempQ;
    
    
    char selected[144]; 
    char Uchoice[144]; 
    long Nb_questions_theme = 0;
    long Nb_answers_Theme = 0;
    long sizeofReponse = 0;
    short score=0;
    CLEAR
    printf("Quel Theme vous interesse ? >> ");
    fgets(selected,144,stdin); 
    selected[strlen(selected)-1]=0;


    printf("Quel utilisateur vous interesse ? >> "); 
    fgets(Uchoice,144,stdin); 
    Uchoice[strlen(Uchoice)-1]=0;
    questions = (Question *)malloc(sizeof(questions));
    Seek_User(USERFILE,Uchoice,&fetched); //Get The User Profile;
    if(fetched.iDProfil<=0)
        return;
    /* checking question themes */

    stream = fopen(QUESTFILE,"rb");
    fread(questions,sizeof(questions),1,stream);
    while(questions->idQuestion > 0)
    {
        if(strcmp(questions->theme,selected)==0)
            Nb_questions_theme++;
        fread(questions,sizeof(questions),1,stream);
    }
    fseek(stream,0,SEEK_SET);

    free(questions);

    questions = (Question*)malloc(sizeof(questions)*Nb_questions_theme);
    memset(questions,0,Nb_questions_theme);

    for(int i =0;i<Nb_questions_theme;i++)
    {
        do
        {
            fread(&tempQ,sizeof(Question),1,stream);
        } while (strcmp(tempQ.theme,selected)!=0);

        memcpy((questions+i),&tempQ,sizeof(Question));
    }
    fclose(stream);
    /* NOW QUESTIONS ARE SET */

    /* Setting ANSWER data */ 
    stream = fopen(ANSWFILE,"ab");
    sizeofReponse = ftell(stream)/sizeof(reponse);
    fclose(stream);
    stream = fopen(ANSWFILE,"rb");
    
    for(int i = 0;i<sizeofReponse;i++)
    {
        fread(&TempR,sizeof(reponse),1,stream);
        if(strcmp(ReturnTheme_ById(TempR.idQuestion),selected)==0)
            Nb_answers_Theme++;
    }

    rep = (reponse*)malloc(sizeof(reponse)*Nb_answers_Theme);
    fseek(stream,0,SEEK_SET);
    for(int i=0;i<sizeofReponse;i++)
    {
        fread(&TempR,sizeof(reponse),1,stream);
        if(strcmp(ReturnTheme_ById(TempR.idQuestion),selected)==0 && TempR.idProfil == fetched.iDProfil)
            score+=TempR.points;
    }
    fclose(stream);

    /* NOW ANSWERS ARE SET */


    free(rep);
    free(questions);

    printf("L'utilisateur %s a accumule %hd points pour le theme %s\n",Uchoice,score,selected);
    getchar();

}

char *ReturnTheme_ById(long ID)
{
    FILE *questionsFile = fopen(QUESTFILE,"rb");
    char *str = NULL;
    
    
    Question *fetch = (Question*)malloc(sizeof(Question));

    fread(fetch,sizeof(Question),1,questionsFile);

    while(fetch->idQuestion != ID && fetch->idQuestion >0)
        fread(fetch,sizeof(Question),1,questionsFile);

    if(fetch->idQuestion>0)
    {
        str=(char *) malloc(sizeof(char)*50+1);
        strcpy(str,fetch->theme);
    }
    free(fetch);
    fclose(questionsFile);


    return str;
}
void delete_ForIntegrity_Answers(long ID)
{
    reponse *buffer = NULL;
    FILE *Answers = fopen(ANSWFILE,"ab");
    createAnswersFile("$tempAnsw");
    FILE *stamp = fopen("$tempAnsw","r+b");
    long SizeFile = ftell(Answers);
    fclose(Answers);
    Answers = fopen(ANSWFILE,"r+b");
    


    buffer = (reponse*)malloc(sizeof(reponse));

    while(ftell(Answers)<SizeFile)
    {
        memset(buffer,0,sizeof(reponse));
        fread(buffer,sizeof(reponse),1,Answers);
        if(buffer->idProfil != ID)
            fwrite(buffer,sizeof(reponse),1,stamp);
    }
    free(buffer);
    fclose(Answers);
    fclose(stamp);
    remove(ANSWFILE);
    rename("$tempAnsw",ANSWFILE);

}

void BestScore()
{
    CLEAR
    char *stringcountry = NULL;
    FILE *parties_file = fopen("partie.dat","ab");
    long size = ftell(parties_file)/sizeof(Partie);
    fclose(parties_file);
    parties_file= fopen("partie.dat","rb");
    Partie *parties = (Partie *)malloc(sizeof(Partie)*size);
    Partie temp;
    long fiveplayers=0;
    

    long *Ids = (long *)malloc(sizeof(long)*size);
    
    long x,y;

    
    for(x=0;x<size;x++)
        fread((parties+x),sizeof(Partie),1,parties_file);
    fclose(parties_file);
    for(x=0;x<size;x++)
        *(Ids+x) = (parties+x)->IdProfil;

    for(x=0;x<size;x++)
    {
        
        for(y=x+1;y<size;y++)
        {
            if((parties+x)->IdProfil == (parties+y)->IdProfil)
            {
                (parties+x)->scoreTotal+=(parties+y)->scoreTotal;
                (parties+y)->IdProfil = -1;
            }
        }
        
    }
    printf("%12s \t\t\t|\tSCORE\t|\tPAYS\t\n","JOUEUR");
    printf("%12s \t\t\t|\t     \t|\t\n","");
    for(x=0;x<size;x++)
    {
        if((parties+x)->IdProfil != -1)
        {
            for(y=x+1;y<size;y++)
            {
                if((parties+x)->IdProfil != -1)
                {
                    if((parties+x)->scoreTotal<(parties+y)->scoreTotal)
                    {
                        temp = *(parties+x);
                        *(parties+x)=*(parties+y);
                        *(parties+y)=temp;
                    }
                }
            }
        }
    }

    for(x=0;x<size&&fiveplayers<100;x++)
    {
        if((parties+x)->IdProfil != -1)
        {
            stringcountry = ReturnCountryByid((parties+x)->IdProfil);
            if(stringcountry==NULL)
                printf("%12s\t\t\t|\t%hd\t|\t%s\n",ReturnNameById((parties+x)->IdProfil),(parties+x)->scoreTotal,"CANT FETCH");
            else
            {
                printf("%12s\t\t\t|\t%hd\t|\t%s\n",ReturnNameById((parties+x)->IdProfil),(parties+x)->scoreTotal,stringcountry);
            }

            
            fiveplayers++;
        }
    }
    printf("\n--Appuyez sur enter--\n");
    getchar();
}