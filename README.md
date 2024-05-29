# Universal_wargame
Projet de stage.

Malheuresement, on n'a pas eu le temps de faire le lien entre le mouteur du jeu et l'openGL

Dans le CMakelist : commenter/decommenter pour choisir:
 la 1ere partie est sans bibliotheque graphique juste un affichage console.
 la 2ere partie est avec bibliotheque graphique telle que glew, glfw et assimp pour lire les mesh.

Dans terminal:
"mkdir build && cd build"
"cmake .."
"make"


Pour excuter la partie 1 :
Dans terminal:
"./Universal_wargame"


Pour excuter la partie 2 :

Installation necéssaire :
	"sudo apt install g++ make libglew-dev libglew2.2 libglfw3 libglfw3-dev"

Puis il faut installer assimp https://github.com/assimp/assimp

taper dans terminal  "ldd ./graphique" pour bien verifier les liens
puis "export LD_LIBRARY_PATH=repertoire_ou_vous_avez_installer_assim/bin"

Dans terminal:
"./graphique"


Touches pour se deplacer :

		Z

Q   S   D

La souris pour pivoter.

Touches + et - pour changer la vitesse du camera.

Touches echape pour quitter.

