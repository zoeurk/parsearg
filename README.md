#parsearg  
Petite librairie pour anylser les arguments d'un programme (Pour les plateform non-glibc).  
La librairie est libre d'utilisation, de modification et de distribution  
n'oubliez par de faire un:  
export LD_LIBRARY_PATH="/path/to/library:$LD_LIBRARY_PATH"
avant d'utiliser la lib  

Pour installer la librairie:  
	libtoolize  
	autoreconf --install  
	./configure --prefix=/usr --exec-prefix=/usr  
	make  
	make install (en super utilisateur)
