#include <stdlib.h>
#include <stdio.h>
#include <stdbool.h>
#include <SDL.h>
#include <SDL_image.h>
#include <gtk/gtk.h>


int main(int argc, const char* argv[])
{

  SDL_Surface *screen, *image;
  SDL_Event event;
  bool done = false;
  if(argc != 2) return 1;

  if(SDL_Init(SDL_INIT_VIDEO) == -1) {
    printf("SDL_Init: %s\n", SDL_GetError());
    return 1;
  }

  image = IMG_Load(argv[1]);
  if(!image) {
    printf("Image failed to load %s \n ", IMG_GetError());
    SDL_Quit();
    return 1;
  }

  printf("Loaded %s : %dx%d %dbpp\n", argv[1], image->w, image->h,
  image->format->BitsPerPixel);

  screen = SDL_SetVideoMode(image->w, image->h, image->format->BitsPerPixel,
    SDL_ANYFORMAT);

  if(!screen) {
    printf("SDL_SetVideoMode : %s \n", SDL_GetError());
    SDL_FreeSurface(image);
    SDL_Quit();
    return 1;
  }

  SDL_WM_SetCaption(argv[1], argv[1]);

  SDL_BlitSurface(image, 0, screen, 0);
  SDL_Flip(screen);

  while(!done && SDL_WaitEvent(&event) != -1) {
    switch(event.type) {
      case SDL_KEYDOWN:
      case SDL_QUIT:
        done = true;
        break;
      case SDL_VIDEOEXPOSE:
        SDL_BlitSurface(image, 0, screen, 0);
        SDL_Flip(screen);
        break;
      default:
        break;
    }
  }

  SDL_FreeSurface(image);
  SDL_Quit();


  /*  ------------
    GTK Window Simple
  ------------ */
  /*
  GtkWidget* p_Window;
  GtkWidget* p_Label;
  gchar* sUtf8;

  gtk_init(&argc,&argv);

  p_Window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
  gtk_window_set_title(GTK_WINDOW(p_Window), "GTK+ 2.10");
  gtk_window_set_default_size(GTK_WINDOW(p_Window), 260, 40);
  gtk_window_set_position (GTK_WINDOW (p_Window), GTK_WIN_POS_CENTER);
  g_signal_connect(G_OBJECT(p_Window), "destroy", G_CALLBACK(gtk_main_quit), NULL);

  sUtf8 = g_locale_to_utf8("La Bibliothèque GTK+ à bien été Installée !", -1, NULL, NULL, NULL);
  p_Label=gtk_label_new(sUtf8);
  g_free(sUtf8);
  gtk_container_add(GTK_CONTAINER(p_Window), p_Label);

  gtk_widget_show_all(p_Window);

  gtk_main();
  */
  
  return 0;
}
