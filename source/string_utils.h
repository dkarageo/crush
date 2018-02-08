/**
 * string_utils.h
 *
 * Created by Dimitrios Karageorgiou, AEM: 8420
 * for course: Operating Systems.
 *
 * Electrical and Computers Engineering Department,
 * Aristotle University of Thessaloniki, Greeece,
 * 2017-2018.
 *
 * This header declares routines useful for common string manipulations.
 *
 * Functions defined in string_utils.h:
 *  -char *strtok_multi_solid(char **str, const char *delim, const char *solid_delim)
 *  -int str_char_occurencies(char *str, const char token)
 *  -int str_str_occurencies(char *str, const char *token)
 *  -void str_char_replace(char *str, char c, char new)
 *  -char *str_trim(char *str, char c)
 *
 * Version: 0.1
 */

#ifndef __string_utils_h__
#define __string_utils_h__


/**
 * Splits a string into substrings using a delimiter, avoiding splitting
 * inside substrings marked as solid.
 *
 * It searches the string pointed by '*str' and finds the first substring that
 * starts from a character sequence different than 'delim' and ends upon
 * 'delim' or the end of '*str' string ('\0'). If 'delim' is found inside
 * a block marked as solid, it is skipped and search continues.
 *
 * A solid block, is a block that starts with 'solid_delim' and ends upon a
 * matching 'solid_delim'. If no ending 'solid_delim' is found for a solid
 * block, returned values are undefined.
 *
 * The content of '*str' is updated, so that it points after the returned
 * substring (the first byte after the delimiting bytes). Also each occurence
 * of 'delim' inside '*str', is replaced by null bytes ('\0').
 *
 * Subsequent calls to strtok_multi_solid() effectively allows for splitting
 * an entire string.
 *
 * WARNING: 'str' reference and '*str' string gets altered. On final substring
 * returned value on '*str' should expected to be NULL.
 *
 * Parameters:
 *  -str : A pointer to a pointer to a string, to be searched for the occurence
 *          of 'delim'.
 *  -delim : A string to be used as a delimiter.
 *  -solid_delim : A string used as starting and ending border of a solid block.
 *
 * Returns:
 *  A reference to the first character of the substring beggining after all
 *  occurencies of 'delim'. If no such substring is found, eg. when an empty
 *  string or a string containing only delimiters is given, or when a NULL
 *  reference is given, it returns NULL.
 */
char *strtok_multi_solid(char **str, const char *delim, const char *solid_delim);

/**
 * Counts the occurencies of a char into a string.
 *
 * Parameters:
 *  -str : The string to be searched.
 *  -token : The character whose occurencies in str should be counted.
 *
 * Returns:
 *  Number of occurencies of token into str.
 */
int str_char_occurencies(char *str, const char token);

/**
 * Counts the occurencies of a string token into a string.
 *
 * The characters at position where a previous match of the token occured,
 * are never used again. For example if the token is the string "aa"
 * and str is "bbaaa", only one occurence of "aa" is counted, since after
 * first match, the first two 'a' are not used again on lookup.
 *
 * Parameters:
 *  -str : The string to be searched.
 *  -token : The string whose occurencies in str should be counted.
 *
 * Returns:
 *  Number of occurencies of token in str.
 */
int str_str_occurencies(char *str, const char *token);

/**
 * Replaces all occurencies of a char in a string, by a new one.
 *
 * Parameters:
 *  -str : String whose contents to be altered.
 *  -c : Old character to be replaced by new.
 *  -new : The new character to replace all occurences of c.
 */
void str_char_replace(char *str, char c, char new);

/**
 * Creates a new string by the contents of the given one, with all occurences
 * of given character on both edges trimmed.
 *
 * WARNING: A new string is allocated. The operation is not done in-place. A
 * call to free() should follow this function when the returned string is no more
 * needed.
 *
 * Parameters:
 *  -str : String to be trimmed.
 *  -c : Character whose occurencies to be removed from both edges of str.
 *
 * Returns:
 *  A reference to the new string object.
 */
char *str_trim(char *str, char c);

#endif
