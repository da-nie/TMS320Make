#include <windows.h>
#include <stdio.h>
#include <shlwapi.h>

#include <string>
#include <vector>
#include <algorithm>
#include <stdint.h>

//------------------------------------------------------------------------------
bool Processing(void);//запустить на выполнение
void ProcessingFile(const std::string &path,const std::string &mask,std::vector<std::string> &file_array);//обработка
void FindFile(const std::string &path,const std::string &mask,std::vector<std::string> &file_array);//обработка файлов
void FindPath(const std::string &path,const std::string &mask,std::vector<std::string> &file_array);//обработка каталогов
DWORD Execute(const char *name,const char *param,const char *directory,bool use_stdout_and_stderror);//запуск на выполнение
bool ProcessingCFiles(const std::string &path,const std::string &mask,const std::string &ac30_file_name,const std::string &include_file_name);//обработка c-файлов
bool ProcessingIFFiles(const std::string &path,const std::string &opt30_file_name);//обработка if-файлов
bool ProcessingOPTFiles(const std::string &path,const std::string &cg30_file_name);//обработка opt-файлов
bool ProcessingASMFiles(const std::string &path,const std::string &asm30_file_name);//обработка asm-файлов
bool ProcessingOBJFiles(const std::string &path,const std::string &lnk30_file_name,const std::string &libs_file_name);//обработка obj-файлов
bool ProcessingOUTFiles(const std::string &path);//обработка out-файлов

//----------------------------------------------------------------------------------------------------
//главная функция программы
//----------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevstance,LPSTR lpstrCmdLine,int nCmdShow)
{
 if (Processing()==false)
 {
  fprintf(stderr," \r\nStop compilation.\r\n \r\n");
  exit(EXIT_FAILURE);
 }
 exit(EXIT_SUCCESS);
}

//----------------------------------------------------------------------------------------------------
//запустить на выполнение
//----------------------------------------------------------------------------------------------------
bool Processing(void)
{
 //узнаем текущий каталог
 char path[MAX_PATH];
 GetCurrentDirectory(MAX_PATH,path);

 //удаляем исполняемый файл
 std::string output_file_name=path;
 output_file_name+="\\out.out";
 DeleteFile(output_file_name.c_str());
 std::string output_dat_file_name=path;
 output_dat_file_name+="\\out.dat";
 DeleteFile(output_dat_file_name.c_str());
 std::string output_dat_crc_file_name=path;
 output_dat_crc_file_name+="\\out-crc.dat";
 DeleteFile(output_dat_crc_file_name.c_str());
 
 //узнаем каталог инструментария
 char module_file_name[MAX_PATH];
 GetModuleFileName(GetModuleHandle(NULL),module_file_name,MAX_PATH);
 PathRemoveFileSpec(module_file_name);
 std::string tools_file_name=module_file_name;
 tools_file_name+="\\";

 std::string libs_file_name="\""+tools_file_name+"lib"+"\"";
 std::string include_file_name="\""+tools_file_name+"include"+"\"";
 std::string ac30_file_name="\""+tools_file_name+"bin\\ac30.exe"+"\"";
 std::string opt30_file_name="\""+tools_file_name+"bin\\opt30.exe"+"\"";
 std::string cg30_file_name="\""+tools_file_name+"bin\\cg30.exe"+"\"";
 std::string asm30_file_name="\""+tools_file_name+"bin\\asm30.exe"+"\"";
 std::string lnk30_file_name="\""+tools_file_name+"bin\\lnk30.exe"+"\"";

 if (ProcessingCFiles(path,".c",ac30_file_name,include_file_name)==false) return(false);
 if (ProcessingCFiles(path,".cc",ac30_file_name,include_file_name)==false) return(false);
 if (ProcessingIFFiles(path,opt30_file_name)==false) return(false);
 if (ProcessingOPTFiles(path,cg30_file_name)==false) return(false);
 if (ProcessingASMFiles(path,asm30_file_name)==false) return(false);
 if (ProcessingOBJFiles(path,lnk30_file_name,libs_file_name)==false) return(false);

 if (ProcessingOUTFiles(path)==false) return(false);
 return(true);
}

//----------------------------------------------------------------------------------------------------
//обработка
//----------------------------------------------------------------------------------------------------
void ProcessingFile(const std::string &path,const std::string &mask,std::vector<std::string> &file_array)
{
 FindFile(path,mask,file_array);
 FindPath(path,mask,file_array);
}
//----------------------------------------------------------------------------------------------------
//обработка файлов
//----------------------------------------------------------------------------------------------------
void FindFile(const std::string &path,const std::string &mask,std::vector<std::string> &file_array)
{
 //переименовываем файлы
 WIN32_FIND_DATA wfd;
 HANDLE handle=FindFirstFile(mask.c_str(),&wfd);
 if (handle==INVALID_HANDLE_VALUE) return;
 while(true)
 {
  if (wfd.cFileName[0]!='.' && !(wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))//если это файл
  {
   //добавляем файл в список
   std::string file_name=path;
   file_name+="\\";
   file_name+=wfd.cFileName;
   //убираем расширение файла
   std::string name_we=file_name;
   name_we.erase(name_we.find_last_of("."),std::string::npos);
   file_array.push_back(name_we);
  }
  if (FindNextFile(handle,&wfd)==FALSE) break;
 }
 FindClose(handle);
}
//----------------------------------------------------------------------------------------------------
//обработка каталогов
//----------------------------------------------------------------------------------------------------
void FindPath(const std::string &path,const std::string &mask,std::vector<std::string> &file_array)
{
 char current_directory[MAX_PATH];
 if (GetCurrentDirectory(MAX_PATH,current_directory)==FALSE) return;
 if (SetCurrentDirectory(path.c_str())==FALSE) return;
 //обрабатываем каталоги
 WIN32_FIND_DATA wfd;
 HANDLE handle=FindFirstFile("*",&wfd);
 if (handle==INVALID_HANDLE_VALUE) 
 {
  SetCurrentDirectory(current_directory);
  return;
 }
 while(true)
 {
  if (wfd.cFileName[0]!='.' && (wfd.dwFileAttributes&FILE_ATTRIBUTE_DIRECTORY))//если это директория
  {   
   std::string new_path=path;
   new_path+="\\";
   new_path+=wfd.cFileName;
   SetCurrentDirectory(new_path.c_str());
   ProcessingFile(new_path.c_str(),mask,file_array);
   SetCurrentDirectory(path.c_str());
  }
  if (FindNextFile(handle,&wfd)==FALSE) break;
 }
 FindClose(handle);
 SetCurrentDirectory(current_directory);
}
//----------------------------------------------------------------------------------------------------
//запуск на выполнение
//----------------------------------------------------------------------------------------------------
DWORD Execute(const char *name,const char *param,const char *directory,bool use_stdout_and_stderror)
{
 PROCESS_INFORMATION pi;
 STARTUPINFO si;

 HANDLE duplicate_hStdOutput=INVALID_HANDLE_VALUE;
 HANDLE duplicate_hStdError=INVALID_HANDLE_VALUE;

 ZeroMemory(&si,sizeof(STARTUPINFO));
 si.cb=sizeof(STARTUPINFO);
 si.dwFlags=STARTF_USESHOWWINDOW|STARTF_FORCEOFFFEEDBACK;
 si.wShowWindow=SW_HIDE;

 if (use_stdout_and_stderror==true)
 {
  HANDLE hStdOutput=GetStdHandle(STD_OUTPUT_HANDLE);
  HANDLE hStdError=GetStdHandle(STD_ERROR_HANDLE);

  DuplicateHandle(GetCurrentProcess(),hStdOutput,GetCurrentProcess(),&duplicate_hStdOutput,0,TRUE,DUPLICATE_SAME_ACCESS);
  DuplicateHandle(GetCurrentProcess(),hStdError,GetCurrentProcess(),&duplicate_hStdError,0,TRUE,DUPLICATE_SAME_ACCESS);
  
  si.dwFlags|=STARTF_USESTDHANDLES;
  si.hStdOutput=duplicate_hStdOutput;
  si.hStdInput=GetStdHandle(STD_INPUT_HANDLE);
  si.hStdError=duplicate_hStdError;
 }

 std::string file_name=name;
 file_name+=" ";
 file_name+=param;
  
 if (CreateProcess(NULL,const_cast<char *>(file_name.c_str()),NULL,NULL,TRUE,CREATE_NEW_CONSOLE,NULL,NULL,&si,&pi)==FALSE)
 {  
  if (duplicate_hStdOutput!=INVALID_HANDLE_VALUE) CloseHandle(duplicate_hStdOutput);
  if (duplicate_hStdError!=INVALID_HANDLE_VALUE) CloseHandle(duplicate_hStdError);  
  fprintf(stderr,"Can not execute %s\r\n",name);
  return(EXIT_FAILURE);
 }
 
 if (pi.hProcess!=INVALID_HANDLE_VALUE)
 {
  DWORD dwExitCode=STILL_ACTIVE;
  while (dwExitCode==STILL_ACTIVE)
  {
   WaitForSingleObject(pi.hProcess,1000);
   GetExitCodeProcess(pi.hProcess,&dwExitCode);
  }
  CloseHandle(pi.hProcess);
  if (duplicate_hStdOutput!=INVALID_HANDLE_VALUE) CloseHandle(duplicate_hStdOutput);
  if (duplicate_hStdError!=INVALID_HANDLE_VALUE) CloseHandle(duplicate_hStdError);  
  return(dwExitCode);
 }
 
 if (duplicate_hStdOutput!=INVALID_HANDLE_VALUE) CloseHandle(duplicate_hStdOutput);
 if (duplicate_hStdError!=INVALID_HANDLE_VALUE) CloseHandle(duplicate_hStdError); 
 fprintf(stderr,"Can not execute %s\r\n",name);
 return(EXIT_FAILURE);
}


//----------------------------------------------------------------------------------------------------
//обработка c-файлов
//----------------------------------------------------------------------------------------------------
bool ProcessingCFiles(const std::string &path,const std::string &mask,const std::string &ac30_file_name,const std::string &include_file_name)
{
 printf("Compilation %s-file.\r\n",mask.c_str());

 std::vector<std::string> file_array;
 //компилируем c-файлы
 ProcessingFile(path,"*"+mask,file_array); 
 bool no_error=true;
 auto output_c_func=[&](const std::string &str)
 {
  std::string file_name="\""+str+mask+"\"";
  fprintf(stdout,"****************************************************************************************************\r\n");
  fprintf(stdout,"compilation %s\r\n",file_name.c_str());
  fprintf(stdout,"****************************************************************************************************\r\n");
  std::string param="-i"+include_file_name+" -k -v30 -als -fr ";
  param+=file_name;
  if (Execute(ac30_file_name.c_str(),param.c_str(),str.c_str(),false)!=EXIT_SUCCESS) no_error=false;
  
  //выводим err-файл, если он есть
  std::string err_file_name=str+".err";
  FILE *file=fopen(err_file_name.c_str(),"rb");
  if (file!=NULL)
  {
   fprintf(stdout,"ERROR!\r\n \r\n");
   no_error=false;   
   while(true)
   {
    char b;
	if (fread(&b,sizeof(char),1,file)==0) break;
	fprintf(stdout,"%c",b);
   }
   fclose(file);
  }
  else fprintf(stdout,"ok.\r\n");
  fprintf(stdout," \r\n");
 }; 
 std::for_each(file_array.begin(),file_array.end(),output_c_func);
 return(no_error);
}
//----------------------------------------------------------------------------------------------------
//обработка if-файлов
//----------------------------------------------------------------------------------------------------
bool ProcessingIFFiles(const std::string &path,const std::string &opt30_file_name)
{
 printf("Optimize if-file.\r\n");

 std::vector<std::string> file_array;
 ProcessingFile(path,"*.if",file_array);
 bool no_error=true;

 auto output_if_func=[&](const std::string &str)
 {
  std::string file_name="\""+str+".if\"";
  printf("optimize %s\r\n",file_name.c_str());
  if (Execute(opt30_file_name.c_str(),file_name.c_str(),str.c_str(),false)!=EXIT_SUCCESS) no_error=false;
 }; 
 std::for_each(file_array.begin(),file_array.end(),output_if_func);
 return(no_error);
}
//----------------------------------------------------------------------------------------------------
//обработка opt-файлов
//----------------------------------------------------------------------------------------------------
bool ProcessingOPTFiles(const std::string &path,const std::string &cg30_file_name)
{
 printf("Create asm-file.\r\n");

 std::vector<std::string> file_array;
 ProcessingFile(path,"*.opt",file_array);
 bool no_error=true;

 auto output_opt_func=[&](const std::string &str)
 {
  std::string file_name="\""+str+".opt\"";
  printf("create asm %s\r\n",file_name.c_str());
  if (Execute(cg30_file_name.c_str(),file_name.c_str(),str.c_str(),false)!=EXIT_SUCCESS) no_error=false;
 }; 
 std::for_each(file_array.begin(),file_array.end(),output_opt_func);
 return(no_error);
}
//----------------------------------------------------------------------------------------------------
//обработка asm-файлов
//----------------------------------------------------------------------------------------------------
bool ProcessingASMFiles(const std::string &path,const std::string &asm30_file_name)
{
 printf("Compile asm-file.\r\n");
 std::vector<std::string> file_array;
 ProcessingFile(path,"*.asm",file_array);
 bool no_error=true;

 auto output_asm_func=[&](const std::string &str)
 {
  std::string file_name="\""+str+".asm\"";
  printf("create obj %s\r\n",file_name.c_str());
  std::string param="-ls -v30 ";
  param+=file_name;
  if (Execute(asm30_file_name.c_str(),param.c_str(),str.c_str(),false)!=EXIT_SUCCESS) no_error=false;
 }; 
 std::for_each(file_array.begin(),file_array.end(),output_asm_func);
 return(no_error);
}
//----------------------------------------------------------------------------------------------------
//обработка obj-файлов
//----------------------------------------------------------------------------------------------------
bool ProcessingOBJFiles(const std::string &path,const std::string &lnk30_file_name,const std::string &libs_file_name)
{
 printf("Create out-file.\r\n");

 std::vector<std::string> file_array;
 //собираем проект
 ProcessingFile(path,"*.obj",file_array);
 std::string obj_list;
 auto output_obj_func=[&](const std::string &str)
 {
  std::string file_name="\""+str+".obj\"";
  obj_list+=file_name+" ";
 }; 
 std::for_each(file_array.begin(),file_array.end(),output_obj_func);

 std::string param="-c -m out.map -o out.out -x -i ";
 param+=libs_file_name;
 param+=" -l rts30.lib ";
 param+=obj_list;
 param+=" c30.cmd";

 if (Execute(lnk30_file_name.c_str(),param.c_str(),path.c_str(),true)!=EXIT_SUCCESS) return(false);
 return(true);
}

//----------------------------------------------------------------------------------------------------
//обработка out-файлов
//----------------------------------------------------------------------------------------------------
bool ProcessingOUTFiles(const std::string &path)
{
 printf("Create dat-file.\r\n");
 std::vector<uint8_t> out_file_data;
 FILE *file_out=fopen((path+"\\out.out").c_str(),"rb");
 if (file_out==NULL)
 {
  printf("Error open out.out!\r\n");
  return(false);
 }
 while(1)
 {
  uint8_t s;
  if (fread(&s,sizeof(uint8_t),1,file_out)==0) break;
  out_file_data.push_back(s);
 }
 fclose(file_out);

 //ищем секцию данных и секцию загрузчика
 std::vector<uint8_t> data_section_name;
 data_section_name.push_back('.');
 data_section_name.push_back('d');
 data_section_name.push_back('a');
 data_section_name.push_back('t');
 data_section_name.push_back('a');

 std::vector<uint8_t> boot_section_name;
 boot_section_name.push_back('b');
 boot_section_name.push_back('o');
 boot_section_name.push_back('o');
 boot_section_name.push_back('t');
 boot_section_name.push_back('.');
 boot_section_name.push_back('a');
 boot_section_name.push_back('s');
 boot_section_name.push_back('m');

 std::vector<uint8_t>::iterator iterator_data_section=std::search(out_file_data.begin(),out_file_data.end(),data_section_name.begin(),data_section_name.end());
 if (iterator_data_section==out_file_data.end())
 {
  printf("Error find .data section in out.out file!\r\n");
  return(false);
 }
 std::vector<uint8_t>::iterator iterator_boot_section=std::search(out_file_data.begin(),out_file_data.end(),boot_section_name.begin(),boot_section_name.end());
 if (iterator_boot_section==out_file_data.end())
 {
  printf("Error find boot.asm section in out.out file!\r\n");
  return(false);
 }

 std::vector<uint8_t> dat_file_data;

 size_t size_dat_file=0;
 iterator_data_section+=48;//перемещаемся к первому байту данных 
 size_t counter=11*4;//почему-то такой размер заголовка
 while(iterator_data_section<iterator_boot_section && counter>0)
 {
  uint8_t b;
  b=*iterator_data_section;
  iterator_data_section++;
  counter--;
  size_dat_file+=sizeof(uint8_t);
  dat_file_data.push_back(b);
 }
 //непонятная секция (адреса прерываний?)
 uint32_t l1=0xFB000002;
 uint32_t l2=0xFB000100;
 for(size_t n=0;n<26;n++)
 {
  size_dat_file+=sizeof(uint32_t);
  dat_file_data.push_back((l1>>0)&0xff);
  dat_file_data.push_back((l1>>8)&0xff);
  dat_file_data.push_back((l1>>16)&0xff);
  dat_file_data.push_back((l1>>24)&0xff);

  size_dat_file+=sizeof(uint32_t);
  dat_file_data.push_back((l2>>0)&0xff);
  dat_file_data.push_back((l2>>8)&0xff);
  dat_file_data.push_back((l2>>16)&0xff);
  dat_file_data.push_back((l2>>24)&0xff);
 }
 size_dat_file+=sizeof(uint32_t);
 dat_file_data.push_back((l1>>0)&0xff);
 dat_file_data.push_back((l1>>8)&0xff);
 dat_file_data.push_back((l1>>16)&0xff);
 dat_file_data.push_back((l1>>24)&0xff);

 //данные
 while(iterator_data_section<iterator_boot_section)
 {
  uint8_t b;
  b=*iterator_data_section;
  iterator_data_section++;
  size_dat_file+=sizeof(uint8_t);
  dat_file_data.push_back(b);
 }
 //дозаписываем файл
 while(size_dat_file<65536-sizeof(uint32_t))
 {
  uint8_t b=0;
  size_dat_file+=sizeof(uint8_t);
  dat_file_data.push_back(b);
 }
 //считаем контрольную сумму и создаём файл с ней
 //создаём dat-файл
 FILE *file_dat=fopen((path+"\\out.dat").c_str(),"wb");
 if (file_dat==NULL)
 {
  printf("Error create out.dat!\r\n");
  return(false);
 }

 FILE *file_crc_dat=fopen((path+"\\out-crc.dat").c_str(),"wb");
 if (file_crc_dat==NULL)
 {
  printf("Error create out-crc.dat!\r\n");
  fclose(file_dat);
  return(false);
 }
 fprintf(file_crc_dat,"1651 1 1000 0 4000\r\n");
 fprintf(file_dat,"1651 1 0 0 3fff\r\n");
 uint32_t crc=0;
 size_t size=dat_file_data.size();
 for(size_t n=0;n<size;)
 {
  uint32_t b0=dat_file_data[n++];
  uint32_t b1=dat_file_data[n++];
  uint32_t b2=dat_file_data[n++];
  uint32_t b3=dat_file_data[n++];

  uint32_t word=0;
  word<<=8;word+=b3;
  word<<=8;word+=b2;
  word<<=8;word+=b1;
  word<<=8;word+=b0;

  crc+=word;

  fprintf(file_crc_dat,"0x%08x\r\n",word);
  fprintf(file_dat,"0x%08x\r\n",word);
 }
 fprintf(file_crc_dat,"0x%08x\r\n",crc);
 fclose(file_dat);
 fclose(file_crc_dat);
 printf("CRC: 0x%08x\r\n",crc);
 return(true);
}
