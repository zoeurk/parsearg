#parsearg  
Petite librairie pour anylser les arguments d'un programme (Pour les plateform non-glibc).  
La librairie est libre d'utilisation, de modification et de distribution  
n'oubliez par de faire un:  
export LD_LIBRARY_PATH="/path/to/library:$LD_LIBRARY_PATH"
avant d'utiliser la lib  
l' original de l' exemple 2 et 3 est basex et sur math.c (https://github.com/zoeurk/basex et https://github.com/zoeurk/math)

Pour installer la librairie:
	libtoolize
	aclocal
	autoconf
	autoreconf --install --force
	./configure --prefix=/usr --exec-prefix=/usr
	make
	make install (en super utilisateur)
