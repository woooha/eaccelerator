#include "ea_preload.h"
#define MAX_EACC_FILENAME_LEN 65535

extern eaccelerator_mm * ea_mm_instance;

PHP_FUNCTION(eaccelerator_preload_file){
    char * filename;
    int filename_len;
    zend_file_handle file_handle;

    if( zend_parse_parameters(ZEND_NUM_ARGS() TSRMLS_CC, "s", &filename, &filename_len) == FAILURE){
        RETURN_FALSE;
    }

    if( FAILURE == zend_stream_open(filename, &file_handle TSRMLS_CC) ){
        RETURN_FALSE;
    }

    if( NULL == ea_mm_instance ){
        RETURN_FALSE;
    }

    if( !eaccelerator_compile_file(&file_handle, ZEND_REQUIRE TSRMLS_CC) ){
        RETURN_FALSE;
    }

    RETURN_TRUE;
}
