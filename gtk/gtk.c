#include <stdlib.h>
#include <gtk/gtk.h> 
#include "db/db.c"
#include "db/db.h"

/********************/
/***Identification***/
/********************/

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

/********************/
/******Database******/
/********************/

enum 
{

  LIST_ITEM = 0,
  N_COLUMNS
};

void init_list(GtkWidget *list) 
{
  GtkCellRenderer *renderer;
  GtkTreeViewColumn *column;
  GtkListStore *store;

  renderer = gtk_cell_renderer_text_new ();
  column = gtk_tree_view_column_new_with_attributes("List Items",
      renderer, "text", LIST_ITEM, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

  store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

  gtk_tree_view_set_model(GTK_TREE_VIEW(list), 
      GTK_TREE_MODEL(store));

  g_object_unref(store);
}

/*
void add_to_list(GtkWidget *list, const gchar *str) 
{
  GtkListStore *store;
  GtkTreeIter iter;

  store = GTK_LIST_STORE(gtk_tree_view_get_model
      (GTK_TREE_VIEW(list)));

  gtk_list_store_append(store, &iter);
  gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
}
*/

void add_dabase(GtkWidget *list)
{
  GtkListStore *strore;
  GtkTreeIter iter;

  store = GTK_LIST_STORE(gtk_tree_view_get_model
      (GTK_TREE_VIEW(list)));
  
  FILE *db;
  db = fopen(

}

void on_changed(GtkWidget *widget, gpointer label) 
{

  GtkTreeIter iter;
  GtkTreeModel *model;
  gchar *value;

  if (gtk_tree_selection_get_selected(
        GTK_TREE_SELECTION(widget), &model, &iter)) {

    gtk_tree_model_get(model, &iter, LIST_ITEM, &value,  -1);
    gtk_label_set_text(GTK_LABEL(label), value);
    g_free(value);
  }
}

void database()
{ 
  GtkWidget* dWindow;
  GtkWidget *list;

  GtkWidget *box;
  GtkWidget *label;
  GtkTreeSelection *selection;

  // creation of the window
  dWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(dWindow), 270, 250); 
  gtk_window_set_position(GTK_WINDOW(dWindow), GTK_WIN_POS_MOUSE);
  gtk_window_set_title(GTK_WINDOW(dWindow), "Database");
  gtk_container_set_border_width(GTK_CONTAINER(dWindow), 10);

  list = gtk_tree_view_new();

  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);

  // init box
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start(GTK_BOX(box), list, TRUE, TRUE, 5);

  // init list
  label = gtk_label_new("");
  gtk_box_pack_start(GTK_BOX(box), label, FALSE, FALSE, 5);

  gtk_container_add(GTK_CONTAINER(dWindow), box);

  // init list (suite)
  init_list(list);
  // add_to_list(list, "Alien");
  // add_to_list(list, "Leon");
  // add_to_list(list, "The Verdict");
  // add_to_list(list, "North Face");
  // add_to_list(list, "Der Untergang");

  // init tree
  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

  g_signal_connect(selection, "changed", G_CALLBACK(on_changed), label);

  printf("clicked database button\n");
  gtk_widget_show_all(dWindow); 
}

/********************/
/********Menu********/
/********************/

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
