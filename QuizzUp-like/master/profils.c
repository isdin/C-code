
#include "index.h"





profil *new_profil();
short IS_number(char *);
void UPPER_case(char *);


bool Valid_date(short,short,short);


short Age_returning(short ,short ,short );
short isLeapYear(short,short);

void My_profile(profil *,short); 
short toString(char *);

void SET_geo(char *); 






short IS_number(char *input)
{
  short i = 0;
  short j;
  char numbers[10] = {"123456789"};

  while (*(input + i))
  {
    for (j = 0; j < 10; j++)
      if (numbers[j] == *(input + i))
        return 0;


    i++;
  }

  if (i > MAXCHAR)
    return 0;
  else
    return 1;
}

bool SET_string(char *input, bool Hide_input)
{
  char buffer;
  bool get_out = true;
  short i = 0;
  bool space_seen = false;
  buffer = getchar();
  while(buffer==' ') buffer=getchar();
  if (Hide_input)
    {
    	printf("HIDDEN\n");
    }
  else
  {
    while (((buffer != '\n' && buffer != '\r' && i < MAXCHAR - 2)&&get_out))
    {
    	if ((buffer < 65 || buffer > 90) && (buffer< 97 || buffer > 122)&&buffer!=' ')
    		  get_out = false;
    	if(!isprint(buffer))
    	  	get_out= false;
      
      if(space_seen&&i>1)
      {
          i++;
          buffer=getchar();
         *(input + i) = toupper(buffer);
          space_seen = false;
      }

      else
        *(input+i) = buffer;
      

      buffer = getchar();
      if(buffer==' ')
        {
          *(input+i+1) = ' '; 
          i++;
          space_seen=true;
        }
      else
        i++;
    }
    *(input + i) = 0;
  }
  if(!get_out)
  {
    while(buffer!='\n')
      buffer = getchar();
  }

  if(i==0)
    get_out=false;

  return !get_out;
}

void UPPER_case(char *input)
{


  if (*input < 122 && *input > 97)
    *input -= 0x20;
  else
    return;
}

short menuGeneral(bool connected, char *input)
{
  short choice;
  CLEAR
  if (connected)
  {
    printf("1. Se deconnecter : %s\n", input);
    printf("2. Jouer\n");
    printf("3. Menu profil\n");
    printf("4. Afficher les utilisateurs\n");
    printf("5. Menu question \n");
    printf("6. Best score !\n");
  }
  else
    printf("1. S'inscrire/Se connecter Pour Jouer\n");

    
  
  printf("0. Quitter\n> ");

  do
  {
    scanf("%hd", &choice);
    getchar();

  } while (choice > 6 || choice < 0);

  if (choice > 5 && !connected)
    choice = -1;


  return choice;
}

profil *new_profil()
{
  short yy=0,jj=0,mm=0; 
  short langch = 0;
  profil *new = NULL;
  bool existe = false;
  bool notprintable = false;
  new = (profil *) malloc(sizeof(profil));
  memset(new,0,sizeof(profil));
  int str_len = 0;
  new->iDProfil = set_id(3);
  do
  {
    
    if(existe)
      printf("L'utilisateur existe deja, veuillez changer.\n");
    if(notprintable)
      printf("Chaine de caractere non imprimable\n");
    notprintable = false;


    printf("* Veuillez saisir votre nom : ");
    fgets(new->nom,MAXCHAR,stdin);
    new->nom[strlen(new->nom)-1]=0;
    str_len=0;
    do
    {
      if(!isprint(new->nom[str_len]))
        notprintable = true;
      str_len++;
    } while (str_len < strlen(new->nom)&&!notprintable);
    
    existe = User_Exist(new->nom);
  }while(existe|| notprintable);
  
  
  printf("* Votre code langue : 1. FR, 2. EN, 3. DE,4. NL\n");
  do
  {
    scanf("%hd",&langch);
    getchar();
  } while (langch>4 || langch<1);
  if(langch == 1)
    strcpy(new->codeLangue,"FR"); 
  else
  {
    if(langch==2)
      strcpy(new->codeLangue,"EN");
    else
    {
      if(langch==3)
        strcpy(new->codeLangue,"DE");
      else
      {
        strcpy(new->codeLangue,"NL");
      }
      
    }
    
  }
  
  


  printf("Veuillez saisir votre ville : ");
  SET_geo(new->ville);
  printf("Veuillez saisir votre pays : ");
  SET_geo(new->pays);
  printf("Veuillez saisir votre region : ");
  SET_geo(new->region);
  printf("* Veuillez saisir votre password : ");
  
  do
  {
    if(notprintable)
      printf("Chaine de caractere non imprimable\n");
    notprintable=false;
    printf(">> ");
    fgets(new->password,MAXCHAR,stdin);
    new->password[strlen(new->password)-1]=0;
    str_len=0;
    do
    {
      if(!isprint(new->password[str_len]))
        notprintable = true;
      str_len++;
    } while (str_len < strlen(new->password)&&!notprintable);
  } while (notprintable);


  do
  {
    printf("* Veuillez saisir votre date de naissance jj/mm/aaaa : ");
    saisie_date(&jj,&mm,&yy);
  }while(!Valid_date(jj,mm,yy));


  new->DdN.jour = jj; 
  new->DdN.mois = mm; 
  new->DdN.annee = yy; 

  return new;
}

void Set_TimeStamp(profil *input)
{

  time(&input->lastActivity);
}

void Get_TimeStamp(profil *input)
{
  if (input->lastActivity)
    printf("\nVotre Derniere Activite : %s\n", ctime(&input->lastActivity));
}
bool Valid_date(short dd,short mm,short yy)
{
   time_t timer;
   struct tm* tm_info;
   char day[3];
   char month[3];
   char year[5];
   time(&timer);
   tm_info = localtime(&timer);
   strftime(day, 3, "%d", tm_info);
   strftime(month, 3, "%m", tm_info);
   strftime(year, 5, "%Y", tm_info);
   short Jour = toString(day); 
   short Mois=toString(month);
   short Annee=toString(year); 
   bool All_good; 



     
    //check year
    if(yy>=1900 && yy<=9999)
    {
        //check month
        if(mm>=1 && mm<=12)
        {
            //check days
            if((dd>=1 && dd<=31) && (mm==1 || mm==3 || mm==5 || mm==7 || mm==8 || mm==10 || mm==12))
                All_good =  true;
            else if((dd>=1 && dd<=30) && (mm==4 || mm==6 || mm==9 || mm==11))
                All_good = true;
            else if((dd>=1 && dd<=28) && (mm==2))
                All_good =  true;
            else if(dd==29 && mm==2 && (yy%400==0 ||(yy%4==0 && yy%100!=0)))
                All_good =  true;
            else
                All_good =  false;
        }
        else
        {
            All_good =  false;
        }
    }
    else
    {
       		All_good =  false;
    }
 	
 	if(yy>Annee){
 		All_good = false; 
 		printf("Annee plus grand\n");
 	}
 	if(yy>=Annee && mm >Mois){
 		printf("Mois trop grand\n");
 		All_good =  false; 
 	}
 	if(yy>=Annee && mm >=Mois && dd>=Jour){
 		printf("Mois & jour trop grand\n");
 		All_good =  false; 
 	}
 	if(Age_returning(dd,mm,yy)<13){
 		printf("Pas 13 ans\n");
 		All_good =  false; 
 	}
    return All_good;    
}


void My_profile(profil *user,short choice)
{
  char tmpDATA[MAXCHAR]; 
  char tmpDATA_bis[MAXCHAR]; 
  long todel = -1;
  PayLoad Towrite; 
  printf("\n");


  if(choice==1)
  {
    memset(user->ville,0,MAXCHAR);
    memset(user->region,0,MAXCHAR);
    memset(user->pays,0,MAXCHAR);
    printf("Veuillez saisir votre nouvelle Ville : ");
    SET_geo(user->ville); 
    printf("Veuillez saisir votre nouvelle region : ");
    SET_geo(user->region); 
    printf("Veuillez saisir votre nouveau Pays : ");
    SET_geo(user->pays);
  }
  else
  {
    if(choice==2)
    {
      do
      {
        memset(user->password,0,50);
        printf("Veuillez saisir votre nouveau mot de passe : ");
        SET_string(tmpDATA,false); 
        printf("Veuillez confirmer votre mot de passe : ");
        SET_string(tmpDATA_bis,false); 
      }while(strcmp(tmpDATA,tmpDATA_bis)); 

      strcpy(user->password,tmpDATA);

    }
    else
    {
      if(choice==3)
      {
        Get_profile(user);
      }
      else
      {
      	if(choice==4)
      		ReadAnswer(user->iDProfil,true);
      	else
      		if(choice==5)
      			GetMyGames(user,true);
        	printf("Erreur, votre choix n'est pas valable.\n");
        
      }

    }
  }

  todel = compareSeq(user->nom); 
  if(todel!=-5)
  {
    deleteFileSeqLog(USERFILE,todel);
    Set_TimeStamp(user);
    Towrite.user = *user;
  
    writeFileSeqLog(USERFILE,&Towrite);
  
  
  }
  

}


short menuProfil(profil *user,bool *connected)
{
  short choice=0; 
  short subchoice=0;
 
  CLEAR
  printf("1. Mon profil \n");
  printf("2. un autre profil\n");
  printf("0. Annuler\n");
  
  
  do
  {
    scanf("%hd",&choice);
    getchar();
  } while (choice<0||choice>2);

  if(!choice)
    return 0;


  if(choice==1)
    {
      CLEAR
      printf("\n* Modification *\n\n");
      printf("1. Modifier mon pays\n"); 
      printf("2. Modifier mon mot de passe\n");
      printf("\n* Profil *\n\n");
      printf("3. Afficher mon Profil\n");
      printf("4. Supprimer mon Profil\n");
      printf("\n* MES SCORES *\n\n");
      printf("5. Afficher Mes parties et score\n");
      printf("6. Afficher reponses\n");
      printf("7. Afficher le score par theme\n");
      printf("0. Retour Menu principal \n");
      do
      {
        scanf("%hd",&subchoice); 
        getchar(); 
      }while(subchoice<0||subchoice>7);

      if(subchoice==0)
        return 0;

      else
        {

            switch (subchoice)
            {
              case 0: return 0; 
              break; 
              case 1: My_profile(user,subchoice); 
              break; 
              case 2: My_profile(user,subchoice); 
              break; 
              case 3 : My_profile(user,subchoice); 
              break; 
              case 4 : 
                        printf("Etes-vous sur de vouloir supprimer votre Compte ?\n");
                        printf("|| Toute vos reponses et donnee seront perdue|||\n");
                        printf("[1]/[0]\n > ");
                        do
                        {
                            scanf("%hd",&subchoice);
                            getchar();
                        } while (subchoice != 0 && subchoice != 1);
                        
                      if(!subchoice)
                        return 0;
                      long TempID = user->iDProfil;
                      deleteFileSeqLog(USERFILE,compareSeq(user->nom)); 
                      free(user);
                      user = NULL;
                      *connected = false;
                      delete_ForIntegrity(TempID);
              break;
              case 5 : 


              GetMyGames(user,true);
              break;
              case 6 : 
              	ReadAnswer(user->iDProfil,true); 
              break;
              case 7 : PointbyTheme();
              break;
              default : return 0; 
              break;
            }
          }
          
        
      
    }
    
    
  
  
  
  
  
  else
    Other_Profile();
  return 0;
}

void SET_geo(char *input)
{

  char buffer; 
  int i=0; 


  i=0;
  buffer = getchar(); 

  while(buffer!='\n')
  {
    *(input+i) = buffer; 
    buffer = getchar(); 
    i++; 
  }
  
  if(i==1 || i==0)
  {
    strcpy(input,"Unset");
  }
  *(input) = toupper(*input);
  for (i = 1; i < strlen(input); ++i)
  {
    *(input+i) = tolower(*(input+i));
  }
}


short toString(char a[]) 
{

  int c, sign=0, offset, n;

  if (a[0] == '-')
  { 
    sign = -1;
  }

  if (sign == -1) {  
    offset = 1;
  }
  else {
    offset = 0;
  }

  n = 0;

  for (c = offset; a[c] != '\0'; c++) {
    n = n * 10 + a[c] - '0';
  }

  if (sign == -1) {
    n = -n;
  }

  return n;
}

short isLeapYear(short year, short mon) 
{
    short flag = 0;
    if (year % 100 == 0) 
    {
            if (year % 400 == 0) 
            {
                    if (mon == 2) 
                    {
                            flag = 1;
                    }
            }
    } 
    else if (year % 4 == 0) 
    {
            if (mon == 2) 
            {
                    flag = 1;
            }
    }
    return (flag);
}

short Age_returning(short days,short month,short year)
{

    short DaysInMon[] = {31, 28, 31, 30, 31, 30,31, 31, 30, 31, 30, 31};

    time_t ts;
    struct tm *ct;

    ts = time(NULL);
    ct = localtime(&ts);

    days = DaysInMon[month - 1] - days + 1;

  
    if (isLeapYear(year, month)) 
    {
            days = days + 1;
    }


    days = days + ct->tm_mday;
    month = (12 - month) + (ct->tm_mon);
    year = (ct->tm_year + 1900) - year - 1;

  
    if (isLeapYear((ct->tm_year + 1900), (ct->tm_mon + 1))) 
    {
            if (days >= (DaysInMon[ct->tm_mon] + 1)) 
            {
                    days = days - (DaysInMon[ct->tm_mon] + 1);
                    month = month + 1;
            }
    } 
    else if (days >= DaysInMon[ct->tm_mon]) 
    {
            days = days - (DaysInMon[ct->tm_mon]);
            month = month + 1;
    }

    if (month >= 12) 
    {
            year = year + 1;
            month = month - 12;
    }

    
    

    return year;
}

profil *connectAttempt()
{
  profil *temp = NULL; 
  char usr[MAXCHAR];
  long posix = -5;
  char pass[MAXCHAR];
  printf("Veuillez saisir votre nom d'utilisateur : "); 
  fgets(usr,MAXCHAR,stdin);
  usr[strlen(usr)-1]=0;
  printf("Veuillez saisir votre mot de passe : "); 
  fgets(pass,MAXCHAR,stdin);
  pass[strlen(pass)-1]=0;
  
  posix = compareSeq(usr);
  if(posix!=-5)
    {
      temp = comparePass(usr,pass,posix);
    }

  if(temp != NULL)
    return temp;

	return 0;
}

void disconnect(profil *goodBye)
{
  free(goodBye);
  goodBye = NULL;
}

void init_App()
{
  char PATHTOFILE[125]=USERFILE;
  short choice = 1;
  short sub_choice = 0;
  short Attempt = 0;
  bool connected = false;
  profil *temp = NULL;
  PayLoad Towrite; 
  

  while (choice)
  {
    if (connected)
      choice = menuGeneral(connected, temp->nom);
    else
      choice = menuGeneral(connected, NULL);
    if(choice==1&& connected)
      connected = false;
    switch (choice)
    {
      case 0 : return;
        break;
      case 1  :

        CLEAR
        if(!connected)
        {
          do
          {
            printf("1. Se connecter\n");
            printf("2. S'inscrire\n");
            printf("0. Quitter\n> ");
            scanf("%hd", &sub_choice);
            getchar();
            if(!sub_choice)
              return;
          }while (sub_choice != 1 && sub_choice != 2);
        }

        if (sub_choice == 1 && connected)
          {
            disconnect(temp);
            connected = false;
            temp = NULL;
            choice = -5;
            sub_choice = -5;
          }
          else
          {
            if(sub_choice==1 && !connected)
            {
              Attempt=0;
              temp = NULL;
              do
              {
                CLEAR
                printf("Essai Numero %d /3\n",Attempt+1);
                temp = connectAttempt();
                Attempt++;
              }while(Attempt<3 && temp == NULL);
              if(temp!=NULL)
                connected = true;
            }
            else
            {
              temp = new_profil();
              if(temp!=NULL)
                connected = true;
              Set_TimeStamp(temp);
              Towrite.user = *temp;
              
              writeFileSeqLog(PATHTOFILE,&Towrite);
            }
            


          }



        break;
      case 2 : 
      CLEAR
      if(connected)
                  LaunchGame(temp);


        break;
      case 3 : 
      CLEAR
      menuProfil(temp,&connected);
        break;
      case 4 : if(connected)
                  Print_All_Users();
      break;
      case 5 : 
      CLEAR
      if(connected)
                  menuQuestion(temp);
      break; 
      case 6 : 
      CLEAR
      BestScore();
      break;
      default : 
        break; 
        
    }
  }

}
void Get_profile(profil *user)
{
    int i; 

    CLEAR
    printf("Vos donnee Actuelle : \n");
    printf("ID : %ld\n",user->iDProfil);
    printf("NOM : ");
    puts(user->nom); 
    printf("CODE LANGUE : ");
    puts(user->codeLangue); 
    printf("VILLE : ");
    puts(user->ville); 
    printf("REGION : ");
    puts(user->region); 
    printf("PAYS : "); 
    puts(user->pays); 
    printf("DDN : %hd/%hd/%hd\n",user->DdN.jour,user->DdN.mois,user->DdN.annee);
    printf("PASSWORD : ");
    for(i=0;i<strlen(user->password);printf("*"),i++); 
    printf("\n"); 
    Get_TimeStamp(user); 
    printf("--------------Appuyez sur enter------------------\n");
    getchar();
}

void Get_Other_profile(profil *user)
{
    int i; 

    CLEAR
    printf("Les donnees de %s : \n",user->nom);
    printf("ID : %ld\n",user->iDProfil);
    printf("NOM : ");
    puts(user->nom); 
    printf("CODE LANGUE : ");
    puts(user->codeLangue); 
    printf("VILLE : ");
    puts(user->ville); 
    printf("REGION : ");
    puts(user->region); 
    printf("PAYS : "); 
    puts(user->pays); 
    printf("DDN : %hd/%hd/%hd\n",user->DdN.jour,user->DdN.mois,user->DdN.annee);
    printf("PASSWORD : ");
    for(i=0;i<strlen(user->password);printf("*"),i++); 
    printf("\n"); 
    Get_TimeStamp(user); 
    printf("--------------Appuyez sur enter------------------\n");
    getchar();
   
}

void Other_Profile()
{
  CLEAR
  char buffer;
  short subchoice=0;
  char seekName[MAXCHAR];
  long pos = 0; 
  profil *temp = (profil *)malloc(sizeof(profil));
  printf("Veuillez Saisir le nom a rechercher\n> ");
  fgets(seekName,MAXCHAR,stdin);
  seekName[strlen(seekName)-1]=0;

  pos = Seek_User(USERFILE,seekName,temp);
  if(pos!=-5)
  {
    Get_Other_profile(temp);
    printf("Modification Possible Pour Le profil %s : \n",temp->nom);
    printf("1. Modifier le pays\n"); 
    printf("2. Modifier le mot de passe\n");
    
    printf("3. Afficher le Profil\n");
    printf("4. Afficher les reponses\n");
    printf("5. Afficher les parties\n");
    printf("0. Retour Menu principal \n");
      do
      {
      	printf(">> ");
        scanf("%hd",&subchoice); 
        getchar(); 
      }while(subchoice<0||subchoice>5);
    if(subchoice)
    {
      My_profile(temp,subchoice);
    }
    
  }
  else
  {
    printf("AUCUN PROFIL : \"%s\" dans la Base de Donnee\n ",seekName);
    printf("Appuyez sur Enter pour retourner au menu\n>");
    buffer = getchar();
    while(buffer!='\n')
    	buffer = getchar();
  }
  
  free(temp);
  temp = NULL;

}

long UsersDB_size()
{
  FILE *pf = fopen(USERFILE,"ab");
  long size = ftell(pf); 
  size/=sizeof(profil); 
  fclose(pf); 

  return size;
}

void saisie_date(short *j,short *m, short *a)
{
  short jj,mm,aa;
	short i=0;
  short k=0;
	char format[100];
	char day[4]; 
	char month[4]; 
	char year[6];
  short occurence = 0;
  bool tolong = false;
  do
  {
    tolong = false;
    occurence = 0;
	  fgets(format,100,stdin);
	  format[strlen(format)-1]=0;
    for(i=0;i<strlen(format);i++)
    {
      if(format[i]=='/')
        occurence++;
      
      if(occurence==2)
      {
        occurence = 0;
        for(int j=i+1;j<strlen(format);j++)
        {
          occurence++;
        }
        if(occurence>4)
        {
          tolong = true;
          i=101;
        }
      }

    }
  }while(tolong);
  
	day[0] = format[0]; 
	day[1] = format[1];
	day[2]=0;
	month[0] = format[3]; 
	month[1] = format[4]; 
	month[2]=0;
	for(i=6,k=0;i<10;i++,k++)
		year[k]=format[i];

	year[k]=0;

	jj=(short)atoi(day);
	mm = (short)atoi(month);
	aa = (short)atoi(year);

  *j = jj;
  *m = mm;
  *a = aa;



}

char *ReturnCountryByid(long ID)
{
long pos = 1; 
  

    char *usn = (char *) malloc(sizeof(char *)*144);
    profil *user = NULL; 
    FILE *fichier = fopen(USERFILE,"rb");
    Header *head = NULL; 
    head = (Header * ) malloc(sizeof(Header));
    fread(head,sizeof(Header),1,fichier);
    pos = head->PTO;
    free(head);
    while(pos!=-1)
    {
        
        fseek(fichier,pos*sizeof(profil)+sizeof(Header)+sizeof(long)*pos,SEEK_SET);
        user = (profil *) malloc(sizeof(profil));
        fread(user,sizeof(profil),1,fichier); 
        fread(&pos,sizeof(long),1,fichier);
        if(user->iDProfil==ID)
        {
          strcpy(usn,user->pays);
          free(user);
          fclose(fichier);
          return usn;
        }
        
        free(user);
    }

    fclose(fichier); 


    CLEAR
    free(usn);
    return NULL;

}