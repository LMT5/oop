#include "tar.h"
void date(int sec)
{
	time_t rawtime = sec;
	struct tm *info;
	char buffer[80];
	
	info = localtime( &rawtime );
	strftime(buffer,80,"%Y-%m-%d %H:%M ", info);
	cout<<buffer; 	
}
int count_zero(char* str,int size)
{
	int count=0;
	for(int i=0;i<size;i++)
	{
		if(str[i] != '\0')
			count+=1;
	}
	return count;
}
bool check_end(tar_header header)
{
	int count = 0;
	count+=count_zero(header.filename,100);
	count+=count_zero(header.filemode,8);
	count+=count_zero(header.userid,8);
	count+=count_zero(header.groupid,8);
	count+=count_zero(header.filesize,12);
	count+=count_zero(header.mtime,12);
	count+=count_zero(header.checksum,8);
	if(header.type != '\0')
	{
		count+=1;
	}
	count+=count_zero(header.lname,100);
	count+=count_zero(header.USTAR_id,6);
	count+=count_zero(header.USTAR_ver,2);
	count+=count_zero(header.username,32);
	count+=count_zero(header.groupname,32);
	count+=count_zero(header.devmajor,8);
	count+=count_zero(header.devminor,8);
	count+=count_zero(header.prefix,155);
	count+=count_zero(header.pad,12);
	if(count == 0)
		return true;
	else
		return false;
}
void initial(char* str,int size)
{
	for(int i=0;i<size;i++)
		str[i]=0;
}
TarFile::TarFile(const char* tar_name)
    : file(nullptr), size(0)
{
	file_names.clear();
	file_sizes.clear();
	file_data_start_addrs.clear();
	file.open(tar_name, ios::in);
	name = tar_name;
	if (!file) 
	{
		cout<<"mytar: "<<tar_name<<": Cannot open: No such file or directory"<<endl;
		cout<<"mytar: Error is not recoverable: exiting now"<<endl;
	}
}

TarFile::~TarFile()
{
    if (file) {
        file.close();
    }
    file_names.clear();
    file_sizes.clear();
    file_data_start_addrs.clear();
}
bool TarFile::IsValidTarFile()
{
	if (!file) 
	{
		return false;
	}
	const int block_size{ 512 };
	tar_header header;
	//initial
	initial(header.filename,100);
	initial(header.filemode,8);
	initial(header.userid,8);
	initial(header.groupid,8);
	initial(header.filesize,12);
	initial(header.mtime,12);
	initial(header.checksum,8);
	header.type = 0;
	initial(header.lname,100);
	initial(header.USTAR_id,6);
	initial(header.USTAR_ver,2);
	initial(header.username,32);
	initial(header.groupname,32);
	initial(header.devmajor,8);
	initial(header.devminor,8);
	initial(header.prefix,155);
	initial(header.pad,12);

	file.seekg(0,ios::end);
	size = file.tellg();
	file.seekg(0,ios::beg);
	
	if (size % block_size !=0)
	{
		cout<<"mytar: "<<name<<": Cannot open: No such file or directory"<<endl;
		cout<<"mytar: Error is not recoverable: exiting now"<<endl;
		return false;
	}
	
	size_t pos{ 0 };
	//cout<<"error1"<<endl;
	int count=0;
	while(1)
	{
		size_t read_size = 0;
		file.read(header.filename,100);
		file.read(header.filemode,8);
		file.read(header.userid,8);
		file.read(header.groupid,8);
		file.read(header.filesize,12);
		file.read(header.mtime,12);
		file.read(header.checksum,8);
		file.get(header.type);
		file.read(header.lname,100);
		file.read(header.USTAR_id,6);
		file.read(header.USTAR_ver,2);
		file.read(header.username,32);
		file.read(header.groupname,32);
		file.read(header.devmajor,8);
		file.read(header.devminor,8);
		file.read(header.prefix,155);
		file.read(header.pad,12);	
		
		if(check_end(header))
		{
			count++;
			if(count!=2)
				continue;
		}
		//cout<<count<<endl;
		if(count == 2)
		{
			break;
		}

		pos += block_size;
		size_t file_size;
		//cout<<header.filesize<<endl;
		file_size = stol(header.filesize, nullptr, 8);
		//cout<<file_size<<endl;
		size_t file_block_count = (file_size + block_size -1)/block_size;
		
		if(count == 0)
		{
			switch(header.type)
			{
				case '0':// intentionlly dropping through
				case '\0':
					//normal file
					type.push_back('-');
					break;
				case '1':
					// hard link
					type.push_back('l');
					break;
				case '2':
					// symbolic link
					type.push_back('l');
					break;
				case '3':
					// device file/special file
					type.push_back('c');
					break;
				case '4':
					// block device	
					type.push_back('b');
					break;
				case '5':
					// directory
					type.push_back('d');
					break;
				case '6':
					// named pipe
					type.push_back('p');
					break;
				default:
					break;
			}
			file_sizes.push_back(file_size);
			file_names.push_back(std::string(header.filename));
			file_data_start_addrs.push_back(pos);
			file_mode.push_back(header.filemode);
			user_names.push_back(header.username);
			group_names.push_back(header.groupname);
			mtime.push_back(header.mtime);
		}
		pos += file_block_count * block_size;
		file.seekg(pos,ios::beg);
	}
	//cout<<"error2"<<endl;
	file.seekg(0,ios::beg);
	
	return true;
}
std::vector<std::string> TarFile::GetFileNames()
{
	return file_names;
}
bool TarFile::GetFileContents(const char* file_name, char* contents)
{
    	bool flag = false;
    	for (int i = 0; i < file_names.size(); i++) 
	{
        	std::string name_(file_name);
 
		if (file_names[i].compare(name_) == 0) 
		{
			int file_size = file_sizes[i];
			flag = true;
			file.seekg(file_data_start_addrs[i],ios::beg);
			file.read(contents,file_size);
			file.seekg(0, ios::beg);
	
			break;
	        }
	}

	return flag;
}
size_t TarFile::GetFileSize(const char* file_name)
{
	size_t file_size{0};
 
	for (int i = 0; i < file_names.size(); i++) 
	{
		std::string name_(file_name);
 
		if (file_names[i].compare(name_) == 0) 
		{
			file_size = file_sizes[i];
			break;
		}
	}
	return file_size;
}
size_t TarFile::GetTarSize()
{
	return size;
}
void File_mode(char size)
{
	
	if(size == '0')
	cout<<"---";
	else if(size == '1')
	cout<<"--x";
	else if(size == '2')
	cout<<"-w-";
	else if(size == '3')
	cout<<"-wx";
	else if(size == '4')
	cout<<"r--";
	else if(size == '5')
	cout<<"r-x";
	else if(size == '6')
	cout<<"rw-";
	else
	cout<<"rwx";	
}
void TarFile::list()
{
	for(int i=0;i<file_names.size();i++)
	{
		cout<<type[i];
		
		string temp;
		temp = to_string(stol(file_mode[i]));
		
		File_mode(temp[0]);
		File_mode(temp[1]);
		File_mode(temp[2]);
		cout<<" "<<user_names[i]<<"/"<<group_names[i]<<"	"<<file_sizes[i]<<" ";
		date(stol(mtime[i],nullptr,8));
		cout<<" "<<file_names[i]<<endl;
	}
}
