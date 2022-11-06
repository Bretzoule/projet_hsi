# Projet HSI

[![wakatime](https://wakatime.com/badge/user/1d55ca4f-dbfd-4718-af05-8971f2e93456/project/d6e83f52-7f8a-4d0f-928d-9bf6f8715074.svg)](https://wakatime.com/badge/user/1d55ca4f-dbfd-4718-af05-8971f2e93456/project/d6e83f52-7f8a-4d0f-928d-9bf6f8715074)

Projet de Hardware Software Interface dont l'objectif était de créer un BCGV (boîtier central de gestion du véhicule), le tout connecté à une interface Grafana s'apparentant à un tableau de bord.

---

## Prérequis

- NodeJS > 16.0
- gcc > 11.0
- docker > 20.0

Les targets de compilations doivent être lancées uniquement depuis le makefile principal et depuis le dossier courant.

## Compilation

Compilation comlète (Génération -> Création librairies statiques -> Compilation) : `make all`
(@GENERATED : Pour le générateur de code)
(@STATIC : Pour les librairies statiques)
(@APP : Pour l'application)

Pour nettoyer les .o : `make clean`

Pour nettoyer les fichiers générés via le générateur : `make cleangenerated`

Pour supprimer tout les fichiers générables : `make mrproper`

## Lancer l'application

Lancer le Docker (dans le dossier /docker ): `docker compose up`

Compiler l'appli (dans le dossier / ): `make all`

Lancer l'application (dans le dossier / ): `make runall`

---

### Doxygen

Le fichier de configuration Doxygen (Doxyfile) est déjà généré, il suffit de taper `make doxy`
et l'index html de la documentation s'ouvre.

---

### Principe de fonctionnement

##### Q1/Q2 :

_script/index.js_ // _script/variables.json_ //
Nous avons créé un tableau contenant l'intégralité de nos types et structures que nous avons ensuite transformé dans un fichier ".json". Nous avons choisi d'utiliser Javascript pour notre générateur compte tenu de son affinité avec le JSON et de nos compétences.

##### Q3 :

_app/src/app.c_
Notre main n'a fait qu'évoluer au cours de la création de l'application mais ce dernier à toujours compté une boucle infinie contenant des appels successifs au éléments de notre système.

##### Q4 :

_app/save/fsm.h_ // _app/save/lightsFSM.c_ // _app/save/wipersFSM.c_ // _app/save/blinkingLightsFSM.c_
Les FSM permettent de gérer les transitions entre les états de notre app, elles sont appelés entre la récéption d'une trame et l'envoi d'une nouvelle. Elles sont conçues autour d'une structure d'état-transitions ainsi qu'une fonction `getNextEvent` qui permet de passer d'un état à un autre, via une fonction donnée.
Les FSM n'étant pas totalement fonctionnelles, nous avons préféré ne pas les intégrer au programme dans l'immédiat.

##### Q5 :

_makefile_ // _app/makefile_ // _app/makefile_static_ // _run.sh_
Notre premier makefile inclus le deux autres, ce qui nous permet d'utiliser des targets générales, dépendantes des targets présentes dans les sous makefiles. Ces makefile peuvent également appeler le fichier `run.sh`, qui lance notre driver puis notre programme. (il y a une attente de quelques millisecondes entre les deux appels puisque le driver met parfois un peu de temps à s'initialiser...).

##### Q6 :

_app/src/frameUtils.c_ // _app/include/frameUtils.h_
Le décodage des trames se fait en plusieurs étapes, tout d'abord on s'assure que cette dernière à bien été récupérée auprès du driver. Ensuite, pour l'UDP on compare le numéro de trame avec celui attendu et pour la LNS on compare le CRC8 envoyé avec celui que l'on calcule sur la trame reçue. Dans le cas ou tout et bon, on démarre la conversion des trames et on stocke les valeurs dans la structure BCGV.

##### Q7 :

_app/src/frameUtils.c_ // _app/include/frameUtils.h_
Pour la trame LNS, qui est une succession de 5 petits blocs envoyés via un seul échange LNS. Les valeurs constituant cette trame sont prises depuis la structure BCGV.
Pour ce qui est de la trame UDP, elle est construite d'un seul trait via les données du BCGV et est envoyée ensuite.

#### Q8 :

L'organisation de l'application est délimitée par des commentaires présentant chaque section dans le main. Initialisation -> @ -> Lecture UDP -> Décodage UDP (si trame valide) -> Lecture LNS -> Décodage LNS (si CRC8 valide) -> FSMs -> Encodage/Envoi UDP -> Encodage/Envoi LNS -> @

### Problèmes connus :

##### FSMs

Les FSM ne sont pas intégralement fonctionnelles et n'ont donc pas été implémentées, leur code se situe dans le dossier "save" de l'application.

##### Acquittement

Le driver ne semble pas retourner correctement les valeurs d'acquittement après que l'on lui ai envoyé la trame LNS des valeurs en cours.

## Contribution

HAMON Mathilde <<hamonmathi@eisti.eu>>
LAIZET Damien <<laizetdami@eisti.eu>>
LEFLOCH Thomas <<leflochtho@eisti.eu>>
