bit boat = 0;
bit wolf = 0;
bit goat = 0;
bit cabb = 0;

#define safe !(((wolf == goat) || (goat == cabb)) && goat != boat)

active proctype main() {
	do
	:: /*(wolf != goat) && (goat != cabb) -> */atomic { printf("boat\n");  			 boat = 1 - boat }
	:: /*(goat != cabb) && */(wolf == boat) -> atomic { printf("wolf\n");  wolf = 1 - wolf;  boat = 1 - boat }
	:: (goat == boat) 		    	-> atomic { printf("goat\n");  goat = 1 - goat;  boat = 1 - boat }
	:: /*(wolf != goat) && */(cabb == boat) -> atomic { printf("cabb\n");  cabb = 1 - cabb;  boat = 1 - boat }
	od
}

ltl {
//	!<>(boat && wolf && goat && cabb)
	!(safe U (boat && wolf && goat && cabb))
}
