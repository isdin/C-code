/*********************************************************************/
/* Manipulation de fichiers binaires.                                */
/*  Organisation sequentielle logique.                               */
/*  Taille d'enregistrement fixe.                                    */
/*  Adressage par numero d'enregistrement (de 0 a nbenreg-1          */
/*  Fichier non bidonn�                                              */
/*********************************************************************/
#include "mytype.h"
typedef struct
{
  // Adapter cette structure aux besoins de l'application
  profil user;
} PayLoad;

typedef struct
{
  long PTO;
  long PTL;
} Header;   // structure destinee a contenir PTO et PTL

typedef struct
{
  PayLoad payload;  // contenu fictif a adapter
  long    offset;   // numero de l'enregistrement suivant dans l'ordre logique choisi. -1 pour le dernier.
} EnrSeqLog;

