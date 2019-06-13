install-clang : *.c
	@echo "=============================================================================================="
	@echo "                         COMPILATION AVEC CLANG"
	@echo "=============================================================================================="
	sudo apt-get install clang
	clang -Wall -o play *.c
	@echo -n "entrez './play' pour jouer\n"
	@echo -n " "
install-gcc : *.c
	@echo "=============================================================================================="
	@echo "                         COMPILATION AVEC GCC --Des warnings vont apparaitre GCC bug # 53119"
	@echo "=============================================================================================="
	gcc -Wall -o play *.c
	@echo -n "Entrez './play' pour jouer\n"
	@echo -n " "
