#ICU Face Recognition 

How to start ?
==============

Commencez par télécharger une distrib Linux qui marche (internet etc...).
Ensuite vous allez devoir télécharger deux framework SDL2 et GTK+2, ouvrez un terminal et lancez l'installation de GTK.
`sudo apt-get install libgtk2.0-dev`et`sudo apt-get install libgtk2.0-0`

Si tous ce passe bien il nous restera plus que SDL2.

On commence par DL l'archive : 
`http://www.libsdl.org/download-2.0.php` prenez soit le zip ou le tar, sortez tout et aller dans votre terminal jusqu'au dossier SDL2 extrait.

Une fois dedans executez ces commandes : 
```
    mkdir build
    cd build
    ../configure
    make
    sudo make install
```
(pour plus d'infos http://wiki.libsdl.org/Installation) 

 
Use git with terminal command
=============================

> Apprendre les commandes : https://try.github.io/
> Se connecter avec ssh : https://help.github.com/articles/generating-ssh-keys/

After that
==========
Une fois connecté par SSH par git ainsi que l'installation de GTK2 et SDL2, il vous reste plus qu'à clone le projet.
`git clone  git://github.com/Gumcher/ICU.git`

Vous avez désormais un dossier `./ICU`
### 27/09/2015 
Pour le moment il y a juste un fichier maingtk-example et mainsdl-example pour pouvoir tester si gtk et sdl marche de votre côté.
Pour les tester : 
```
make gtkall #pour tester gtk
make sdlall #pour tester sdl
```
vous aurez un fichier *gtkexe* ou/et *sdlexe* en fct de la commande make.
`./gtkexe` pour tester gtk
`./sdlexe` pour tester sdl
Vous devriez avoir une fenêtre pour chaque (SDL : juste un titre rien dedans, GTK: un texte dedans).

