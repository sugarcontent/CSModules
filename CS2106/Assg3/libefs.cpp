#include "libefs.h"

// FS Descriptor
TFileSystemStruct *_fs;

// Open File Table
TOpenFile *_oft;

// Open file table counter
int _oftCount=0;

// Mounts a paritition given in fsPartitionName. Must be called before all
// other functions
void initFS(const char *fsPartitionName, const char *fsPassword)
{
	mountFS(fsPartitionName, fsPassword);
	_fs = getFSInfo();
	_oft->inodeBuffer = makeInodeBuffer();
	_oft->buffer = makeDataBuffer();

}

// Opens a file in the partition. Depending on mode, a new file may be created
// if it doesn't exist, or we may get FS_FILE_NOT_FOUND in _result. See the enum above for valid modes.
// Return -1 if file open fails for some reason. E.g. file not found when mode is MODE_NORMAL, or
// disk is full when mode is MODE_CREATE, etc.

int openFile(const char *filename, unsigned char mode)
{
	_oft->openMode = mode;
	_oft->filePtr = findFile(filename);
	_oft->fileName = filename;
	FILE *fp;

	if(_oft->filePtr == FS_FILE_NOT_FOUND)
	{
		if(mode == 1)
			fp = fopen(filename, "a+");
	}
	else
	{
		fp = fopen(filename, "r+");
	}
	
	if(fp == NULL)
		return -1;

	return 0;	
}

// Write data to the file. File must be opened in MODE_NORMAL or MODE_CREATE modes. Does nothing
// if file is opened in MODE_READ_ONLY mode.
void writeFile(int fp, void *buffer, unsigned int dataSize, unsigned int dataCount)
{
	if(_oft->openMode == 0 || _oft->openMode == 1) 
	{
		FILE *fp = fdopen(_oft->filePtr, "r+");
		unsigned long len = fread(buffer, sizeof(dataSize), dataCount, fp);
		unsigned int dirNdx = makeDirectoryEntry(_oft->fileName, 0x0, len);
		
		unsigned long freeBlock; 
		
		int i;
		int numBlocks = ceil((double)(dataSize * dataCount) / _oft->blockSize); 
		
		for(i=0; i<numBlocks; i++) 
		{
			freeBlock = findFreeBlock();
			markBlockBusy(freeBlock);
		
			loadInode(_oft->inodeBuffer, dirNdx);
			_oft->inodeBuffer[0]=freeBlock;

			writeBlock((char *)buffer, freeBlock);
			saveInode(_oft->inodeBuffer, dirNdx);
		
			updateFreeList();
			updateDirectory();
			
		buffer = (char *)buffer +  _oft->blockSize;
		}

			unmountFS();
			free(buffer);
			free(_oft->inodeBuffer);
	} 
}

// Flush the file data to the disk. Writes all data buffers, updates directory,
// free list and inode for this file.
void flushFile(int fp)
{
}

// Read data from the file.
void readFile(int fp, void *buffer, unsigned int dataSize, unsigned int dataCount)
{
}

// Delete the file. Read-only flag (bit 2 of the attr field) in directory listing must not be set. 
// See TDirectory structure.
void delFile(const char *filename);

// Close a file. Flushes all data buffers, updates inode, directory, etc.
void closeFile(int fp);

// Unmount file system.
void closeFS();

