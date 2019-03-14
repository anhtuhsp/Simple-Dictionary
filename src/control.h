#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <gtk/gtk.h>
#include <ctype.h>
#include <gdk/gdkkeysyms.h>
#include "/home/anhtu/C advance/C_project/src/bt/btree.h"

typedef struct{
	char word[30];
	int no_match;
	int cnt_tab;
	char suggest[5][30];
	//BTA *tree;
}SuggestData;

extern GtkBuilder *builder;
extern GtkWidget  *mainWindow;
extern GtkWidget  *displayEntry;
extern GtkWidget  *inputEntry;
extern GtkTextBuffer *displayBuffer;
extern GtkTextBuffer *inputBuffer;
extern BTA        *database;

void searchWord();
void Show_Delete_Dialog();
void Show_Edit_Window();
void Show_Add_Window();
void showAbout();
void FormatedText(char* meaning);
void on_btn_delete_cancel_clicked(GtkButton *button, gpointer *wid);
void on_btn_delete_ok_clicked(GtkButton *button, GtkWidget *parent);
void on_btn_edit_apply_clicked(GtkWidget *widget, gpointer Array);
void on_btn_edit_cancel_clicked(GtkButton *button, GtkWidget *wid);
void on_btn_add_cancel_clicked(GtkButton *button, GtkWidget *wid);
void on_btn_add_apply_clicked();
void on_key_down(GtkWidget *entry, GdkEvent *event);
void Show_message(GtkWidget * parent , GtkMessageType type,  char * mms, char * content);
void Show_delete_message(GtkWidget * parent , GtkMessageType type,  char * mms, char * content);
//static void enter_callback (GtkWidget *entry, gpointer user_data);
gboolean delete_entry(GtkEntry * entry, GdkEventKey * event, gpointer user_data);
gboolean on_key_press (GtkEntry * entry, GdkEventKey *event, gpointer user_data);
void soundex(char *name, char *sound);
gboolean func(GtkEntryCompletion *completion, const gchar *key, GtkTreeIter *iter, gpointer user_data);

