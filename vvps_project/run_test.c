#include <stdio.h>
#include <stdlib.h>
#include "CUnit/CUnit.h"
#include "CUnit/Automated.h"

void add_tests(void);

int main( int argc, char *argv[] )
{
       if(CU_initialize_registry()){
                fprintf(stderr, " Initialization of Test Registry failed. ");
                exit(1);
        }else{
                add_tests();
                CU_set_output_filename("gauss_test");
                CU_list_tests_to_file();
                CU_automated_run_tests();
                CU_cleanup_registry();
        }
        return 0;
}
