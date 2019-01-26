# Projet MINIGIMP 
## Par Laura Dietsch et Alexis Bihan

### Pour lancer le programme 

Le programme se lance en ligne de commandes. L'éxecutable se trouve dans le dossier minigimp. 

### Arguments

1. **DOIT TOUJOURS ETRE LE PREMIER ARGUMENT** Le chemin de l'image PPM à modifier.
2. *-h width height ou -histo width height* Option qui active la génération de deux histogrammes de l'image. L'histogramme des nuances de gris et l'histogramme de couleurs RVB. Ils sont générés sous la forme d'une image ppm de taille width x height.
3. Les différents effets détaillés plus bas. 
4. **DOIT TOUJOURS ETRE LE DERNIER ARGUMENT** Le chemin de l'image PPM transformée.

### Codes des effets

Ces effets peuvent être mis dans n'importe quel ordre en ligne de commande et on peut appliquer autant d'effets qu'on veut à une image.

* *ADDLUM x* - Ajout de luminosité où x est le pourcentage à ajouter.
* *DIMLUM x* - Diminution de luminosité où x est le pourcentage de diminution.
* *ADDCON x* - Ajout de contraste où x est le pourcentage d'ajout.
* *DIMCON x* - Diminution de constraste où x est le pourcentage de diminution.
* *INVERT* - Inversion des couleurs.
* *SEPIA* - Effet sépia.
* *MIRROR* - Miroir de l'image selon une symétrie complète.
* *HMIRROR* - Miroir de l'image selon une symétrie horizontale.
* *VMIRROR* - Miroir de l'image selon une symétrie verticale.
* *BW* - Passage en nuances de gris.
* *REDISH* - Passage en nuances de gris sauf pour le rouge qui garde son intensité originale.
* *GREENISH* - Comme *REDISH* mais pour le vert.
* *BLUEISH* - Comme *REDISH* mais pour le bleu.
* *RED* - Passage en nuances de rouge.
* *GREEN* - Comme *RED* mais pour le vert.
* *BLUE* - Comme *RED* mais pour le bleu.
* *YELLOW* - Comme *RED* mais pour le jaune.
* *PURPLE* - Comme *RED* mais pour le violet.
* *ORANGE* - Comme *RED* mais pour le orange.
* *PINK* - Comme *RED* mais pour le rose.
* *REDBLUE* - Rend les nuances de gris sombres bleu et les nuances de gris clairs rouge. 
* *MORERED* - Passage en nuances de gris sauf pour le rouge qui vaut 255 tout le temps.
* *MOREGREEN* - Comme *MORERED* mais pour le vert.
* *MOREBLUE* - Comme *MORERED* mais pour le bleu.
* *BICOLOR a b c - x y z* - Applique un dégradé linéaire entre 2 couleurs au choix. Ici *a b c* représentent respectivement le rouge, le vert et le bleu de la première couleur et *x y z* resprésentent la même chose pour la seconde couleur. 

### Exemple d'utilisation 

Depuis la racine du projet, écrire dans la console : 

$ make
$ cd bin
$ ./minigimp ../images/flowers.ppm -h 800 600 BICOLOR 0 0 229 - 255 105 80 VMIRROR ADDLUM 20 ADDCON 20 ../images/output.ppm

L'image de départ :

![Image de fleur](../images/flowers.ppm)

L'image d'arrivée :

![Image de fleur transformée](../images/output.ppm)



