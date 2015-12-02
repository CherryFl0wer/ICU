#include <stdlib.h>
#include <gtk/gtk.h> 
#include <stdio.h>

void OnDestroy(GtkWidget *pWidget, gpointer pData);
void AddBtn(GtkWidget *pWindow);
//void gtk_button_get_always_show_image(GtkButton *button);

int main(int argc,char **argv)
{ 
  /* Déclaration du widget */
  GtkWidget *pWindow;
  gtk_init(&argc,&argv);

  /* Création de la fenêtre */
  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_MOUSE);
  gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
  // gtk_window_set_title(GTK_WINDOW(pWindow), "ICU");

  /* Connexion du signal "destroy" */
  g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  /* Insertion du bouton */
  AddBtn(pWindow);

  /* Affichage de la fenêtre */
  gtk_widget_show(pWindow);

  /* Demarrage de la boucle evenementielle */
  gtk_main();

  return EXIT_SUCCESS;
}


void OnDestroy(GtkWidget *pWidget, gpointer pData)
{
  pWidget = NULL;
  pData = NULL;
/* Arret de la boucle evenementielle */
  gtk_main_quit();
}

void AddBtn(GtkWidget *pWindow)
{
  GtkWidget *pQuitBtn;
  GtkWidget *pImage;
   
  //init image
  pImage = gtk_image_new_from_file("/home/eriovi/Téléchargements/door-in-icon.png");
  
  //init button
  pQuitBtn = gtk_button_new();
  gtk_button_set_label(GTK_BUTTON(pQuitBtn), "Database");
  gtk_button_set_image(GTK_BUTTON(pQuitBtn), pImage);
//  gtk_button_get_always_show_image(GTK_BUTTON(pQuitBtn));
   
  /* Insertion du bouton dans la fenetre */
  gtk_container_add(GTK_CONTAINER(pWindow), pQuitBtn);
}


