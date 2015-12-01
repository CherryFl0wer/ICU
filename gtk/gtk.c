#include <stdlib.h>
#include <gtk/gtk.h> 
#include <stdio.h>


void OnDestroy(GtkWidget *pWidget, gpointer pData);

int main(int argc,char **argv)
{ 
/* Déclaration du widget */
  GtkWidget *pWindow;
  gtk_init(&argc,&argv);

/* Création de la fenêtre */
  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_MOUSE);
  gtk_window_set_default_size(GTK_WINDOW(pWindow), 320, 200);
  gtk_window_set_title(GTK_WINDOW(pWindow), "ICU");
  //gtk_window_set_decorated(GTK_WINDOW(pWindow), TRUE);

/* Connexion du signal "destroy" */
  g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(OnDestroy), NULL);

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
