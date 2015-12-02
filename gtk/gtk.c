#include <stdlib.h>
#include <gtk/gtk.h> 
#define EXEMPLE_1 0
#define EXEMPLE_2 1
#define EXEMPLE_3 2

void AddBtn(GtkWidget *pWindow, gint iExemple);
void gtk_button_set_always_show_image(GtkButton *button, gboolean always_show);

int main(int argc, char **argv)
{ 
  GtkWidget* pWindow;
  gtk_init(&argc, &argv);
  /* Creation de la fenetre */
  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(pWindow), 320 ,200); 

  /* Connexion du signal "destroy" de la fenetre */
  g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  /* Insertion du bouton */
  AddBtn(pWindow, EXEMPLE_1);
  /* Affichage de la fenetre */
  gtk_widget_show_all(pWindow); 
  /* Demarrage de la boucle evenementielle */
  gtk_main();
  return EXIT_SUCCESS; 
}
/*
 *   void AddBtn(GtkWidget *pWindow, gint iExemple)
 *     
 *       Fonction en charge d'inserer le bouton dans la fenetre
 *        
 *          Parametre :
 *            - pWindow : fenetre parente
 *              - iExemple : mode de creation 
 *                EXEMPLE_1 pour un bouton label
 *                  EXEMPLE_2 pour un bouton EXEMPLE_1 + raccourci
 *                    EXEMPLE_3 pour un bouton EXEMPLE_2 + image
 *                    */
void AddBtn(GtkWidget *pWindow, gint iExemple)
{
  iExemple = 0;

  GtkWidget *pQuitBtn;
//  GtkWidget *pLabel;
  GtkWidget *pImage;

  //init image
  pImage = gtk_image_new_from_file("images/door-in-icon.png");

  //init label
//  pLabel = gtk_label_new("QUIT");
  
  //init button
  pQuitBtn = gtk_button_new();
//  gtk_container_add(GTK_CONTAINER(pQuitBtn), pLabel);
  gtk_button_set_label(GTK_BUTTON(pQuitBtn), "QUIT");
  gtk_button_set_image(GTK_BUTTON(pQuitBtn), pImage);

//  GtkSettings *default_settings = gtk_setting_get_default();
//  g_object_set(default_settings, "gtk-button-images", TRUE, NULL);

  gtk_button_set_always_show_image(GTK_BUTTON(pQuitBtn), TRUE);

  gtk_window_set_title(GTK_WINDOW(pWindow), "Les boutons - Exemple 1");


  /* Connexion du signal "clicked" du bouton */
  g_signal_connect(G_OBJECT(pQuitBtn), "clicked", G_CALLBACK(gtk_main_quit), NULL);
  /* Insertion du bouton dans la fenetre */
  gtk_container_add(GTK_CONTAINER(pWindow), pQuitBtn);
}

