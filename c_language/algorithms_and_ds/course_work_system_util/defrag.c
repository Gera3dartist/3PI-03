#include "defrag.h"
#define SIZE_LIMIT 1073741824
#define KB 1024

superblock *superblock_p;
void* buffer, *newInodes;
FILE *newdisk;
int usedBlocks, filesize;

int main(int argc, char *argv[]){
  char *filename;

  filename = "disk-to-defrag";
  read_input(filename);
  defragment();
  populate_free_blocks();
  free(buffer);
  free(newInodes);
  fclose(newdisk);
  return 0;
}

void read_input(char* address){
  usedBlocks = 0; //set block index

  FILE *fp = fopen(address, "r");
  if (fp == NULL) {
    printf("File not found.\n");
    exit(1);
  }
  int namelen = strlen(address) + strlen("-defrag") + 1;
  char* newname = (char*)malloc(namelen);
  strcpy(newname, address);
  strcat(newname, "-defrag");
  newdisk = fopen(newname, "w+");
  free(newname);
  if (newdisk == NULL) error_exit();

  if (fseek(fp, 0, SEEK_END) == -1) error_exit();
  filesize = ftell(fp);
  if (filesize == -1) error_exit();
  if (filesize > SIZE_LIMIT){
    printf("File is too large.\n");
    exit(1);
  }
  if (fseek(fp, 0, SEEK_SET) == -1) error_exit();
  buffer = malloc(filesize);
  if (buffer == NULL){
    printf("Not enough memory.\n");
    exit(1);
  }
  if (fread(buffer, 1, filesize, fp) == -1) error_exit();
  // read superblock
  superblock_p = (superblock*) (buffer + 512);
#undef SIZE_OF_BLOCK
#define SIZE_OF_BLOCK superblock_p->size
 
  if (superblock_p->inode_offset >= superblock_p->data_offset) error_exit();
  if (fseek(newdisk, KB + SIZE_OF_BLOCK * (superblock_p->data_offset), SEEK_SET) == -1) error_exit();
  fclose(fp);
  return;
}

int defragment(){
  int numInode = (superblock_p->data_offset - superblock_p->inode_offset) * SIZE_OF_BLOCK / (INODESIZE + 0.0);
#undef N_INODES
#define N_INODES numInode
  //create copy
  newInodes = malloc(INODESIZE * N_INODES);
  memcpy(newInodes, buffer + 1024 + SIZE_OF_BLOCK * superblock_p->inode_offset, INODESIZE * N_INODES);
  
  for (int i = 0; i < N_INODES; i++){
    inode *temp = (inode*) (buffer + 1024 + SIZE_OF_BLOCK * superblock_p->inode_offset + i * INODESIZE);
    if (temp->nlink == 1){
      inode *newtemp = (inode*) (newInodes + i * INODESIZE);
      track_block(temp, newtemp, i);
    }
  }
  return 0;
}

void write_block(int index){ 
  void *block = buffer + 1024 + SIZE_OF_BLOCK * superblock_p->data_offset + SIZE_OF_BLOCK * index;
  if (fwrite(block, 1, SIZE_OF_BLOCK, newdisk) != SIZE_OF_BLOCK) error_exit();
}

void write_index_block(int start, int end){
  int indices[SIZE_OF_BLOCK/4];
  int j = 0;
  for (int i = start; i <= end; i++){
    indices[j] = i;
    j++;
  }

  if (fwrite(indices, 1, SIZE_OF_BLOCK, newdisk) != SIZE_OF_BLOCK) error_exit();
  if (fseek(newdisk, 0, SEEK_END) == -1) error_exit();
}

void write_inode(inode* node, int index){
  long add = 1024 + SIZE_OF_BLOCK * superblock_p->inode_offset + index * sizeof(inode);
  if (fseek(newdisk, add, SEEK_SET) == -1) error_exit();
  if (fwrite(node, 1, INODESIZE, newdisk) != INODESIZE) error_exit();
  if (fseek(newdisk, 0, SEEK_END) == -1) error_exit();
}

void track_block(inode *node, inode *temp, int index){
  //tracking all blocks
  int data_left = node->size;

  //direct blocks
  for (int i = 0; i < N_DBLOCKS; i++){
    if (data_left <= 0) break;
    write_block(node->dblocks[i]);
    temp->dblocks[i] = usedBlocks;
    usedBlocks++;
    data_left = data_left - SIZE_OF_BLOCK;
  }

  //indirect blocks
  for (int i = 0; i < N_IBLOCKS; i++){
    if (data_left <= 0) break;
    int ival = node->iblocks[i];
    write_index_block(usedBlocks + 1, usedBlocks + SIZE_OF_BLOCK/4);
    temp->iblocks[i] = usedBlocks;
    usedBlocks++;
    for (int j = 0; j < SIZE_OF_BLOCK; j+=4){
      if (data_left <= 0) break;
      void *dadd = buffer + 1024 + SIZE_OF_BLOCK * superblock_p->data_offset + SIZE_OF_BLOCK * ival + j;
      int dval = *((int*) dadd);
      write_block(dval);
      usedBlocks++;
      data_left = data_left - SIZE_OF_BLOCK;
    }
  }

  //i2blocks
  for (int i = 0; i < 1; i++){
    if (data_left <= 0) break;
    int i2val = node->i2block;
    write_index_block(usedBlocks + 1, usedBlocks + SIZE_OF_BLOCK / 4);
    temp->i2block = usedBlocks;
    usedBlocks++;
    int count = data_left;
    int numBlocks = 0;
    for (int j = 0; j < SIZE_OF_BLOCK; j+=4){
      if (count <= 0) break;
      write_index_block(usedBlocks + (j/4+1)*SIZE_OF_BLOCK/4, usedBlocks + (j/4+2)*SIZE_OF_BLOCK/4 -1);
      numBlocks++;
      count = count - SIZE_OF_BLOCK;
    }
    usedBlocks += numBlocks; 
    for (int j = 0; j < SIZE_OF_BLOCK; j+=4){
      if (data_left <= 0) break;
      void* iadd = buffer + 1024 + SIZE_OF_BLOCK*superblock_p->data_offset + SIZE_OF_BLOCK*i2val + j;
      if (iadd >= buffer+filesize || iadd < buffer) error_exit();
      int ival = *((int*) iadd);
      for (int k = 0; k < SIZE_OF_BLOCK; k+=4){
	if (data_left <= 0) break;
	void *dadd = buffer + 1024 + SIZE_OF_BLOCK * superblock_p->data_offset + SIZE_OF_BLOCK * ival + j;
	if (dadd >= buffer+filesize || dadd < buffer) error_exit();
	int dval = *((int*) dadd);

	write_block(dval);
	usedBlocks++;
	data_left = data_left - SIZE_OF_BLOCK;
      }
    }
  }
  //i3blocks
  for (int i = 0; i < 1; i++){
    if (data_left <= 0) break;
    int i3val = node->i3block;
    write_index_block(usedBlocks + 1, usedBlocks + SIZE_OF_BLOCK / 4);
    temp->i2block = usedBlocks;
    usedBlocks++;
    int count = data_left;
    int curIndex = usedBlocks;
    for (int j = 0; j < SIZE_OF_BLOCK; j+=4){
      if (count <= 0) break;
      write_index_block(curIndex + (j/4+1)*SIZE_OF_BLOCK/4, curIndex + (j/4+2)*SIZE_OF_BLOCK/4 -1);
      usedBlocks++;
      count = count - SIZE_OF_BLOCK;
    }
    int startdblock = (curIndex + (SIZE_OF_BLOCK/4 + 1)*SIZE_OF_BLOCK/4);
    for (int k = 0; k < SIZE_OF_BLOCK*SIZE_OF_BLOCK; k+=(SIZE_OF_BLOCK/4)){
      if (count <= 0) break;
      write_index_block(startdblock, startdblock + SIZE_OF_BLOCK/4 - 1);
      startdblock += SIZE_OF_BLOCK/4;
      usedBlocks++;
      count = count - SIZE_OF_BLOCK;
    }
    for (int j = 0; j < SIZE_OF_BLOCK; j+=4){
      if (data_left <= 0) break;
      void* i2add = buffer + 1024 + SIZE_OF_BLOCK*superblock_p->data_offset + SIZE_OF_BLOCK*i3val + j;
      if (i2add >= buffer+filesize || i2add < buffer) error_exit();
      int i2val = *((int*) i2add);
      for (int k = 0; k < SIZE_OF_BLOCK; k+=4){
	if (data_left <= 0) break;
	void *iadd = buffer + 1024 + SIZE_OF_BLOCK * superblock_p->data_offset + SIZE_OF_BLOCK * i2val + j;
	if (iadd >= buffer+filesize || iadd < buffer) error_exit();
	int ival = *((int*) iadd);
	for (int l = 0; l < SIZE_OF_BLOCK; l+=4){
	  if (data_left <= 0) break;
	  void *dadd = buffer + 1024 + SIZE_OF_BLOCK*superblock_p->data_offset + SIZE_OF_BLOCK * ival + j;
	  if (dadd >= buffer+filesize || dadd < buffer) error_exit();
	  int dval = *((int*) dadd);

	  write_block(dval);
	  usedBlocks++;
	  data_left = data_left - SIZE_OF_BLOCK;
	}
      }
    }
  }
  write_inode(temp, index);
  return;
}

int populate_free_blocks(){
  superblock_p->free_block = usedBlocks;
  rewind(newdisk);
  if (fwrite(buffer, 1, 1024, newdisk) != 1024) error_exit();
  if (fseek(newdisk, 0, SEEK_END) == -1) error_exit();
  
  int hasSwap = 1;
  void* swapadd = buffer + 1024 + SIZE_OF_BLOCK * superblock_p->swap_offset;
  void* maxDataAdd = swapadd - 1;
  if (swapadd >= buffer+filesize || swapadd < buffer+1024){
    hasSwap = 0;
    //printf("Invalid swap offset\n");
    maxDataAdd = buffer + filesize - 1;
  }
  void* temp = buffer + 1024 + SIZE_OF_BLOCK * superblock_p->data_offset + SIZE_OF_BLOCK * usedBlocks;
  int numFreeBlocks = (maxDataAdd - (buffer+1024+SIZE_OF_BLOCK*(superblock_p->data_offset + usedBlocks - 1) + 1)) / 512;
  for (int i = 0; i < numFreeBlocks-1; i++){
    *(int*)temp = usedBlocks;
    fwrite(temp, 1, SIZE_OF_BLOCK, newdisk);
    usedBlocks++;
    temp = temp + SIZE_OF_BLOCK;
  }
  *(int*)(temp) = -1;
  fwrite(temp, 1, SIZE_OF_BLOCK, newdisk);
  //copy swap region
  if (hasSwap == 1){
    fwrite(swapadd, 1, buffer + filesize - swapadd - 1, newdisk);
  }
  return 0;
}

void error_exit(){
  free(buffer);
  free(newInodes);
  fclose(newdisk);
  exit(1);
}