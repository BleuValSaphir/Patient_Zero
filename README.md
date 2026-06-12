# Patient Zero

## Description
Patient Zero est un remake du célèbre jeu Wolfenstein, un jeu d'exploration de labyrinthes.
Vous incarnez un patient qui vient de se réveiller d'une opération et qui part à la recherche de sa fille dans un hôpital infesté de zombies.

## Prérequis
Pour compiler et exécuter ce projet, vous aurez besoin de :
- GCC
- Make
- CSFML (`libcsfml-dev`)

## Compilation
Pour compiler le projet, exécutez simplement la commande suivante à la racine du dépôt :

```bash
make
```

## Utilisation
Pour lancer le jeu, exécutez le fichier binaire compilé :

```bash
./wolf3d
```
Vous pouvez également utiliser `./wolf3d -h` ou `./wolf3d -help` pour afficher le message d'aide.

## Commandes

### Clavier et souris

- **Déplacement** : `W`, `A`, `S`, `D` (ou `Z`, `Q`, `S`, `D` selon vos paramètres)

- **Caméra / Vue** : `Souris`

- **Tir / Attaque** : `Clic gauche`

- **Recharger** : `R`
- **Briquet** : `F`
- **Boutique** : `Maintenir B`
- **Menu Pause** : `Échap`

### Manette (Gamepad)

- **Déplacement** : `Joystick gauche`
- **Caméra / Vue** : `Joystick droit`
- **Tir / Attaque** : `Gâchette droite (RT/R2)`
- **Recharger** : `Bouton X / Carré`
- **Briquet** : `Bouton Y / Triangle`
- **Boutique** : `Bouton Select / Back`
- **Menu Pause** : `Bouton Start / Options`
- **Changer d'arme / Soin** : `Croix directionnelle (D-Pad)`


### Armes et inventaire

- `1` : Équiper le couteau
- `2` : Équiper le pistolet
- `3` : Équiper le MP5
- `4` : Équiper l'arme spéciale
- `5` : Utiliser la trousse de soins
