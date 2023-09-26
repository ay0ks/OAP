/* Copyright (c) 2023, Dimitriy "ay0ks" <dimitriy@darkcat.cloud>
|  All rights reserved.
|  This source code is licensed under the GNU General Public License v3.0 license found in the
|  LICENSE file in the root directory of this source tree. 
*/

#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include "OL/ARRAY.h"
#include "OL/MAP.h"
#include "OL/CLASS.h"
#include "OL/ASSERT.h"

OL_array_new(OAP_option_keys, char*);

typedef struct {
    char *id;
    char *description;
    OAP_option_keys *keys;
    char *value_description;
    char *value_brief;
    char *value_default;
    char *value;
    bool required;
    bool value_required;
    bool hidden;
} OAP_option;

OL_ctor(OAP_option);
OL_dtor(OAP_option);
OL_getter(OAP_option, keys, OAP_option_keys*);
OL_setter(OAP_option, id, char*);
OL_setter(OAP_option, description, char*);
OL_setter(OAP_option, value_description, char*);
OL_setter(OAP_option, value_brief, char*);
OL_setter(OAP_option, value_default, char*);
OL_setter(OAP_option, value, char*);
OL_setter(OAP_option, required, bool);
OL_setter(OAP_option, value_required, bool);
OL_setter(OAP_option, hidden, bool);

typedef struct {
    char *id;
    char *value_description;
    char *value_brief;
    char *value_default;
    char *value;
    bool required;
} OAP_argument;

OL_ctor(OAP_argument);
OL_setter(OAP_argument, id, char*);
OL_setter(OAP_argument, value_default, char*);
OL_setter(OAP_argument, value, char*);
OL_setter(OAP_argument, value_description, char*);
OL_setter(OAP_argument, value_brief, char*);
OL_setter(OAP_argument, required, bool);

OL_map_new(OAP_options, OAP_option);
OL_map_new(OAP_arguments, OAP_argument);

typedef struct {
    char *program;
    char *program_name;
    char *program_version;
    char *program_description;
    OAP_options *options;
    OAP_arguments *arguments;
} OAP;

OL_ctor(OAP, char* program_name, char *program_version, char* program_description);
OL_dtor(OAP);
OL_setter(OAP, program, char*);
OL_setter(OAP, program_name, char*);
OL_setter(OAP, program_version, char*);
OL_setter(OAP, program_description, char*);

void OAP_addopt(OAP *parser, char *description, char *value_brief, char *value_description, char *value_default, char *id, bool required, bool value_required, bool hidden, size_t key_count, ...);
void OAP_addarg(OAP *parser, char *value_brief, char *value_description, char *value_default, char *id, bool required);
char *OAP_getopt(OAP *parser, char *id);
void OAP_getarg(OAP *parser, char *id);
bool OAP_is(char *value, char *needle);
void OAP_version(OAP *parser);
void OAP_usage(OAP *parser, OAP_options_node **options_iterator, OAP_arguments_node **arguments_iterator);
void OAP_help(OAP *parser, OAP_options_node **options_iterator, OAP_arguments_node **arguments_iterator);
void OAP_option_parse(OAP *parser, char *argument, OAP_options_node **options_iterator, OAP_arguments_node **arguments_iterator);
void OAP_parse(OAP *parser, int argument_count, char **argument_vector);
