/*
 * AT-SPI 2 Examples. Simple AT.
 *
 * Copyright (c) 2011 Alejandro Leiva <aleiva@emergya.com>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License
 * as published by the Free Software Foundation; either version 2
 * of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * Author: Alejandro Leiva <aleiva@emergya.com>
 *
 * Ported from CSPI examples.
 *
 */

#include <stdlib.h>
#include <stdio.h>

#include "atspi/atspi.h"

// Device listeners prototypes
gboolean
device_listener_test (const AtspiDeviceEvent *stroke, void *user_data);

void
device_listener_test_destroy (void *data);

// Event listeners prototypes
void
event_listener_generic (const AtspiEvent *event);

void
event_listener_generic_destroy (void *data);


int
main (int argc, char **argv)
{

	int atspi_status;
	int i, j;
	gint n_desktops, n_apps;
	AtspiAccessible *desktop, *application;
	gchar *desktop_name, *application_name;
	GError **error;

	int *user_data;
	AtspiDeviceListener *test_listener;

    AtspiEventListener *generic_listener;

	atspi_status = atspi_init ();
	printf ("Starting [atspi status = %i]\n", atspi_status);

	// Create device listeners
	test_listener = atspi_device_listener_new (&device_listener_test, user_data, device_listener_test_destroy);

	// Register device listeners
	atspi_register_keystroke_listener (test_listener, NULL, NULL, ATSPI_KEY_PRESSED,  ATSPI_KEYLISTENER_ALL_WINDOWS | ATSPI_KEYLISTENER_CANCONSUME, error);

	// Create event listeners
    generic_listener = atspi_event_listener_new_simple (event_listener_generic, event_listener_generic_destroy);
    atspi_event_listener_register (generic_listener, "object:", error);

	n_desktops = atspi_get_desktop_count ();
	//GArray *a_desktops = atspi_get_desktop_list ();

	for (i = 0; i < n_desktops; i++)
	{

		desktop = atspi_get_desktop (i);		
		desktop_name = atspi_accessible_get_name (desktop, error);
		printf ("Desktop [%i]: %s\n", i, desktop_name);

		n_apps = atspi_accessible_get_child_count(desktop, error);

		for (j = 0; j < n_apps; j++)
		{
			application = atspi_accessible_get_child_at_index (desktop, j, error);
			application_name = atspi_accessible_get_name (application, error);
			printf ("Application [%i]: %s\n", j, application_name);
		}
	}

	atspi_event_main();

	atspi_event_quit();

	atspi_status = atspi_exit ();

	printf ("Stopping atspi2 [status = %i]\n", atspi_status);

	return atspi_status; 
}

gboolean
device_listener_test (const AtspiDeviceEvent *stroke, void *user_data)
{

	printf ("Somebody called me :-/\n");
	return TRUE;
}

void
device_listener_test_destroy (void *data)
{
	printf ("Somebody wants to destroy me :-/\n");
}

void
event_listener_generic (const AtspiEvent *event)
{
    printf ("focus: type = %s\n", event->type);
    // object:children-changed:add
    // source: desktop frame | main
    // application: none
}

void
event_listener_generic_destroy (void *data)
{
    printf ("event_listener_focus_destroy\n");
}
