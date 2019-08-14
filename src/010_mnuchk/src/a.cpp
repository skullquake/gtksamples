#include<gtk/gtk.h>
#include<gdk/gdkkeysyms.h>
void toggle_statusbar(GtkWidget *widget,GtkWidget* statusbar){
	if(gtk_check_menu_item_get_active(GTK_CHECK_MENU_ITEM(widget))){
		gtk_widget_show(statusbar);
	}else{
		gtk_widget_hide(statusbar);
	}
}
GdkPixbuf *create_pixbuf(const gchar* filename){
	GdkPixbuf *pixbuf;
	GError *error=NULL;
	pixbuf=gdk_pixbuf_new_from_file(filename,&error);
	if (!pixbuf){
		fprintf(stderr,"%s\n",error->message);
		g_error_free(error);
	}
	return pixbuf;
}
void print_msg(GtkWidget *widget,gpointer window){
	g_print("Button clicked\n");
}
int main(int argc,char *argv[]){

	GtkWidget *window;
	GtkWidget *vbox;
	GtkWidget *menubar;
	GtkWidget *fileMenu;
	GtkWidget *fileMi;
	GtkWidget *newMi;
	GtkWidget *openMi;
	GtkWidget *quitMi;
	GtkWidget *sep;
	GtkWidget *tog_stat;
	GtkAccelGroup *accel_group=NULL;
	GdkPixbuf *icon;
	GtkWidget *button;
	GtkWidget *halign;

	gtk_init(&argc,&argv);

	window = gtk_window_new(GTK_WINDOW_TOPLEVEL);
	icon=create_pixbuf("../res/a.png");  
	gtk_window_set_icon(GTK_WINDOW(window),icon);
	gtk_window_set_position(GTK_WINDOW(window),GTK_WIN_POS_CENTER);
	gtk_window_set_title(GTK_WINDOW(window),"Some Title");
	gtk_window_set_default_size(GTK_WINDOW(window),320,240);

	vbox=gtk_vbox_new(FALSE,0);
	gtk_container_add(GTK_CONTAINER(window),vbox);
	menubar=gtk_menu_bar_new();
	fileMenu=gtk_menu_new();
	accel_group=gtk_accel_group_new();
	gtk_window_add_accel_group(GTK_WINDOW(window),accel_group);
	fileMi=gtk_menu_item_new_with_mnemonic("_File");
	newMi=gtk_image_menu_item_new_from_stock(GTK_STOCK_NEW,NULL);
	openMi=gtk_image_menu_item_new_from_stock(GTK_STOCK_OPEN,NULL);
	sep=gtk_separator_menu_item_new();
	tog_stat=gtk_check_menu_item_new_with_label("View statusbar");
	gtk_check_menu_item_set_active(GTK_CHECK_MENU_ITEM(tog_stat),TRUE);
	quitMi=gtk_image_menu_item_new_from_stock(GTK_STOCK_QUIT,accel_group);
	gtk_widget_add_accelerator(quitMi,"activate",accel_group,GDK_q,GDK_CONTROL_MASK,GTK_ACCEL_VISIBLE);
	gtk_menu_item_set_submenu(GTK_MENU_ITEM(fileMi),fileMenu);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu),newMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu),openMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu),sep);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu),tog_stat);
	gtk_menu_shell_append(GTK_MENU_SHELL(fileMenu),quitMi);
	gtk_menu_shell_append(GTK_MENU_SHELL(menubar),fileMi);
	gtk_box_pack_start(GTK_BOX(vbox),menubar,FALSE,FALSE,0);


	button=gtk_button_new_with_mnemonic("_Button");
	g_signal_connect(button,"clicked",G_CALLBACK(print_msg),NULL);
	gtk_widget_set_tooltip_text(button, "Button widget");
	halign=gtk_alignment_new(0,0,0,0);
	gtk_container_add(GTK_CONTAINER(halign),button);
	gtk_container_add(GTK_CONTAINER(window),halign);  

	g_signal_connect(G_OBJECT(window),"destroy",G_CALLBACK(gtk_main_quit), NULL);  
	g_signal_connect(G_OBJECT(quitMi), "activate",G_CALLBACK(gtk_main_quit), NULL);

	gtk_widget_show_all(window);
	gtk_main();
	return 0;
}



