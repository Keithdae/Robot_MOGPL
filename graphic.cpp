/* COMPILE USING:  g++ -Wall -pedantic -g -std=c++11 graphic.cpp graph.cpp `pkg-config --cflags --libs gtk+-3.0` -o fen*/
#include <gtk/gtk.h>
#include "graph.h"

using namespace std;

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

typedef struct {
   int xStart;
   int yStart;
   int xGoal;
   int yGoal;

   int dirStart;
   /* Nord  => 0
   *  Est   => 1
   *  Sud   => 2
   *  Ouest => 3
   */

   int n; // Nombre de lignes du probleme
   int m; // Nombre de colonnes du probleme 
   string chaine_res;

   std::vector< std::vector<bool> > grid;  // true => obstacle ; false => libre
} struct_problem ;

struct_problem sp;

static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data)
{   
   struct_problem *p = &sp;
   int case_width = 500/((p->n < p->m)?p->m:p->n);

   /* Set color for background */
   cairo_set_source_rgb(cr, 1, 1, 1);
   /* fill in the background color*/
   cairo_paint(cr);

   /* set color for lines */
   cairo_set_source_rgb(cr, 0.2479, 0.3183, 0.67);
   /* set the line width */
   cairo_set_line_width(cr,1);

   /*drawing the lines of the grid (columns)*/
   for(int i=0;i<=p->m;i++)
   {
      cairo_move_to(cr, 25+i*case_width,25);
      cairo_line_to(cr, 25+i*case_width,25+case_width*p->n);
      cairo_stroke(cr);   
   }

   /*drawing the lines of the grid (rows)*/
   for(int i=0;i<=p->n;i++)
   {
      cairo_move_to(cr, 25,25+i*case_width);
      cairo_line_to(cr, 25+p->m*case_width,25+case_width*i);
      cairo_stroke(cr);   
   }
     
   /* set color for rectangle */
   cairo_set_source_rgb(cr, 0.4508, 0.9044, 0.92);
   /* set the line width */
   cairo_set_line_width(cr,1);
   /*drawing the obstacles*/
   for(int i=0;i<p->n;i++)
   {
        for(int j=0;j<p->m;j++)
        {
            if(p->grid[i][j]==1)
            {
                /* draw the rectangle */
                cairo_rectangle (cr, 26+j*case_width, 26+i*case_width, case_width-2, case_width-2);
                /* stroke the rectangle's path with the chosen color so it's actually visible */
                cairo_fill(cr);
            }   
        }
    }

   /* draw start circle */
   cairo_set_source_rgb(cr, 0., 0., 0.);
   cairo_set_line_width(cr,2);
   cairo_arc(cr, 25+p->yStart*case_width, 25+p->xStart*case_width, 0.25*case_width, 0, 2*G_PI);
   cairo_fill(cr);
   /* draw goal circle */
   cairo_arc(cr, 25+p->yGoal*case_width, 25+p->xGoal*case_width, 0.25*case_width, 0, 2*G_PI);
   cairo_fill(cr);
   /* draw start direction arrow */
   switch(p->dirStart)
   {
    case 0:
        cairo_move_to(cr,25+p->yStart*case_width-0.1*case_width, 25+p->xStart*case_width-0.25*case_width);
        cairo_line_to(cr,25+p->yStart*case_width, 25+p->xStart*case_width-0.4*case_width);
        cairo_line_to(cr,25+p->yStart*case_width+0.1*case_width, 25+p->xStart*case_width-0.25*case_width);
        cairo_close_path(cr);
        cairo_fill(cr);  
        break;
    case 1:
        cairo_move_to(cr,25+p->yStart*case_width+0.25*case_width, 25+p->xStart*case_width-0.1*case_width);
        cairo_line_to(cr,25+p->yStart*case_width+case_width*0.4, 25+p->xStart*case_width);
        cairo_line_to(cr,25+p->yStart*case_width+0.25*case_width, 25+p->xStart*case_width+0.1*case_width);
        cairo_close_path(cr);
        cairo_fill(cr);  
        break;
    case 2: 
        cairo_move_to(cr,25+p->yStart*case_width-0.1*case_width, 25+p->xStart*case_width+0.25*case_width);
        cairo_line_to(cr,25+p->yStart*case_width, 25+p->xStart*case_width+0.4*case_width);
        cairo_line_to(cr,25+p->yStart*case_width+0.1*case_width, 25+p->xStart*case_width+0.25*case_width);
        cairo_close_path(cr);
        cairo_fill(cr);  
        break;
    case 3:
        cairo_move_to(cr,25+p->yStart*case_width-0.25*case_width, 25+p->xStart*case_width-0.1*case_width);
        cairo_line_to(cr,25+p->yStart*case_width-case_width*0.4, 25+p->xStart*case_width);
        cairo_line_to(cr,25+p->yStart*case_width-0.25*case_width, 25+p->xStart*case_width+0.1*case_width);
        cairo_close_path(cr);
        cairo_fill(cr);  
        break;
    default:
        cairo_fill(cr);  
   }

   /* draw path */
   ifstream res(p->chaine_res);
   if(!res.is_open())
   {
    cerr << "Échec de l'ouverture du fichier!" << endl; 
   }
   else{
    string mot;
    res >> mot;
    int x = p->xStart, x1;
    int y = p->yStart, y1;
    int dir = p->dirStart;
    cairo_set_source_rgb(cr, 0., 0., 0.);
    cairo_set_line_width(cr,4);
    while ( x != p->xGoal || y != p->yGoal) 
    { 
        res >> mot;
        if(mot == "D")
        {
            dir = (dir + 1) % 4;
        }
        else if (mot == "G")
        {
            dir = (dir - 1 + 4) % 4;
        }
        else if(mot == "a1")
        {
            if(dir == 0)
            {
                x1 = x - 1; y1 = y;
            }
            else if (dir == 1)
            {
                x1 = x; y1 = y + 1;
            }
            else if (dir == 2)
            {
                x1 = x + 1; y1 = y;
            }
            else if (dir == 3)
            {
                x1 = x; y1 = y - 1;
            }
            cairo_move_to(cr, 25+y*case_width,25+x*case_width);
            cairo_line_to(cr, 25+y1*case_width,25+x1*case_width);
            cairo_stroke(cr);
            x = x1; y = y1;
        }
        else if(mot == "a2")
        {
            if(dir == 0)
            {
                x1 = x - 2; y1 = y;
            }
            else if (dir == 1)
            {
                x1 = x; y1 = y + 2;
            }
            else if (dir == 2)
            {
                x1 = x + 2; y1 = y;
            }
            else if (dir == 3)
            {
                x1 = x; y1 = y - 2;
            }
            cairo_move_to(cr, 25+y*case_width,25+x*case_width);
            cairo_line_to(cr, 25+y1*case_width,25+x1*case_width);
            cairo_stroke(cr);
            x = x1; y = y1;
        }
        else if (mot == "a3")
        {
            if(dir == 0)
            {
                x1 = x - 3; y1 = y;
            }
            else if (dir == 1)
            {
                x1 = x; y1 = y + 3;
            }
            else if (dir == 2)
            {
                x1 = x + 3; y1 = y;
            }
            else if (dir == 3)
            {
                x1 = x; y1 = y - 3;
            }
            cairo_move_to(cr, 25+y*case_width,25+x*case_width);
            cairo_line_to(cr, 25+y1*case_width,25+x1*case_width);
            cairo_stroke(cr);
            x = x1; y = y1;
        }
    } 
    res.close();
    }
   return FALSE;
}

void solution_window(){
    graph solver = graph();
    solver.readProblems("test");
    sp.xStart = solver.getProblems()[0].xStart;
    sp.yStart = solver.getProblems()[0].yStart;
    sp.xGoal = solver.getProblems()[0].xGoal;
    sp.yGoal = solver.getProblems()[0].yGoal;
    sp.dirStart = solver.getProblems()[0].dirStart;
    sp.n = solver.getProblems()[0].n; 
    sp.m = solver.getProblems()[0].m; 
    sp.chaine_res = "testResults";
    sp.grid = solver.getProblems()[0].grid; 

    GtkWidget *window;
    GtkWidget *da, *container;

    window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window), "La balade du Robot...");
    gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
    g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    container = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window), container);
    gtk_widget_set_size_request (container, WINDOW_WIDTH, WINDOW_HEIGHT);

    da = gtk_drawing_area_new();
    gtk_widget_set_size_request (da, 550, 550);
    g_signal_connect (da, "draw", G_CALLBACK(draw_cb), NULL);

    gtk_fixed_put(GTK_FIXED(container), da, 30, 30);
    gtk_widget_show(container);
    gtk_widget_show(da);
    gtk_widget_show (window);
}

static gboolean click(GtkWidget *button,GdkEventButton *event,gpointer data){
    GtkWidget* p = (GtkWidget*) data;
    gtk_widget_set_visible(p,FALSE);
    solution_window();
    return FALSE;
}

void first_window(){
    GtkWidget *window1;
    GtkWidget *container1, *spinB1, *spinB2, *spinB3, *lab1, *lab2, *lab3, *button;
    window1 = gtk_window_new (GTK_WINDOW_TOPLEVEL);
    gtk_window_set_title(GTK_WINDOW(window1), "La balade du Robot...");
    gtk_window_set_position(GTK_WINDOW(window1), GTK_WIN_POS_CENTER);
    g_signal_connect (window1, "destroy", G_CALLBACK (gtk_main_quit), NULL);

    container1 = gtk_fixed_new();
    gtk_container_add(GTK_CONTAINER(window1), container1);
    gtk_widget_set_size_request (container1, 500, 170);

    GtkAdjustment * ad = gtk_adjustment_new (10,10,50,1,0,0);
    GtkAdjustment * ad1 = gtk_adjustment_new (10,10,50,1,0,0);
    GtkAdjustment * ad2 = gtk_adjustment_new (0,0,500,1,0,0);
    spinB3 = gtk_spin_button_new(ad2,0,0);
    spinB1 = gtk_spin_button_new(ad,0,0);
    spinB2 = gtk_spin_button_new(ad1,0,0);

    lab1 = gtk_label_new ("Nombre de lignes:");
    lab2 = gtk_label_new ("Nombre de colones:");
    lab3 = gtk_label_new ("Nombre d'obstacles:");

    button = gtk_button_new_with_label("Générer grille");
    gtk_widget_set_size_request(button,110,30);

    gtk_fixed_put(GTK_FIXED(container1), lab1, 30, 30);
    gtk_fixed_put(GTK_FIXED(container1), lab2, 180, 30);
    gtk_fixed_put(GTK_FIXED(container1), lab3, 330, 30);
    gtk_fixed_put(GTK_FIXED(container1), spinB1, 40, 60);
    gtk_fixed_put(GTK_FIXED(container1), spinB2, 200, 60);
    gtk_fixed_put(GTK_FIXED(container1), spinB3, 360, 60);
    gtk_fixed_put(GTK_FIXED(container1), button, 195, 120);

    g_signal_connect(button,"button-press-event",G_CALLBACK(click),window1);

    gtk_widget_show_all (window1);
}

int main (int argc, char *argv[])
{
   gtk_init (&argc, &argv);

   first_window();

   gtk_main ();

   return 0;
}
