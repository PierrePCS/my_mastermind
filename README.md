<div align="center">

# 🧠 My Mastermind — Jeu de Logique en C

![Language C](https://img.shields.io/badge/Language-C-00599C?style=for-the-badge&logo=c&logoColor=white)
![Compiler](https://img.shields.io/badge/Compiler-GCC-4EAA25?style=for-the-badge&logo=gnu&logoColor=white)
![Build](https://img.shields.io/badge/Build-Makefile-F34F29?style=for-the-badge&logo=cmake&logoColor=white)
![System Calls](https://img.shields.io/badge/I%2FO-read()_%2F_write()-blueviolet?style=for-the-badge)

**Une implémentation complète en langage C du célèbre jeu de déduction Mastermind en ligne de commande.**  
*Projet Algorithmique & Programmation Système — Colint School*

</div>

---

## 📖 Présentation du projet

**My Mastermind** est une recréation en **langage C** du jeu de société classique *Mastermind*.  
Le programme génère (ou reçoit en paramètre) un **code secret composé de 4 chiffres compris entre `0` et `8`**. Le joueur dispose d'un nombre limité de tentatives (par défaut **10 rounds**) pour deviner la combinaison exacte.

À chaque essai valide, le programme analyse la proposition et indique :
- 🎯 **Well placed pieces** : le nombre de chiffres corrects et placés au **bon endroit**.
- 🔄 **Misplaced pieces** : le nombre de chiffres présents dans le code secret mais placés au **mauvais endroit**.

> [!IMPORTANT]
> La lecture de l'entrée standard est réalisée caractère par caractère via l'appel système bas niveau `read(0, &c, 1)` (conformément aux contraintes du sujet) et gère proprement la fin de fichier **`EOF` (`Ctrl + D`)** ainsi que les saisies invalides (`Wrong input!`).

---

## 🛠️ Prérequis

Avant de compiler et lancer le jeu, vérifiez que le compilateur **GCC** et l'outil **Make** sont installés sur votre machine :

```bash
gcc --version
make --version
```

---

## 🚀 Installation & Compilation (Commandes complètes)

Ouvrez votre terminal et exécutez les commandes suivantes dans l'ordre :

### 1️⃣ Cloner le dépôt et accéder au dossier

```bash
git clone https://github.com/PierrePCS/my_mastermind.git
cd my_mastermind
```

### 2️⃣ Compiler le projet avec `Makefile`

Le projet inclut un `Makefile` complet compilant les sources avec les flags stricts `-Wall -Wextra -Werror` :

```bash
make
```

*(Sous Windows sans l'utilitaire `make`, vous pouvez compiler directement avec `gcc` :)*
```bash
gcc -Wall -Wextra -Werror -o my_mastermind main.c game.c utils.c
```

### 3️⃣ Commandes de nettoyage du `Makefile`

| Commande | Action |
| :--- | :--- |
| `make` ou `make all` | Compile les fichiers `.c` et génère l'exécutable `my_mastermind` |
| `make clean` | Supprime uniquement les fichiers objets intermédiaires (`*.o`) |
| `make fclean` | Supprime les fichiers objets (`*.o`) **et** l'exécutable `my_mastermind` |
| `make re` | Nettoie tout (`fclean`) puis recompile intégralement le projet |

---

## ⚙️ Options de lancement

L'exécutable `my_mastermind` accepte deux options en ligne de commande pouvant être utilisées seules ou combinées :

| Option | Paramètre | Valeur par défaut | Description |
| :---: | :---: | :---: | :--- |
| **`-c`** | `[CODE]` | *Généré aléatoirement* | Définit manuellement le code secret de 4 chiffres (`0` à `8`). |
| **`-t`** | `[ATTEMPTS]` | `10` | Définit le nombre maximal de tentatives (rounds) autorisées. |

### ▶️ Exemples de commandes de démarrage

- **Lancer une partie classique** (code aléatoire sans doublons, 10 essais) :
  ```bash
  ./my_mastermind
  ```

- **Lancer une partie avec un code secret précis (`0123`)** :
  ```bash
  ./my_mastermind -c "0123"
  ```

- **Lancer une partie avec un code secret (`5812`) et seulement 5 tentatives** :
  ```bash
  ./my_mastermind -c "5812" -t 5
  ```

---

## 🎮 Règles de validation & Déroulement d'une partie

### ✅ Format d'une proposition valide
Pour qu'une saisie soit acceptée par le programme, elle doit respecter **toutes** les conditions suivantes :
1. Faire **exactement 4 caractères** de long.
2. Contenir uniquement des chiffres compris entre **`'0'` et `'8'`** inclus (le chiffre `'9'`, les lettres et les symboles sont rejetés).

> [!TIP]
> Si l'utilisateur entre une proposition invalide (trop courte, trop longue, contenant `'9'` ou des lettres), le programme affiche `Wrong input!` et **redemande une saisie sans consommer le tour actuel**.  
> Pour quitter proprement la partie à tout moment, appuyez sur **`Ctrl + D`** (`EOF`).

### 🖥️ Exemple de session de jeu complète

```text
$ ./my_mastermind -c "0123"
Will you find the secret code?
Please enter a valid guess
---
Round 0
>1456
Well placed pieces: 0
Misplaced pieces: 1
---
Round 1
>tata
Wrong input!
>4132
Well placed pieces: 1
Misplaced pieces: 2
---
Round 2
>0123
Congratz! You did it!
```

---

## 🧠 Architecture & Fonctionnement du Code

Le projet est découpé de manière modulaire en **3 fichiers sources (`.c`)**, **1 fichier d'en-tête (`.h`)** et **1 `Makefile`** :

### 1. [`main.c`](main.c) — Point d'entrée & Parsing des arguments
- Analyse les arguments `argc` / `argv` passés en ligne de commande (`-c` pour le code secret, `-t` pour le nombre de tours).
- Appelle `generate_random_code()` si aucun code n'a été fourni via `-c`.
- Lance la boucle principale du jeu avec `play_game(secret_code, attempts)`.

### 2. [`game.c`](game.c) — Moteur du jeu & Algorithme de comparaison
- **`count_well_placed(char *secret, char *guess)`** : Parcourt les 4 positions et compte les correspondances exactes (`secret[i] == guess[i]`).
- **`count_misplaced(char *secret, char *guess)`** : Travaille sur des copies locales (`secret_copy`, `guess_copy`), masque d'abord les pions bien placés avec `'*'` pour éviter tout double comptage, puis comptabilise les chiffres présents ailleurs dans le code secret.
- **`play_game(char *secret_code, int attempts)`** : Gère l'affichage des rounds, la boucle de saisie et de validation, la détection de victoire (`Congratz! You did it!`) et l'arrêt sur `EOF`.

### 3. [`utils.c`](utils.c) — Fonctions utilitaires & Entrées/Sorties
- **`my_strlen(char *str)`** & **`my_strcpy(char *dest, char *src)`** : Réimplémentation des fonctions standards de manipulation de chaînes de caractères.
- **`is_valid_code(char *str)`** : Vérifie que la chaîne contient exactement 4 caractères compris entre `'0'` et `'8'`.
- **`is_char_in_str(char *str, char c)`** : Vérifie si un chiffre est déjà présent dans la chaîne (utilisé pour éviter les doublons lors de la génération aléatoire).
- **`generate_random_code(char *secret_code)`** : Initialise le générateur pseudo-aléatoire avec `srand(time(NULL))` et tire 4 chiffres uniques entre `'0'` et `'8'`.
- **`read_input(char *buffer)`** : Lit l'entrée standard (`stdin`, descripteur `0`) octet par octet avec l'appel système `read(0, &c, 1)` jusqu'au retour à la ligne `'\n'` ou `EOF`.

---

## 📂 Structure du dépôt

```text
my_mastermind/
├── Makefile          # Script de compilation automatisé (all, clean, fclean, re)
├── README.md         # Documentation complète du projet
├── my_mastermind.h   # Fichier d'en-tête (includes et prototypes des fonctions)
├── main.c            # Parsing des arguments (-c, -t) et initialisation
├── game.c            # Boucle de jeu et calcul des pions bien/mal placés
└── utils.c           # Fonctions utilitaires, validation, aléatoire et lecture read()
```

