echo "QUIZZ UP LIKE!"
echo "Gcc comporte des bugs qui affiche des warnings"

read -p "Voulez-vous installer le compilateur Clang? [Y]es/[N]o >> " yn
   case $yn in
        [Yy]* ) make install-clang;;
        [Nn]* ) make install-gcc;;
	*) echo "Y ou N";;
	esac
