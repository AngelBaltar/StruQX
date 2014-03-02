/* StruQX - SQL XML DATABASE
 * CommandLine.c
 * Copyright (C)  Angel Baltar Diaz
 *
 * This program is free software: you can redistribute it and/or
 * modify it under the terms of the GNU General Public
 * License as published by the Free Software Foundation; either
 * version 3 of the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public
 * License along with this program.  If not, see
 * <http://www.gnu.org/licenses/>.
 */
#include <stdlib.h>
#include <stdio.h>
#include "CommandLine/CommandLine.h"
#include "StruQXErrorCodes.h"
#include "Debug/StruQXDebug.h"
#include "MessagePrinters/HelpPrinter.h"


static struct option long_options[] =
{
		{"version",  no_argument, 0, 'v'},
		{"help",  no_argument, 0, 'h'},
#ifdef DEBUG_MODE
		{"debug",  no_argument,0,'d'},
#endif
		{0, 0, 0, 0}
};

static char* command_line_descs['z'];

/**
 * initializes the command line options descriptions
 */
void init_command_descriptions(void)
{
#ifdef DEBUG_MODE
     command_line_descs['d']="Set the debug mode to execute code into DEBUG macro.";
#endif
     command_line_descs['v']="Show the version of the programm.";
     command_line_descs['h']="Print the general command line help.";
}

/**
 * 
 * @return the defined command line options 
 */
struct option* getCommandLineOptions(void)
{
    return long_options;
}

/**
 * 
 * @return the descriptions for the command line options 
 */
char ** getCommandLineDescriptions(void)
{
    return command_line_descs;
}


/**
 * parses command line arguments
 * @param argc argc from the commandline
 * @param argv argv from the commandline
 */
void parse_arguments(int argc, char **argv)
{
       
	int c;
        const char* opts="hvd";
	init_command_descriptions();
        for(;;){

		int option_index = 0;
		c = getopt_long (argc, argv,opts,long_options, &option_index);

		/* Detect the end of the options. */
		if (c == -1){
			break;
		}

		switch (c)
		{
		case 0:
			/* If this option set a flag, do nothing else now. */
			if (long_options[option_index].flag != 0){
				break;
			}
			printf ("option %s", long_options[option_index].name);
			if (optarg){
				printf (" with arg %s", optarg);
			}
			printf ("\n");
			break;
		case 'h':
			print_command_line_help();
			exit(SUCCESS_CODE);
			break;
		case 'v':
                        print_version();
			exit(SUCCESS_CODE);
			break;
#ifdef DEBUG_MODE
		case 'd':
			//set debug on
                        enable_debug();
                        DEBUG(
                                printf("DEBUG MODE IS SETTED\n");
                                )
			break;
#endif
		case '?':
			print_command_line_help();
			/* getopt_long already printed an error message. */
			exit(ERR_CMD_ARGUMENTS_ERROR);
			break;

		default:
			print_command_line_help();
			exit(SUCCESS_CODE);
		}
	}
	if(optind+1<argc) //More than one input file
	{
		exit(ERR_CMD_ARGUMENTS_ERROR);
	}
}
