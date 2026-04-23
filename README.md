<div align="center">
<img ./img/header_img.avif>

# Simple Shell

### Ton premier voyage dans les coulisses d'un terminal Unix

*Un mini-shell écrit en C, pensé pour comprendre ce qui se passe réellement quand tu tapes une commande.*

![Language](https://img.shields.io/badge/language-C-blue.svg)
![Standard](https://img.shields.io/badge/standard-gnu89-informational)
![Platform](https://img.shields.io/badge/platform-Linux-lightgrey)
![Status](https://img.shields.io/badge/status-active-success)
![School](https://img.shields.io/badge/Holberton-School-ff0048)

</div>

---

## Sommaire

- [À quoi ça sert ?](#à-quoi-ça-sert-)
- [Ce que tu vas découvrir](#ce-que-tu-vas-découvrir)
- [Structure du projet](#structure-du-projet)
- [Comment démarrer](#comment-démarrer)
- [Les Flowcharts expliqués](#les-flowcharts-expliqués)
- [Comment contribuer](#comment-contribuer)
- [Contact](#contact)

---

## À quoi ça sert ?

Quand tu tapes `ls` dans un terminal, un programme invisible écoute, lit ta commande, puis la fait tourner. Ce programme s'appelle un **shell**.

Ce projet recrée une version miniature de ce genre de programme, en langage C. Tu peux le voir comme un *bouton "play"* qui lance n'importe quelle commande Unix que tu lui donnes.

> **C'est quoi un shell ?**
> Imagine un traducteur entre toi et ton ordinateur. Toi tu parles en mots (`ls`, `pwd`, `cat`), l'ordinateur comprend en électricité. Le shell fait le pont entre les deux.

---

## Ce que tu vas découvrir

En explorant ce projet, tu vas toucher du doigt :

- **Le langage C** — un langage proche de la machine, utilisé partout.
- **Le fonctionnement d'un terminal** — prompt, commandes, exécution.
- **Les appels système** — comment un programme demande à l'ordinateur de faire quelque chose.
- **La gestion de la mémoire** — allouer, utiliser, libérer.
- **La variable `PATH`** — comment l'ordinateur trouve les programmes à exécuter.
- **Les processus** — comment un programme en lance un autre (`fork` et `execve`).

> **C'est quoi un appel système ?**
> C'est un message officiel que ton programme envoie au noyau (le chef d'orchestre de l'ordinateur) pour lui demander un service : lire un fichier, créer un processus, etc.

---

## Structure du projet

À la racine, voici ce que tu vas trouver. Chaque fichier a un rôle précis, comme les instruments d'un orchestre.

```text
holbertonschool-simple_shell/
│
├── simple_shell.c        # Le point d'entrée : c'est ici que tout commence (fonction main)
├── simple_shell.h        # Le "carnet d'adresses" : déclare toutes les fonctions du projet
├── shell_loop.c          # La boucle principale : affiche le prompt "$", lit, exécute, recommence
├── helpers.c             # Les aides : lecture de ligne et exécution de commandes
├── builtins.c            # Les commandes internes : exit et env
├── PATH.c                # Le chercheur : trouve où se cache un programme sur ton disque
├── string_spliter.c      # Le découpeur : transforme "ls -l" en ["ls", "-l"]
├── myfunctions.c         # Les outils maison : nos propres strlen, strdup, strcmp...
│
├── man_1_simple_shell    # Le manuel officiel (format "man page" Unix)
├── AUTHORS               # La liste des créateurs du projet
├── README.md             # Le fichier que tu lis en ce moment
│
└── Flowchart/
    └── Flowchart Simple_Shell.png   # Le schéma visuel du fonctionnement du shell
```

> **C'est quoi un fichier `.h` ?**
> C'est un fichier "en-tête". Il ne contient pas le code des fonctions, mais la liste de leurs noms. Comme une table des matières qui permet aux autres fichiers de se retrouver.

---

## Comment démarrer

Pas de panique, c'est plus simple que ça en a l'air. Suis les étapes dans l'ordre.

### Prérequis

Avant de commencer, tu auras besoin de :

- Un système **Linux** ou **macOS**.
- Un **terminal** (celui fourni par défaut fonctionne très bien).
- Le compilateur **`gcc`** installé.
- **`git`** pour récupérer le projet.

> **C'est quoi un compilateur ?**
> C'est un traducteur qui transforme le code C (lisible par un humain) en un programme exécutable (lisible par la machine).

---

### Étape 1 — Vérifie que `gcc` est installé

Ouvre un terminal et tape cette commande :

```bash
gcc --version
```

Si une version s'affiche, tu es prêt. Sinon, installe-le avec :

```bash
sudo apt install gcc
```

---

### Étape 2 — Récupère le projet

Cette commande télécharge le code sur ton ordinateur :

```bash
git clone https://github.com/TonNom/holbertonschool-simple_shell.git
```

---

### Étape 3 — Entre dans le dossier

```bash
cd holbertonschool-simple_shell
```

> **C'est quoi `cd` ?**
> Ça veut dire *"change directory"*. C'est comme double-cliquer sur un dossier pour l'ouvrir, mais en version texte.

---

### Étape 4 — Compile le projet

Cette commande transforme les fichiers `.c` en un programme exécutable appelé `hsh` :

```bash
gcc -Wall -Werror -Wextra -pedantic -std=gnu89 \
    simple_shell.c shell_loop.c helpers.c builtins.c \
    PATH.c string_spliter.c myfunctions.c -o hsh
```

> **C'est quoi ces drapeaux `-Wall -Werror` ?**
> Ce sont des options qui demandent au compilateur d'être très strict. Il va refuser le moindre petit défaut dans le code. C'est pour garantir un code propre.

---

### Étape 5 — Lance le shell

```bash
./hsh
```

Tu verras apparaître un petit prompt :

```bash
$
```

Tape une commande, n'importe laquelle :

```bash
$ ls
AUTHORS  PATH.c  builtins.c  helpers.c  hsh  ...
$ pwd
/home/toi/holbertonschool-simple_shell
$ env
PATH=/usr/local/bin:/usr/bin:/bin
HOME=/home/toi
```

Pour quitter, tape simplement :

```bash
$ exit
```

Ou appuie sur **Ctrl + D**.

Félicitations. Tu viens d'exécuter ton propre shell.

---

### Bonus — Consulte le manuel

Un manuel complet au format Unix est fourni. Affiche-le avec :

```bash
man ./man_1_simple_shell
```

---

## Les Flowcharts expliqués

Le dossier **`Flowchart/`** contient un schéma qui illustre visuellement la logique du shell.

### Flowchart Simple_Shell.png

![Flowchart du Simple Shell](Flowchart/Flowchart%20Simple_Shell.png)

> **C'est quoi un flowchart ?**
> C'est un dessin avec des boîtes et des flèches qui montre, étape par étape, comment un programme prend ses décisions. Comme une recette de cuisine illustrée.

#### Ce que raconte le diagramme

Le shell suit toujours la même danse, encore et encore :

1. **Il affiche un prompt** — le petit `$` qui te dit "vas-y, parle".
2. **Il lit ta ligne** — ce que tu tapes au clavier, suivi de Entrée.
3. **Il découpe ta ligne** — `ls -l` devient deux morceaux : `ls` et `-l`.
4. **Il vérifie si c'est une commande interne** — comme `exit` ou `env`.
5. **Sinon, il cherche le programme** — dans tous les dossiers listés dans `PATH`.
6. **Il crée un clone de lui-même** (`fork`) et lance la commande dans le clone.
7. **Il attend la fin du clone** puis reprend la boucle au point 1.

C'est ce cycle infini qui donne l'illusion d'un "assistant" qui t'écoute en permanence.

---

## Comment contribuer

Tu veux améliorer le projet ? Super. Voici le chemin le plus doux pour y arriver.

### Étape 1 — Fork le dépôt

Sur la page GitHub du projet, clique sur le bouton **Fork** en haut à droite. Cela crée ta propre copie personnelle.

### Étape 2 — Clone ta copie

```bash
git clone https://github.com/TON-PSEUDO/holbertonschool-simple_shell.git
cd holbertonschool-simple_shell
```

### Étape 3 — Crée une nouvelle branche

```bash
git checkout -b ma-nouvelle-idee
```

> **C'est quoi une branche ?**
> C'est un "brouillon parallèle" du projet. Tu peux y faire tes changements sans abîmer la version principale.

### Étape 4 — Fais tes modifications

Ouvre les fichiers, teste tes idées, recompile avec la commande `gcc` vue plus haut.

### Étape 5 — Enregistre tes changements

```bash
git add .
git commit -m "Description courte de ton changement"
git push origin ma-nouvelle-idee
```

### Étape 6 — Ouvre une Pull Request

Retourne sur GitHub. Un bouton vert **Compare & pull request** apparaît. Clique, décris ton idée, envoie. C'est fait.

---

## Contact

Une question ? Une suggestion ? Un bug trouvé ? N'hésite pas.

| Auteur  | Email                          |
|---------|--------------------------------|
| McPe4ce | phil.ghanem@gmail.com          |
| Oliium  | jeremie.rouxel@outlook.fr      |

---

<div align="center">

**Bonne exploration, et bienvenue dans les entrailles d'Unix.**

*Projet réalisé dans le cadre du cursus Holberton School.*

</div>
