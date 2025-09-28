#include <gtk/gtk.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>

GtkWidget *entry_time1_hh, *entry_time1_mm, *entry_time1_ss;
GtkWidget *entry_time2_hh, *entry_time2_mm, *entry_time2_ss;
GtkWidget *label_result;
GtkWidget *combo_choice;
GtkWidget *window, *grid, *button_calculate, *button_clear;
GtkWidget *label_time1, *label_time2, *label_choice;

// Function to perform the calculation
void calculation(int time1[], int time2[], int choice)
{
    if (choice == 1) // Addition
    {
        time1[0] += time2[0];
        time1[1] += time2[1];
        time1[2] += time2[2];

        if (time1[2] >= 60)
        {
            time1[1] += time1[2] / 60;
            time1[2] %= 60;
        }

        if (time1[1] >= 60)
        {
            time1[0] += time1[1] / 60;
            time1[1] %= 60;
        }
    }
    else if (choice == 2) // Subtraction
    {
        time1[0] -= time2[0];
        time1[1] -= time2[1];
        time1[2] -= time2[2];

        if (time1[2] < 0)
        {
            time1[2] += 60;
            time1[1]--;
        }

        if (time1[1] < 0)
        {
            time1[1] += 60;
            time1[0]--;
        }
    }
}

// Function to handle the button click event
void on_calculate_button_clicked(GtkButton *button, gpointer data)
{
    int time1[3], time2[3];
    int choice;

    // Get the input time values from the entry widgets
    time1[0] = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_time1_hh))); // Hours of Time 1
    time1[1] = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_time1_mm))); // Minutes of Time 1
    time1[2] = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_time1_ss))); // Seconds of Time 1

    time2[0] = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_time2_hh))); // Hours of Time 2
    time2[1] = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_time2_mm))); // Minutes of Time 2
    time2[2] = atoi(gtk_editable_get_text(GTK_EDITABLE(entry_time2_ss))); // Seconds of Time 2

    // Get the selected choice (1 or 2 for addition or subtraction)
    // GtkDropDown returns 0-based index; map to 1(Add) or 2(Subtract)
    guint selected = gtk_drop_down_get_selected(GTK_DROP_DOWN(combo_choice));
    choice = (int)selected + 1;

    // Perform the calculation (either addition or subtraction)
    calculation(time1, time2, choice);

    // Display the result in the label
    char result[50];
    snprintf(result, sizeof(result), "Result: %02d:%02d:%02d", time1[0], time1[1], time1[2]);
    gtk_label_set_text(GTK_LABEL(label_result), result);
}

// Function to reset values to default
void on_clear_button_clicked(GtkButton *button)
{
    // Clear all entry fields
    gtk_editable_set_text(GTK_EDITABLE(entry_time1_hh), "");
    gtk_editable_set_text(GTK_EDITABLE(entry_time1_mm), "");
    gtk_editable_set_text(GTK_EDITABLE(entry_time1_ss), "");
    gtk_editable_set_text(GTK_EDITABLE(entry_time2_hh), "");
    gtk_editable_set_text(GTK_EDITABLE(entry_time2_mm), "");
    gtk_editable_set_text(GTK_EDITABLE(entry_time2_ss), "");

    // Reset dropdown to default (Add)
    gtk_drop_down_set_selected(GTK_DROP_DOWN(combo_choice), 0);

    // Reset the result label text
    gtk_label_set_text(GTK_LABEL(label_result), "Result: --:--:--");
}

static void activate(GtkApplication *app, gpointer user_data)
{

    // Create a new application window
    window = gtk_application_window_new(app);
    gtk_window_set_title(GTK_WINDOW(window), "Time Calculator");
    gtk_window_set_default_size(GTK_WINDOW(window), 420, 260);

    // Create a grid layout for the widgets
    grid = gtk_grid_new();
    gtk_grid_set_row_spacing(GTK_GRID(grid), 12);
    gtk_grid_set_column_spacing(GTK_GRID(grid), 12);
    gtk_widget_set_margin_top(grid, 16);
    gtk_widget_set_margin_bottom(grid, 16);
    gtk_widget_set_margin_start(grid, 16);
    gtk_widget_set_margin_end(grid, 16);
    gtk_window_set_child(GTK_WINDOW(window), grid);

    // Label for Time 1
    label_time1 = gtk_label_new("Enter Time 1 (HH MM SS):");
    gtk_grid_attach(GTK_GRID(grid), label_time1, 0, 0, 1, 1);

    // Entry fields for Time 1
    entry_time1_hh = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_time1_hh), "HH");
    gtk_entry_set_input_purpose(GTK_ENTRY(entry_time1_hh), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_max_length(GTK_ENTRY(entry_time1_hh), 3);
    gtk_widget_set_hexpand(entry_time1_hh, TRUE);
    gtk_grid_attach(GTK_GRID(grid), entry_time1_hh, 1, 0, 1, 1);
    entry_time1_mm = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_time1_mm), "MM");
    gtk_entry_set_input_purpose(GTK_ENTRY(entry_time1_mm), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_max_length(GTK_ENTRY(entry_time1_mm), 2);
    gtk_widget_set_hexpand(entry_time1_mm, TRUE);
    gtk_grid_attach(GTK_GRID(grid), entry_time1_mm, 2, 0, 1, 1);
    entry_time1_ss = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_time1_ss), "SS");
    gtk_entry_set_input_purpose(GTK_ENTRY(entry_time1_ss), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_max_length(GTK_ENTRY(entry_time1_ss), 2);
    gtk_widget_set_hexpand(entry_time1_ss, TRUE);
    gtk_grid_attach(GTK_GRID(grid), entry_time1_ss, 3, 0, 1, 1);

    // Label for Time 2
    label_time2 = gtk_label_new("Enter Time 2 (HH MM SS):");
    gtk_grid_attach(GTK_GRID(grid), label_time2, 0, 1, 1, 1);

    // Entry fields for Time 2
    entry_time2_hh = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_time2_hh), "HH");
    gtk_entry_set_input_purpose(GTK_ENTRY(entry_time2_hh), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_max_length(GTK_ENTRY(entry_time2_hh), 3);
    gtk_grid_attach(GTK_GRID(grid), entry_time2_hh, 1, 1, 1, 1);
    entry_time2_mm = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_time2_mm), "MM");
    gtk_entry_set_input_purpose(GTK_ENTRY(entry_time2_mm), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_max_length(GTK_ENTRY(entry_time2_mm), 2);
    gtk_grid_attach(GTK_GRID(grid), entry_time2_mm, 2, 1, 1, 1);
    entry_time2_ss = gtk_entry_new();
    gtk_entry_set_placeholder_text(GTK_ENTRY(entry_time2_ss), "SS");
    gtk_entry_set_input_purpose(GTK_ENTRY(entry_time2_ss), GTK_INPUT_PURPOSE_NUMBER);
    gtk_entry_set_max_length(GTK_ENTRY(entry_time2_ss), 2);
    gtk_grid_attach(GTK_GRID(grid), entry_time2_ss, 3, 1, 1, 1);

    // Label for Choice (Addition/Subtraction)
    label_choice = gtk_label_new("Choose Operation:");
    gtk_grid_attach(GTK_GRID(grid), label_choice, 0, 2, 1, 1);

    // DropDown for addition or subtraction
    const char *choices[] = {"Add", "Subtract", NULL};
    combo_choice = gtk_drop_down_new_from_strings(choices);
    gtk_drop_down_set_selected(GTK_DROP_DOWN(combo_choice), 0); // default to Add
    gtk_grid_attach(GTK_GRID(grid), combo_choice, 1, 2, 2, 1);

    // Button to calculate
    button_calculate = gtk_button_new_with_label("Calculate");
    g_signal_connect(button_calculate, "clicked", G_CALLBACK(on_calculate_button_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_calculate, 0, 3, 4, 1);

    // Button to clear
    button_clear = gtk_button_new_with_label("Clear");
    g_signal_connect(button_clear, "clicked", G_CALLBACK(on_clear_button_clicked), NULL);
    gtk_grid_attach(GTK_GRID(grid), button_clear, 0, 4, 4, 1);

    // Label to display the result (large, centered, spans full width)
    label_result = gtk_label_new("Result: --:--:--");
    gtk_widget_set_hexpand(label_result, TRUE);
    gtk_widget_set_halign(label_result, GTK_ALIGN_CENTER);
    gtk_widget_set_margin_top(label_result, 12);
    gtk_widget_set_margin_bottom(label_result, 12);
    gtk_label_set_xalign(GTK_LABEL(label_result), 0.5);
    gtk_grid_attach(GTK_GRID(grid), label_result, 0, 5, 4, 1);

    // Apply simple CSS to enlarge the result label
    const char *css = ".result-label { font-size: 20px; font-weight: bold; }";
    GtkCssProvider *provider = gtk_css_provider_new();
    gtk_css_provider_load_from_string(provider, css);
    GdkDisplay *display = gdk_display_get_default();
    gtk_style_context_add_provider_for_display(display, GTK_STYLE_PROVIDER(provider), GTK_STYLE_PROVIDER_PRIORITY_APPLICATION);
    g_object_unref(provider);
    gtk_widget_add_css_class(label_result, "result-label");

    // Show the window and its contents
    gtk_window_present(GTK_WINDOW(window));
}

int main(int argc, char *argv[])
{
    GtkApplication *app = gtk_application_new("com.example.timecalc", G_APPLICATION_DEFAULT_FLAGS);
    g_signal_connect(app, "activate", G_CALLBACK(activate), NULL);
    int status = g_application_run(G_APPLICATION(app), argc, argv);
    g_object_unref(app);
    return status;
}
