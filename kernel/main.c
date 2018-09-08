
/*++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                            main.c
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++
                                                    Forrest Yu, 2005
++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++++*/


//
//  main.c
//
//  Created by wennie on 2017/9/18.
//  Copyright © 2017年 wennie. All rights reserved.
//

#include <stdio.h>
#include <string.h>

/*======================================================================*
                            kernel_main
 *======================================================================*/
PUBLIC int kernel_main()
{
	disp_str("-----\"kernel_main\" begins-----\n");

	struct task* p_task;
	struct proc* p_proc= proc_table;
	char* p_task_stack = task_stack + STACK_SIZE_TOTAL;
	u16   selector_ldt = SELECTOR_LDT_FIRST;
        u8    privilege;
        u8    rpl;
	int   eflags;
	int   i, j;
	int   prio;
	for (i = 0; i < NR_TASKS+NR_PROCS; i++) {
	        if (i < NR_TASKS) {     /* 任务 */
                        p_task    = task_table + i;
                        privilege = PRIVILEGE_TASK;
                        rpl       = RPL_TASK;
                        eflags    = 0x1202; /* IF=1, IOPL=1, bit 2 is always 1 */
			prio      = 15;
                }
                else {                  /* 用户进程 */
                        p_task    = user_proc_table + (i - NR_TASKS);
                        privilege = PRIVILEGE_USER;
                        rpl       = RPL_USER;
                        eflags    = 0x202; /* IF=1, bit 2 is always 1 */
			prio      = 5;
                }

		strcpy(p_proc->name, p_task->name);	/* name of the process */
		p_proc->pid = i;			/* pid */

		p_proc->ldt_sel = selector_ldt;

		memcpy(&p_proc->ldts[0], &gdt[SELECTOR_KERNEL_CS >> 3],
		       sizeof(struct descriptor));
		p_proc->ldts[0].attr1 = DA_C | privilege << 5;
		memcpy(&p_proc->ldts[1], &gdt[SELECTOR_KERNEL_DS >> 3],
		       sizeof(struct descriptor));
		p_proc->ldts[1].attr1 = DA_DRW | privilege << 5;
		p_proc->regs.cs	= (0 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.ds	= (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.es	= (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.fs	= (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.ss	= (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.gs	= (SELECTOR_KERNEL_GS & SA_RPL_MASK) | rpl;

		p_proc->regs.eip = (u32)p_task->initial_eip;
		p_proc->regs.esp = (u32)p_task_stack;
		p_proc->regs.eflags = eflags;

		/* p_proc->nr_tty		= 0; */

		p_proc->p_flags = 0;
		p_proc->p_msg = 0;
		p_proc->p_recvfrom = NO_TASK;
		p_proc->p_sendto = NO_TASK;
		p_proc->has_int_msg = 0;
		p_proc->q_sending = 0;
		p_proc->next_sending = 0;

		for (j = 0; j < NR_FILES; j++)
			p_proc->filp[j] = 0;

		p_proc->ticks = p_proc->priority = prio;

		p_task_stack -= p_task->stacksize;
		p_proc++;
		p_task++;
		selector_ldt += 1 << 3;
	}

	k_reenter = 0;
	ticks = 0;

	p_proc_ready	= proc_table;

	init_clock();
        init_keyboard();

	restart();

	while(1){}
}

/*======================================================================*
                               TestA
 *======================================================================*/
void TestA()
{

}


//文件系统
//要实现的指令：
//touch 创建空文件
//mkdir 创建空文件夹
//rm	删除文件
//rmdir	删除空文件夹
//file	查看文件
//ls	查看当前路径下文件列表
//cd	更改路径
//sv	保存当前文件系统

#define MAX_FILE_NAME_LEN 30
#define MAX_FILE_CONTENT_LEN 50
#define MAX_CHILDREN_NUM 10

#define SYS_DATA_FILE_NAME "dataFile"

//文件ID  文件名  文件类型（-1为空、0为文件夹、1为文件）  父节点ID  
//0 孩子数  孩子ID数组
//1 文本字符串
struct FCB {
	int type;
	int FCBID;
	int fatherID;
	char FCBName[MAX_FILE_NAME_LEN];

	char content[MAX_FILE_CONTENT_LEN];

	int childrenNum;
	int children[MAX_CHILDREN_NUM];
};

int nextID
*FCB currentDir;

int NewFCB()
{

}

//从虚拟硬盘中加载初始文件系统
void FMInit()
{

}

void ReadCommand()
{

}

//创建空文件
void Command_touch()
{

}

//创建空文件夹
void Command_mkdir()
{

}

//删除文件
void Command_rm()
{

}

//删除空文件夹
void Command_rmdir()
{

}

//查看文件
void Command_file()
{

}

//查看文件夹
void Command_ls()
{

}

//改变路径
void Command_cd()
{

}

//保存当前文件系统
void Command_sv()
{

}

//帮助菜单
void ShowHelp()
{

}

//输入指令有误
void CommandWrong()
{

}
char currentCmd[128];

void TestB()
{
	int fd_stdin = open("/dev_tty1", O_RDWR);
	assert(fd_stdin == 0);
	int fd_stdout = open("/dev_tty1", O_RDWR);
	assert(fd_stdout == 1);

	FMInit();

	while (1) {
		//ReadCommand();

		if (currentCmd[0] == 't'&&currentCmd[1] == 'o'&&currentCmd[2] == 'u'&&currentCmd[3] == 'c'&&currentCmd[4] == 'h')
			Command_touch();

		else if (currentCmd[0] == 'm'&&currentCmd[1] == 'k'&&currentCmd[2] == 'd'&&currentCmd[3] == 'i'&&currentCmd[5] == 'r')
			Command_mkdir();

		else if (currentCmd[0] == 'r'&&currentCmd[1] == 'm')
			Command_rm();

		else if (currentCmd[0] == 'r'&&currentCmd[1] == 'm'&&currentCmd[2] == 'd'&&currentCmd[3] == 'i'&&currentCmd[4] == 'r')
			Command_rmdir();

		else if (currentCmd[0] == 'f'&&currentCmd[1] == 'i'&&currentCmd[2] == 'l'&&currentCmd[3] == 'e')
			Command_file();

		else if (currentCmd[0] == 'l'&&currentCmd[1] == 's')
			Command_ls();

		else if (currentCmd[0] == 'c'&&currentCmd[1] == 'd')
			Command_cd();

		else if (currentCmd[0] == 's'&&currentCmd[1] == 'v')
			Command_sv();

		else if (!strcmp(cuurentCmd, "help") || !strcmp(cuurentCmd, "Help") || !strcmp(cuurentCmd, "HELP"))
			ShwoHelp();

		else CommandWrong();
	}
}
