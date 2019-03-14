/////////////////////////////////////////////////////////////////////////////////////////////

#include "control.h"

/////////////////////////////////////////////////////////////////////////////////////////////

#define ds(x) printf("%s\n", x)

//<ADD FUNCTION>
void Show_Add_Window(){
	
	GtkWidget       *window_add;
	GtkWidget       *btn_cancel, *btn_add;
	GtkWidget       *word_entry;
	GtkWidget       *meaning_entry;
	GtkWidget       *data_array[2];
	GtkTextBuffer   *meaning_text;
	
 
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
        
	window_add = GTK_WIDGET(gtk_builder_get_object(builder, "window_add"));
	word_entry = GTK_WIDGET(gtk_builder_get_object(builder, "txt_word_add"));
	meaning_entry = GTK_WIDGET(gtk_builder_get_object(builder, "text_add_meaning"));
	btn_cancel = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_cancel"));
    btn_add = GTK_WIDGET(gtk_builder_get_object(builder, "btn_add_apply"));
      
    meaning_text = gtk_text_view_get_buffer(GTK_TEXT_VIEW(meaning_entry));
	
	data_array[0] = word_entry;
	data_array[1] = meaning_entry;
	data_array[2] = window_add;
	
	g_signal_connect(btn_add, "clicked", G_CALLBACK(on_btn_add_apply_clicked), data_array);
    g_signal_connect(btn_cancel, "clicked", G_CALLBACK(on_btn_add_cancel_clicked), window_add);
		
	gtk_widget_show(window_add);
	gtk_main();
	gtk_widget_destroy (window_add);
}


void on_btn_add_cancel_clicked(GtkButton *button, GtkWidget *wid){
    gtk_widget_destroy(wid);
}


void on_btn_add_apply_clicked(GtkWidget *widget, gpointer *Array){
	GtkWidget *inputText = ((GtkWidget**)Array)[0];
	GtkWidget *mean = ((GtkWidget**)Array)[1];
    GtkTextIter start, end;
    BTint x;
    int result;
    char wordText[50], meanText[10000];

    
    gtk_text_buffer_get_start_iter(gtk_text_view_get_buffer(GTK_TEXT_VIEW(mean)), &start);
    gtk_text_buffer_get_end_iter(gtk_text_view_get_buffer(GTK_TEXT_VIEW(mean)), &end);
    
    strcpy(wordText, (char*)gtk_entry_get_text(GTK_ENTRY(inputText)));
    strcpy(meanText, (char*)gtk_text_buffer_get_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(mean)), &start, &end, FALSE));
    
    
    if(wordText[0] == '\0' || meanText[0] == '\0')
      Show_message(((GtkWidget**)Array)[2], GTK_MESSAGE_WARNING, "Warning!", "You must fill all the entry.");
    else if(bfndky(database, wordText, &x) == 0)
      Show_message(((GtkWidget**)Array)[2], GTK_MESSAGE_ERROR, "Error!", "This word is already in you dictionary.");
    else{
		result = btins(database, wordText, meanText, strlen(meanText));
		if(result == 0)
		  Show_message(((GtkWidget**)Array)[2], GTK_MESSAGE_INFO, "Success!", "Update word success!");
		 else
		  Show_message(((GtkWidget**)Array)[2], GTK_MESSAGE_ERROR, "Error!", "Update met error!");
	}
}


//<\ADD FUNCTION>

//<EDIT FUNCTION>

void Show_Edit_Window(){
	
	GtkWidget *window_edit;
	GtkWidget *btn_cancel, *btn_edit;
	GtkWidget *word_entry;
	GtkWidget *meaning_entry;
	GtkWidget *data_array[2];
	GtkTextBuffer *meaning_text;
	
    builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
        
	window_edit = GTK_WIDGET(gtk_builder_get_object(builder, "window_edit"));
	
	btn_cancel    = GTK_WIDGET(gtk_builder_get_object(builder, "btn_edit_cancel"));
    btn_edit      = GTK_WIDGET(gtk_builder_get_object(builder, "btn_edit_apply"));
    word_entry    = GTK_WIDGET(gtk_builder_get_object(builder, "txt_word_edit"));
    meaning_entry = GTK_WIDGET(gtk_builder_get_object(builder, "text_edit_meaning"));
    
    gtk_entry_set_text(GTK_ENTRY(word_entry), gtk_entry_get_text(GTK_ENTRY(inputEntry)));
	meaning_text = gtk_text_view_get_buffer(GTK_TEXT_VIEW(displayEntry));
	gtk_text_view_set_buffer(GTK_TEXT_VIEW(meaning_entry), meaning_text);

	data_array[0] = word_entry;
	data_array[1] = meaning_entry;
	data_array[2] = window_edit;
    
	g_signal_connect(btn_edit, "clicked", G_CALLBACK(on_btn_edit_apply_clicked), data_array);
    g_signal_connect(btn_cancel, "clicked", G_CALLBACK(on_btn_edit_cancel_clicked), window_edit);
	
	
	gtk_widget_show(window_edit);
	gtk_main();
	gtk_widget_destroy (window_edit);
}


void on_btn_edit_cancel_clicked(GtkButton *button, GtkWidget *wid){
    gtk_widget_destroy(wid);
}


void on_btn_edit_apply_clicked(GtkWidget *widget, gpointer Array){
	GtkWidget* inputText = ((GtkWidget**)Array)[0];
	GtkWidget* mean = ((GtkWidget**)Array)[1];
	GtkTextIter start;
	GtkTextIter end;
	BTint x;
	int result;
	char *wordText, *meanText;

	
	gtk_text_buffer_get_start_iter (gtk_text_view_get_buffer(GTK_TEXT_VIEW(mean)), &start);
	gtk_text_buffer_get_end_iter (gtk_text_view_get_buffer(GTK_TEXT_VIEW(mean)), &end);
	
	wordText = (char*)gtk_entry_get_text(GTK_ENTRY(inputText));
    meanText =  (char*)gtk_text_buffer_get_text(gtk_text_view_get_buffer(GTK_TEXT_VIEW(mean)), &start, &end, FALSE);
		
	if (wordText[0] == '\0' || meanText[0] == '\0') 
		Show_message(((GtkWidget**)Array)[2], GTK_MESSAGE_WARNING, "Warning!",
		             "You must fill all the entry");
	else if (bfndky(database, wordText, &x ) != 0)
		Show_message(((GtkWidget**)Array)[2], GTK_MESSAGE_ERROR, "Error!",
		             "Couldn't find this word in dictionary.");
	else {
		result = btupd(database, wordText, meanText, strlen(meanText) + 1);
		
		if (result == 0)
			Show_message(((GtkWidget**)Array)[2], GTK_MESSAGE_INFO, "Success!",
			             "Update word success.");
		else
			Show_message(((GtkWidget**)Array)[2], GTK_MESSAGE_ERROR, "Error!", "Update met error!");
	}
}
    
void on_btn_edit_ok_clicked(GtkButton *button, GtkWidget *wid){
    gtk_widget_destroy(wid);
    }
//<\EDIT FUNCTION>

//<DELETE FUNCTION>

void Show_Delete_Dialog(){
	
	GtkWidget       *window_del;
	GtkWidget *btn_cancel, *btn_ok;
	
	builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
	
    btn_cancel = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete_cancel"));
    btn_ok = GTK_WIDGET(gtk_builder_get_object(builder, "btn_delete_ok"));
    
    
	window_del = GTK_WIDGET(gtk_builder_get_object(builder, "delete_message"));
	g_signal_connect(btn_ok, "clicked", G_CALLBACK(on_btn_delete_ok_clicked), window_del);
    g_signal_connect(btn_cancel, "clicked", G_CALLBACK(on_btn_delete_cancel_clicked), window_del);	
	
	gtk_dialog_run(GTK_DIALOG(window_del));
	gtk_widget_destroy (window_del);
}
void on_btn_delete_ok_clicked(GtkButton *button, GtkWidget *parent){
	char *wordText;
	wordText = (char*)gtk_entry_get_text(GTK_ENTRY(inputEntry));
	  
    printf("%s\n", wordText);
    
    if(btdel(database, wordText) == 0){
      Show_delete_message(parent, GTK_MESSAGE_INFO, "Success", "Delete success!");
      gtk_widget_destroy(parent);
    }
    else{
    Show_delete_message(parent, GTK_MESSAGE_ERROR, "Error", "Delete met error!");
	  gtk_widget_destroy(parent);
	}
    
		  
}

void on_btn_delete_cancel_clicked(GtkButton *button, gpointer *wid){
     gtk_widget_destroy(GTK_WIDGET(wid));	
}

void on_window_main_destroy()
{
    gtk_main_quit();
}

//<\END DELETE>

//<ABOUT>

void showAbout(){
	
	GtkWidget       *window_about;

	builder = gtk_builder_new();
    gtk_builder_add_from_file (builder, "glade/window_main.glade", NULL);
    
	window_about = GTK_WIDGET(gtk_builder_get_object(builder, "about_dialog"));
	gtk_dialog_run(GTK_DIALOG(window_about));
	gtk_widget_destroy(window_about);
}

//<END_ABOUT>

////////////////////////////////////////////////////////////////////////////////////////////

//<SEARCH>
void searchWord() {
	char  word[50], meaning[10000];
	char *check;
	const gchar* input;
	int rsize;

    strcpy(word, (char*)gtk_entry_get_text(GTK_ENTRY(inputEntry)));
	
    displayBuffer = gtk_text_view_get_buffer(GTK_TEXT_VIEW(displayEntry));
	 
	if(bfndky(database, word, (BTint*)&rsize) == QNOKEY){
		strcpy(meaning, "This word isn't database");
	}
	else{
		btsel(database, word, meaning, 10000, &rsize);
	}
	
	FormatedText(meaning);	
}

void FormatedText(char* meaning)
{
    FILE *stream;
    GtkTextIter iter;
    char lineBuffer[2000];
    static int isCreated = 0;

    stream = fmemopen(meaning, strlen(meaning)+1, "r+");

    gtk_text_buffer_set_text(displayBuffer, "", -1);
    gtk_text_buffer_get_start_iter(displayBuffer, &iter);

    if (!isCreated)
    {
        //Create tag table
        gtk_text_buffer_create_tag(displayBuffer, "lmarg15", "left_margin", 15, NULL);
        gtk_text_buffer_create_tag(displayBuffer, "lmarg30", "left_margin", 30, NULL);
        gtk_text_buffer_create_tag(displayBuffer, "lmarg35", "left_margin", 35, NULL);
        gtk_text_buffer_create_tag(displayBuffer, "blue_fg", "foreground", "blue", NULL);
        gtk_text_buffer_create_tag(displayBuffer, "red_fg", "foreground", "red", NULL);
        gtk_text_buffer_create_tag(displayBuffer, "green_fg", "foreground", "green", NULL);
        gtk_text_buffer_create_tag(displayBuffer, "italic", "style", PANGO_STYLE_ITALIC, NULL);
        gtk_text_buffer_create_tag(displayBuffer, "bold", "weight", PANGO_WEIGHT_BOLD, NULL);

        isCreated = 1;
    }

    while (fgets(lineBuffer, 2000, stream) != NULL)
    {
        switch (lineBuffer[0])
        {
        case '@':
            gtk_text_buffer_insert(displayBuffer, &iter, "\n", -1);
            gtk_text_buffer_insert_with_tags_by_name(displayBuffer, &iter, lineBuffer, -1, "bold", "blue_fg",  NULL);
            gtk_text_buffer_insert(displayBuffer, &iter, "\n", -1);
            break;
        case '*':
            gtk_text_buffer_insert_with_tags_by_name(displayBuffer, &iter, lineBuffer, -1, "red_fg", "lmarg15",  NULL);
            break;
        case '!':
            lineBuffer[0] = '>';
            gtk_text_buffer_insert_with_tags_by_name(displayBuffer, &iter, lineBuffer, -1, "green_fg", "lmarg15",  NULL);
            break;
        case '>':
            lineBuffer[0] = '>';
            gtk_text_buffer_insert_with_tags_by_name(displayBuffer, &iter, lineBuffer, -1, "green_fg", "lmarg15",  NULL);
            break;
        case '-':
            gtk_text_buffer_insert_with_tags_by_name(displayBuffer, &iter, lineBuffer, -1, "lmarg30",  NULL);
            break;
        case '=':
            lineBuffer[0] = '+';
            gtk_text_buffer_insert_with_tags_by_name(displayBuffer, &iter, lineBuffer, -1, "italic", "lmarg35",  NULL);
            break;
        case '+':
            lineBuffer[0] = '+';
            gtk_text_buffer_insert_with_tags_by_name(displayBuffer, &iter, lineBuffer, -1, "italic", "lmarg35",  NULL);
            break;
        default:
            gtk_text_buffer_insert(displayBuffer, &iter, lineBuffer, -1);
            break;
        }
    }
}

//<\END SEARCH>

//<EDIT>

//<\END EDIT>

////////////////////////////////////////////////////////////////////////////////////////////

void Show_message(GtkWidget * parent , GtkMessageType type,  char * mms, char * content) {
	GtkWidget *mdialog;
	mdialog = gtk_message_dialog_new(GTK_WINDOW(parent),
	                                 GTK_DIALOG_DESTROY_WITH_PARENT,
	                                 type,
	                                 GTK_BUTTONS_OK,
	                                 "%s", mms);
	gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(mdialog), "%s",  content);
	gtk_dialog_run(GTK_DIALOG(mdialog));
	gtk_widget_destroy(mdialog);
}

void Show_delete_message(GtkWidget * parent , GtkMessageType type,  char * mms, char * content) {
	GtkWidget *mdialog;
	mdialog = gtk_message_dialog_new(GTK_WINDOW(parent),
	                                 GTK_DIALOG_MODAL,
	                                 type,
	                                 GTK_BUTTONS_OK,
	                                 "%s", mms);
	gtk_message_dialog_format_secondary_text(GTK_MESSAGE_DIALOG(mdialog), "%s",  content);
	gtk_dialog_run(GTK_DIALOG(mdialog));
	gtk_widget_destroy(mdialog);
}

/////////////////////////////////////////////////////////////////////////////////////////////////


void soundex(char *name, char *sound)
  //char   * name;
 // char   * sound;  /* supply at least 5 pre-allocated characters */
{
  char   * in = name,
         * out = sound;
  char   prev = '\0';
  int    is_first = 1;
  char   code;

  while (*in != '\0' && out - sound < 4)
  {
    switch(tolower(*in))
    {
      case 'b':
      case 'f':
      case 'p':
      case 'v':
        code = '1';
      break;

      case 'c':
      case 'g':
      case 'j':
      case 'k':
      case 'q':
      case 's':
      case 'x':
      case 'z':
        code = '2';
      break;

      case 'd':
      case 't':
        code = '3';
      break;

      case 'l':
        code = '4';
      break;

      case 'm':
      case 'n':
        code = '5';
      break;

      case 'r':
        code = '6';
      break;

      /* includes "aehiouwy", punctuation, numbers and control chars */
      default:
        code = 0;
      break;
    }

    if (is_first)
    {
      *out++ = toupper(*in);
      is_first = 0;
    }
    else if (code && prev != code)
      *out++ = code;
    prev = code;

    in++;
  }

  while (out - sound < 4)
    *out++ = '0';

  *out = '\0';

}

gboolean on_key_press (GtkEntry * entry, GdkEventKey *event, gpointer user_data)
{
      SuggestData * t_data = user_data;
      char sound_word[30], sound_key[30];
      int i=1;
      int re_val, k = 0, m = 0;
      BTint  val;

      //func to set the position before the first node in the tree to traverse tree
      btpos(database, 1);

      int * no_match = &(t_data->no_match);
      char key[100], c;
      char tc[10] = "";
      const gchar * entry_text;
      int * cnt_tab = &t_data->cnt_tab;
      
      //list for drop down
      GtkListStore *ls = gtk_list_store_new(1, G_TYPE_STRING);
      GtkTreeIter iter;
      GtkEntryCompletion *completion = gtk_entry_completion_new(); //create completion dropdown. search gtk_entry_completion

     
      //get text in the entry
      entry_text = gtk_entry_get_text(GTK_ENTRY(entry));
      strcpy(t_data->word, entry_text);
      
      //handle the auto_completion, select suggested words and set to the entry
      if(event->keyval == GDK_KEY_Tab){
          //printf("tab key pressed\n");
          if(strcmp(t_data->suggest[0], "") != 0){
			  //De quay vong ve cai dau tien
              if(*cnt_tab >= 6){
                  *cnt_tab = 0;
              }

              if(strcmp(t_data->suggest[*cnt_tab], "") == 0){
                  *cnt_tab = 0;
              }

              (*cnt_tab)++;

              if(*cnt_tab < 6 && strcmp(t_data->suggest[*cnt_tab - 1], "") != 0 ){
              //printf("word found: %s\n", t_data->suggest[*cnt_tab - 1]);
              gchar m_word[30]; //lay trong suggest truyen vao entry
              strcpy(m_word, t_data->suggest[*cnt_tab - 1]);
              gtk_entry_set_text (entry, m_word);
              gtk_editable_set_position(GTK_EDITABLE(entry), -1);
              }

              strcpy(t_data->word, t_data->suggest[*cnt_tab - 1]);
              soundex(t_data->word, sound_word);
              //printf("t_data->word: %s\n", t_data->word);

          }
         
       while(i==1){

              //func to get to the next key in the tree, return the key of the node (the word) to the string variable key passed in
              re_val = bnxtky(database, key, &val);

              if(re_val==QNOKEY){
                  printf("no more keys\n");
                  i=0;
              }
              else if(re_val!=0){
                  printf("error occured while select next\n");
                  i=0;
              }
              else {
                  
                  if(strlen(t_data->word) >= 3 && strncmp(t_data->word, key, strlen(t_data->word) - 2) == 0){
                    if(m<10){
                      soundex(key, sound_key);
                      if(strcmp(sound_word, sound_key) == 0){
                        //add to list, k++
                        //printf("key: %s\nsoundex key: %s\n", key, sound_key);
                        gtk_list_store_append(ls, &iter);
                        gtk_list_store_set(ls, &iter, 0, key, -1);
                        m++;
                      }
                    }
                  }
                  else{
                      if(m<10){
                        soundex(key, sound_key);
                        if(strcmp(sound_word, sound_key) == 0){
                        //add to list, k++
                        gtk_list_store_append(ls, &iter);
                        gtk_list_store_set(ls, &iter, 0, key, -1);
                        m++;
                        }
                      }
                  }
              }
        }
      
      gtk_entry_completion_set_model(completion, GTK_TREE_MODEL(ls));
      gtk_entry_completion_set_match_func(completion, (GtkEntryCompletionMatchFunc)func, NULL, NULL);
      gtk_entry_set_completion(GTK_ENTRY(entry), completion);
      gtk_entry_completion_set_text_column(completion, 0);
      
      return TRUE;
      }

      
      c = gdk_keyval_name (event->keyval)[0];

      if(c>='a'&& c<='z'){
            //printf("key pressed: %c\n",c);
            for(int j =0; j<5; j++){
            strcpy(t_data->suggest[j], "");
          }
          tc[0] = c;
          strcat(t_data->word, tc);
          soundex(t_data->word, sound_word);
        
        //printf("s: %s\n",t_data->word);

        i = 1;
        m = 0;
        //traverse the tree to find match words for autocomplete and soundex
        while(i==1){
            re_val = bnxtky(database, key, &val);

            if(re_val==47){
                //printf("no more keys\n");
                i=0;
            }
            else if(re_val!=0){
                printf("error occured while select next\n");
                i=0;
            }
            else {
                if(strncmp(t_data->word, key, strlen(t_data->word)) == 0){

                    if(k<5){
                        strcpy(t_data->suggest[k], key);   
                        //printf("suggest %d: %s\n", k, t_data->suggest[k]);
                        k++;
                    }
                }
                if(strlen(t_data->word) >= 3 && strncmp(t_data->word, key, strlen(t_data->word) - 2) == 0){
                  if(m<10){
                    soundex(key, sound_key);
                      if(strcmp(sound_word, sound_key) == 0){
                          //add to list, k++
                          gtk_list_store_append(ls, &iter);
                          gtk_list_store_set(ls, &iter, 0, key, -1);
                          m++;
                      }
                  }
                } 
                else{
                    if(m<10){
                      soundex(key, sound_key);
                        if(strcmp(sound_word, sound_key) == 0){
                          //add to list, k++
                          gtk_list_store_append(ls, &iter);
                          gtk_list_store_set(ls, &iter, 0, key, -1);
                          m++;
                        }
                    }
                }
            }
        }
        gtk_entry_completion_set_model(completion, GTK_TREE_MODEL(ls));
        gtk_entry_completion_set_match_func(completion, (GtkEntryCompletionMatchFunc)func, NULL, NULL);
        gtk_entry_set_completion(GTK_ENTRY(entry), completion);
        gtk_entry_completion_set_text_column(completion, 0);
  }
  
    return FALSE;
}

//func used when user delete a word, when the next key pressed, the current text in the entry will be taken, not the text before delete
gboolean delete_entry(GtkEntry * entry, GdkEventKey * event, gpointer user_data){
      const gchar * entry_word;
      GtkListStore *ls = gtk_list_store_new(1, G_TYPE_STRING);
      GtkTreeIter iter;
      GtkEntryCompletion *completion = gtk_entry_completion_new();

      entry_word =  gtk_entry_get_text(GTK_ENTRY(entry));
      //printf("entry word: %s\n", entry_word);

}

gboolean func(GtkEntryCompletion *completion, const gchar *key, GtkTreeIter *iter, gpointer user_data) {
    
    return TRUE;
}

