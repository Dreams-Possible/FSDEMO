#ifndef FS_H
#define FS_H

#include"Main.h"

//重定义Printf函数
#define FS_Print_Error printf
#define FS_Print_Warn printf
#define FS_Print_Normal printf

//重定义节点名称最大字符数
#define FS_Node_Name_MAXNumber 32


//定义文件节点类型
typedef enum
{
    File,//文件类型
    Directory,//目录类型
}FS_Type;

//定义文件节点
typedef struct FS_Node
{
    u8 Name[FS_Node_Name_MAXNumber];//文件或目录的名称

    FS_Type Type;//文件类型

    struct FS_Node *Out;//指向上级目录的指针
    struct FS_Node *In;//指向下级目录/文件的指针
    //struct FS_Node *Last;//指向当前目录上一文件节点的指针
	struct FS_Node *Next;//指向当前目录下一文件节点的指针

}FS_Node;


//创建节点索引
//当前父文件夹
extern FS_Node*FS_Node_Current;



//初始化文件节点
//创建根目录
u8 FS_Initialization();


//创建文件节点
//父文件节点，节点类型，节点名称
FS_Node*FS_Node_Create(FS_Node*Node,FS_Type Type,const char*Name);

//显示父文件节点
//父文件节点
void FS_Node_List(FS_Node*Node);

//新建文件节点
//父文件节点，节点类型，节点名称
void FS_New(const char*Type,const char*Name);

//显示文件节点
//父文件节点
void FS_Show();

//打开文件节点
//名称
void FS_Open(const char*Name);





// //声明当前文件节点全局变量 
// extern FS_Node*FS_CurrentNode;


// //创建文件节点 
// FS_Node*CreateFS_Node(u8*FileName,FS_Type FS_Type_FS_Node);

// //添加文件节点 
// int AddFS_Node(FS_Node*TargetFS_Node,FS_Node*NewFS_Node);

// //显示选定文件节点及其内部的所有文件节点
// int ShowFS_Node(u8*TargetFS_Node); 

// //文件节点初始化 
// void FS_NodeInit();

// //新建文件节点
// int NewFS_Node(u8*FileType,u8*FileName); 






#endif
