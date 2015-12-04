#include <stdlib.h>
#include <gtk/gtk.h> 

void AddBtn(GtkWidget *pWindow);

int main(int argc, char **argv)
{ 
  GtkWidget* pWindow;
  gtk_init(&argc, &argv);

  /* Creation de la fenetre */
  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(pWindow), 320 ,200); 
  gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_MOUSE);
  gtk_window_set_title(GTK_WINDOW(pWindow), "ICU");
  gtk_container_set_border_width(GTK_CONTAINER(pWindow), 15);

  /* Connexion du signal "destroy" de la fenetre */
  g_signal_connect(G_OBJECT(pWindow), "destroy", G_CALLBACK(gtk_main_quit), NULL);
  /* Insertion du bouton */
  AddBtn(pWindow);
  /* Affichage de la fenetre */
  gtk_widget_show_all(pWindow); 
  /* Demarrage de la boucle evenementielle */
  gtk_main();
  return EXIT_SUCCESS; 
}

void AddBtn(GtkWidget *pWindow)
{
  GtkWidget *pQuitBtn;
  //GtkWidget *pDataBtn;
  GtkWidget *pImage;

  //  init image
  pImage = gtk_image_new_from_file("images/door-in-icon.png");

  //  init button quit
  pQuitBtn = gtk_button_new();
  gtk_button_set_label(GTK_BUTTON(pQuitBtn), "QUIT");
  gtk_button_set_image(GTK_BUTTON(pQuitBtn), pImage);

  // init button data
  //pDataBtn = gtk_button_new();
  //gtk_button_set_label(GTK_BUTTON(pDataBtn), "Database");

  //  option image  
  gtk_button_set_always_show_image(GTK_BUTTON(pQuitBtn), TRUE);

  /* Connexion du signal "clicked" du bouton */
  g_signal_connect(G_OBJECT(pQuitBtn), "clicked", G_CALLBACK(gtk_main_quit), NULL);
  /* Insertion du bouton dans la fenetre */
  //  gtk_container_add(GTK_CONTAINER(pWindow), pDataBtn);
  gtk_container_add(GTK_CONTAINER(pWindow), pQuitBtn);
}

