#ifndef DIALOGS_H
#define DIALOGS_H

GtkDialogFlags flags;
GtkWidget * dialog;

void showErrorDialog(GtkWindow *window, const gchar* message){
	flags = GTK_DIALOG_MODAL;
    dialog = gtk_message_dialog_new (window,
                                 flags,
                                 GTK_MESSAGE_ERROR,
                                 GTK_BUTTONS_CLOSE,
                                 "%s",
                                 message);
    int response = gtk_dialog_run(GTK_DIALOG(dialog));
    gtk_widget_destroy(dialog);
}
#endif