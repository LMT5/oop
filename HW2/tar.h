#ifndef FBC_MESSY_TEST_TAR_HPP_
#define FBC_MESSY_TEST_TAR_HPP_
 
#include <vector>
#include <string>
#include <fstream>
#include <iostream>
#include <cstdlib>
#include<ctime>
using namespace std; 
typedef struct TarHeader 
{
	char filename[100];
	char filemode[8];
	char userid[8];
	char groupid[8];
	char filesize[12];
	char mtime[12];
	char checksum[8];
	char type;
	char lname[100];
	/* USTAR Section */
	char USTAR_id[6];
	char USTAR_ver[2];
	char username[32];
	char groupname[32];
	char devmajor[8];
	char devminor[8];
	char prefix[155];
	char pad[12];
} tar_header;

#define TMAGIC   "ustar"        /* ustar and a null */
#define TMAGLEN  6
#define TVERSION "00"           /* 00 and no null */
#define TVERSLEN 2

#define REGTYPE  '0'            /* regular file */
#define AREGTYPE '\0'           /* regular file */
#define LNKTYPE  '1'            /* link */
#define SYMTYPE  '2'            /* reserved */
#define CHRTYPE  '3'            /* character special */
#define BLKTYPE  '4'            /* block special */
#define DIRTYPE  '5'            /* directory */
#define FIFOTYPE '6'            /* FIFO special */
#define CONTTYPE '7'            /* reserved */


class TarFile 
{
	public:
	    TarFile(const char* tar_name);
	    bool IsValidTarFile();
	    std::vector<std::string> GetFileNames();
	    bool GetFileContents(const char* file_name, char* contents);
	    size_t GetFileSize(const char* file_name);
	    size_t GetTarSize();
	    ~TarFile();
	    void list();
	private:
	    fstream file;
	    size_t size;
	    std::vector<std::string> file_names;
	    std::vector<size_t> file_sizes;
	    std::vector<size_t> file_data_start_addrs;
	    std::vector<char> type;
	    std::vector<std::string> file_mode;
	    std::vector<std::string> user_names;
	    std::vector<std::string> group_names;
	    std::vector<std::string> mtime;
	    const char* name;
};
void date(int sec);
int test_tar();
int count_zero(char* str,int size);
void initial(char* str,int size);
bool check_end(tar_header header);
void File_mode(char size);
#endif 
