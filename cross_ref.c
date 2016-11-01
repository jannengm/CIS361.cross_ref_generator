#include "llist.h"

/*This enum is to designate the state of input of a file. The tyoe
 * of the current "word" being read in is one of the following:
 *
 *  IDENT   The current word is an identifier
 *  STRING  The current word is within a string or character literal
 *  COMMENT The current word is within a multi-line block comment
 *  LINE_COMMENT    The current word is part of a single line comment
 *  NON_IDENT   The current word falls into non of the above categories
 *
 *  Where a "word" is any sequence of characters, including whitespace,
 *  delimited by a transition from one state to another*/
enum state_t{ NON_IDENT, IDENT, STRING, COMMENT, LINE_COMMENT };

/*A simple boolean enum*/
enum bool_t{ FALSE, TRUE };

/*Typedefs*/
typedef enum state_t state_t;
typedef enum bool_t bool_t;

/*Function prototypes*/
int is_ident_char(char ch);
void process_file(const char * path, list_t * linked_list);

int main(int argc, char* argv[]){
    list_t linked_list;
    init_list(&linked_list);

    /*Check for correct number of arguments*/
    if(argc != 2){
        fprintf(stderr, "Usage: [%s] [path to file]\n", argv[0]);
        exit(1);
    }

    /*Process the input file*/
    process_file(argv[1], &linked_list);

    /*Print the contents of the linked list to stdout*/
    print_list(&linked_list);

    /*Clean up and exit*/
    free_list(&linked_list);
    return 0;
}

/*Checks if the passed character is a valid identifier character or not.
 * Returns 1 if true, else 0*/
int is_ident_char(char ch){
    if(isalnum(ch) || ch == '_')
        return 1;
    else
        return 0;
}

/*Takes as arguments a string containing the path to an input file and
 * a pointer to a linked list used to store identifiers. Reads through
 * the input file character by character and stores all identifiers in
 * the provided linked list as well as the line numbers in which those
 * identifiers appear. The processing of identifiers is modeled as a
 * finite state machine using the states described in enum state_t*/
void process_file(const char * path, list_t * linked_list){
    /*The file to read input from*/
    FILE * in_file;

    /*Keeps track of the two most recently read characters*/
    char ch;
    char prev_ch = '\n';

    /*Identifiers are built character by character while the input is
     * in the IDENT state*/
    char ident[IDENT_LEN];

    /*Keeps track of the current line # of the input file*/
    int line = 1;

    /*Used to iterate through the ident[] array and add characters
     * to the end*/
    int index = 0;

    /*The input starts in the NON_IDENT state*/
    state_t state = NON_IDENT;

    /*Flag to designate whether or not the current line is a preprocessor
     * directive. The STRING state behaves differently if true*/
    bool_t preprocess = FALSE;

    /*Open specified file*/
    in_file = fopen(path, "r");
    if(in_file == NULL){
        fprintf(stderr, "Failed to open file %s\n", path);
        free_list(linked_list);
        exit(1);
    }

    /*Initialize ch to be the first character of the file*/
    ch = (char)fgetc(in_file);

    /*If the file is empty, exit the program*/
    if(ch == EOF){
        fprintf(stderr, "Empty file\n");
        fclose(in_file);
        free_list(linked_list);
        exit(1);
    }

    /*Loop through the file one character at a time until the end of file
     * is reached*/
    do {

        /*If the line starts with #, preprocessor instruction */
        if(prev_ch == '\n' && ch == '#'){
            preprocess = TRUE;
        }

        switch(state){
            /*The case where we are not currently reading an identifier,
             * nor a string or comment*/
            case NON_IDENT:
                if( !preprocess && ( ch == '"' || ch == '\'' ) )
                    state = STRING;
                else if(prev_ch == '/' && ch == '*')
                    state = COMMENT;
                else if(prev_ch == '/' && ch == '/')
                    state = LINE_COMMENT;
                else if( is_ident_char(ch) && !isdigit(ch) ){
                    /*Start building identifier string*/
                    state = IDENT;
                    memset(ident, 0, IDENT_LEN);
                    ident[index++] = ch;
                    /*Check not about to overflow max identifier length*/
                    if(index == IDENT_LEN){
                        fprintf(stderr, "Identifier at line %d over "
                                "maximum allowed length", line);
                    }
                }
                break;

            /*The case where we are currently reading an identifier*/
            case IDENT:
                if( !preprocess && ( ch == '"' || ch == '\'' ) )
                    state = STRING;
                else if(prev_ch == '/' && ch == '*')
                    state = COMMENT;
                else if(prev_ch == '/' && ch == '/')
                    state = LINE_COMMENT;
                else if( is_ident_char(ch) ){
                    /*add the character to identifier*/
                    ident[index++] = ch;
                }
                else {
                    /*end identifier, add it to the linked lister*/
                    state = NON_IDENT;
                    ident[index] = '\0';
                    index = 0;
                    add(linked_list, ident, line);
                }
                break;

            /*The case where we are currently reading a string. Assumes
             * strings are ended on the same line they are created*/
            case STRING:
                if(ch == '"' || ch == '\'')
                    state = NON_IDENT;
                break;

            /*The case where we are currently reading is a block comment*/
            case COMMENT:
                if(prev_ch == '*' && ch == '/')
                    state = NON_IDENT;
                break;

            /*The case where we are reading a single line comment. Assumes '\n' ,
             * '\0' , and EOF are the only characters used to terminate a line*/
            case LINE_COMMENT:
                if(ch == '\n' || ch == '\0')
                    state = NON_IDENT;
                break;
        }

        /*Update the line counter if a newline is encountered*/
        if(ch == '\n') {
            line++;
            preprocess = FALSE;
        }

        prev_ch = ch;

    }while( (ch = (char)fgetc(in_file) ) != EOF );

    fclose(in_file);
}
