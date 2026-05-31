#include "types.h"
typedef struct INFORMATION
{
    //MP3 FILE INFO
    char *mp3_fname;
    FILE *fptr_mp3;

    //TEMPORARY FILE
    char *tempmp3_fname;
    FILE *fptr_tempmp3;
} Information;

//FUNCTION DECLARATION OF calling_help
 void calling_help();

 //FUNCTION DECLARATION OF printing_default
 void printing_default();

//FUNCTION DECLARATION OF read_and_validation
 status read_and_validate_args(int argc,char *argv[],Information *Info);

//FUNCTION DECLARATION OF view_the_data
 status view_the_data(Information *Info);

//FUNCTION DECLARATION OF open_files
 status open_files(Information *Info);

//FUNCTION DECLARATION OF skip_10bytes
 status skip_10byte(Information *Info);

// FUNCTION DECLARATION OF get_size
 int get_size(Information *Info);

//FUNCTION DECLARATION OF skip_tag_data
 status skip_flag_data(Information *Info);

//FUNCTION DECLARATION OF printing_size
 status printing_size(int size,Information *Info);

//FUNCTION DECLARATION OF read_and_validate_args_for_edit
 status read_and_validate_args_for_edit(int argc,char *argv[],Information *Info);

//FUNCTION DECLARATION OF edit_the_data
 status edit_the_data(char *argv[],Information *Info);

//FUNCTION DECLARATION OF copy_10byte
 status copy_10byte(Information *Info);

//FUNCTION DECLARATION OF convert_big_into_little
 int convert_big_into_little(int oldsize);

//FUNCTION DECLARATION OF convert_little_into_big
 int convert_little_into_big(int x);