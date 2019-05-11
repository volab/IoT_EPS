==============================
Informations générales IoT_EPS
==============================

:Auteur:               Le VoLab (MajorLee, Poltergeist42)
:Site_Web:             https://www.volab.org
:Projet:               IoT_EPS
:Version:              190105
:dépôt GitHub:         https://github.com/volab/IoT_EPS.git
:documentation:        
:Licence:              CC BY-NC-SA 4.0
:Liens:                https://creativecommons.org/licenses/by-nc-sa/4.0/

####


Description
==============

IoT Electronic Power Strip : Une multiprise connectée sur laquelle chaque plot est configurable.

La connections sans fil se fait selon 2 modes possibles

- le bloc de prise est un point d'accès Wifi (mode AP)
- le bloc de prise se connecte à un réseau Wifi existant (mode Client)

Pas de mode Cloud pour le moment.

####


Arborescence du projet
========================

Pour aider à la compréhension de mon organisation,voici un bref descriptif de l'arborescence de ce projet.Cette arborescence est à reproduire si vous récupérez cedépôt depuis GitHub. ::

    ProjectDir_Name        # Dossier racine du projet (non versionner)
    |
    +--project             # (Branch master) contient l'ensemble du projet en lui même
    |  |
    |  +--_1_userDoc       # Contiens toute la documentation relative au projet
    |  |   |
    |  |   \--source       # Dossier réunissant les sources utilisées par Sphinx
    |  |
    |  +--_2_modelisation  # Contiens tous les plans et toutes les modélisations du projet
    |  |
    |  +--_3_software      # Contiens toute la partie programmation du projet
    |  |
    |  +--_4_PCB           # Contient toutes les parties des circuits imprimés (routage,
    |  |                   # Implantation, typon, fichier de perçage, etc.)
    |  |
    |  +--_5_techDoc       # Contiens toutes les documentations techniques des différents composants
    |  |                   # ou éléments qui constituent le projet. Ces éléments sont identifiés
    |  |                   # par un liens Web dans la documentation. Ce dossier n'est pas 'poussé'
    |  |                   # dans le dépôt distant (.gitignore).
    |  |
    |  +--_6_research      # Regroupe toutes les recherches relatives à l'élaboration ou au
    |  |                   # développement du projet. Ces éléments sont identifiés
    |  |                   # par un liens Web dans la documentation. Ce dossier n'est pas 'poussé'
    |  |                   # dans le dépôt distant (.gitignore).
    |  |
    |  \--_7_rushes        # Contient tous les éléments qui seront potentiellement intégrés dans la
    |                      # doc ou dans le projet. Ce dossier n'est pas 'poussé' dans le dépôt 
    |                      # distant (.gitignore).
    |
    +--webDoc              # Dossier racine de la documentation qui doit être publiée
    |  |
    |  \--html             # (Branch gh-pages) C'est dans ce dossier que Sphinx va
    |                      # générer la documentation a publié sur internet
    |
    \--trash               # Se dossier sert à retirer des éléments du projet sans les
                           # supprimé réélement. Ce dossier n'est pas pris en compte par
                           # GIT ou par GitHub
