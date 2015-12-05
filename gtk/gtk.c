#include <stdlib.h>
#include <gtk/gtk.h> 
#include "db/db.c"

void identification()
{
  GtkWidget* iWindow;

  // creation of the window
  iWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(iWindow), 400, 450); 
  gtk_window_set_position(GTK_WINDOW(iWindow), GTK_WIN_POS_MOUSE);
  gtk_window_set_title(GTK_WINDOW(iWindow), "Identification");
  gtk_container_set_border_width(GTK_CONTAINER(iWindow), 15);

  printf("clicked identification button\n");
  gtk_widget_show_all(iWindow);
}

void database()
{ 
  GtkWidget* dWindow;

  // creation of the window
  dWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(dWindow), 400, 450); 
  gtk_window_set_position(GTK_WINDOW(dWindow), GTK_WIN_POS_MOUSE);
  gtk_window_set_title(GTK_WINDOW(dWindow), "Database");
  gtk_container_set_border_width(GTK_CONTAINER(dWindow), 15);

  printf("clicked database button\n");
  gtk_widget_show_all(dWindow); 
}

void AddBtn(GtkWidget *pWindow)
{
  GtkWidget *box;

  GtkWidget *pQuitBtn;
  GtkWidget *pDataBtn;
  GtkWidget *pIdenBtn;

  GtkWidget *pQuitIm;
  GtkWidget *pDataIm;
  GtkWidget *pIdenIm;

  // init vbox
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 3);
  gtk_container_add(GTK_CONTAINER(pWindow), box);

  // init image
  pQuitIm = gtk_image_new_from_file("images/exit_icon.png");
  pDataIm = gtk_image_new_from_file("images/database_icon.png");
  pIdenIm = gtk_image_new_from_file("images/recognition_icon.png");

  // init button quit
  pQuitBtn = gtk_button_new();
  gtk_button_set_label(GTK_BUTTON(pQuitBtn), "Quit");
  gtk_button_set_image(GTK_BUTTON(pQuitBtn), pQuitIm);
  gtk_button_set_image_position(GTK_BUTTON(pQuitBtn), GTK_POS_TOP);
  

  // init button data
  pDataBtn = gtk_button_new();
  gtk_button_set_label(GTK_BUTTON(pDataBtn), "Database");
  gtk_button_set_image(GTK_BUTTON(pDataBtn), pDataIm);
  gtk_button_set_image_position(GTK_BUTTON(pDataBtn), GTK_POS_TOP);

  // init button Iden
  pIdenBtn = gtk_button_new();
  gtk_button_set_label(GTK_BUTTON(pIdenBtn), "Identification");
  gtk_button_set_image(GTK_BUTTON(pIdenBtn), pIdenIm);
  gtk_button_set_image_position(GTK_BUTTON(pIdenBtn), GTK_POS_TOP);

  // option image  
  gtk_button_set_always_show_image(GTK_BUTTON(pQuitBtn), TRUE); 
  gtk_button_set_always_show_image(GTK_BUTTON(pDataBtn), TRUE);
  gtk_button_set_always_show_image(GTK_BUTTON(pIdenBtn), TRUE);

  // button in the box
  gtk_box_pack_start(GTK_BOX(box), pIdenBtn, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), pDataBtn, TRUE, TRUE, 0);
  gtk_box_pack_start(GTK_BOX(box), pQuitBtn, TRUE, TRUE, 0);

  // button signal
  g_signal_connect(G_OBJECT(pQuitBtn), "clicked", G_CALLBACK(gtk_main_quit), NULL);
  g_signal_connect(G_OBJECT(pDataBtn), "clicked", G_CALLBACK(database), NULL);
  g_signal_connect(G_OBJECT(pIdenBtn), "clicked", G_CALLBACK(identification), NULL);
}

int main(int argc, char **argv)
{ 
  GtkWidget* pWindow;
  gtk_init(&argc, &argv);

  /* Creation de la fenetre */
  pWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(pWindow), 400, 450); 
  gtk_window_set_position(GTK_WINDOW(pWindow), GTK_WIN_POS_CENTER);
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
