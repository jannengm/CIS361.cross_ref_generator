#include "llist.h"

enum state_t{ NON_IDENT, IDENT, STRING, COMMENT, LINE_COMMENT };

enum bool_t{ FALSE, TRUE };

typedef enum state_t state_t;
typedef enum bool_t bool_t;

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

    process_file(argv[1], &linked_list);

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

void process_file(const char * path, list_t * linked_list){
    FILE * in_file;
    char ch, prev_ch = '\n', ident[IDENT_LEN];
    state_t state = NON_IDENT;
    int line = 1, index = 0;
    bool_t preprocess = FALSE;
//    node_t * new_node;

    /*Open specified file*/
    in_file = fopen(path, "r");
    if(in_file == NULL){
        fprintf(stderr, "Failed to open file %s\n", path);
        exit(1);
    }

    /*Initialize ch to be the first character of the file*/
    ch = (char)fgetc(in_file);
    if(ch == EOF){
        perror("Empty file");
        fclose(in_file);
        exit(1);
    }

    do {

        /*If the line starts with #, preprocessor instruction */
        if(prev_ch == '\n' && ch == '#'){
            preprocess = TRUE;
        }

        switch(state){
            /*The case where we are not currently reading an identifier, nor a string or comment*/
            case NON_IDENT:
                if( !preprocess && ( ch == '"' || ch == '\'' ) )
                    state = STRING;
                else if(prev_ch == '/' && ch == '*')
                    state = COMMENT;
                else if(prev_ch == '/' && ch == '/')
                    state = LINE_COMMENT;
                else if( is_ident_char(ch) && !isdigit(ch) ){
                    //Start identifier string
                    state = IDENT;
                    ident[index++] = ch;
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
                    //add to identifier
                    ident[index++] = ch;
                }
                else {
                    //end identifier, create new entry
                    state = NON_IDENT;
                    ident[index] = '\0';
//                    printf("%d\t%s\n", line, ident);
                    index = 0;
//                    new_node = init_node(ident, line, NULL);
                    add(linked_list, ident, line);
                }
                break;

            /*The case where we are currently reading a string. Assumes strings are ended
             * on the same line they are created*/
            case STRING:
                if(ch == '"' || ch == '\'')
                    state = NON_IDENT;
                break;

            /*The case where we are currently reading is a block comment*/
            case COMMENT:
                if(prev_ch == '*' && ch == '/')
                    state = NON_IDENT;
                break;

            /*The case where we are reading a single line comment. Assumes '\n' , '\0' ,
             * and EOF are the only characters used to terminate a line*/
            case LINE_COMMENT:
                if(ch == '\n' || ch == '\0')
                    state = NON_IDENT;
                break;
        }

        /*Check not about to overflow max identifier length*/
        if(index == IDENT_LEN){
            fprintf(stderr, "Identifier at line %d over maximum allowed length", line);
        }

        if(ch == '\n') {
            line++;
            preprocess = FALSE;
        }

        prev_ch = ch;

    }while( (ch = (char)fgetc(in_file) ) != EOF );

    fclose(in_file);
}
