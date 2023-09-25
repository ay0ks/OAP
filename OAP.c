#include <stdarg.h>
#include <stdbool.h>
#include <stddef.h>
#include <stdint.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <malloc.h>
#include "OAP.h"
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

OL_ctor(OAP_option) {
    OAP_option *option = malloc(sizeof(OAP_option));
    option->keys = OL_new(OAP_option_keys);
    return option;
}

OL_dtor(OAP_option) {
    void **option_keys_iterator = OAP_option_keys_iter(it->keys);
    for (size_t i = 0; i != OAP_option_keys_len(it->keys); i++) {
        if (option_keys_iterator[i] != NULL) {
            free(option_keys_iterator[i]);
        }
    }
    free(option_keys_iterator);
    OL_del(OAP_option_keys, it->keys);
    if (OL_is_not_null_ptr(it->id))
        free(it->id);
    if (OL_is_not_null_ptr(it->description))
        free(it->description);
    if (OL_is_not_null_ptr(it->value_description))
        free(it->value_description);
    if (OL_is_not_null_ptr(it->value_brief))
        free(it->value_brief);
    if (OL_is_not_null_ptr(it->value))
        free(it->value);
    free(it);
}

OL_getter(OAP_option, keys, OAP_option_keys*) {
    return it->keys;
}

OL_setter(OAP_option, id, char*) {
    if (OL_is_null_ptr(id)) return;
    
    it->id = malloc(strlen(id)+1);
    strcpy(it->id, strdup(id));
}

OL_setter(OAP_option, description, char*) {
    if (OL_is_null_ptr(description)) return;
    
    it->description = malloc(strlen(description)+1);
    strcpy(it->description, strdup(description));
}

OL_setter(OAP_option, value_description, char*) {
    if (OL_is_null_ptr(value_description)) return;
    
    it->value_description = malloc(strlen(value_description)+1);
    strcpy(it->value_description, strdup(value_description));
}

OL_setter(OAP_option, value_brief, char*) {
    if (OL_is_null_ptr(value_brief)) return;
    
    it->value_brief = malloc(strlen(value_brief)+1);
    strcpy(it->value_brief, strdup(value_brief));
}

OL_setter(OAP_option, value_default, char*) {
    if (OL_is_null_ptr(value_default)) return;
    
    it->value_default = malloc(strlen(value_default)+1);
    strcpy(it->value_default, strdup(value_default));
}

OL_setter(OAP_option, value, char*) {
    if (OL_is_null_ptr(value)) return;
    
    it->value = malloc(strlen(value)+1);
    strcpy(it->value, strdup(value));
}

OL_setter(OAP_option, required, bool) {
    it->required = required;
}

OL_setter(OAP_option, value_required, bool) {
    it->value_required = value_required;
}

OL_setter(OAP_option, hidden, bool) {
    it->hidden = hidden;
}

typedef struct {
    char *id;
    char *value_description;
    char *value_brief;
    char *value_default;
    char *value;
    bool required;
} OAP_argument;

OL_ctor(OAP_argument) {
    OAP_argument *argument = malloc(sizeof(OAP_argument));
    return argument;
}

OL_setter(OAP_argument, id, char*) {
    if (OL_is_null_ptr(id)) return;
    
    it->id = malloc(strlen(id)+1);
    strcpy(it->id, strdup(id));
}

OL_setter(OAP_argument, value_default, char*) {
    if (OL_is_null_ptr(value_default)) return;
    
    it->value_default = malloc(strlen(value_default)+1);
    strcpy(it->value_default, strdup(value_default));
}

OL_setter(OAP_argument, value, char*) {
    if (OL_is_null_ptr(value)) return;
    
    it->value = malloc(strlen(value)+1);
    strcpy(it->value, strdup(value));
}

OL_setter(OAP_argument, value_description, char*) {
    if (OL_is_null_ptr(value_description)) return;
    
    it->value_description = malloc(strlen(value_description)+1);
    strcpy(it->value_description, strdup(value_description));
}

OL_setter(OAP_argument, value_brief, char*) {
    if (OL_is_null_ptr(value_brief)) return;
    
    it->value_brief = malloc(strlen(value_brief)+1);
    strcpy(it->value_brief, strdup(value_brief));
}

OL_setter(OAP_argument, required, bool) {
    it->required = required;
}

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

OL_setter(OAP, program, char*) {
    if (OL_is_not_null_ptr(program)) {
        it->program = malloc(strlen(program)+1);
        strcpy(it->program, program);
    }
}

OL_setter(OAP, program_name, char*) {
    if (OL_is_not_null_ptr(program_name)) {
        it->program_name = malloc(strlen(program_name)+1);
        strcpy(it->program_name, program_name);
    }
}

OL_setter(OAP, program_version, char*) {
    if (OL_is_null_ptr(program_version)) return;
    
    it->program_version = malloc(strlen(program_version)+1);
    strcpy(it->program_version, strdup(program_version));
}

OL_setter(OAP, program_description, char*) {
    if (OL_is_not_null_ptr(program_description)) {
        it->program_description = malloc(strlen(program_description)+1);
        strcpy(it->program_description, program_description);
    }
}

OL_ctor(OAP, char* program_name, char *program_version, char* program_description) {
    OAP *parser = malloc(sizeof(OAP));
    OAP_set_program_name(parser, program_name);
    OAP_set_program_version(parser, program_version);
    OAP_set_program_description(parser, program_description);
    parser->options = OL_new(OAP_options, 64);
    parser->arguments = OL_new(OAP_arguments, 64);
    return parser;
}

OL_dtor(OAP) {
    OAP_options_node **options_iterator = OAP_options_iter(it->options);
    for (size_t i = 0; i != OAP_options_len(it->options); i++) {
        if (options_iterator[i] != NULL) {
            OAP_options_node *option_node = options_iterator[i];
            OAP_option *option = option_node->val;
            OL_del(OAP_option, option);
            //free(option_node->key);
            //free(option_node);
        }
    }
    //free(options_iterator);
    if (OL_is_not_null_ptr(it->program_name))
        free(it->program_name);
    if (OL_is_not_null_ptr(it->program_description))
        free(it->program_description);
    OL_del(OAP_options, it->options);
    free(it);
}

size_t _OAP_longest_string_size(size_t count, char **args) {
    size_t n = 0;
    for (size_t i = 0; i != count; i++) {
        size_t s = strlen(args[i]);
        if (s > n) n = s;
    }
    return n;
}

void OAP_addopt(OAP *parser, char *description, char *value_brief, char *value_description, char *value_default, char *id, bool required, bool value_required, bool hidden, size_t key_count, ...) {
    va_list args;
    char **option_keys = calloc(key_count, sizeof(char*));
    va_start(args, key_count);
    for (size_t i = 0; i != key_count; i++) {
        const char *option_key;
        if ((option_key = va_arg(args, const char*)) != NULL) {
            option_keys[i] = calloc(strlen(option_key)+1, sizeof(char));
            strcpy(option_keys[i], strdup(option_key));
        }
    }
    va_end(args);
    OAP_option *option = OL_new(OAP_option);
    OAP_option_set_id(option, id);
    OAP_option_set_description(option, description);
    OAP_option_set_value_brief(option, value_brief);
    OAP_option_set_value_description(option, value_description);
    OAP_option_set_value_default(option, value_default);
    OAP_option_set_required(option, required);
    OAP_option_set_value_required(option, value_required);
    OAP_option_set_hidden(option, hidden);
    for (size_t i = 0; i != key_count; i++)
        OAP_option_keys_push(OAP_option_get_keys(option), option_keys[i]);
    OAP_options_set(parser->options, id, option);
    free(option_keys);
}

void OAP_addarg(OAP *parser, char *value_brief, char *value_description, char *value_default, char *id, bool required) {
    OAP_argument *argument = OL_new(OAP_argument);
    OAP_argument_set_id(argument, id);
    OAP_argument_set_value_brief(argument, value_brief);
    OAP_argument_set_value_description(argument, value_description);
    OAP_argument_set_value_default(argument, value_default);
    OAP_argument_set_required(argument, required);
    OAP_arguments_set(parser->arguments, id, argument);
}

char *OAP_getopt(OAP *parser, char *id) {
    return ((OAP_option*)OAP_options_get(parser->options, id))->value;
}

void OAP_getarg(OAP *parser, char *id) {

}

bool OAP_is(char *value, char *needle) {
    if (OL_is_not_null_ptr(value) && strncmp(value, needle, strlen(needle)) == 0)
        return true;
    return false;
}

void OAP_version(OAP *parser) {
    if (OL_is_not_null_ptr(parser->program_name))
        printf("%s", parser->program_name);
    else
        printf("%s", parser->program);
    if (OL_is_not_null_ptr(parser->program_version))
        printf(" version %s\n", parser->program_version);
    else
        printf(" version unknown\n");
    exit(0);
}

void OAP_usage(OAP *parser, OAP_options_node **options_iterator, OAP_arguments_node **arguments_iterator) {
    printf("Usage: ");
    printf("%s", parser->program_name);
    for (size_t i = 0; i != OAP_options_len(parser->options); i++) {
        if (options_iterator[i] != NULL) {
            OAP_options_node *option_node = options_iterator[i];
            OAP_option *option = option_node->val;
            OAP_option_keys *option_keys = option->keys;
            void **option_keys_iterator = OAP_option_keys_iter(option_keys);
            size_t option_keys_count = OAP_option_keys_len(option_keys);
            printf(" ");
            if (!option->required)
                printf("[");
            for (size_t j = 0; j != option_keys_count; j++) {
                char *option_key_value = option_keys_iterator[j];
                char *option_key = malloc(strlen(option_key_value)+2);
                sprintf(option_key, "/%s", option_key_value);
                if (j+1 == option_keys_count)
                    printf("%s", option_key);
                else
                    printf("%s|", option_key);
            }
            if (OL_is_not_null_ptr(option->value_brief))
                printf(":%s", option->value_brief);
            if (!option->required)
                printf("]");
        }
    }
    for (size_t i = 0; i != OAP_arguments_len(parser->arguments); i++) {
        if (arguments_iterator[i] != NULL) {
            OAP_arguments_node *argument_node = arguments_iterator[i];
            OAP_argument *argument = argument_node->val;
            printf(" ");
            if (!argument->required)
                printf("[");
            printf("%s",  argument->value_brief);
            if (!argument->required)
                printf("]");
        }
    }
    printf("\n");
    printf("Use /Help for details.\n");
    exit(0);
}

void OAP_help(OAP *parser, OAP_options_node **options_iterator, OAP_arguments_node **arguments_iterator) {
    printf("Program: ");
    if (OL_is_not_null_ptr(parser->program_name)) {
        printf("%s", parser->program_name);
        if (OL_is_not_null_ptr(parser->program_description))
            printf(": %s\n", parser->program_description);
        else
            printf(": no description.\n");
    } else {
        printf("%s", parser->program);
        if (OL_is_not_null_ptr(parser->program_description))
            printf(": %s\n", parser->program_description);
        else
            printf(": no description.\n");
    }
    printf("\n");
    printf("Options:\n");
    for (size_t i = 0; i != OAP_options_len(parser->options); i++) {
        if (options_iterator[i] != NULL) {
            OAP_options_node *option_node = options_iterator[i];
            OAP_option *option = option_node->val;
            OAP_option_keys *option_keys = option->keys;
            void **option_keys_iterator = OAP_option_keys_iter(option_keys);
            printf("%*c", 2, ' ');
            size_t option_keys_count = OAP_option_keys_len(option_keys);
            for (size_t j = 0; j != option_keys_count; j++) {
                char *option_key_value = option_keys_iterator[j];
                char *option_key = malloc(strlen(option_key_value)+2);
                sprintf(option_key, "/%s", option_key_value);
                if (j+1 == option_keys_count)
                    printf("%s", option_key);
                else
                    printf("%s, ", option_key);
            }
            if (option->required)
                printf(" (required)");
            printf("\n");
            printf("%*cId: %s\n", 4, ' ', option->id);
            printf("%*cValue:", 4, ' ');
            if (OL_is_not_null_ptr(option->value_brief))
                printf(" %s", option->value_brief);
            if (option->value_required) {
                printf(" (required)");
            } else {
                printf(" (optional)");
                if (OL_is_not_null_ptr(option->value_default))
                    printf(" (default: %s)", option->value_default);
                else if (OL_is_not_null_ptr(option->value_brief))
                    printf(" (default: nothing)");
            }
            printf("\n");
            if (OL_is_not_null_ptr(option->value_description))
                printf("%*c%s\n", 6, ' ', option->value_description);
            else
                printf("%*cNo description\n", 6, ' ');
            printf("\n");
            if (OL_is_not_null_ptr(option->description))
                printf("%*c%s\n", 4, ' ', option->description);
            else
                printf("%*cOption has no description.", 4, ' ');
            printf("\n");
        }
    }
    exit(0);
}

void OAP_option_parse(OAP *parser, char *argument, OAP_options_node **options_iterator, OAP_arguments_node **arguments_iterator) {
    OAP_option *option = NULL;
    for (size_t i = 0; i != OAP_options_len(parser->options); i++) {
        if (options_iterator[i] != NULL) {
            OAP_options_node *option_node = options_iterator[i];
            OAP_option *maybe_option = option_node->val;
            OAP_option_keys *maybe_option_keys = maybe_option->keys;
            void **maybe_option_keys_iterator = OAP_option_keys_iter(maybe_option_keys);
            for (size_t j = 0; j != OAP_option_keys_len(maybe_option_keys); j++) {
                char *_maybe_option_key = maybe_option_keys_iterator[j];
                char *maybe_option_key = malloc(strlen(_maybe_option_key)+2);
                sprintf(maybe_option_key, "/%s", _maybe_option_key);
                char *argument_key = strdup(argument);
                char *argument_value;
                if ((argument_value = strchr(argument_key, ':')) != NULL)
                    *argument_value = 0;
                if (strncmp(argument_key, maybe_option_key, strlen(argument_key)) == 0) {
                    char *option_key_value;
                    if (OL_is_not_null_ptr(maybe_option->value_brief)) {
                        if (OL_is_not_null_ptr((option_key_value = strstr(argument, ":")))) {
                            option_key_value++;
                            OAP_option_set_value(maybe_option, option_key_value);
                        } else {
                            if (maybe_option->required) {
                                fprintf(stderr, "%s has required value which was never provided\n", argument_key);
                                fprintf(stderr, "Specify it using %s:%s\n", argument_key, maybe_option->value_brief);
                                fprintf(stderr, "Use /Help for details.\n");
                                exit(1);
                            }
                        }
                    } else {
                        OAP_option_set_value(maybe_option, "true");
                    }
                    
                    OAP_options_del(parser->options, option_node->key);
                    OAP_options_set(parser->options, option_node->key, maybe_option);
                }
            }
        }
    }
}

void OAP_parse(OAP *parser, int argument_count, char **argument_vector) {
    OAP_options_node **options_iterator = OAP_options_iter(parser->options);
    OAP_arguments_node **arguments_iterator = OAP_arguments_iter(parser->arguments);
    OAP_set_program(parser, argument_vector[0]);    
    if (!OAP_options_has(parser->options, "help"))
        OAP_addopt(parser, "Print the help message.", NULL, NULL, NULL, "help", false, false, false, 3, "?", "H", "Help");  
    if (!OAP_options_has(parser->options, "usage"))
        OAP_addopt(parser, "Get usage information.", NULL, NULL, NULL, "usage", false, false, false, 2, "U", "Usage");    
    if (!OAP_options_has(parser->options, "version"))
        OAP_addopt(parser, "Get version information.", NULL, NULL, NULL, "version", false, false, false, 2, "V", "Version");    
    if (argument_count > 1) {
        for (int i = 1; i != argument_count; i++) {
            OAP_option_parse(parser, argument_vector[i], options_iterator, arguments_iterator);
        }
    } else if (OAP_options_len(parser->options) > 0) {
        for (size_t i = 0; i != OAP_options_len(parser->options); i++) {
            if (options_iterator[i] != NULL) {
                OAP_options_node *option_node = options_iterator[i];
                OAP_option *option = option_node->val;
                if (option->required) {
                    fprintf(stderr, "%s is required\n", option->id);
                    OAP_usage(parser, options_iterator, arguments_iterator);
                }
            }
        }
    }
    if (OAP_is(OAP_getopt(parser, "usage"), "true"))
        OAP_usage(parser, options_iterator, arguments_iterator);
    else if (OAP_is(OAP_getopt(parser, "help"), "true"))
        OAP_help(parser, options_iterator, arguments_iterator);
    else if (OAP_is(OAP_getopt(parser, "version"), "true"))
        OAP_version(parser);
}