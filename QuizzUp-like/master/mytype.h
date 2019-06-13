typedef enum
{
  false, true
} bool;


#define MAXCHAR 50
typedef struct date date;
typedef struct profil profil;
typedef struct reponse reponse;
typedef struct Question Question;



struct date
{
  short jour;
  short mois;
  short annee;
};

struct profil
{
  long iDProfil;
  char nom[MAXCHAR];
  char codeLangue[3];
  char ville[MAXCHAR];
  char region[MAXCHAR];
  char pays[MAXCHAR];
  char password[MAXCHAR];
  time_t lastActivity;
  date DdN;
};
struct Question
{
  long idQuestion;
  char theme[MAXCHAR];
  char libelle[144];
  char correctAnswer[MAXCHAR];
  char distracteur1[MAXCHAR];
  char distracteur2[MAXCHAR];
  char distracteur3[MAXCHAR];
};
struct reponse
{
  long idProfil;
  long idQuestion;
  long idPartie;
  short reponseDonnee;
  short points;
  time_t timestamp;
};