#include <gtk/gtk.h>
#include "control.h"

#define FILENAME "AnhViet.dat"

 GtkBuilder      *builder; 
 GtkWidget       *mainWindow;
 GtkWidget       *add_word_entry;
 GtkWidget       *add_meaning_entry;
 GtkWidget       *displayEntry;
 GtkWidget       *inputEntry;
 GtkTextBuffer   *inputBuffer;
 GtkTextBuffer   *displayBuffer;
 BTA             *database;


int main(int argc, char *argv[])
{
	SuggestData *in_suggest = (SuggestData*)malloc(sizeof(SuggestData));

    GtkWidget *btn_search, *btn_add, *btn_edit, *btn_delete, *btn_about, *btn_quit;
    gtk_init(&argc, &argv);
    database = btopn(FILENAME, 0, FALSE);
     
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
 
	//Set up for suggest data
	strcpy(in_suggest->word, "");
	in_suggest->no_match = 0;
	in_suggest->cnt_tab = 0;
	for(int k = 0; k < 5; k++)
		strcpy(in_suggest->suggest[k], "");
	
    //Connect Component With UI in Glade
    mainWindow = GTK_WIDGET(gtk_builder_get_object(builder, "window_main"));
    btn_search = GTK_WIDGET(gtk_builder_get_object(builder, "btn_search"));
    btn_add = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add"));
    btn_edit = GTK_WIDGET(gtk_builder_get_object(builder, "btn_edit"));
    btn_delete = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete"));
    btn_about = GTK_WIDGET(gtk_builder_get_object(builder, "btn_about"));
    btn_quit = GTK_WIDGET(gtk_builder_get_object(builder, "btn_quit"));
    
    displayEntry = GTK_WIDGET(gtk_builder_get_object(builder, "txt_display_word"));
    inputEntry = GTK_WIDGET(gtk_builder_get_object(builder, "search_bar"));
    add_word_entry = GTK_WIDGET(gtk_builder_get_object(builder, "txt_word_add"));
    add_meaning_entry = GTK_WIDGET(gtk_builder_get_object(builder, "txt_meaning_add"));
    
    //Connect widgets with its func
    g_signal_connect(btn_search, "clicked", G_CALLBACK(searchWord), NULL);
    g_signal_connect(btn_add, "clicked", G_CALLBACK(Show_Add_Window), NULL);
    g_signal_connect(btn_edit, "clicked", G_CALLBACK(Show_Edit_Window), NULL);
    g_signal_connect(btn_delete, "clicked", G_CALLBACK(Show_Delete_Dialog), NULL);
    g_signal_connect(btn_about, "clicked", G_CALLBACK(showAbout), NULL);
    g_signal_connect(btn_quit, "clicked", G_CALLBACK(gtk_main_quit), NULL);
    g_signal_connect(inputEntry, "delete-text", G_CALLBACK(delete_entry), NULL);
    g_signal_connect(inputEntry, "key_press_event", G_CALLBACK(on_key_press), in_suggest);
    g_signal_connect(inputEntry, "activate", G_CALLBACK(searchWord), NULL);
    

    gtk_builder_connect_signals(builder, NULL);    
    g_object_unref(builder);
    
    gtk_widget_show(mainWindow);                  
    gtk_main();
    free(in_suggest);
    printf("1\n");
    btcls(database);
 
    return 0;
}
 
