#include "index.h"

int main(int argc, char const *argv[])
{

    //Mise en place de l'environnement


    createFileSeqLog(USERFILE);
    createFileInd(QUESTFILE);
    createFilePartie("partie.dat");
    createAnswersFile(ANSWFILE);

    //Initialisation de l'application




if(argc>1)
{
    if(strcmp(argv[1],"-help")==0)
    {
        Help();
    }
    else
    {
        if(strcmp(argv[1],"-127")==0)
    {
        Teacher_Quote();
    }
    else
        init_App();
    }

}
else
    init_App();



    return 0;
}
