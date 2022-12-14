# R-Type

#### INTEGRANTS:

-Cognoms: Dumitru Maroz		Nom:Alexandru

-Cognoms: Rodríguez Rubio	Nom:Álvaro

#### FUNCIONALITATS:

-Estructura bàsica de 4 pantalles: menú principal, jugar, instruccions i crèdits.

-Un nivell amb un boss al final amb varietat. Al principi comença a l'espai i s'endintra dins d'una nau amb dues zones diferents i al superarles s'accedeix a la sala del boss.

-La nau pot disparar, polsant la tecla ‘X’, de forma normal i també carregant el canó, mantenint premuda aquesta mateixa tecla un cert temps, per un atac més poderós. Aquest segon atac fa més mal i travessa als enemics. A més depenent del temps que es carregui és més o menys poderós tenint tres nivells. Nosaltres ho hem fet creant un projectil major el qual va travessant l'objecte, per tant, genera més d'una col·lisió, el provoca que faci més mal.

-La nau pot adquirir el dispositiu “Force”. El qual es mou amb la nau, és invulnerable, fa mal als enemics que toca, i es pot millorar recollint objectes que dropegen els enemics.

-Hi ha dos objectes de millora del dispositiu “Force” que provoca que aquest dispari de manera diferent. El primer és un que et permet fer boles de foc que recorren els límits del mapa i la segona és disparar unes ones més grans que el tret carregat inclòs i que fa més mal.

-Tenim quatre tipus d'enemics:
	L'enemic 1, que és terrestre i es dedica a saltar pel mapa.
	L'enemic 2, vola i dispara en qualsevol angle.
	L'enemic 3, aquest és una torreta que se situa a terra i dispara en qualsevol angle i distancia.
	L'enemic 4, es dedica a perseguir al jugador de manera vertical servint de barrera i es mou de manera horitzontal seguint la velocitat del mapa, dispara en un cert angle per davant i per darrere en direcció al jugador i resisteix més que un enemic normal.

-Tecles per saltar contingut:
	Invulnerabilitat: No es pot morir (tecla ‘G’).
	Crear el “Force” si no es té (tecla ‘F’).
	Poder saltar a punts concrets del nivell (tecles numèriques ‘1’, ‘2’, ‘3’, ‘4’ i ‘5’).
	Poder pujar de nivell el “Force” o baixar-ho (tecles ‘H’ i ‘J’ respectivament).
	Canviar entre les dues opcions de poder especial, o adquirir-ho si no ho tenies (tecla 'K')
	Pausa, o reanudar, el moviment del mapa (tecla 'P')
	Avançar o retrocedir el mapa (tecles 'W' i 'Q' respectivament)
	Poder veure les colliderboxs de tots els elements (tecla ‘D’).

-So: música de fons al menú principal, instruccions i crèdits i una cançó pel joc i una pel boss, a més d'efectes especials al disparar, al eliminar un element i al apareixer per primer cop.

-Capa de background: a l'exterior tenim estrelles movent-se a una velocitat diferent que la dels planetes i el mapa, i a l'interor la primera zona té el fons que es mou a diferent velocitat que el mapa.

-Interactivitat de totes les entitats del joc: a l'eliminar-se una entitat hi ha una explosió, i al impactar les bales es genera una animació. També hi ha transicions de loading entre cada escena.

-Animacions:
	Animació d’entrada al nivell.
	Animació de la “Force”.
	Canvi del sprite de la nau quan es mou en vertical.
	Animacions dels enemics.
	Explosions en la mort d’enemics.
	Parpelleig quan el boss rep mal.

De manera adicional, per facilitar-nos el treball de generació d'enemics i collideboxs del mapa, hem creat un script que a través de dibuixar en la imatge del mapa, calcula les coordenades per generar aquest elements. A més d'un sistema de collisions construit de zero per facilitarnos el cacul de col·lisions.
