/* COMPILE USING:  g++ -Wall -pedantic -g -std=c++11 test.cpp graph.cpp `pkg-config --cflags --libs gtk+-3.0` -o fen*/
#include <gtk/gtk.h>
#include "graph.h"

using namespace std;

#define WINDOW_WIDTH  800
#define WINDOW_HEIGHT 600

GtkWidget *window;
GtkWidget *da, *container, *button;

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

   std::vector< std::vector<bool> > grid;  // true => obstacle ; false => libre
} struct_problem ;

static gboolean draw_cb(GtkWidget *widget, cairo_t *cr, gpointer data)
{   
   struct_problem *p = (struct_problem *) data;
   int case_width = 500/((p->n < p->m)?p->m:p->n);

   /* Set color for background */
   cairo_set_source_rgb(cr, 1, 1, 1);
   /* fill in the background color*/
   cairo_paint(cr);

   /* set color for lines */
   cairo_set_source_rgb(cr, 0.2479, 0.3183, 0.67);
   /* set the line width */
   cairo_set_line_width(cr,1);

   /*drawing the lines of the grid*/
   for(int i=0;i<=p->m;i++)
   {
      cairo_move_to(cr, 2+i*case_width,2);
      cairo_line_to(cr, 2+i*case_width,2+case_width*p->n);
      cairo_stroke(cr);   
   }

   for(int i=0;i<=p->n;i++)
   {
      cairo_move_to(cr, 2,2+i*case_width);
      cairo_line_to(cr, 2+p->m*case_width,2+case_width*i);
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
                cairo_rectangle (cr, 3+j*case_width, 3+i*case_width, case_width-2, case_width-2);
                /* stroke the rectangle's path with the chosen color so it's actually visible */
                cairo_fill(cr);
            }   
        }
    }

   /* draw start circle */
   cairo_set_source_rgb(cr, 0., 0., 0.);
   cairo_set_line_width(cr,2);
   cairo_arc(cr, 2+p->yStart*case_width, 2+p->xStart*case_width, 0.25*case_width, 0, 2*G_PI);
   cairo_fill(cr);
   cairo_arc(cr, 2+p->yGoal*case_width, 2+p->xGoal*case_width, 0.25*case_width, 0, 2*G_PI);
   cairo_fill(cr);
   switch(p->dirStart)
   {
    case 0:
        cairo_move_to(cr,2+p->yStart*case_width-0.1*case_width, 2+p->xStart*case_width-0.25*case_width);
        cairo_line_to(cr,2+p->yStart*case_width, 2+p->xStart*case_width-0.4*case_width);
        cairo_line_to(cr,2+p->yStart*case_width+0.1*case_width, 2+p->xStart*case_width-0.25*case_width);
        cairo_close_path(cr);
        cairo_fill(cr);  
        break;
    case 1:
        cairo_move_to(cr,2+p->yStart*case_width+0.25*case_width, 2+p->xStart*case_width-0.1*case_width);
        cairo_line_to(cr,2+p->yStart*case_width+case_width*0.4, 2+p->xStart*case_width);
        cairo_line_to(cr,2+p->yStart*case_width+0.25*case_width, 2+p->xStart*case_width+0.1*case_width);
        cairo_close_path(cr);
        cairo_fill(cr);  
        break;
    case 2: 
        cairo_move_to(cr,2+p->yStart*case_width-0.1*case_width, 2+p->xStart*case_width+0.25*case_width);
        cairo_line_to(cr,2+p->yStart*case_width, 2+p->xStart*case_width+0.4*case_width);
        cairo_line_to(cr,2+p->yStart*case_width+0.1*case_width, 2+p->xStart*case_width+0.25*case_width);
        cairo_close_path(cr);
        cairo_fill(cr);  
        break;
    case 3:
        cairo_move_to(cr,2+p->yStart*case_width-0.25*case_width, 2+p->xStart*case_width-0.1*case_width);
        cairo_line_to(cr,2+p->yStart*case_width-case_width*0.4, 2+p->xStart*case_width);
        cairo_line_to(cr,2+p->yStart*case_width-0.25*case_width, 2+p->xStart*case_width+0.1*case_width);
        cairo_close_path(cr);
        cairo_fill(cr);  
        break;
    default:
        cairo_fill(cr);  
   }

   return FALSE;
}

static gboolean clicked(GtkWidget *widget, gpointer data)
{
    gtk_widget_set_visible(da,TRUE);
    return TRUE;
}

int main (int argc, char *argv[])
{
   graph solver = graph();
   solver.readProblems("testGen");
   struct_problem sp;
   sp.xStart = solver.getProblems()[0].xStart;
   sp.yStart = solver.getProblems()[0].yStart;
   sp.xGoal = solver.getProblems()[0].xGoal;
   sp.yGoal = solver.getProblems()[0].yGoal;
   sp.dirStart = solver.getProblems()[0].dirStart;
   sp.n = solver.getProblems()[0].n; 
   sp.m = solver.getProblems()[0].m; 
   sp.grid = solver.getProblems()[0].grid; 

   gtk_init (&argc, &argv);

   window = gtk_window_new (GTK_WINDOW_TOPLEVEL);
   gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
   g_signal_connect (window, "destroy", G_CALLBACK (gtk_main_quit), NULL);

   container = gtk_fixed_new();
   gtk_container_add(GTK_CONTAINER(window), container);
   gtk_widget_set_size_request (container, WINDOW_WIDTH, WINDOW_HEIGHT);

   da = gtk_drawing_area_new();
   gtk_widget_set_size_request (da, 550, 550);
   g_signal_connect (da, "draw", G_CALLBACK(draw_cb),  &sp);

   button = gtk_button_new_with_label("Solution");
   gtk_widget_set_size_request (button, 90, 20);
   g_signal_connect (button, "clicked", G_CALLBACK(clicked),  NULL);

   gtk_fixed_put(GTK_FIXED(container), da, 30, 30);
   gtk_fixed_put(GTK_FIXED(container), button, 600, 50);
   gtk_widget_show(container);
   gtk_widget_show(button);
   gtk_widget_show (window);

   gtk_main ();

   return 0;
}