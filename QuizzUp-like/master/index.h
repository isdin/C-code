#include <stdio.h>
#include <time.h>
#include <ctype.h>
#include <limits.h>
#include <stdlib.h>
#include <string.h>


#include "OrgSeqLog.h"
#define USERFILE "profils.dat"
#define ANSWFILE "reponses.dat"
#define QUESTFILE "questions.dat"
#define CLEAR system("clear");

typedef struct Index Index; 
struct Index
{
    long idQuestion;
    char theme[MAXCHAR];
    char libelle[144];
    char correctAnswer[MAXCHAR];
    char distracteur1[MAXCHAR];
    char distracteur2[MAXCHAR];
    char distracteur3[MAXCHAR];
    long position; 
};


typedef struct Partie Partie; 
struct Partie
{
  long IdPartie;
  long IdProfil;
  long IdQestion[5];
  short scoreTotal;
  char theme[MAXCHAR];
};
typedef struct MyGames MyGames;
struct MyGames
{
  Partie *data; 
  MyGames *Next;
};



//Lancement
void init_App();
bool SET_string(char *, bool);
void Fchk_win32();

//LES MENU
short menuGeneral(bool, char *);
short menuProfil(profil *,bool *connected);
short menuReponse(profil *,reponse *); 
void menuQuestion(profil *); 
void main_frameMODIF(); 
void Teacher_Quote();
void Help();

//GESTION DES FICHIERS ET DATA LOGIQUE
long UsersDB_size();
int createFileSeqLog(char *);                             // Creer fichier SeqLog
int writeFileSeqLog(char *,PayLoad *);                    // Ajouter enregistrement SeqLog
int comparePayLoad(PayLoad *,PayLoad *);                  // Comparer le contenu de deux enregistrements pour les classer
int searchFileSeqLog(char *,char *,long,PayLoad *);       // Chercher un enregistrement SeqLog
int deleteFileSeqLog(char *,long deletepos);              // Supprimer un enregistrement SeqLog
long compareSeq(char *); 
void Print_All_Users();
void Get_profile(profil *); 
void Other_Profile();
long set_id(short choice);
void check_Id_files();
long Seek_User(char *filename,char *seeked,profil *FillMe);
void Get_Other_profile(profil *user);
void Get_TimeStamp(profil *);
void Set_TimeStamp(profil *);

//GESTION DE LA CONNEXION
profil *connectAttempt();
profil *Connection_Approuved(char *,char *);
profil *comparePass(char *,char *,long);
void disconnect(profil *);
bool User_Exist(char *);


//GESTION DES FICHIERS ET DATA INDEXEE
void createFileInd(char *Filename);
void WriteQuestion(char *Filename,Question *); 
void DeleteRecordIndex();
bool isSame(char *lib1,char *lib2,char *lib3);
void MakeIndex(char *Filename,Index *fetch,long );
void SortIndexLabel(char *Filename,Index *,long);
void SortIndexTheme(char *Filename,Index *,long); 

long Question_SeekandChange();
Question *SetQuestion();
void Fill_index(char *Filename,Index *input);
long allocate_Index(char *fileName);

void PrintByTheme_HardDrive(char *Filename,Index *,long ); //LECTURE SUR DISQUE VIA POSITION
void PrintByLabel_HardDrive(char *Filename,Index *,long );

void PrintByTheme_MEMORY(char *Filename,Index *,long ); //LECTURE VIA MEMOIRE 
void PrintByLabel_MEMORY(char *Filename,Index *,long );
void Change_me(Question *);
void Print_one_question(Question *);
void Print_FromTheme(char *theme,Index *Theme_index,long); 
void Search_fromString(Index *Data,char *str,long size);

/*GESTION FICHIERS ET DATA PHYSIQUE*/

//GESTION DU JEU
void createFilePartie(char *fileName);
void createAnswersFile(char *Filename);
void LaunchGame(profil *User);  //Theme Select
short QandA(Index *theme,long *Random_index,profil *user,Partie *input);
void SaveAnswer(reponse *Tosave);
short GiveScore(time_t input);
void WriteAnswer(reponse *input);
long Size_of_Reponse();
void WritePartie(Partie *input);
long PartieSize();
void ReadAnswer(long ID,bool onlyme);
void ReadPartie();
void GetMyGames(profil *user,bool myself);


//FONCTION GENERAL

void BestScore();
void PointbyTheme();
void saisie_date(short *j,short *m, short *a);
char *ReturnNameById(long ID);
char *ReturnTheme_ById(long ID);
char *ReturnCountryByid(long id);

//Gestion des integritée 
void delete_ForIntegrity(long IDuser);
void delete_ForIntegrity_partie(long IDuser);
void delete_ForIntegrity_Answers(long ID);








