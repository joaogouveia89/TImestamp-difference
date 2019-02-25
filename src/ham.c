#include "app.h"

// gcc `pkg-config --cflags gtk+-3.0` -o hours-amount-calculation src/ham.c `pkg-config --libs gtk+-3.0`
GtkWindow *window = NULL;
GtkLabel* result = NULL;


static gboolean deleteEvent( GtkWidget *widget,
                              GdkEvent  *event,
                              gpointer   data )
{
    g_print ("delete event occurred\n");

    return FALSE;
}

static void destroy( GtkWidget *widget,
                     gpointer   data )
{
    gtk_main_quit ();
}

GtkWindow* setupWindow(GtkBuilder* builder){
   /* Connect signal handlers to the constructed widgets. */
   window = GTK_WINDOW(gtk_builder_get_object (builder, APP_NAME));
   gtk_window_set_decorated(window, GTK_WINDOW_TOPLEVEL);
   g_signal_connect (window, "delete-event",
                  G_CALLBACK (deleteEvent), NULL);

    g_signal_connect (window, "destroy",
                  G_CALLBACK (destroy), NULL);
}

int isFieldEmpty(const gchar* data){
  if(data == NULL || data[0] == '\0')
    return 1;
  return 0;
}

int validateData(const gchar* field){
  if(isFieldEmpty(field) == 0 &&
   gCharToInt(field[0]) != -1 &&
   gCharToInt(field[1]) != -1 &&
   timeStrToInt(field) >= 0 && 
   timeStrToInt(field) < 24)
    return 1;
    showErrorDialog(window, "Fields should have only numeric characters");
  return 0;
}


void calculateHours(GtkWidget *widget, gpointer *data){
  TList* list = (TList*) data;
  TList* aux = list;
  if(validateData(gtk_entry_get_text (GTK_ENTRY ((aux->t).hour))) == 0 ||
    validateData(gtk_entry_get_text (GTK_ENTRY ((aux->t).minute))) == 0 ||
    validateData(gtk_entry_get_text (GTK_ENTRY ((aux->t).second))) == 0 ||
    validateData(gtk_entry_get_text (GTK_ENTRY ((aux->next->t).hour))) == 0 ||
    validateData(gtk_entry_get_text (GTK_ENTRY ((aux->next->t).minute))) == 0 ||
    validateData(gtk_entry_get_text (GTK_ENTRY ((aux->next->t).second))) == 0
    ){
    return;
  }

  timestamp ts1, ts2, diff;

  ts1.hour = timeStrToInt(gtk_entry_get_text (GTK_ENTRY ((aux->t).hour)));
  ts1.min = timeStrToInt(gtk_entry_get_text (GTK_ENTRY ((aux->t).minute)));
  ts1.sec = timeStrToInt(gtk_entry_get_text (GTK_ENTRY ((aux->t).second)));

  ts2.hour = timeStrToInt(gtk_entry_get_text (GTK_ENTRY ((aux->next->t).hour)));
  ts2.min = timeStrToInt(gtk_entry_get_text (GTK_ENTRY ((aux->next->t).minute)));
  ts2.sec = timeStrToInt(gtk_entry_get_text (GTK_ENTRY ((aux->next->t).second)));

  diff = difference(ts1, ts2);

  if(result != NULL){
    gchar * labeltxt = g_strdup_printf("Result: %i hours %i minutes %i seconds", diff.hour, diff.min, diff.sec);
    gtk_label_set_text(result, labeltxt);
  }
}


int main(int argc, char *argv[]){
	GObject* calculateButton = NULL;
	GError *error = NULL;
  TList* list = NULL;
  timestampFields ts1;
  timestampFields ts2;

	gtk_init(&argc, &argv);

	GtkBuilder* builder = gtk_builder_new();

	/* Construct a GtkBuilder instance and load our UI description */
	if (gtk_builder_add_from_file (builder, UI_FILE, &error) == 0){
      g_printerr ("Error loading file: %s\n", error->message);
      g_clear_error (&error);
      return 1;
    }

   window = setupWindow(builder);

   // first two intervals = required
   ts1.hour = gtk_builder_get_object(builder, "hour1entry");
   ts1.minute = gtk_builder_get_object(builder, "min1entry");
   ts1.second = gtk_builder_get_object(builder, "sec1entry");

   ts2.hour = gtk_builder_get_object(builder, "hour2entry");
   ts2.minute = gtk_builder_get_object(builder, "min2entry");
   ts2.second = gtk_builder_get_object(builder, "sec2entry");

   list = addTimestampFields(list, ts1);
   list = addTimestampFields(list, ts2);

   calculateButton = gtk_builder_get_object (builder, "buttonCalculate");
   result = GTK_LABEL(GTK_WIDGET(gtk_builder_get_object(builder, "result")));

   g_signal_connect (calculateButton, "clicked", G_CALLBACK (calculateHours), list);

   gtk_main ();

  return 0;

}