#include <libdazeus.h>
#include <stdlib.h>
#include <stdio.h>
#include "megahal.h"
#include <string.h>

int main(int argc, char *argv[]) {
	if(argc != 2) {
		fprintf(stderr, "Usage: %s socket\n", argv[0]);
		return 1;
	}
	dazeus *d = libdazeus_create();
	if(!d) {
		fprintf(stderr, "Failed to create DaZeus object.\n");
		return 2;
	}
	if(!libdazeus_open(d, argv[1])) {
		fprintf(stderr, "Error connecting to DaZeus: %s\n", libdazeus_error(d));
		libdazeus_close(d);
		return 3;
	}

	if(!libdazeus_subscribe(d, "PRIVMSG")) {
		fprintf(stderr, "Error subscribing to PRIVMSG: %s\n", libdazeus_error(d));
		libdazeus_close(d);
		return 4;
	}

	megahal_setnobanner();
	megahal_setdirectory(".");

	megahal_initialize();
	printf("Megahal> %s\n", megahal_initial_greeting());

	dazeus_event *e;
	// Wait indefinitely for an event
	while((e = libdazeus_handle_event(d, -1))) {
		if(strcmp(e->event, "PRIVMSG") != 0) {
			fprintf(stderr, "Unexpected event %s\n", e->event);
			libdazeus_event_free(e);
			continue;
		}
		// parameters: network sender destination message
		char *input = e->parameters->next->next->next->value;
		if(strncmp(input, "}megahal ", 9) == 0) {
			char *network = e->parameters->value;
			char *destination = e->parameters->next->next->value;
			char *who = e->parameters->next->value;
			input += 9;
			printf("%s> %s\n", who, input);
			const char * const output = megahal_do_reply(input, 1);
			printf("Megahal> %s\n", output);

			// TODO: hack, see if we were the destination
			char *reply_to = destination;
			if(strncmp(reply_to, "#", 1) != 0 && strncmp(reply_to, "&", 1) != 0) {
				reply_to = who;
			}

			libdazeus_message(d, network, reply_to, output);
		} else if(strncmp(input, "}", 1) != 0) {
			megahal_learn_no_reply(input, 1);
		}
		megahal_command("#SAVE");
	}

	megahal_cleanup();
	libdazeus_close(d);
	return 0;
}

