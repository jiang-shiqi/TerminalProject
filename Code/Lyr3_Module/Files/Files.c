#include "Files.h"
#include "diskio.h"		/* Declarations of disk functions */
#include "MMC_SD.h"
#include "stdio.h"
#include "Rocker.h"

//uint8_t sd_RxBuf[TWO_BLOCK];        //SD卡数据接收缓冲区
//uint8_t sd_TxBuf[TWO_BLOCK] = {0};  //SD卡数据发送缓冲区

//FRESULT res; //读写文件返回值   

//FIL FileSyatemSrc,FileSystemDst; //文件系统结构体 包含文件指针等成员
 

//BYTE FileRxBuffer[ONE_BLOCK]; //FILE COPY BUFFER 
//BYTE TxFileBuffer[] = "This is the FATFS System!\r\n"; 
//BYTE TxFileBuffer[] = "文件系统试验!\r\n";

FileManagerList_st fileManagerList;


//扫描当前目录
FRESULT ScanCurrentDirectory( FileManagerList_st *fileManagerList, char *path)
{
	FATFS fs;
	FRESULT  res;
	DIR dir;
  FILINFO fno;
	u32 i;
	
	//挂载文件系统
	res = f_mount(&fs, "", 1 );  //强制重复装载可能会导致返回FR_NOT_READY失败 ----待验证 
  if (res != FR_OK)     
      return res; //挂载文件系统失败   
	res = f_opendir(&dir, path);      //打开路径path 并将路径信息存储在dir 
	if (res != FR_OK)     
      return res; //打开目录失败
	
	//读取文件	
	for(;fileManagerList->num <DISFILELINE_MAX;fileManagerList->num++)	
	{
		res = f_readdir(&dir, &fno);  
		if((res != FR_OK)||(fno.fname[0] == 0))
			break;
		if (fno.fattrib & AM_DIR) {               //是文件夹
			fileManagerList->attr[fileManagerList->num].type = FOLDER;  //文件类型 --文件夹
			snprintf(fileManagerList->attr[fileManagerList->num].name, (size_t)DISFILECHAR_MAX-1,"%s", fno.fname);	      
    } 
    else {                                   //是文件   
			fileManagerList->attr[fileManagerList->num].type = DOCUMENT;  //文件类型 ----暂定
			snprintf(fileManagerList->attr[fileManagerList->num].name, (size_t)DISFILECHAR_MAX-1,"%s", fno.fname);
    }  
	}
	//抹除后4位显示
	for(i=fileManagerList->num;(fileManagerList->num <DISFILELINE_MAX)&&(i<(fileManagerList->num+4));i++)
	{
		fileManagerList->attr[i].type = 0xff;  //空
	}
	f_closedir(&dir); 
	
	return FR_OK;
}

u8 FileManagerKey_Status = None;
u8 FileManagerKey_Backup = None;
char FileManagerCurretPath[100]="/";

void FileManager_Init(void)
{
    strcpy(FileManagerCurretPath,"/\0");
    fileManagerList.num = 0;
    fileManagerList.poi = 0;
    fileManagerList.currentSite = 0;
    fileManagerList.lvevl = 0;
    ScanCurrentDirectory(&fileManagerList, FileManagerCurretPath);
}

 
void FileManager_Service(void)
{ 
	u32 cupA;
	FRESULT res;
	
	//计算按键值 
	switch(YGVal[0].dir)
	{
    case 0x01:
			FileManagerKey_Status = (FileManagerKeyStatus_e)Up; 
			break;
    case 0x02:
			FileManagerKey_Status = (FileManagerKeyStatus_e)Down; 
			break;
    case 0x08:
			FileManagerKey_Status = (FileManagerKeyStatus_e)Enter; 
			break;
    case 0x04:
			FileManagerKey_Status = (FileManagerKeyStatus_e)Back; 
			break;
		default:
			FileManagerKey_Status = (FileManagerKeyStatus_e)None; 
			break;
	}
	
	//计算当前显示框位置
	switch(FileManagerKey_Status)
	{
		case (FileManagerKeyStatus_e)Up:
		    //状态1：指针和当前位置都在第一位
            if((fileManagerList.poi == 0)&&(fileManagerList.currentSite == 0 ))
            {
                
            }
		    //状态2：指针在第一位 当前位置不是第一位
            else if((fileManagerList.poi == 0  )&&(fileManagerList.currentSite != 0 ))
            {
                fileManagerList.currentSite--;
            }
		    //状态3：指针不在第一位 当前位置任意
			else if(fileManagerList.poi != 0)
			{
                fileManagerList.poi--;
                fileManagerList.currentSite--;
			}
			break;
		
		case (FileManagerKeyStatus_e)Down:
			 
		    //状态1：指针任意 当前位置在最后一位
		    if(fileManagerList.currentSite >= fileManagerList.num-1)
		    {

		    }
		    //状态2：指针在最后一位 当前位置不在最后一位
            else if((fileManagerList.poi >= 3)&&(fileManagerList.currentSite < fileManagerList.num-1))
            {
                fileManagerList.currentSite++;
            }
		    //状态3：指针不再最后一位 当前位置任意
            else if(fileManagerList.poi < 3)
            {
                fileManagerList.poi++;
                fileManagerList.currentSite++;
            }
			break;
		
		case (FileManagerKeyStatus_e)Enter:{
    		    //文件属性为文件夹则可进入
    		    //其他文件进入相应启动器
    		    switch(fileManagerList.attr[fileManagerList.currentSite].type)
    		    {
                    case FOLDER:
                        //拼接新路径
												if(fileManagerList.lvevl == 0)
												{ 
													strcat(FileManagerCurretPath,fileManagerList.attr[fileManagerList.currentSite].name);
												}
												else
												{
													strcat(FileManagerCurretPath,"/\0");
													strcat(FileManagerCurretPath,fileManagerList.attr[fileManagerList.currentSite].name);
												}
                        EnterFolder(&fileManagerList,FileManagerCurretPath);
                        break;
                    case DOCUMENT:
                        break;
                    case IMAGE:
                        break;
                    case AUDIO:
                        break;
                    case VIDEO:
                        break;
                    case DAT:
                        break;
                    default:
                        break;
    		    }
		    }
			break;
		
		case (FileManagerKeyStatus_e)Back:
      //只有非第一层才能回退
      if(fileManagerList.lvevl != 0)
      {
          //路径回退一层
				if(fileManagerList.lvevl == 1)
				{
					FileManagerCurretPath[1] = '\0';
					res = FR_OK;
				}
				else
				{ 
          res = BackonePath(FileManagerCurretPath);
				}
          if(res == FR_OK)
          {
              BackFolder(&fileManagerList,FileManagerCurretPath);
          }
      }
			break;
		
		default:
			break;
	}
	FileManagerKey_Status = 0;
	
    /*显示计算区*/
	//赋予显示框指针位置
    FileManagerDisplay.poi = fileManagerList.poi+3;
	
    //赋予路径显示
    strcpy(FileManagerDisplay.path, FileManagerCurretPath);
    
    //赋予显示图标与文件名
		cupA = fileManagerList.currentSite - fileManagerList.poi; 
    FileManagerDisplay.icon01 = fileManagerList.attr[cupA].type;
    strcpy(FileManagerDisplay.line01,fileManagerList.attr[cupA].name);
    FileManagerDisplay.icon02 = fileManagerList.attr[cupA+1].type;
    strcpy(FileManagerDisplay.line02,fileManagerList.attr[cupA+1].name);
    FileManagerDisplay.icon03 = fileManagerList.attr[cupA+2].type;
    strcpy(FileManagerDisplay.line03,fileManagerList.attr[cupA+2].name);
    FileManagerDisplay.icon04 = fileManagerList.attr[cupA+3].type;
    strcpy(FileManagerDisplay.line04,fileManagerList.attr[cupA+3].name);
    
    //赋予进度条显示
    cupA = 100 * (fileManagerList.currentSite - fileManagerList.poi) /fileManagerList.num;
    FileManagerDisplay.progressBarUp   = cupA;
    cupA = 100 * (fileManagerList.currentSite - fileManagerList.poi + 4) /fileManagerList.num;
    FileManagerDisplay.progressBarDown = cupA;
}

//进入文件夹
FRESULT EnterFolder(FileManagerList_st *fileManagerList, char *path)
{
    FRESULT  res;
    //使指针复位到0 目录层级+1
    fileManagerList->num = 0;
    fileManagerList->poi = 0;
    fileManagerList->currentSite = 0;
    fileManagerList->lvevl ++ ;
    //重新扫描路径
    res = ScanCurrentDirectory(fileManagerList, path);
    //如果未成功回退层级
    if(res != FR_OK)
    {
        fileManagerList->lvevl--;
    }

    return res;    
}

//返回上一目录
FRESULT BackFolder(FileManagerList_st *fileManagerList, char *path)
{
    FRESULT  res;
    //使指针复位到0 目录层级-1
    fileManagerList->num = 0;
    fileManagerList->poi = 0;
    fileManagerList->currentSite = 0;
    fileManagerList->lvevl -- ;
    //重新扫描路径
    res = ScanCurrentDirectory(fileManagerList, path);
    //如果未成功回退层级
    if(res != FR_OK)
    {
        fileManagerList->lvevl++;
    }

    return res;    
    
}

//回退一层路径
FRESULT BackonePath(char *path)
{
    u16 cupA;
    u16 i;
    FRESULT res;

    res = FR_INVALID_NAME;
    cupA = strlen(path);
    
    for(i=cupA;i>1;i--)
    {
        if(path[i] == '/')
        {
            path[i] = '\0';
            res = FR_OK;
            break;
        }
    }
    
    return res;
}





















 
