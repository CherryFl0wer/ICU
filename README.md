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
`
    mkdir build
    cd build
    ../configure
    make
    sudo make install
`
(pour plus d'infos http://wiki.libsdl.org/Installation) 

 
Use git with terminal command
=============================

> Apprendre les commandes : https://try.github.io/
> Se connecter avec ssh : https://help.github.com/articles/generating-ssh-keys/
