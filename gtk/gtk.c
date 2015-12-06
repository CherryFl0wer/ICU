#include <stdlib.h>
#include <gtk/gtk.h>
#include "db/db.h"
#include "db/db.c"

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

GtkWidget *list;

char* constchar_to_char(const char *mcc)
{
  char *result = malloc(strlen(mcc) + 1);
  unsigned long i = 0;
  while(i < strlen(mcc))
  {
    result[i] = mcc[i];
    i++;
  }
  result[i] = 0;

  return result;
  free(result);
}

/*** entry ***/
void append_item(GtkWidget *widget, gpointer entry) 
{
  GtkListStore *store;
  GtkTreeIter iter;

  const char *str = gtk_entry_get_text(entry); 

  FILE *db = fopen("database.obj", "r+b");
  person *new = calloc(1,sizeof(struct Person));
  strcpy(new->name, constchar_to_char(str));
  person *answer = calloc(1,sizeof(struct Person));
  bool find = false;
  while((fread(answer, sizeof(struct Person), 1, db)) && !find)
  {
    if (strcmp(answer->name, new->name)==0)
    {
      find = true;
    }
  }
  if(!find)
  {
    new->nb_pics = 2;
    fwrite(new, sizeof(struct Person), 1, db);
  }
  
  store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
  
  gtk_list_store_append(store, &iter);
  gtk_list_store_set(store, &iter, LIST_ITEM, str, -1);
  
  gtk_entry_set_text(entry, "");

  free(answer);
  free(new);
  fclose(db);

  widget = 0;
}

/*** remove ***/
void remove_item(GtkWidget *widget, gpointer selection) 
{
  GtkListStore *store;
  GtkTreeModel *model;
  GtkTreeIter  iter;
  char *value;

  store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
  model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

  if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) {
    return;
  }

  if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection), 
        &model, &iter)) 
  {
    gtk_tree_model_get(model, &iter, LIST_ITEM, &value,  -1);
    remov(value);
    gtk_list_store_remove(store, &iter);
  }
  widget = 0;
}

/*** remove all ***/
void remove_all(GtkWidget *widget/*, gpointer selection*/) 
{
  GtkListStore *store;
  GtkTreeModel *model;
  GtkTreeIter  iter;

  store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
  model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));

  if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) {
    return;
  }
  
  FILE *db = fopen("database.obj", "w");
  fclose(db);
  gtk_list_store_clear(store);
  widget = 0;
}

/*** new window pictures ***/
void pics_window(char *name)
{
  GtkWidget *window;
  GtkWidget *box;
  GtkWidget *Imag;
  char **pics = get_pict(name);
  /*
  int size=0;
  DIR *d = opendir("imagesreco/");
  struct dirent *dir;
  while (dir == readdir(d))
  {
    char *s1 = malloc(sizeof(char*));
    char *s2 = malloc(sizeof(char*));
    char *s3 = malloc(sizeof(char*));
    strcpy(s1,name);
    strcpy(s2,name);
    strcpy(s3,name);
    strcpy(s1,"1.jpeg");
    strcpy(s2,"11.jpeg");
    strcpy(s3,"111.jpeg");
    if (dir->d_name == s1 || dir->d_name == s2 || dir->d_name == s3)
      size++;
  }
  printf("\n\n%d\n\n",size);
  */
  // init window
  window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_MOUSE);
  gtk_window_set_default_size(GTK_WINDOW(window), 200, 100);
  gtk_window_set_title(GTK_WINDOW(window), name);
  gtk_container_set_border_width(GTK_CONTAINER(window), 5);

  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);

  for(int i = 0; i < 3; i++)
  {
    Imag = gtk_image_new_from_file(pics[i]);
    gtk_box_pack_start(GTK_BOX(box), Imag, FALSE, TRUE, 3);
  }

  gtk_container_add(GTK_CONTAINER(window), box);

  gtk_widget_show_all(window);
}

/*** show pictures ***/
void show_pic(GtkWidget *widget, gpointer selection)
{
  GtkListStore *store;
  GtkTreeModel *model;
  GtkTreeIter  iter;
  char *value;
   
  store = GTK_LIST_STORE(gtk_tree_view_get_model(GTK_TREE_VIEW(list)));
  model = gtk_tree_view_get_model(GTK_TREE_VIEW(list));
   
  if (gtk_tree_model_get_iter_first(model, &iter) == FALSE) 
  {
    return;
  }
  
  if (gtk_tree_selection_get_selected(GTK_TREE_SELECTION(selection),
        &model, &iter))
  {
    gtk_tree_model_get(model, &iter, LIST_ITEM, &value,  -1);
    pics_window(value);
  }
  widget = 0;
}


/*** Init ***/
void init_list(GtkWidget *list) 
{
  GtkCellRenderer    *renderer;
  GtkTreeViewColumn  *column;
  GtkListStore       *store;

  renderer = gtk_cell_renderer_text_new();
  column = gtk_tree_view_column_new_with_attributes("List Item",
      renderer, "text", LIST_ITEM, NULL);
  gtk_tree_view_append_column(GTK_TREE_VIEW(list), column);

  store = gtk_list_store_new(N_COLUMNS, G_TYPE_STRING);

  gtk_tree_view_set_model(GTK_TREE_VIEW(list), GTK_TREE_MODEL(store));

  g_object_unref(store);
}

/*
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
   */

void add_database(GtkWidget *list)
{

  GtkListStore *store;
  GtkTreeIter iter;

  store = GTK_LIST_STORE(gtk_tree_view_get_model
      (GTK_TREE_VIEW(list)));

  FILE *db;
  db = fopen("database.obj", "r");
  fseek(db, 0, SEEK_CUR);
  person *a = malloc(sizeof(struct Person));
  a->nb_pics = 0;

  while ((!feof(db))&&(fread(a, sizeof(struct Person), 1, db)))
  {
    gtk_list_store_append(store, &iter);
    gtk_list_store_set(store, &iter, LIST_ITEM, a->name, -1);
  }

  free(a);
  fclose(db);
}


/*
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
   */

void database()
{ 
  GtkWidget* dWindow;
  GtkWidget *sw;

  GtkWidget *remove;
  GtkWidget *add;
  GtkWidget *removeAll;
  GtkWidget *entry;
  GtkWidget *picture;

  GtkWidget *box;
  GtkWidget *hbox;
  GtkTreeSelection *selection;

  // creation of the window
  dWindow = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_default_size(GTK_WINDOW(dWindow), 370, 270); 
  gtk_window_set_position(GTK_WINDOW(dWindow), GTK_WIN_POS_MOUSE);
  gtk_window_set_title(GTK_WINDOW(dWindow), "Database");
  gtk_container_set_border_width(GTK_CONTAINER(dWindow), 10);

  // init sw
  sw = gtk_scrolled_window_new(NULL, NULL);
  list = gtk_tree_view_new();
  gtk_container_add(GTK_CONTAINER(sw), list);

  gtk_scrolled_window_set_policy(GTK_SCROLLED_WINDOW(sw),
      GTK_POLICY_AUTOMATIC, GTK_POLICY_AUTOMATIC);

  gtk_scrolled_window_set_shadow_type(GTK_SCROLLED_WINDOW(sw),
      GTK_SHADOW_ETCHED_IN);

  gtk_tree_view_set_headers_visible(GTK_TREE_VIEW(list), FALSE);

  // init box
  box = gtk_box_new(GTK_ORIENTATION_VERTICAL, 0);
  gtk_box_pack_start(GTK_BOX(box), sw, TRUE, TRUE, 5);

  // init hbox
  hbox = gtk_box_new(GTK_ORIENTATION_HORIZONTAL, 5);

  // init buttons
  add = gtk_button_new_with_label("Add");
  remove = gtk_button_new_with_label("Remove");
  removeAll = gtk_button_new_with_label("Remove All");
  picture = gtk_button_new_with_label("Picture");
  entry = gtk_entry_new();
  gtk_widget_set_size_request(entry, 120, -1);

  gtk_box_pack_start(GTK_BOX(hbox), add, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), entry, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), remove, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), removeAll, FALSE, TRUE, 3);
  gtk_box_pack_start(GTK_BOX(hbox), picture, FALSE, TRUE, 3);

  gtk_box_pack_start(GTK_BOX(box), hbox, FALSE, TRUE, 3);

  gtk_container_add(GTK_CONTAINER(dWindow), box);

  // init list (suite)
  init_list(list);
  add_database(list);

  // init tree
  selection = gtk_tree_view_get_selection(GTK_TREE_VIEW(list));

  // test buttons clicked
  g_signal_connect(G_OBJECT(add), "clicked",
      G_CALLBACK(append_item), entry);

  g_signal_connect(G_OBJECT(remove), "clicked",
      G_CALLBACK(remove_item), selection);

  g_signal_connect(G_OBJECT(removeAll), "clicked",
      G_CALLBACK(remove_all), selection);

  g_signal_connect(G_OBJECT(picture), "clicked",
      G_CALLBACK(show_pic), selection);

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
