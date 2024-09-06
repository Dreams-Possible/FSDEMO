#include"Main.h"



//命令解释器
void S_Interpreter()
{
	printf("S_CMD>>");

	char Command[128];

	//接收命令字符串 
	fgets(Command,sizeof(Command),stdin);

	//去除换行符
    Command[strcspn(Command,"\n")]=0;

    char*CMD=strtok(Command," ");

	//检测是否有输入
	if(CMD==NULL)
	{
		printf("No S_CMD\n");
		return;
	}

	if(strcmp(CMD,"fs")==0)
	{
		CMD=strtok(NULL," ");
        while(CMD!=NULL)
		{
			//显示文件列表
            if(strcmp(CMD,"l")==0)
			{
                system("cls");
                FS_Show();
				return;
            }else
			//新建文件
			if(strcmp(CMD,"c")==0)
			{
				system("cls");
				char*Type=strtok(NULL," ");
				if(Type!=NULL)
				{
					char*Name=strtok(NULL," ");
					if(Name!=NULL)
					{
						FS_New(Type,Name);
					}else
					{
						FS_New("",Type);
					}
				}else
				{
					printf("Invalid FS_CMD\n");
				}
				return;
			}else
			//删除文件
			if(strcmp(CMD,"d")==0)
			{
				system("cls");
				char*Name=strtok(NULL," ");
				FS_Delete(Name);
				return;
			}else
			//打开文件
			if(strcmp(CMD,"o")==0)
			{
				system("cls");
				char*Name=strtok(NULL," ");
				FS_Open(Name);
				return;
			}else
			{
                printf("Invalid FS_CMD\n");
				return;
            }
        }
		return;
    }
	printf("Invalid S_CMD\n");
	return;
}


void main()
{
	//初始化文件系统 
	FS_Initialization();
	
    while(1)
	{
		S_Interpreter();
	}    
    
	return;
}





