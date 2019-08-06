#include <windows.h>
#include <stdio.h>
#include <shlwapi.h>

#include <string>
#include <vector>
#include <algorithm>

//------------------------------------------------------------------------------
void ProcessingFile(const std::string &path,const std::string &mask,std::vector<std::string> &file_array);//обработка
void FindFile(const std::string &path,const std::string &mask,std::vector<std::string> &file_array);//обработка файлов
void FindPath(const std::string &path,const std::string &mask,std::vector<std::string> &file_array);//обработка каталогов
DWORD Execute(const char *name,const char *param,const char *directory);//запуск на выполнение
bool ProcessingCFiles(const std::string &path,const std::string &mask,const std::string &ac30_file_name,const std::string &include_file_name);//обработка c-файлов
bool ProcessingIFFiles(const std::string &path,const std::string &opt30_file_name);//обработка if-файлов
bool ProcessingOPTFiles(const std::string &path,const std::string &cg30_file_name);//обработка opt-файлов
bool ProcessingASMFiles(const std::string &path,const std::string &asm30_file_name);//обработка asm-файлов
bool ProcessingOBJFiles(const std::string &path,const std::string &lnk30_file_name,const std::string &libs_file_name);//обработка obj-файлов

//----------------------------------------------------------------------------------------------------
//главная функция программы
//----------------------------------------------------------------------------------------------------
int WINAPI WinMain(HINSTANCE hInstance,HINSTANCE hPrevstance,LPSTR lpstrCmdLine,int nCmdShow)
{
 //узнаем текущий каталог
 char path[MAX_PATH];
 GetCurrentDirectory(MAX_PATH,path);

 //узнаем каталог инструментария
 char module_file_name[MAX_PATH];
 GetModuleFileName(GetModuleHandle(NULL),module_file_name,MAX_PATH);
 PathRemoveFileSpec(module_file_name);
 std::string tools_file_name=module_file_name;
 tools_file_name+="\\";

 std::string libs_file_name=tools_file_name+"lib";
 std::string include_file_name=tools_file_name+"include";
 std::string ac30_file_name=tools_file_name+"bin\\ac30.exe";
 std::string opt30_file_name=tools_file_name+"bin\\opt30.exe";
 std::string cg30_file_name=tools_file_name+"bin\\cg30.exe";
 std::string asm30_file_name=tools_file_name+"bin\\asm30.exe";
 std::string lnk30_file_name=tools_file_name+"bin\\lnk30.exe";
 
 if (ProcessingCFiles(path,".c",ac30_file_name,include_file_name)==false)
 {
  fprintf(stderr,"Stop compilation.\r\n");
  exit(EXIT_FAILURE);
 }
 if (ProcessingCFiles(path,".cc",ac30_file_name,include_file_name)==false)
 {
  fprintf(stderr,"Stop compilation.\r\n");
  exit(EXIT_FAILURE);
 }
 ProcessingIFFiles(path,opt30_file_name);
 ProcessingOPTFiles(path,cg30_file_name);
 ProcessingASMFiles(path,asm30_file_name);
 if (ProcessingOBJFiles(path,lnk30_file_name,libs_file_name)==false)
 {
  fprintf(stderr,"Stop compilation.\r\n");
  exit(EXIT_FAILURE);
 }
 exit(EXIT_SUCCESS);
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
 while(1)
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
 while(1)
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
DWORD Execute(const char *name,const char *param,const char *directory)
{
 HANDLE hRead=GetStdHandle(STD_OUTPUT_HANDLE);
 SetStdHandle(STD_ERROR_HANDLE,hRead);

 SHELLEXECUTEINFO lpSEI;
 lpSEI.cbSize=sizeof(SHELLEXECUTEINFO);
 lpSEI.fMask=SEE_MASK_NOCLOSEPROCESS;
 lpSEI.hwnd=NULL;
 lpSEI.lpVerb="open";
 lpSEI.lpFile=name;
 lpSEI.lpParameters=param;
 lpSEI.lpDirectory=directory;
 lpSEI.nShow=SW_MINIMIZE;
 lpSEI.hInstApp=NULL;
 ShellExecuteEx(&lpSEI);
 HANDLE hProcess=lpSEI.hProcess;
 WaitForInputIdle(hProcess,INFINITE);
 if (hProcess)
 {
  DWORD dwExitCode=STILL_ACTIVE;
  while (dwExitCode==STILL_ACTIVE)
  {
   WaitForSingleObject(hProcess,1000);
   GetExitCodeProcess(hProcess,&dwExitCode);
   return(dwExitCode);
  }
 }
 return(0);
}


//----------------------------------------------------------------------------------------------------
//обработка c-файлов
//----------------------------------------------------------------------------------------------------
bool ProcessingCFiles(const std::string &path,const std::string &mask,const std::string &ac30_file_name,const std::string &include_file_name)
{
 printf("Compilation c-file.\r\n");

 std::vector<std::string> file_array;
 //компилируем c-файлы
 ProcessingFile(path,"*"+mask,file_array); 
 bool no_error=true;
 auto output_c_func=[&](const std::string &str)
 {
  std::string file_name=str+mask;
  printf("compilation %s\r\n",file_name.c_str());
  std::string param="-i"+include_file_name+" -k -v30 -als -fr ";
  param+=file_name;
  Execute(ac30_file_name.c_str(),param.c_str(),str.c_str());
  //выводим err-файл, если он есть
  std::string err_file_name=str+".err";
  FILE *file=fopen(err_file_name.c_str(),"rb");
  if (file!=NULL)
  {
   no_error=false;   
   while(1)
   {
    char b;
	if (fread(&b,sizeof(char),1,file)==0) break;
	fprintf(stderr,"%c",b);
   }
   fclose(file);
  }
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

 auto output_if_func=[&](const std::string &str)
 {
  std::string file_name=str+".if";
  printf("optimize %s\r\n",file_name.c_str());
  Execute(opt30_file_name.c_str(),file_name.c_str(),str.c_str());
 }; 
 std::for_each(file_array.begin(),file_array.end(),output_if_func);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//обработка opt-файлов
//----------------------------------------------------------------------------------------------------
bool ProcessingOPTFiles(const std::string &path,const std::string &cg30_file_name)
{
 printf("Create asm-file.\r\n");

 std::vector<std::string> file_array;
 ProcessingFile(path,"*.opt",file_array);

 auto output_opt_func=[&](const std::string &str)
 {
  std::string file_name=str+".opt";
  printf("create asm %s\r\n",file_name.c_str());
  Execute(cg30_file_name.c_str(),file_name.c_str(),str.c_str());
 }; 
 std::for_each(file_array.begin(),file_array.end(),output_opt_func);
 return(true);
}
//----------------------------------------------------------------------------------------------------
//обработка asm-файлов
//----------------------------------------------------------------------------------------------------
bool ProcessingASMFiles(const std::string &path,const std::string &asm30_file_name)
{
 printf("Compile asm-file.\r\n");
 std::vector<std::string> file_array;
 ProcessingFile(path,"*.asm",file_array);

 auto output_asm_func=[&](const std::string &str)
 {
  std::string file_name=str+".asm";
  printf("create obj %s\r\n",file_name.c_str());
  std::string param="-ls -v30 ";
  param+=file_name;
  Execute(asm30_file_name.c_str(),param.c_str(),str.c_str());
 }; 
 std::for_each(file_array.begin(),file_array.end(),output_asm_func);
 return(true);
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
  std::string file_name=str+".obj";
  obj_list+=file_name+" ";
 }; 
 std::for_each(file_array.begin(),file_array.end(),output_obj_func);

 std::string param="-c -m out.map -o out.out -x -i ";
 param+=libs_file_name;
 param+=" -l rts30.lib ";
 param+=obj_list;
 param+=" c30.cmd";

 if (Execute(lnk30_file_name.c_str(),param.c_str(),path.c_str())!=0) return(false);
 return(true);
}
