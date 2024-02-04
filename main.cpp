// this made by nemo
// I think I'm going to define this software License as FreeSoftware.
// 2024/2/4
#define __USE_GTK
#include "mynetwork.h"
#include <pthread.h>
#include <gtk/gtk.h>

struct anlParam{
    unsigned char* buf;
    int len;
};
void* procAnalyzeP(void* param);

void initGTKfunctions(int &argc, char** &argv);
void list_selected(GtkListBox *list, GtkListBoxRow * row, GtkLabel *label);


int main(int argc, char* argv[]){
    pthread_t th;
    anlParam myparam;
    

    initGTKfunctions(argc, argv);
    pthread_create(&th, NULL, procAnalyzeP, NULL);

    gtk_main();
    g_print("gtk quit");
    return 0;
}

void* procAnalyzeP(void* param){
    int soc;
    int readSize;
    u_char buf[65535];
    soc = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_IP));
    while(1){
        readSize = read(soc,buf,sizeof(buf));
        if(readSize > 0){
            AnalyzeIPpacketGTK(buf);
        }else{
            g_print("buf is Null");
        }
	g_print("\n");
    }
}

void initGTKfunctions(int &argc, char** &argv){
    GtkWidget *window;
    GtkWidget *listbox;
    GtkWidget *label;
    GtkWidget *vbox;
    
    gtk_init(&argc, &argv);
    
    window  = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title            (GTK_WINDOW(window),
                                     "ListBox");
    gtk_window_set_default_size     (GTK_WINDOW(window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width  (GTK_CONTAINER(window), 15);
    
    listbox = gtk_list_box_new      ();
    gtk_list_box_insert             (GTK_LIST_BOX(listbox),
                                     gtk_label_new("Windows"),  -1);
    gtk_list_box_insert             (GTK_LIST_BOX(listbox),
                                     gtk_label_new("macOS"),    -1);
    gtk_list_box_insert             (GTK_LIST_BOX(listbox),
                                     gtk_label_new("Ubuntu"),   -1);
    gtk_list_box_insert             (GTK_LIST_BOX(listbox),
                                     gtk_label_new("Fedora"),   -1);
    
    label   = gtk_label_new         (NULL);
    
    vbox    = gtk_box_new           (GTK_ORIENTATION_VERTICAL, 15);
    gtk_box_pack_start              (GTK_BOX(vbox), listbox, 1, 1, 0);
    gtk_box_pack_end                (GTK_BOX(vbox), label,   0, 0, 0);
    gtk_container_add               (GTK_CONTAINER(window), vbox);
    
    g_signal_connect                (listbox,   "row_selected", G_CALLBACK(list_selected), label);
    g_signal_connect                (window,    "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (window);
}
void list_selected(GtkListBox *list, GtkListBoxRow * row, GtkLabel *label)
{
    GtkWidget *child = gtk_bin_get_child(GTK_BIN(row));
    g_print("selected label: %s\n", gtk_label_get_text(GTK_LABEL(child)));
    gtk_label_set_text(label, gtk_label_get_text(GTK_LABEL(child)));
}

#undef __USE_GTK