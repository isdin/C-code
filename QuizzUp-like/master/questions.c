#include "index.h"
#define MAXBIDON 5000


void createFileInd(char *fileName)
{

    FILE * fichier = NULL;
    Question record={-1};
    int i=0;
    int erreur=0;

    fichier=fopen(fileName,"r+b");
    if (fichier==NULL)
    {
        fichier=fopen(fileName,"wb");
        while((i<5000)&&!erreur)
        {
        if(fwrite(&record,sizeof(Question),1,fichier)!=1)
            erreur=-1;
        i++;
        }
        
    }
    fclose(fichier);

}

void WriteQuestion(char *Filename,Question *input)
{
    FILE *stream = NULL; 
    long FileSize = 0;
    createFileInd(Filename);
    bool ending = 1;
    Question trashBin;
    stream = fopen(Filename,"r+b");
    while(!feof(stream)&&ending)
    {
        fread(&trashBin,sizeof(Question),1,stream);
        if(trashBin.idQuestion>0)
            FileSize++;
        else
            ending=0;
        
    }
    if(FileSize==MAXBIDON)
        {
            fclose(stream); 
            printf("LE MAXIMUM DE QUESTION A ETE ATTEINT\n");
            getchar();
            return;
        }
    fseek(stream,sizeof(Question)*FileSize,SEEK_SET);
    fwrite(input,sizeof(Question),1,stream);
    fclose(stream);
}

void MakeIndex(char *Filename,Index *Fetched,long index_size)
{
    long i=0,j=0; 
    long sizeofFile = 0; 
    FILE *pf = fopen(Filename,"rb"); 
    Index temp;
    
    fclose(pf);
    for( i = 0; i < sizeofFile; i++)
    {
        for(j=i+1;j<sizeofFile;j++)
        {
            if((strcmp((Fetched+i)->libelle,(Fetched+j)->libelle))>0)
            {
                temp = *(Fetched+i); 
                *(Fetched+i) = *(Fetched+j); 
                *(Fetched+j) = temp;
            }
        }
    }
}

void SortIndexLabel(char *Filename,Index *Fetched,long sizeofFile)
{
    long i=0,j=0; 
    
    
    Index temp; 
    
    for( i = 0; i < sizeofFile; i++)
    {
        for(j=i+1;j<sizeofFile;j++)
        {
            if((strcmp((Fetched+i)->libelle,(Fetched+j)->libelle))>0)
            {
                temp = *(Fetched+i); 
                *(Fetched+i) = *(Fetched+j); 
                *(Fetched+j) = temp;
            }
        }
    }
    
}
void SortIndexTheme(char *Filename,Index *Fetched,long sizeofFile)
{
    long i=0,j=0; 
    
    Index temp; 
    
    for( i = 0; i < sizeofFile; i++)
    {
        for(j=i+1;j<sizeofFile;j++)
        {
            if((strcmp((Fetched+i)->theme,(Fetched+j)->theme))>0)
            {
                temp = *(Fetched+i); 
                *(Fetched+i) = *(Fetched+j); 
                *(Fetched+j) = temp;
            }
        }
    }

    
}

void PrintByLabel_HardDrive(char *Filename,Index *PayLoad,long index_size)
{
    FILE *data = NULL; 
    Question temp;
    createFileInd(QUESTFILE);
    data= fopen(QUESTFILE,"rb");
    long x;
    
    for( x = 0; x < index_size; x++)
    {
        fseek(data,sizeof(Question)*(PayLoad+x)->position,SEEK_SET);
        fread(&temp,sizeof(Question),1,data);
        puts(temp.libelle);
        
        
    }

    fclose(data);
    

}
void PrintByTheme_HardDrive(char *Filename,Index *PayLoad,long index_size)
{
    FILE *data = NULL; 
    Question temp;
    
    data= fopen(QUESTFILE,"rb");
    long x;
    
    bool printed = false;
    char themes[5000][50]; 
    for( x = 0; x < index_size; x++)
    {
        fseek(data,sizeof(Question)*(PayLoad+x)->position,SEEK_SET);
        fread(&temp,sizeof(Question),1,data);
        strcpy(themes[x],temp.theme);
    if(printed==false)
        puts(temp.theme);

    

    }

    fclose(data);
    getchar();
    

}
void DeleteRecordIndex()
{
    long tempId=-5; 
    long sizeofFile = allocate_Index(QUESTFILE);
    FILE *stream = fopen(QUESTFILE,"r+b");
    FILE *second = NULL; 
    createFileInd("buffer.dat");
    second = fopen("buffer.dat","r+b");

    Question *data = NULL;
    data = (Question *) malloc(sizeof(Question));

    long i=0;
    printf("1. Veuillez saisir l'id de la question a Supprimer [0] pour quitter\n> ");
    scanf("%ld",&tempId); 
    getchar();

    if(!tempId)
    {
        free(data);
        return; 
    }
    for(i=0;i<sizeofFile;i++)
    {
        memset(data,0,sizeof(Question));
        fread(data,sizeof(Question),1,stream);
        if(data->idQuestion!=tempId)
        {
            if(data->idQuestion <=0)
                i=5002;
            else
            {
                fwrite(data,sizeof(Question),1,second);
            }
            
        }
        
    }

    fclose(stream); 
    fclose(second);
    remove(QUESTFILE); 
    rename("buffer.dat",QUESTFILE); 

    free(data);
    



}

long allocate_Index(char *filename)
{
    Question temp;
    
   	FILE *stream = NULL;

    stream = fopen(filename,"rb");
    long SizeOfFile = 0; 
    bool ending = true;
    while(!feof(stream)&&ending)
    {
        fread(&temp,sizeof(Question),1,stream);
        if(temp.idQuestion==-1||temp.idQuestion == 0)
            ending=false;
        else
        {

            SizeOfFile++;
        }
        

    }

    
    fclose(stream);

    return SizeOfFile;
}
void Fill_index(char *Filename,Index *input)
{
    Question temp;
    
    FILE *stream = NULL;

    stream = fopen(Filename,"rb");
    long SizeOfFile = 0; 
    bool ending = true;
    while(!feof(stream)&&ending)
    {
        fread(&temp,sizeof(Question),1,stream);
        if(temp.idQuestion==-1)
            ending=false;
        else
        {
            (input+SizeOfFile)->idQuestion = temp.idQuestion;
            strcpy((input+SizeOfFile)->theme,temp.theme);
            strcpy((input+SizeOfFile)->libelle,temp.libelle);
            strcpy((input+SizeOfFile)->distracteur1,temp.distracteur1);
            strcpy((input+SizeOfFile)->distracteur2,temp.distracteur2);
            strcpy((input+SizeOfFile)->distracteur3,temp.distracteur3);
            strcpy((input+SizeOfFile)->correctAnswer,temp.correctAnswer);

            (input+SizeOfFile)->position = SizeOfFile;
            
            SizeOfFile++;
        }
        

    }

    
    fclose(stream);

}

void menuQuestion(profil *user)
{
	CLEAR
    short choice; 
    Question *new = (Question *) malloc(sizeof(Question));
    char TheString[144]; 
    long Realsize=0;
    Index *Theme = NULL;
    Index *Label= NULL;

    char lookout[144];

    
    Theme = (Index *)malloc(sizeof(Index)*allocate_Index(QUESTFILE));
    memset(Theme,0,Realsize);

    Label = (Index *)malloc(sizeof(Index)*allocate_Index(QUESTFILE));
    Realsize = allocate_Index(QUESTFILE);



        

    Fill_index(QUESTFILE,Theme);
    MakeIndex(QUESTFILE,Theme,Realsize);

    Fill_index(QUESTFILE,Label); 
    MakeIndex(QUESTFILE,Label,Realsize);

    SortIndexTheme(QUESTFILE,Theme,Realsize);
    SortIndexLabel(QUESTFILE,Label,Realsize);
    printf("1. Creer une question\n"); 
    if(Realsize)
    {
        printf("2. Modifier une question\n"); 
        printf("3. Afficher les Theme\n"); 
        printf("4. Afficher les Libelles\n");
        printf("5. Rechercher des question via Mot-Cles\n");
        printf("6. Supprimer une question\n");
    }
    printf("0. Annuler\n> "); 
    if(Realsize)
    {
        do
        {
            scanf("%hd",&choice); 
            getchar();
        } while (choice>6||choice<0);
    }
    else
    {
        do
        {
            scanf("%hd",&choice); 
            getchar();
        } while (choice>1||choice<0);
    }
    
    switch (choice)
    {
        case 1 : 
                new = SetQuestion();
                

            break;
        case 2 : 
                Question_SeekandChange();
        break; 
        case 3 : 
        case 4 :
                
                
                if(choice==3)
                {
                    
                    printf("---------------theme-----------------\n");
                    PrintByTheme_MEMORY(QUESTFILE,Theme,Realsize);
                    printf("Afficher les questions d'un Theme ? [0] pour non\n"); 
                    scanf("%hd",&choice); 
                    getchar(); 
                    if(choice)
                        {
                            printf("Veuillez saisir le Theme ! Sensible a la casse\n> ");
                            fgets(lookout,144,stdin);
                            lookout[strlen(lookout)-1]=0;
                            Print_FromTheme(lookout,Theme,Realsize);

                        }
                    
                }    
                else
                {
                    
                    printf("---------------Labels-----------------\n");
                    PrintByLabel_MEMORY(QUESTFILE,Label,Realsize);
                    getchar();
                }

                
                


        break; 
        case 5 :
                memset(TheString,0,144);
                system("clear");
                printf("Saisissez la phrase ou le mot a rechercher : ");
                fgets(TheString,144,stdin);
                TheString[strlen(TheString)-1]=0;
                Search_fromString(Label,TheString,Realsize);

        break;
        case 6 :
                DeleteRecordIndex();
        break; 
        default: 
                    free(Theme); 
                    free(Label);
                    free(new);
                    return;
            break;
    }
    free(Theme); 
    free(Label);
    free(new);
}
long Question_SeekandChange()
{
    FILE *seeker = fopen(QUESTFILE,"r+b"); 
    char str[144];
    long ID; 
    printf("Veuillez saisir le theme de la question a changer > \n");
    fgets(str,144,stdin); 
    str[strlen(str)-1]=0;
    Index *temp = NULL; 
    Question changeMe; 
    long i = 0;
    long size = allocate_Index(QUESTFILE);
    
    temp = (Index *) malloc(sizeof(Index)*size);
    memset(temp,0,sizeof(Index));
    long pos=0; 
    Fill_index(QUESTFILE,temp);
    MakeIndex(QUESTFILE,temp,allocate_Index(QUESTFILE));

    for(i=0;i<size;i++)
    {
        if(strcmp((temp+i)->theme,str)==0)
            {
                printf("ID : %ld\n",(temp+i)->idQuestion);
                printf("Libelle : "); 
                puts((temp+i)->libelle);
                pos = 1;
            }
    }
    if(pos)
    {

        printf("Veuillez saisir L'id de la question a Modifier : "); 
        scanf("%ld",&ID); 
        getchar(); 

        for(i=0;i<size;i++)
        {
            if(ID == (temp+i)->idQuestion)
                {
                    pos = (temp+i)->position; 
                    i=size+1;
                }
        }
        if(pos>=0)
        {
            fseek(seeker,sizeof(Question)*pos,SEEK_SET);
            fread(&changeMe,sizeof(Question),1,seeker);
            rewind(seeker); 
            fseek(seeker,sizeof(Question)*pos,SEEK_SET);
            Change_me(&changeMe);
            fwrite(&changeMe,sizeof(Question),1,seeker);
        }
        else
        {
            printf("ID NON VALIDE retour au menu\n"); 
            getchar();
            
        }
        
    }
    else
    {
        printf("Theme non trouver. Retour au menu\n"); 
        getchar();
        
    }
    
    fclose(seeker); 
    free(temp);
    return -1;
}

void Change_me(Question *sended)
{
    short choice; 
    short sure = 0;
    short rebeg=0; 
    Question *input = (Question *) malloc(sizeof(Question));
    memset(input,0,sizeof(Question));
    *input = *sended;

    system("clear");
    printf("Donnee Actuel : \n"); 
    Print_one_question(sended);
    printf("Que voulez vous changer :\n");

    printf("1. Le Libelle\n"); 
    printf("2. Theme\n"); 
    printf("3. Les distracteurs\n");
    printf("4. Reponse  \n");
    printf("0. ANNULER\n> ");
    scanf("%hd",&choice);
    getchar();

    switch (choice)
    {
        case 1 : 
                    printf("Saisissez le Libelle : ");
                    while(SET_string(input->libelle,0)); 
        break; 
        case 2 : 
                    printf("Saisissez le Theme : "); 
                    fgets(input->theme,MAXCHAR,stdin);
                    input->theme[strlen(input->theme)-1]=0;
        break; 
        case 3 : 
                do
                {
                    rebeg =0;
                    printf("Saisissez le distracteur 1 : ");
                    while(SET_string(input->distracteur1,0));

                    printf("Saisissez le distracteur 2 : ");
                    while(SET_string(input->distracteur2,0));

                    printf("Saisissez le distracteur 3 : ");
                    while(SET_string(input->distracteur3,0));

                    if(strcmp(input->distracteur1,input->distracteur2)==0)
                        rebeg=1; 
                    if(strcmp(input->distracteur1,input->distracteur3)==0)
                        rebeg=1;
                    if(strcmp(input->distracteur2,input->distracteur1)==0)
                        rebeg=1;
                    if(strcmp(input->distracteur2,input->distracteur3)==0)
                        rebeg=1;
                    if(strcmp(input->distracteur3,input->distracteur1)==0)
                        rebeg=1;
                    if(strcmp(input->distracteur3,input->distracteur2)==0)
                        rebeg=1;
                if(rebeg)
                    printf("Les distracteurs doivent etre Different ! \n");
                } while (rebeg);
                

        break; 
        case 4 :    
                printf("Saisissez la bonne Reponse: "); 
                while(SET_string(input->correctAnswer,0));
        break; 

        break; 
        
        default : 
        free(input);
        return;
    }

    printf("Ancienne donne : \n");
    Print_one_question(sended); 
    printf("Nouvelle donnee : \n");
    Print_one_question(input);

    printf("Voulez-vous Sauvegarder les modifications ? [1]/[0] > "); 
    scanf("%hd",&sure);
    getchar();

    if(sure)
        *sended = *input; 
    
    free(input);

}
Question *SetQuestion()
{
	CLEAR
    Question *new = NULL; 
    char temp[144];
    
    int i=0;
    short printable = 0;
    new = (Question *) malloc(sizeof(Question)); 
    memset(new,0,sizeof(Question));
    
    printf("Saisissez le Theme : "); 
    fgets(new->theme,MAXCHAR,stdin);
    new->theme[strlen(new->theme)-1]=0;

    printf("Saisissez le Libelle : ");
    do
    {
        printable=0;
        memset(temp,0,144);
        fgets(temp,144,stdin);
        temp[strlen(temp)-1]=0;
        for(i=0;i<strlen(temp);i++)
        {
            if(!isprint(temp[i]))
                printable = 1;
        }
    } while (printable);
    strcpy(new->libelle,temp);

	do
	{
	        printf("Saisissez le distracteur 1 : ");
	            do
	            {
	                printable=0;
	                memset(temp,0,144);
	                fgets(temp,144,stdin);
	                temp[strlen(temp)-1]=0;
	                for(i=0;i<strlen(temp);i++)
	                {
	                    if(!isprint(temp[i]))
	                        printable = 1;
	                }
	            } while (printable);
	        strcpy(new->distracteur1,temp);



        printf("Saisissez le distracteur 2 : ");
            do
            {
                printable=0;
                memset(temp,0,144);
                fgets(temp,144,stdin);
                temp[strlen(temp)-1]=0;
                for(i=0;i<strlen(temp);i++)
                {
                    if(!isprint(temp[i]))
                        printable = 1;
                }
            } while (printable);
        strcpy(new->distracteur2,temp);

        printf("Saisissez le distracteur 3 : ");
            do
            {
                printable=0;
                memset(temp,0,144);
                fgets(temp,144,stdin);
                temp[strlen(temp)-1]=0;
                for(i=0;i<strlen(temp);i++)
                {
                    if(!isprint(temp[i]))
                        printable = 1;
                }
            } while (printable);
        strcpy(new->distracteur3,temp);


	}while(isSame(new->distracteur1,new->distracteur2,new->distracteur3)); 
	    printf("Saisissez la bonne Reponse: "); 
	        do
	    {
	        printable=0;
	        memset(temp,0,144);
	        fgets(temp,144,stdin);
	        temp[strlen(temp)-1]=0;
	        for(i=0;i<strlen(temp);i++)
	        {
	            if(!isprint(temp[i]))
	                printable = 1;
	        }
	    } while (printable);
	    strcpy(new->correctAnswer,temp);

	    new->idQuestion = set_id(2);
	    WriteQuestion(QUESTFILE,new);
    

    return new;
}

void Print_one_question(Question *input)
{
	
    printf("ID : %ld\n",input->idQuestion);
    printf("Libelle : ");
    puts(input->libelle);
    printf("Theme : "); 
    puts(input->theme);
    printf("Distracteur 1 : "); 
    puts(input->distracteur1); 
    printf("Distracteur 2 : "); 
    puts(input->distracteur2);  
    printf("Distracteur 3 : "); 
    puts(input->distracteur3);
    printf("Reponse : "); 
    puts(input->correctAnswer); 
    
}

void Print_FromTheme(char *theme,Index *index,long index_size)
{

    FILE *data = NULL; 
    Question temp;
    memset(&temp,0,sizeof(Question));
    data= fopen(QUESTFILE,"rb");
    long x;
    
    for( x = 0; x < index_size; x++)
    {
        if(strcmp((index+x)->theme,theme)==0)
        {
            fseek(data,sizeof(Question)*(index+x)->position,SEEK_SET);
            fread(&temp,sizeof(Question),1,data);
            Print_one_question(&temp);
        }
        
        
    }

    fclose(data);
    getchar();
}

void PrintByLabel_MEMORY(char *unecessary,Index *PayLoad,long index_size)
{
    long x;
    long z;
    bool printed = false;
    

        for( x = 0; x < index_size; x++)
        {
            printed = false;
            
            for(z=x-1;z>=0;z--)
                {
                    if(strcmp((PayLoad+x)->libelle,(PayLoad+z)->libelle)==0)
                        printed = true;
                }

            if(!printed)
                puts((PayLoad+x)->libelle);
            
        }
    
}


void PrintByTheme_MEMORY(char *unecessary,Index *PayLoad,long index_size)
{
    long x;
    long z;
    bool printed = false;
    for( x = 0; x < index_size; x++)
    {
        printed = false;
        
        for(z=x-1;z>=0;z--)
            {
                if(strcmp((PayLoad+x)->theme,(PayLoad+z)->theme)==0)
                    printed = true;
            }

        if(!printed)
            puts((PayLoad+x)->theme);
        
        
        
    }
}

void Search_fromString(Index *Data,char *str,long size)
{
    long x; 
    long i=1;
    char *string= NULL;
    Question tampon; 

    
    
    for(x=0;x<size;x++)
    {

        
        string = strstr((Data+x)->libelle,str);
        if(string!=NULL)
        {
            
            memset(&tampon,0,sizeof(Question)); 
            tampon.idQuestion=(Data+x)->idQuestion;
            strcpy(tampon.theme,(Data+x)->theme);
            strcpy(tampon.correctAnswer,(Data+x)->correctAnswer);           
            strcpy(tampon.distracteur1,(Data+x)->distracteur1);
            strcpy(tampon.distracteur2,(Data+x)->distracteur2);
            strcpy(tampon.distracteur3,(Data+x)->distracteur3);
            strcpy(tampon.libelle,(Data+x)->libelle);
            printf("\n----------------------\n");
            Print_one_question(&tampon);
            printf("\n----------------------\n");
            i++;
        }
        string = NULL;

        
        
    }

    printf("%ld occurences trouvee  -----------\nPRESS ENTER\n",i); 
    getchar();
}

bool isSame(char *s1,char *s2,char *s3)
{
    if(strcmp(s1,s2)==0)
        return true;
    if(strcmp(s1,s3)==0)
        return true;
    if(strcmp(s2,s3)==0)
        return true;

    return false;

}