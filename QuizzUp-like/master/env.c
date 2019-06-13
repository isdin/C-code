
#include "index.h"



typedef struct Ids Ids;
struct Ids
{
    long reponse;
    long question;
    long profil;
};

void check_Id_files()
{
    FILE *id_data = NULL;
    Ids id_value;
    id_value.profil = 0;
    id_value.question=0;
    id_value.reponse =0;

    id_data = fopen("id_data.dat","r+b");
    if(id_data==NULL)
    {
        id_data = fopen("id_data.dat","wb");
        fwrite(&id_value,sizeof(Ids),1,id_data);
    }

    fclose(id_data);

}
/*
input : quel Id a creer  1 reponse 2 question 3 profil
process : Lis le derniers Id par rapport a l'octet
output : next Id
*/
long set_id(short choice)
{

    FILE *data_id = NULL;
    data_id = fopen("id_data.dat","r+b");
    Ids Id_current;
    if(data_id == NULL)
    {
        check_Id_files();
        data_id = fopen("id_data.dat","r+b");
    }

    fread(&Id_current,sizeof(Ids),1,data_id);
    fseek(data_id,0,SEEK_SET);

    switch (choice)
    {
        case 1 :
            Id_current.reponse +=1;
            break;
        case 2 : Id_current.question +=1;
        break;
        case 3: Id_current.profil +=1;
        break;
        default:
            break;
    }

    fwrite(&Id_current,sizeof(Ids),1,data_id);
    fclose(data_id);

    switch (choice)
    {
        case 1 :
            return Id_current.reponse;
            break;
        case 2 : return Id_current.question;
        break;
        case 3: return Id_current.profil;
        break;
        default:
            break;
    }

    return -5;

}

