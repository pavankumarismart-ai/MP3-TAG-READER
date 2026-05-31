#include <stdio.h>
#include<string.h>
#include<stdlib.h>
#include "function.h"
#include "types.h"

// FUNCTION DEFINATION
status open_files(Information *Info)
{
    // mp3 file
    Info->fptr_mp3 = fopen(Info->mp3_fname, "rb");
   
    if (Info->fptr_mp3 == NULL)
    {
    	perror("fopen");
    	fprintf(stderr, "ERROR: Unable to open file %s\n", Info->mp3_fname);

    	return failure;
    }
    return success;
}

// FUNCTION DEFINATION 
void calling_help()
{
    printf("--------------------------------------HELP MENU--------------------------------------\n");
    printf("1. -v -> To view mp3 file contents\n2. -e -> To edit mp3 file contents\n");
    printf("         2.1. -t -> To edit song title\n");
    printf("         2.2. -a -> To edit artist name\n");
    printf("         2.3. -A -> To edit album name\n");
    printf("         2.4. -y -> To edit year\n");
    printf("         2.5. -m -> To edit content\n");
    printf("         2.1. -c -> To edit comment\n");
    printf("-------------------------------------------------------------------------------------\n");
}

// FUNCTION DEFINATION 
void printing_default()
{   printf("-------------------------------------------------------------------------------------\n");
    printf("ERROR : ./a.out : INVALID ARGUMENTS\n");
    printf("USAGE:\n");
    printf("To view please pass like this: ./a.out -v mp3filename\n");
    printf("To edit please pass like this: ./a.out -e -t/-a/-A/-m/-y/-c changing_text filename\n");
    printf("To get help pass like this: ./a.out --help\n");
    printf("-------------------------------------------------------------------------------------\n");
}

// FUNCTION DEFINATION 
status read_and_validate_args(int argc,char *argv[], Information *Info)
{
    //CHECKING .mp3 TAG OR NOT
    if(strstr(argv[2],".mp3")!=NULL)
    {  
        Info->mp3_fname=argv[2];
        return success;
    }
    else{
        return failure;
    }
}
// FUNCTION DEFINATION OF VIEW_THE_DATA
status view_the_data(Information *Info)
{
    if(open_files(Info)==success)
    {
    }
    else{
        return failure;
    }
    printf("-------------------------------------------------------------------------------------\n");
    printf("                        MP3 TAG READER AND EDITOR FOR ID3v2                          \n");
    printf("-------------------------------------------------------------------------------------\n");
    printf("------------------------------SELECTED VIEW DETAILS----------------------------------\n");
    skip_10byte(Info);

    for(int i=0;i<6;i++)
    {
    skip_flag_data(Info);
    int size=0; 
    size=get_size(Info);
    skip_flag_data(Info);

    // CALLING PRINTING_SIZE FUNCTION
    printing_size(size,Info);
    }
    printf("-------------------------------------------------------------------------------------\n");
    printf("---------------------------DETAILS DISPLAYED SUCCESSFULLY----------------------------\n");

}
// FUNCTION DEFINATION 
status skip_10byte(Information *Info)
{
    long int pos=ftell(Info->fptr_mp3);
    
    
    fseek(Info->fptr_mp3,10, SEEK_CUR);
    pos=ftell(Info->fptr_mp3);
    
}

// FUNCTION DEFINATION 
status skip_flag_data(Information *Info)
{
    long int pos=ftell(Info->fptr_mp3);
    char buffer[4];
    fread(buffer, 1,4, Info->fptr_mp3);
    if(strcmp(buffer,"TIT2")==0)
    {
        printf("%-20s:","TITLE");
    }
    else if(strcmp(buffer,"TPE1")==0)
    {
        printf("%-20s:","ARTIST");
    }
    else if(strcmp(buffer,"TALB")==0)
    {
        printf("%-20s:","ALBUM");
    }
    else if(strcmp(buffer,"TYER")==0)
    {
        printf("%-20s:","YEAR");
    }
    else if(strcmp(buffer,"TCON")==0)
    {
        printf("%-20s:","MUSIC");
    }
    else if(strcmp(buffer,"COMM")==0)
    {
        printf("%-20s:","COMMENT");
    }
}

// FUNCTION DEFINATION 
int get_size(Information *Info)
{
    unsigned char size[4];

    for(int i=0;i<4;i++)
    {
        fread(&size[i],1,1,Info->fptr_mp3);
    }

    int tag_size=((size[0] ) << 24) | ((size[1] ) << 16) | ((size[2] ) << 8)  | (size[3] );
    return tag_size;
}

// FUNCTION DEFINATION 
// status skip_flag_data(Information *Info)
// {
//     long int pos=ftell(Info->fptr_mp3);
    
//     fseek(Info->fptr_mp3,3, SEEK_CUR);
//     pos=ftell(Info->fptr_mp3);
// }
// FUNCTION DEFINATION 
status printing_size(int size,Information *Info)
{
    char ch;
    for(int i=1;i<=size-1;i++)

    {
    fread(&ch, sizeof(char), 1, Info->fptr_mp3);
    fwrite(&ch, sizeof(char), 1, stdout);
    }

    printf("\n");
    long int pos=ftell(Info->fptr_mp3);
    

}

// FUNCTION DEFINATION
status read_and_validate_args_for_edit(int argc,char *argv[], Information *Info)
{
    // COMPARE ARGV[4] HAVING .mp3 OR NOT
    if(strstr(argv[4],".mp3")!=NULL)
    {
        printf("INFO : PROPER FILE NAME IS RECIVED\n");
        Info->mp3_fname=argv[4];
    }
    else{
        return failure;
    }

    // CHECK WHEATHER THE TAG OPTION IS PROVIDING CORRECT OR OR NOT
    if((strcmp(argv[2],"-a") && strcmp(argv[2],"-t") && strcmp(argv[2],"-A") && strcmp(argv[2],"-m") && strcmp(argv[2],"-y") && strcmp(argv[2],"-c") ) ==0)
    {
        printf("INFO : PROPER TAG OPTION IS RECIVED\n");
        return success;
    }
    else{
        return failure;
    }
}

// FUNCTION DEFINATION 
status edit_the_data(char *argv[],Information *Info)
{
    int newsize=strlen(argv[3])+1;
    char *ch_text=argv[3];
    char usertag[5];
    if(strcmp(argv[2],"-t")==0)
    {
        strcpy(usertag,"TIT2");
    }
    else if(strcmp(argv[2],"-a")==0)
    {
        strcpy(usertag,"TPE1");
    }
    else if(strcmp(argv[2],"-A")==0)
    {
        strcpy(usertag,"TALB");
    }
    else if(strcmp(argv[2],"-y")==0)
    {
        strcpy(usertag,"TYER");
    }
    else if(strcmp(argv[2],"-m")==0)
    {
        strcpy(usertag,"TCON");
    }
    else if(strcmp(argv[2],"-c")==0)
    {
        strcpy(usertag,"COMM");
    }

    if(open_files(Info)==success)
    {
        printf("INFO : FILE IS PRESENT \n");
    }
    else{
        printf("No mp3 file is present\n");
        return failure;
    }
    // FOPEN THE TEMPFILE.MP3
    Info->fptr_tempmp3 = fopen("tempfile.mp3", "w");
    if (Info->fptr_tempmp3 == NULL)
    {
        perror("fopen");
        return failure;
    }

    // CALLING COPY_10BYTE
    copy_10byte(Info);

    // RUN FOR LOOP FOR 6 TIMES TO CHECK AND UPDATE THE NEW DATA
    for(int i=0;i<6;i++)
    {
         char tag[5];
        
         // READ 4 BYTE TO GET TAG
         fread(&tag, sizeof(char), 4, Info->fptr_mp3);

         // COMPARE WITH USER GIVEN TAG
         if(strcmp(tag,usertag)==0)
         {
            int oldsize=0;
            fread(&oldsize, sizeof(char), 4, Info->fptr_mp3);
            
            // convert the old size to little endian
            oldsize=convert_big_into_little(oldsize);
           
            // convert the new size into big endian
            newsize=convert_little_into_big(newsize);
            
            // write 4 byte of tag and new size into tempfile
            fwrite(&tag, sizeof(char), 4, Info->fptr_tempmp3);
            fwrite(&newsize, sizeof(char), 4, Info->fptr_tempmp3);

            //read and write flag
            char flag[3];
            fread(&flag, sizeof(char), 3, Info->fptr_mp3);
            fwrite(&flag, sizeof(char), 3, Info->fptr_tempmp3);

            // skip old size and write the new changing string
            char data[oldsize-1];
            fseek(Info->fptr_mp3, oldsize-1, SEEK_CUR);
            fwrite(argv[3], sizeof(char), strlen(argv[3]), Info->fptr_tempmp3);
         }
         else
         {
            // read the tag
            int oldsize1=0;
            fwrite(&tag, sizeof(char), 4, Info->fptr_tempmp3);
            fread(&oldsize1, sizeof(char), 4, Info->fptr_mp3);
          
            // write the old size int tempfile
            fwrite(&oldsize1, sizeof(char), 4, Info->fptr_tempmp3);

            // read and write flag 
            char flag[3];
            fread(&flag, sizeof(char), 3, Info->fptr_mp3);
            fwrite(&flag, sizeof(char), 3, Info->fptr_tempmp3);

            oldsize1=convert_big_into_little(oldsize1);
           
            // read and write the data
            char data[oldsize1-1];
            fread(&data, sizeof(char), oldsize1-1, Info->fptr_mp3);
            fwrite(&data, sizeof(char), oldsize1-1, Info->fptr_tempmp3);
         }
    }

    // COPY REMAING DATA
    char ch;
    while(fread(&ch, sizeof(char), 1, Info->fptr_mp3))
    {
        fwrite(&ch, sizeof(char), 1, Info->fptr_tempmp3);
    }
    fclose(Info->fptr_mp3);
    fclose(Info->fptr_tempmp3);

    //REMOVE THE MAIN FILE
    if (remove(Info->mp3_fname) != 0)
    {
        perror("remove failed");
        return failure;
    }

    // RENAME THE TEMPREVERE FILE WITH MAIN FILE
    if (rename("tempfile.mp3", Info->mp3_fname) != 0)
    {
        perror("rename failed");
        return failure;
    }
    printf("--------------------AFTER THE EDIT THIS IS THE FOLLOWING DETAILS---------------------\n");

    //CALLING THE VIEW FUNCTION AFTER THE EDIT
    view_the_data(Info);
}

// FUNCTION DEFINATION OF COPY_10BYTE
status copy_10byte(Information *Info)
{
    char ch[10];
    fread(&ch, sizeof(char), 10, Info->fptr_mp3);
    fwrite(&ch, sizeof(char), 10, Info->fptr_tempmp3);
}

// // FUNCTION DEFINATION OF bi_to_little
int convert_big_into_little(int x)
{
    return ((x >> 24) & 0x000000FF) | ((x >> 8)  & 0x0000FF00) | ((x << 8)  & 0x00FF0000) | ((x << 24) & 0xFF000000);
}

// FUNCTION DEFINATION OF convert_little_into_big
int convert_little_into_big(int x)
{
    return ((x >> 24) & 0x000000FF) | ((x >> 8)  & 0x0000FF00) | ((x << 8)  & 0x00FF0000) | ((x << 24) & 0xFF000000);
}
