#include"FileSystem.h"


//创建节点索引
//当前父文件夹
FS_Node*FS_Node_Current=NULL;

//初始化文件节点
//创建根目录
u8 FS_Initialization()
{
	//分配内存
    FS_Node*NewNode=(FS_Node*)malloc(sizeof(FS_Node));

	//内存不足
	if(NewNode==NULL)
	{
		FS_Print_Error("Error ");
		FS_Print_Error("No Memory\n");
		FS_Print_Error("SF Fail\n");
		return 1;
	}

	//注册根文件节点
	FS_Node_Current=NewNode;
	strcpy(NewNode->Name,"Root");
	NewNode->Type=Directory;
	NewNode->Out=NULL;
	NewNode->In=NULL;
	NewNode->Next=NULL;
	FS_Print_Warn("SF Done\n");
	return 0;
}



//新建文件节点
//父文件节点，节点类型，节点名称
FS_Node*FS_Node_Create(FS_Node*Node,FS_Type Type,const char*Name)
{
	//检查父文件节点有效性
	if (Node== NULL)
	{
		FS_Print_Error("Error ");
		FS_Print_Error("Invalid Node\n");
		return NULL;
	}

	//检查节点名称
	if(strcmp(Name,"")==0||strcmp(Name,".")==0||strlen(Name)>=FS_Node_Name_MAXNumber)
	{
		//无效的名称
		FS_Print_Error("Error ");
		FS_Print_Error("Invalid Name\n");
		return NULL;
	}

	//分配内存
    FS_Node*NewNode=(FS_Node*)malloc(sizeof(FS_Node));

	//内存不足
	if(NewNode==NULL)
	{
		FS_Print_Error("Error ");
		FS_Print_Error("No Memory\n");
		return NULL;
	}

	//注册当前文件节点
	//说明该文件节点下还没有文件节点，向其添加第一个文件节点
	if(Node->In==NULL)
	{
		Node->In=NewNode;
        strcpy(NewNode->Name,Name);
        NewNode->Type=Type;
        NewNode->Out=Node;
        NewNode->In=NULL;
        NewNode->Next=NULL;
		FS_Print_Warn("Creat Done\n");
		return NewNode;
	}else//说明该目录下已有节点 ，向后继续添加节点
	{
		FS_Node*CurrentNode=Node->In;
		//跳过先前已经注册的文件节点
		while(CurrentNode->Next!=NULL)
		{
			CurrentNode = CurrentNode->Next;
		}
		CurrentNode->Next=NewNode;
        strcpy(NewNode->Name,Name);
        NewNode->Type=Type;
        NewNode->Out=Node;
        NewNode->In=NULL;
        NewNode->Next=NULL;
		FS_Print_Warn("Creat Done\n");
		return NewNode;
	}
}


//删除文件节点
//父文件节点，名字
u8 FS_Node_Delete(FS_Node*Node,const char*Name)
{
	//检查父文件节点有效性
	if(Node==NULL)
	{
		FS_Print_Error("Error ");
		FS_Print_Error("Invalid Node\n");
		return 1;
	}
	//检查父文件节点内是否有文件节点
	FS_Node*CurrentNode=Node->In;
	if(CurrentNode==NULL)
	{
		FS_Print_Error("Error ");
		FS_Print_Error("No Node\n");
		return 2;
	}

	FS_Node*LastNode=CurrentNode;
	//查找要删除的文件节点
   	while(strcmp(CurrentNode->Name,Name)!=0)
	{
		LastNode=CurrentNode;
		CurrentNode=CurrentNode->Next;
		//结束遍历
		if(CurrentNode==NULL)//要删除的文件节点不存在
		{
			FS_Print_Error("Error ");
			FS_Print_Error("No Node\n");
			return 3;
		}
   }

	//如果删除的是第一个文件节点
	if(CurrentNode==CurrentNode->Out->In)
	{
		CurrentNode->Out->In=CurrentNode->Next;
	}
	//如果删除的是最后一个文件节点
	if(CurrentNode->Next==NULL)
	{
		LastNode->Next=NULL;
	}else//如果删除的不是最后一个文件节点
	{
		LastNode->Next=CurrentNode->Next;
	}

	//如果该文件节点不包含其他文件节点
   	if(CurrentNode->In==NULL)
	{
		free(CurrentNode);
	}else//如果该文件节点包含其他文件节点
	{
		LastNode=CurrentNode;
        CurrentNode=CurrentNode->In;
		free(LastNode);
	    while(CurrentNode->Next!=NULL)
		{
			if(CurrentNode->In!=NULL)//如果该文件节点包含其他文件节点
		    {
		    	//删除其所包含的文件节点
		        FS_Node_Delete(CurrentNode,CurrentNode->In->Name); 
			}
			LastNode=CurrentNode;
	        CurrentNode=CurrentNode->Next;
	        free(LastNode);
	        //结束遍历
	        if(CurrentNode==NULL)
	        {
	    		break;
			}
	    }
    }
	FS_Print_Warn("Delete Done\n");
	return 0;
}



//显示父文件节点
//父文件节点
void FS_Node_List(FS_Node*Node)
{
	FS_Print_Warn("--------\n");
	//显示父当前文件节点名称
    FS_Print_Normal("%s\n",Node->Name);
    
    //检查当前文件节点是否为空
    if(Node->In!=NULL)
	{
		//切换到该文件节点内的文件节点
		FS_Node*CurrentNode=Node->In;
		if(CurrentNode->Type==Directory)
		{//目录类型 
			FS_Print_Normal("|>%s\n",CurrentNode->Name);
		}else
		{//文件类型 
			FS_Print_Normal("|=%s\n",CurrentNode->Name);
		}
	    // CurrentNode=Node->In;
	    //遍历当前文件节点下所有文件节点
	    while(CurrentNode->Next!=NULL)
		{
			 CurrentNode = CurrentNode->Next;
	        if(CurrentNode->Type==Directory)
			{//目录类型 
	            FS_Print_Normal("|>%s\n",CurrentNode->Name);
	        }else
			{//文件类型 
	            FS_Print_Normal("|=%s\n",CurrentNode->Name);
	        }
	    }
	}

	//检查其父文件节点是否为空
	if(Node->Out!=NULL)
	{
		//如果不为空则显示退出符号
		FS_Print_Normal("<%s\n",Node->Out->Name);
	}
	FS_Print_Warn("--------\n");
	return;
}




//新建文件节点
//父文件节点，节点类型，节点名称
void FS_New(const char*Type,const char*Name)
{
	FS_Type Type_Type=File;
	//判断文件类型
	if(strcmp(Type,"f")==0)
	{
		Type_Type=File;
	}else
	if(strcmp(Type,"d")==0)
	{
		Type_Type=Directory;
	}else
	{
		FS_Print_Warn("Type Warn\n");
	}

	//新建文件节点
	if(FS_Node_Create(FS_Node_Current,Type_Type,Name)==NULL)
	{
		FS_Print_Error("Creat Fail\n");
	}
	//显示父文件节点
    FS_Node_List(FS_Node_Current);
	return;
}





//删除文件节点
//父文件节点节点名称
void FS_Delete(const char*Name)
{
	//删除文件节点
	if(FS_Node_Delete(FS_Node_Current,Name))
	{
		FS_Print_Error("Delete Fail\n");
	}
	
	//显示父文件节点
    FS_Node_List(FS_Node_Current);
	return;
}


//显示文件节点
//父文件节点
void FS_Show()
{
	//显示父文件节点
    FS_Node_List(FS_Node_Current);
	return;
}







//打开文件节点
//名称
void FS_Open(const char*Name)
{
	//如果文件节点为.则返回先前文件节点
	if(strcmp(Name,".")==0)
	{
		if(FS_Node_Current->Out==NULL)
		{
			FS_Print_Error("Back Fail\n");
			FS_Print_Error("No Node\n");
		}else
		{
			FS_Node_Current=FS_Node_Current->Out;
		}
		//显示父文件节点
    	FS_Node_List(FS_Node_Current);
		return;
	}else
	{
		FS_Node*CurrentNode=FS_Node_Current->In;
		if(CurrentNode==NULL)
		{
			FS_Print_Error("Open Fail\n");
			FS_Print_Error("No Node\n");
		}else
		{
			//查找选定的文件节点
			while(strcmp(CurrentNode->Name,Name)!=0)
			{
				CurrentNode=CurrentNode->Next;
				//结束遍历
				if(CurrentNode==NULL)
				{
					//文件节点不存在
					FS_Print_Error("Open Fail\n");
					FS_Print_Error("No Name\n");
					//显示父文件节点
					FS_Node_List(FS_Node_Current);
					return;
				}
			}
			//找到文件节点
			FS_Node_Current=CurrentNode;
		}
		//显示父文件节点
		FS_Node_List(FS_Node_Current);
		return;
	}
} 









