// this made by nemo
// I think I'm going to define this software License as "Free"Software.
// I dedicate this for my/our FREEDOM future.
// 2024/2/4
#define __USE_GTK
#include "mynetwork.h"
#include <pthread.h>
#include <gtk/gtk.h>


typedef struct myAppWidgets{
    GtkWidget *window;
    GtkWidget *listbox;
    GtkWidget *label;
    GtkWidget *vbox;
} myAppWidgets_t;
void initGTKfunctions(int &argc, char** &argv, myAppWidgets_t &wdg);
void list_selected(GtkListBox *list, GtkListBoxRow * row, GtkLabel *label);

struct anlParam{
    const char* buf;
    int len;
    myAppWidgets_t wdg;
};
void* procAnalyzeP(void* param);


int main(int argc, char* argv[]){
    pthread_t th;
    myAppWidgets_t wdg;
    anlParam myparam;
    
    myparam.buf = "hoge";
    myparam.len = sizeof(myparam.buf);

    initGTKfunctions(argc, argv, wdg);
    myparam.wdg = wdg;

    pthread_create(&th, NULL, procAnalyzeP, &myparam);

    gtk_main();
    g_print("gtk quit");
    return 0;
}

void initGTKfunctions(int &argc, char** &argv, myAppWidgets_t &wdg){
    gtk_init(&argc, &argv);
    
    wdg.window  = gtk_window_new(GTK_WINDOW_TOPLEVEL);

    gtk_window_set_title            (GTK_WINDOW(wdg.window),
                                     "ListBox");
    gtk_window_set_default_size     (GTK_WINDOW(wdg.window), 320, 240);
    gtk_window_set_position         (GTK_WINDOW(wdg.window), GTK_WIN_POS_CENTER);
    gtk_container_set_border_width  (GTK_CONTAINER(wdg.window), 15);
    
    wdg.listbox = gtk_list_box_new      ();
    gtk_list_box_insert             (GTK_LIST_BOX(wdg.listbox),
                                     gtk_label_new("Windows"),  -1);
    gtk_list_box_insert             (GTK_LIST_BOX(wdg.listbox),
                                     gtk_label_new("macOS"),    -1);
    gtk_list_box_insert             (GTK_LIST_BOX(wdg.listbox),
                                     gtk_label_new("Ubuntu"),   -1);
    gtk_list_box_insert             (GTK_LIST_BOX(wdg.listbox),
                                     gtk_label_new("Fedora"),   -1);
    
    wdg.label   = gtk_label_new         (NULL);
    
    wdg.vbox    = gtk_box_new           (GTK_ORIENTATION_VERTICAL, 15);
    gtk_box_pack_start              (GTK_BOX(wdg.vbox), wdg.listbox, 1, 1, 0);
    gtk_box_pack_end                (GTK_BOX(wdg.vbox), wdg.label,   0, 0, 0);
    gtk_container_add               (GTK_CONTAINER(wdg.window), wdg.vbox);
    
    //g_signal_connect                (listbox,   "row_selected", G_CALLBACK(list_selected), label);
    g_signal_connect                (wdg.window,    "destroy", G_CALLBACK(gtk_main_quit), NULL);
    
    gtk_widget_show_all             (wdg.window);
}
/*
void list_selected(GtkListBox *list, GtkListBoxRow * row, GtkLabel *label)
{
    GtkWidget *child = gtk_bin_get_child(GTK_BIN(row));
    g_print("selected label: %s\n", gtk_label_get_text(GTK_LABEL(child)));
    gtk_label_set_text(label, gtk_label_get_text(GTK_LABEL(child)));
}*/

void* procAnalyzeP(void* param){
    struct anlParam *prm = (anlParam *)param;
    g_print(prm->buf);

    int soc;
    int readPnum;
    u_char buf[65535];
    soc = socket(PF_PACKET,SOCK_RAW,htons(ETH_P_IP));
    while(1){
        readPnum = read(soc,buf,sizeof(buf));
        if(readPnum > 0){
            AnalyzeIPpacketGTK(buf);
        }else{
            g_print("buf is Null");
        }
    gtk_label_set_text((GtkLabel*)prm->wdg.label, (const char*)buf);
	g_print("\n");
    }
}

#undef __USE_GTK