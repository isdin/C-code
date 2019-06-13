/*********************************************************************/
/* Manipulation de fichiers binaires.                                */
/*  Organisation sequentielle logique.                               */
/*  Taille d'enregistrement fixe.                                    */
/*  Adressage par numero d'enregistrement (de 0 a nbenreg-1          */
/*  Fichier non bidonn�                                              */
/*********************************************************************/
#include "index.h"
char *ReturnNameById(long ID)
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
          strcpy(usn,user->nom);
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

void Print_All_Users()
{
    CLEAR
    long pos = 1; 
    char cont = '1';
    profil *user = NULL; 
    FILE *fichier = fopen(USERFILE,"rb");
    Header *head = NULL; 
    head = (Header * ) malloc(sizeof(Header));
    fread(head,sizeof(Header),1,fichier);
    pos = head->PTO;
    free(head);
    while(pos!=-1 && cont != '0')
    {
        fseek(fichier,pos*sizeof(profil)+sizeof(Header)+sizeof(long)*pos,SEEK_SET);
        user = (profil *) malloc(sizeof(profil));
        fread(user,sizeof(profil),1,fichier); 
        fread(&pos,sizeof(long),1,fichier);
        //Get_profile(user);
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
        for(int i=0;i<strlen(user->password);printf("*"),i++); 
        printf("\n"); 
        Get_TimeStamp(user); 
        printf("\n-----------------APPUYEZ SUR ENTER ou 0 pour arreter----------\n");
        cont = getchar();
        free(user);
    }

    fclose(fichier); 
  // getchar();

    CLEAR
    
}

bool User_Exist(char *input)
{
  long pos = 1; 
  

    
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
        if(strcmp(user->nom,input)==0)
            return true; 
        free(user);
    }

    fclose(fichier); 


    CLEAR

    return false;
}

long compareSeq(char *input)
{
    

    long pos = 1; 
    long oldpos = -5;
    long found = 0;
    
    profil *user = NULL; 
    FILE *fichier = fopen(USERFILE,"rb");
    Header *head = NULL; 
    head = (Header * ) malloc(sizeof(Header));
    fread(head,sizeof(Header),1,fichier);
    pos = head->PTO;
    free(head);
    while(pos!=-1)
    {
        oldpos = pos; 
        fseek(fichier,pos*sizeof(profil)+sizeof(Header)+sizeof(long)*pos,SEEK_SET);
        user = (profil *) malloc(sizeof(profil));
        fread(user,sizeof(profil),1,fichier); 
        fread(&pos,sizeof(long),1,fichier);
        if(strcmp(user->nom,input)==0)
        {
            pos = -1;
            found = oldpos;
        }
        free(user);
    }

    fclose(fichier); 


    CLEAR

  if(found)
    return found;
  else
      return oldpos;
    
    
    return oldpos;
    

}

profil *comparePass(char *usr,char *psw,long pos)
{

    profil *user = NULL; 
    FILE *fichier = fopen(USERFILE,"rb");
    Header *head = NULL; 
    head = (Header * ) malloc(sizeof(Header));
    fread(head,sizeof(Header),1,fichier);
    // pos = head->PTO;
    free(head);

        fseek(fichier,pos*sizeof(profil)+sizeof(Header)+sizeof(long)*pos,SEEK_SET);
        user = (profil *) malloc(sizeof(profil));
        fread(user,sizeof(profil),1,fichier); 
        fread(&pos,sizeof(long),1,fichier);
        fclose(fichier); 
        if(strcmp(user->password,psw)==0)
        {
          if(strcmp(user->nom,usr)==0)
          {
            return user;
          }   
        }
        else
        {
          free(user); 
          return NULL;
        }
      return NULL;
}

//to be deleted
void main_frameMODIF()
{
    char temp[125]; 
    long pos = 0;
    

    fgets(temp,125,stdin);

    temp[strlen(temp)-1]=0;
    temp[0]=toupper(temp[0]);
    pos = compareSeq(temp);
    if(pos!=-5)
        deleteFileSeqLog(USERFILE,pos);

    Print_All_Users();
    

    
}



/***********************************************************/
/* Creer un fichier sequentiel logique non bidonne         */
/*  IN  : nom du fichier a creer                           */
/*  OUT : 0 en cas de succes, -1 en cas d'erreur           */
/***********************************************************/
int createFileSeqLog(char * fileName)
{
  FILE * fichier = NULL;
  long PTO=-1;  // pas de bloc occupe
  long PTL=-1;  // pas de bloc libre
  Header header={PTO,PTL};
  int erreur=-1;

  fichier=fopen(fileName,"rb");
  if(fichier==NULL)
  {
      fichier=fopen(fileName,"wb");

      if (fichier!=NULL)
          {
            if(fwrite(&header,sizeof(Header),1,fichier)==1)
              erreur=0;
            fclose(fichier);
          }
  }
  else
  {
    erreur = 0;
  }
  
  return erreur;
}

/***********************************************************/
/* Ajouter un enregistrement a un fichier sequentiel       */
/*    logique non bidonne                                 */
/*  IN  : nom du fichier, pointeur vers l'enregistrement   */
/*  OUT : 0 en cas de succes, -1 en cas d'erreur           */
/***********************************************************/
int writeFileSeqLog(char * fileName,PayLoad * record)
{
  FILE * fichier = NULL;
  Header header={-2,-2};      // bloc PTO-PTL
  long pos_old=-2;             // position avant le bloc lu
  long pos_cur=-1;             // position du bloc lu
  long pos_next=-1;            // position du bloc suivant
  long pos_enreg=-1;           // posisition de l'enregistrement a inserer
  int offset=-1;              // offset d'un enregistrement (calcule)
  EnrSeqLog temp={{0},-1};    // A adapter
  EnrSeqLog toWrite={{0},-1}; // Enregistrement a ecrire
  int goOn=0;                 // resultat de la comparaison entre deux enregistrements
  int erreur=0;

  fichier=fopen(fileName,"r+b");
  if (fichier!=NULL)
  {
    if(fread(&header,sizeof(Header),1,fichier)==1)
    {
      // Prendre un bloc libre si pas de blocs libres chaines
      if(header.PTL==-1)
      {
        erreur=-1;
        if(fseek(fichier,0,SEEK_END)==0)
        {
          offset=ftell(fichier);
          pos_enreg=(offset-sizeof(Header))/sizeof(EnrSeqLog);
          if(fwrite(&toWrite,sizeof(EnrSeqLog),1,fichier)==1)
          {
            erreur=0;
          }
        }
      }
      // Prendre un bloc libre il y a des blocs libres chaines
      else
      {
        erreur=-1;
        // Prendre le bloc
        pos_enreg=header.PTL;
        offset=sizeof(Header)+(pos_enreg*sizeof(EnrSeqLog));
        if(fseek(fichier,offset,SEEK_SET)==0)
        {
          if(fread(&temp,sizeof(EnrSeqLog),1,fichier)==1)
          {
            // Mettre PTL a jour
            header.PTL=temp.offset;
            offset=0;
            if(fseek(fichier,offset,SEEK_SET)==0)
            {
              if(fwrite(&header,sizeof(Header),1,fichier)==1)
              {
                erreur=0;
              }
            }
          }
        }
      }

      // Remplir le PayLoad du bloc a enregistrer
      memcpy(&(toWrite.payload),record,sizeof(PayLoad));

      // Ajouter si pas de blocs occupes
      if(header.PTO==-1)
      {
        // Ecrire le nouvel enregistrement
        erreur=-1;
        toWrite.offset=header.PTO;
        //ecrire enregistrement
        offset=sizeof(Header)+(pos_enreg*sizeof(EnrSeqLog));
        if(fseek(fichier,offset,SEEK_SET)==0)
        {
          if(fwrite(&toWrite,sizeof(EnrSeqLog),1,fichier)==1)
          {
            // Mettre a jour PTO
            header.PTO=pos_enreg;
            offset=0;
            if(fseek(fichier,offset,SEEK_SET)==0)
            {
              if(fwrite(&header,sizeof(Header),1,fichier)==1)
              {
                erreur=0;
              }
            }
          }
        }
      }
      // Ajouter si il y a des blocs occupes
      else
      {
        // suivre le chainage
        pos_old=-2; // avant PTO
        pos_cur=-1; // sur PTO
        pos_next=header.PTO;
        do
        {
          // Lire enregistrement suivant
          offset=sizeof(Header)+(pos_next*sizeof(EnrSeqLog));
          if(fseek(fichier,offset,SEEK_SET)==0)
          {
            if(fread(&temp,sizeof(EnrSeqLog),1,fichier)==1)
            {
              pos_old=pos_cur;
              pos_cur=pos_next;
              pos_next=temp.offset;
              goOn=(comparePayLoad(record,&(temp.payload))>0);
              erreur=0;
            }
            else
              erreur=-1;
          }
          else
            erreur=-1;
        }
        while((pos_next!=-1)&&goOn&&(erreur!=-1));
        // Inserer l'enregistrement a la bonne place dans le chainage
        if(erreur!=-1)
        {
          // si goOn>0 insertion du dernier enregistrement
          if(goOn>0)
          {
            erreur=-1;
            toWrite.offset=pos_next;
            //ecrire enregistrement
            offset=sizeof(Header)+(pos_enreg*sizeof(EnrSeqLog));
            if(fseek(fichier,offset,SEEK_SET)==0)
            {
              if(fwrite(&toWrite,sizeof(EnrSeqLog),1,fichier)==1)
              {
                // raccrocher a la tete de liste (a partir de pos_cur)
                offset=sizeof(Header)+(pos_cur*sizeof(EnrSeqLog));
                if(fseek(fichier,offset,SEEK_SET)==0)
                {
                  if(fread(&temp,sizeof(EnrSeqLog),1,fichier)==1)
                  {
                    temp.offset=pos_enreg;
                    if(fseek(fichier,offset,SEEK_SET)==0)
                    {
                      if(fwrite(&temp,sizeof(EnrSeqLog),1,fichier)==1)
                      {
                        erreur=0;
                      }
                    }
                  }
                }
              }
            }
          }
          // si old=-1 insertion entre PTO et le premier enregistrement (cur)
          else if(pos_old==-1)
          {
            erreur=-1;
            toWrite.offset=pos_cur;
            // ecrire enregistrement
            offset=sizeof(Header)+(pos_enreg*sizeof(EnrSeqLog));
            if(fseek(fichier,offset,SEEK_SET)==0)
            {
              if(fwrite(&toWrite,sizeof(EnrSeqLog),1,fichier)==1)
              {
                // ecrire nouveau PTO
                header.PTO=pos_enreg;
                offset=0;
                if(fseek(fichier,offset,SEEK_SET)==0)
                {
                  if(fwrite(&header,sizeof(Header),1,fichier)==1)
                  {
                    erreur=0;
                  }
                }
              }
            }
          }
          // sinon insertion entre deux enregistrements (old et cur)
          else
          {
            erreur=-1;
            toWrite.offset=pos_cur;
            //ecrire enregistrement
            offset=sizeof(Header)+(pos_enreg*sizeof(EnrSeqLog));
            if(fseek(fichier,offset,SEEK_SET)==0)
            {
              if(fwrite(&toWrite,sizeof(EnrSeqLog),1,fichier)==1)
              {
                // raccrocher a la tete de liste (a partir de pos_old)
                offset=sizeof(Header)+(pos_old*sizeof(EnrSeqLog));
                if(fseek(fichier,offset,SEEK_SET)==0)
                {
                  if(fread(&temp,sizeof(EnrSeqLog),1,fichier)==1)
                  {
                    temp.offset=pos_enreg;
                    if(fseek(fichier,offset,SEEK_SET)==0)
                    {
                      if(fwrite(&temp,sizeof(EnrSeqLog),1,fichier)==1)
                      {
                        erreur=0;
                      }
                    }
                  }
                }
              }
            }
          }
        }
      }
    }
    else
      erreur=-1;
    fclose(fichier);
  }
  else
    erreur=-1;

  return erreur;
}

/***********************************************************/
/* Comparer le contenu de deux enregistrements pour les    */
/*    classer                                              */
/*  IN  : pointeurs vers les enregistrements a comparer    */
/*  OUT : >0 si load1>load2                                */
/*        =0 si load1=load2                                */
/*        <0 si load1<load2                                */
/***********************************************************/
int comparePayLoad(PayLoad * load1,PayLoad * load2)
{
  

  return strcmp(load1->user.nom,load2->user.nom);
}

/***********************************************************/
/* Chercher un enregistrement dans un fichier sequentiel   */
/*    logique                                              */
/*  IN  : nom du fichier, pointeur sur la valeur cherchee, */
/*          position de depart pour la recherche(-1 si PTO)*/
/*          pointeur sur l'enregistrement trouve           */
/*  OUT : numero de l'enregistrement trouve,               */
/*          INT_MAX si pas trouve                          */
/*          -1 en cas d'erreur                             */
/***********************************************************/
int searchFileSeqLog(char * fileName,char * value,long startpos,PayLoad * record)
{
  FILE * fichier = NULL;
  Header header={-2,-2};      // bloc PTO-PTL
  long pos_cur=-1;             // position du bloc lu
  long pos_next=-1;            // position du bloc suivant
  int offset=-1;              // offset d'un enregistrement (calcule)
  EnrSeqLog temp={{0},-1};    // A adapter
  int found=0;                // resultat de la comparaison entre deux enregistrements
  int erreur=-1;

  // Lire PTO-PTL
  fichier=fopen(fileName,"rb");
  if (fichier!=NULL)
  {
    if(fread(&header,sizeof(Header),1,fichier)==1)
    {
      // Si fichier vide
      if(header.PTO==-1)
      {
        erreur=INT_MAX;
      }
      // Si fichier non vide -> parcourir chainage a partir de l'enregistrement startpos
      else
      {
        if(startpos==-1)
            pos_next=header.PTO;
        else
            pos_next=startpos;
        do
        {
          // Lire enregistrement suivant
          erreur=-1;
          offset=sizeof(Header)+(pos_next*sizeof(EnrSeqLog));
          if(fseek(fichier,offset,SEEK_SET)==0)
          {
            if(fread(&temp,sizeof(EnrSeqLog),1,fichier)==1)
            {
              // comparer avec la valeur cherchee
              found=(strcmp(value,temp.payload.user.nom)==0); // Inserer la fonction de comparaison qui convient
              pos_cur=pos_next;
              pos_next=temp.offset;
              erreur=0;
            }
          }
        }
        while((pos_next!=-1)&&!found&&(erreur!=-1));
        if(erreur!=-1)
        {
          if(found)
          {
            memcpy(record,&(temp.payload),sizeof(PayLoad));
            erreur=pos_cur;
          }
          else
            erreur=INT_MAX;
        }
      }
    }
    fclose(fichier);
  }

  return erreur;
}

/***********************************************************/
/* Supprimer un enregistrement dans un fichier sequentiel  */
/*    logique                                              */
/*  IN  : nom du fichier, numero de l'enregistrement       */
/*          a supprimer                                    */
/*  OUT : 0 en cas de succes                               */
/*          -1 en cas d'erreur                             */
/***********************************************************/
int deleteFileSeqLog(char * fileName,long deletepos)
{
  FILE * fichier = NULL;
  Header header={-2,-2};      // bloc PTO-PTL
  long pos_cur=-1;             // position du bloc lu
  long pos_next=-1;            // position du bloc suivant
  int offset=-1;              // offset d'un enregistrement (calcule)
  EnrSeqLog temp={{0},-1};    // A adapter
  EnrSeqLog todelete={{0},-1};// A adapter
  int found=0;                // resultat de la comparaison entre deux enregistrements
  int erreur=-1;

  // Lire PTO-PTL
  fichier=fopen(fileName,"rb+");
  if (fichier!=NULL)
  {
    if(fread(&header,sizeof(Header),1,fichier)==1)
    {
      // Si fichier non vide -> parcourir chainage pour trouver le bloc precedent celui a supprimer
      if(header.PTO!=-1)
      {
        erreur=0;
        pos_next=header.PTO;
        found=(pos_next==deletepos);
        // Lire enregistrement suivant
        while((pos_next!=-1)&&!found&&(erreur!=-1))
        {
          erreur=-1;
          offset=sizeof(Header)+(pos_next*sizeof(EnrSeqLog));
          if(fseek(fichier,offset,SEEK_SET)==0)
          {
            if(fread(&temp,sizeof(EnrSeqLog),1,fichier)==1)
            {
              pos_cur=pos_next;
              pos_next=temp.offset;
              found=(deletepos==pos_next);
              erreur=0;
            }
          }
        }
        if(erreur!=-1)
        {
          if(found)
          {
            erreur=-1;
            // accrocher la queue de la liste de blocs occupes
            offset=sizeof(Header)+(deletepos*sizeof(EnrSeqLog));
            if(fseek(fichier,offset,SEEK_SET)==0)
            {
              if(fread(&todelete,sizeof(EnrSeqLog),1,fichier)==1)
              {
                // l'enregistrement a supprimer est le premier de la liste des blocs occupes
                if(pos_cur==-1)
                {
                  header.PTO=todelete.offset;
                  offset=0;
                  if(fseek(fichier,offset,SEEK_SET)==0)
                  {
                    if(fwrite(&header,sizeof(Header),1,fichier)==1)
                    {
                      erreur=0;
                    }
                  }
                }
                // l'enregistrement a supprimer n'est pas le premier du chainage
                else
                {
                  temp.offset=todelete.offset;
                  offset=sizeof(Header)+(pos_cur*sizeof(EnrSeqLog));
                  if(fseek(fichier,offset,SEEK_SET)==0)
                  {
                    if(fwrite(&temp,sizeof(EnrSeqLog),1,fichier)==1)
                    {
                      erreur=0;
                    }
                  }
                }
                // accrocher le bloc a supprimer en tete de la liste des blocs libres
                if(erreur==0)
                {
                  erreur=-1;
                  // D'abord accrocher la queue des blocs libres au bloc supprime
                  todelete.offset=header.PTL;
                  offset=sizeof(Header)+(deletepos*sizeof(EnrSeqLog));
                  if(fseek(fichier,offset,SEEK_SET)==0)
                  {
                    if(fwrite(&todelete,sizeof(EnrSeqLog),1,fichier)==1)
                    {
                      // Ensuite accrocher le bloc supprime a PTL
                      header.PTL=deletepos;
                      offset=0;
                      if(fseek(fichier,offset,SEEK_SET)==0)
                      {
                        if(fwrite(&header,sizeof(Header),1,fichier)==1)
                        {
                          erreur=0;
                        }
                      }
                    }
                  }
                }
              }
            }
          }
          else
          // l'enregistrement a supprimer n'est pas dans la liste des blocs occupes => erreur
          {
            erreur=-1;
          }
        }
      }
    }
    fclose(fichier);
  }
  return erreur;
}

long Seek_User(char *filename,char *seekData,profil *FillMe)
{
    long pos = 1; 
    bool notfound = 1;
    profil *user = NULL; 
    FILE *fichier = fopen(filename,"rb");
    Header *head = NULL; 
    head = (Header * ) malloc(sizeof(Header));
    fread(head,sizeof(Header),1,fichier);
    pos = head->PTO;
    free(head);
    while(pos!=-1&&notfound)
    {
        fseek(fichier,pos*sizeof(profil)+sizeof(Header)+sizeof(long)*pos,SEEK_SET);
        user = (profil *) malloc(sizeof(profil));
        fread(user,sizeof(profil),1,fichier); 
        fread(&pos,sizeof(long),1,fichier);
        if(strcmp(seekData,user->nom)==0)
        {
          notfound=false;
          memcpy(FillMe,user,sizeof(profil));
        }
        free(user);
    }

    fclose(fichier); 
  // getchar();

  
  if(notfound)
    return -5;
  else
  {
    
    return pos;

  }
    
}