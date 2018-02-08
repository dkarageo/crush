/**
 * string_utils.c
 *
 * Created by Dimitrios Karageorgiou, AEM: 8420
 * for course: Operating Systems.
 *
 * Electrical and Computers Engineering Department,
 * Aristotle University of Thessaloniki, Greeece,
 * 2017-2018.
 *
 * This header provides an implementation for interface defined in
 * string_utils.h header.
 *
 * Version: 0.1
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <assert.h>
#include "string_utils.h"


char *strtok_multi_solid(char **str, const char *delim, const char *solid_delim)
{
    // printf("To split by '%s' avoiding '%s': '%s'\n", delim, solid_delim, *str);

    // If a NULL reference provided, just return NULL.
    if (!str || !(*str)) {
        *str = NULL;
        return NULL;
    }
    // If an empty string is provided, just return NULL.
    if (strlen(*str) < 1) {
        *str = NULL;
        return NULL;
    }
    // If no delimiter is provided, return the original reference and point
    // *str to NULL.
    if (!delim && strlen(delim) > 0) {
        char *ret_val = *str;
        *str = NULL;
        return ret_val;
    }

    // Skip all beggining delimiters and replace them by '\0'.
    while(*str != NULL && strstr(*str, delim) == *str) {
        for (int i = 0; i < (int) strlen(delim); i++) {
            *(*str) = '\0';
            (*str)++;
        }
    }

    // printf("To split after trimming: '%s'\n", *str);

    char *starting_pos = *str;  // The beggining of the unsearched part of *str.
    char *ending_pos = NULL;    // The beggining of ending delimiter, if found.
    int found = 0;

    // Find the first occurence of 'delim' that doesn't belong to a solid block.
    while(!found) {
        ending_pos = strstr(starting_pos, delim);
        if (!ending_pos) break;  // No delim found, so nothing to split.

        //printf("From delimiter '%s': '%s'\n", delim, ending_pos);

        // Create a copy of the substring between initial trimmed position
        // of the given string (*str) and beggining of delimiter, so to
        // check if both edges of solid blocks are contained.
        int sub_length = ending_pos - *str;
        char *substr = calloc(sub_length+1, sizeof(char));
        strncpy(substr, *str, sub_length);

        // If even number of solid_delim is contained in substring, then no
        // solid block exists around this delimiter.
        if ((str_str_occurencies(substr, solid_delim) % 2) == 0) found = 1;
        else starting_pos = ending_pos + strlen(solid_delim);

        free(substr);
    }

    // Save trimmed starting position of the string, in order to return it.
    char *temp = *str;
    // Write the beggining of delimiter to *str.
    *str = ending_pos;

    // printf("Remaining (before clear): '%s'\n", *str);

    // If a delimiter found, set it to '\0' and point *str past it.
    if (found) {
        for (int i = 0; i < (int) strlen(delim); i++) {
            *(*str) = '\0';
            (*str)++;
        }
    }

    // printf("Splitted: '%s' Remaining: '%s'\n", temp, *str);

    return temp;
}


int str_char_occurencies(char *str, const char token)
{
    int occurs = 0;
    char *cur_pos = str;

    while ((cur_pos = strchr(cur_pos, (int) token)) != NULL) {
        cur_pos++;
        occurs++;
    }

    return occurs;
}


int str_str_occurencies(char *str, const char *token)
{
    int occurs = 0;
    char *cur_pos = str;

    while((cur_pos = strstr(cur_pos, token)) != NULL) {
        occurs++;
        cur_pos += strlen(token);
    }

    return occurs;
}


void str_char_replace(char *str, char c, char new)
{
    for (int i = 0; i < (int) strlen(str); i++) {
        if (str[i] == c) str[i] = new;
    }
}

char *str_trim(char *str, char c)
{
    size_t length = strlen(str);

    unsigned front = 0;
    unsigned back = length;

    for (;front < length; front++) {
        if (str[front] != c) break;
    }

    for (;back > front; back--) {
        if (str[back-1] != c) break;
    }

    char *trimmed = (char *) calloc((back - front) + 1, sizeof(char));
    strncpy(trimmed, str+front, back-front);

    return trimmed;
}
