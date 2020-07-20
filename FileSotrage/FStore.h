#include <iostream>
#include <vector>
#include <map>
#include <algorithms>


/*
 * Block Mapping as of now not required in basic File Store
 * where we just store data in one simple file. Block Mapping
 * will be required when we split the data across multiple files
 * and create a top level abstration for user with one single 
 * storage view and hence needs mapping from single storage abstraction 
 * to multiple file storage.
 */
 
enum FstoreErrors {
   FSTORE_INIT_FILE_CREATE_FAIL
};

typedef struct {
  char * magic;
  char * fpath;
  FILE * fd;
  int    sz;
  int    tot_blks;
  int    num_free_blks;
  char * bmap_fpath;
  FILE * bmap_file;
  //char * blk_map_path;
  //FILE * blk_map_file; 
} Fhdr_t;  
   
class FStore {
  Fhdr_t * store_hdr;
public:
  Fstore(Fhdr_t *hdr);   // Init Fhdr with cmd args
  int initFStore();      // Create FStore backing file, write Fhdr to file
   
}; 
