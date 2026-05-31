#include<stdio.h>
#include<string.h>
#include"function.h"
#include"types.h"

//FUNCTION DEFINATION OF CHECK OPERATION TYPE
OperationType check_operation_type(int argc,char *argv[])
{
    if(argc==1)
    {
        return do_default;       
    }
    else if(strcmp(argv[1],"-v")==0)
    {
        return do_view;
    }
    else if(strcmp(argv[1],"-e")==0)
    {
        return do_edit;
    }
    else if(strcmp(argv[1],"--help")==0)
    {
        return do_help;
    }
    else
    {
        return do_default;
    }
}

int main(int argc,char* argv[])
{
    Information Info;

    //FUNCTION DEFINATION OF check_operation_type
    OperationType res=check_operation_type(argc,argv);
    if (res==do_view)
    {
      //FUNCTION DEFINATION OF read_and_validate_args
      if(read_and_validate_args(argc,argv,&Info)==success)
      {
        //calling view function
        status res1=view_the_data(&Info);
        if(res1==failure)
        {
            return failure;
        }
      }
       else
       {
          printing_default();
          return failure;  
       }
    }
    else if(res==do_edit)
    {
        if(read_and_validate_args_for_edit(argc,argv, &Info)==success)
        {
            // calling edit function
            status res2=edit_the_data(argv,&Info);
            if(res2==failure)
            {
                return failure;
            }

        }
        else{
            printing_default();
            return failure;
        }
    }
    else if(res==do_help)
    {
        calling_help();
    }
    else{
        printing_default();
    }
    
}