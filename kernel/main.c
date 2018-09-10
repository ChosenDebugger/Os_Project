#include "type.h"
#include "stdio.h"
#include "const.h"
#include "protect.h"
#include "string.h"
#include "fs.h"
#include "proc.h"
#include "tty.h"
#include "console.h"
#include "global.h"
#include "proto.h"

#define MAX_COMMAND_LEN 128

////////////////////////////////BasicFunctions/////////////////////////////

//清屏
void clear()
{
	clear_screen(0, console_table[current_console].cursor);
	console_table[current_console].crtc_start = 0;
	console_table[current_console].cursor = 0;

}

//指令列表
void help()
{
	clear();

	printf(" ==============================================================================\n");
	printf(" ==============================================================================\n");
	printf(" ==                                                                            \n");
	printf(" ==                        <-  Command List  ->                                \n");
	printf(" ==                                                                            \n");
	printf(" ==                                                                            \n");
	printf(" ==              1. help	       ----     Show Help                          \n");
	printf(" ==              2. Carlendar      ----     Start Carlendar                    \n");
	printf(" ==              3. Calculator     ----     Start Calculator                   \n");
	printf(" ==              4. Game1          ----     Play Finger Guessing               \n");
	printf(" ==              5. Game2          ----     Play GoBang                        \n");
	printf(" ==              6. Game3          ----     Play MineSweeper                   \n");
	printf(" ==                                                                            \n");
	printf(" ==                                                                            \n");
	printf(" ==                                                                            \n");
	printf(" ==============================================================================\n");
	printf(" ==============================================================================\n");

}

void startAnimate() {
	long int ii = 9999;
	printf("System is loading...");

	while (ii-->0); ii = 2999999;
	printf("................");
	while (ii-->0); ii = 2999999;
	printf("......");
	while (ii-->0); ii = 999999;
	printf("..");
	while (ii-->0); ii = 6999999;
	printf("..............................");
	while (ii-->0); ii = 9999;
	printf("......");
	while (ii-->0); ii = 999999;
	printf("..");
	while (ii-->0); ii = 9999;
	printf("..");
	while (ii-->0); ii = 999;
	printf(".......");
}


/////////////////////////APPLICATION///////////////////////////////////

//////////////////////////Carlendar////////////////////////////////////

int year, month, day;
int day_of_month[12] = { 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31 };
int current_year, current_month, current_day;

int judgement(int y)  // runnian
{
	if (y % 400 == 0 || (y % 100 != 0 && y % 4 == 0))
		return 1;
	else return 0;
}

int show_week(int year, int month, int day)
{
	/*
	公式:w=(y+[y/4]+[c/4]-2c+[26(m+1)/10]+d-1)%7
	*/
	int w, k;   //zhou ji
	int year_last = year % 100, c = year / 100, m = month;
	if (month == 1)
	{
		year_last -= 1;
		m = 13;
	}
	else if (month == 2)
	{
		year_last -= 1;
		m = 14;
	}
	w = (year_last + year_last / 4 + c / 4 - 2 * c + 26 * (m + 1) / 10 + day - 1); // abs  
	if (w<0)
	{
		k = (w % 7 + 7) % 7;
	}
	else k = w % 7;
	return k;
}

void print_year_month(int fd_stdin)
{
	char inputCmd[MAX_COMMAND_LEN];
	int k, x, first_week;
	int r = 0;
	printf("Please input the year:");

	r = read(fd_stdin, inputCmd, 70);
	inputCmd[r] = 0;
	atoi(inputCmd, &year);

	month = 1;
	do
	{
		clear();
		/*printf("Please input the month: ");
		r = read(fd_stdin, inputCmd, 70);
		inputCmd[r] = 0;
		atoi(inputCmd, &month);
		if (month<1 || month>12)
		{
		printf("The month you input is wrong, please input again!\n");
		printf("Please input the year:");
		}
		} while (1>month || month>12);*/

		char* month_word;
		if (month == 1)
			month_word = "January";
		else if (month == 2)
			month_word = "February";
		else if (month == 3)
			month_word = "March";
		else if (month == 4)
			month_word = "April";
		else if (month == 5)
			month_word = "May";
		else if (month == 6)
			month_word = "June";
		else if (month == 7)
			month_word = "July";
		else if (month == 8)
			month_word = "August";
		else if (month == 9)
			month_word = "September";
		else if (month == 10)
			month_word = "October";
		else if (month == 11)
			month_word = "November";
		else if (month == 12)
			month_word = "December";

		printf("=========================================================\n");
		printf("                         Year %d                         \n", year);
		printf("                         Month %s                        \n", month_word);
		printf("=========================================================\n");
		if (judgement(year))
		{
			day_of_month[1] = 29;
		}
		else day_of_month[1] = 28;
		first_week = show_week(year, month, 1);
		printf("Sun    Mon    Tue    Wed    Thu    Fri    Sat\n");
		for (x = 1; x <= first_week; x++)
		{
			printf("       ");
			if (x % 7 == 0) printf("\n");

		}
		for (k = 1; k <= day_of_month[month - 1]; k++)
		{
			printf("%d     ", k);
			if (k < 10) printf(" ");
			if (x % 7 == 0) printf("\n");
			x++;
		}

		printf("\n");
		printf("=========================================================\n");
		printf("                   Festivals Of This Month               \n");
		printf("=========================================================\n");
		switch (month)
		{
		case 1:
			printf("January 1st is New Year's Day.");
			break;
		case 2:
			printf("Feburary 14th is Valentines Day");
			break;
		case 3:
			printf("March 8th is Women's Day\n");
			printf("March 12th is Arbor Day");
			break;
		case 4:
			printf("April 1st is April Fools Day\n");
			printf("April 5th is Tomb-sweeping Day");
			break;
		case 5:
			printf("May 1st is Labor Day\n");
			printf("May 4th is Chinese Youth Day");
			break;
		case 6:
			printf("June 1st is Children's Day");
			break;
		case 8:
			printf("August 1st is the Army's Day");
			break;
		case 9:
			printf("September 10th is Teacher's Day");
			break;
		case 10:
			printf("October 1st is National Day\n");
			printf("October 31st is Helloween Day");
			break;
		case 12:
			printf("December 25th is Christmas Day");
			break;
		}
		printf("\n\n");
		printf("Choose the number of options: 1.Next Month    2.Last Month    3.Exit Calendar\n");
		int option = 0;
		r = read(fd_stdin, inputCmd, 70);
		inputCmd[r] = 0;
		atoi(inputCmd, &option);
		if (option == 1)
		{
			month++;
			if (month == 13)
			{
				month = 1;
				year++;
			}
		}
		else if (option == 2)
		{
			month--;
			if (month == 0)
			{
				month = 12;
				year--;
			}
		}
		else
			break;

	} while (1);

}

void print(int year, int month, int day, int fd_stdin)
{
	char inputCmd[MAX_COMMAND_LEN];
	int r = 0;
	int week;
	printf("Please input the year:");
	do
	{
		r = read(fd_stdin, inputCmd, 70);
		inputCmd[r] = 0;
		atoi(inputCmd, &year);

		printf("Please input the month:");
		r = read(fd_stdin, inputCmd, 70);
		inputCmd[r] = 0;
		atoi(inputCmd, &month);

		printf("Please input the day:");
		r = read(fd_stdin, inputCmd, 70);
		inputCmd[r] = 0;
		atoi(inputCmd, &day);
		//scanf("%d %d %d", &year, &month, &day);
		if (judgement(year))
		{
			day_of_month[1] = 29;
		}
		printf("\n");
		if (day <= 0 || day >day_of_month[month - 1])
			printf("Month %d don't have day %d,please input again:", month, day);
	} while (day <= 0 || day >day_of_month[month - 1]);
	week = show_week(year, month, day);
	printf("\n");
	switch (month)
	{
	case 1:switch (day)
	{
	default:printf("not festival");
	}break;
	case 2:switch (day)
	{
	case 14:printf("Valentines Day"); break;
	default:printf("not festival");
	}break;
	case 3:switch (day)
	{
	case 8:printf("Women's Day"); break;
	case 12:printf("Arbor Day"); break;
	default:printf("not festival");
	}break;
	case 4:switch (day)
	{
	case 1:printf("April Fools Day"); break;
	case 5:printf("Tomb-sweeping Day"); break;
	default:printf("not festival");
	}break;
	case 5:switch (day)
	{
	case 1:printf("Labor Day"); break;
	case 4:printf("Chinese Youth Day");
	default:printf("not festival");
	}break;
	case 6:switch (day)
	{
	case 1:printf("Children's Day"); break;
	default:printf("not festival");
	}break;
	case 8:switch (day)
	{
	case 1:printf("the Army's Day"); break;
	default:printf("not festival");
	}break;
	case 9:switch (day)
	{
	case 10:printf("Teacher's Day"); break;
	default:printf("not festival");
	}break;
	case 10:switch (day)
	{
	case 1:printf("National Day"); break;
	case 31:printf("Helloween Day"); break;
	default:printf("not festival");
	}break;
	case 12:switch (day)
	{
	case 25:printf("Christmas Day"); break;
	default:printf("not festival");
	}break;
	}
	printf("\n");
	printf("%d %d %d is:", year, month, day);
	switch (week)  //zhouji
	{
	case 0:printf("Sunday"); break;
	case 1:printf("Monday"); break;
	case 2:printf("Tuesday"); break;
	case 3:printf("Wednesday");; break;
	case 4:printf("Thursday"); break;
	case 5:printf("Friday"); break;
	case 6:printf("Saturday"); break;
	}
	printf("\n");
}

void Carlendar(int fd_stdin, int fd_stdout)
{
	char inputCmd[MAX_COMMAND_LEN];
	int r = 0;
	int choice, year = 1000, month = 0, day = 0, flag = 1;
	char c, k;
	for (; 1;)
	{
		printf("==========================================================\n");
		printf("||  ____     _            ____         ___   ____  ___  ||\n");
		printf("|| |        / \\    |     |     |\\   | |   \\ |     |   | ||\n");
		printf("|| |       /   \\   |     |____ | \\  | |   | |____ |___| ||\n");
		printf("|| |      /_____\\  |     |     |  \\ | |   | |     | \\   ||\n");
		printf("|| |____ /       \\ |____ |____ |   \\| |___/ |____ |   \\ ||\n");
		printf("||                                                      ||\n");
		printf("||                                                      ||\n");
		printf("||                    1.Use Calendar                    ||\n");
		printf("||                    2.Search Date                     ||\n");
		printf("||                    0.Exit                            ||\n");
		printf("||                                                      ||\n");
		printf("||========================================================\n");
		printf("\n");
		printf("Please input your choose:   ");
		do
		{
			if (flag)
			{
				r = read(fd_stdin, inputCmd, 70);
				inputCmd[r] = 0;
				if (strcmp(inputCmd, "clear") == 0 || strcmp(inputCmd, "Clear") == 0)
				{
					clear();

					printf("==========================================================\n");
					printf("||  ____     _            ____         ___   ____  ___  ||\n");
					printf("|| |        / \\    |     |     |\\   | |   \\ |     |   | ||\n");
					printf("|| |       /   \\   |     |____ | \\  | |   | |____ |___| ||\n");
					printf("|| |      /_____\\  |     |     |  \\ | |   | |     | \\   ||\n");
					printf("|| |____ /       \\ |____ |____ |   \\| |___/ |____ |   \\ ||\n");
					printf("||                                                      ||\n");
					printf("||                                                      ||\n");
					printf("||                    1.Use Calendar                    ||\n");
					printf("||                    2.Search Date                     ||\n");
					printf("||                    0.Exit                            ||\n");
					printf("||                                                      ||\n");
					printf("||========================================================\n");
					printf("\n");

					printf("Please input your choose:   ");
					continue;
				}
				c = inputCmd[0];
				printf("\n");
				printf("Are you sure choose %c? (y/Y)or(n/N):   ", c);
			}
			if (flag)
			{
				r = read(fd_stdin, inputCmd, 70);
				inputCmd[r] = 0;
				k = inputCmd[0];
			}
			if (k == 'y' || k == 'Y')
			{
				printf("\n");
				if (c == '\n')
				{
					printf("\n");
					printf("input is wrong,please input the number\n");
					printf("\n");
					printf("Please input your choose:   ");
				}
				else
				{
					choice = c - '0';
					if (choice < 0 || choice > 3)
					{
						printf("input is wrong,please input number between 1-3\n");
					}
					else break;
				}
			}
			else if (k == 'n' || k == 'N')
			{
				printf("\n");
				printf("You choose NO,please input again:   ");
				flag = 1;
			}
			if ((k != 'y'&& k != 'Y'&& k != 'n'&& k != 'N'))
			{
				printf("\n");
				printf("please input y/n:   ");
				flag = 0;
				if (flag == 0)
				{
					r = read(fd_stdin, inputCmd, 70);
					inputCmd[r] = 0;
					k = inputCmd[0];
					printf("\n");
					//getchar();
				}
			}
		} while (1);

		if (choice == 1)
		{
			print_year_month(fd_stdin);

		}
		else if (choice == 2)
		{
			print(year, month, day, fd_stdin);

		}

		else if (choice == 0)
			break;
		else
		{
			printf("input is wrong,please input the number\n");
		}
	}
}


//////////////////////////Calculator///////////////////////////////////

#define FORMULA_LENGTH_ 500

char Input[FORMULA_LENGTH_];
char formula[FORMULA_LENGTH_];
int token = 0;
int InitFormula();
double level1();
double level2();
double level3();
int IsAllowed(char temp);
int IsBlank(char c);
double Transfer();

int InitFormula() {
	int t = 0, i = 0;
	int type = 0;
	for (int i = 0; i < strlen(Input); i++) {
		if (!IsAllowed(Input[i]))
			return 0;
		else if (IsBlank(Input[i]))
			continue;
		else if (Input[i] == '\0')
			break;
		else {
			formula[t] = Input[i];
			t++;
		}
		if (Input[i] == '.')
			type = 1;
	}
	if (type == 0)
		return 1;
	else
		return 2;
}

//+ & -
double level1() {
	double temp = level2();
	while (formula[token] == '+' || formula[token] == '-') {
		switch (formula[token]) {
		case '+': token++;
			temp = temp + level2();
			break;
		case '-': token++;
			temp = temp - level2();
			break;
		}
	}
	return temp;
}

//* & /
double level2() {
	double temp = level3();
	while (formula[token] == '*' || formula[token] == '/') {
		switch (formula[token]) {
		case '*': token++;
			temp = temp * level3();
			break;
		case '/': token++;
			temp = temp / level3();
			break;
		}
	}
	return temp;
}

double level3() {
	double temp;
	if (formula[token] == '(') {
		token++;
		temp = level1();
		token++;
	}
	else if ((int)formula[token] >= 48 && (int)formula[token] <= 57) {
		temp = Transfer();
	}
	return temp;
}

int IsAllowed(char temp) {
	if (temp == '+' || temp == '-' || temp == '*' || temp == '/'
		|| (int)temp >= 48 && (int)temp <= 57
		|| temp == '(' || temp == ')' || temp == '.'
		|| IsBlank(temp))
		return 1;
	else
		return 0;
}

int IsBlank(char c) {
	if (c == ' ' || c == '\t' || c == '\n')
		return 1;
	else
		return 0;
}

double Transfer() {
	double temp = 0;
	while ((int)formula[token] >= 48 && (int)formula[token] <= 57) {
		temp = temp * 10 + (int)formula[token] - 48;
		token++;
	}
	if (formula[token] == '.') {
		token++;
		while ((int)formula[token] >= 48 && (int)formula[token] <= 57 && token < strlen(Input)) {
			double add = (int)formula[token] - 48;
			add = add * 0.1;
			temp = temp + add;
			token++;
		}
	}
	return temp;
}

void Calculator(fd_stdin,fd_stdout) {
	clear();

	printf("==========================================================================\n");
	printf("|  ____     _           ____                 _    ______  ____   _____   |\n");
	printf("| |        / \\    |    |     |    | |       / \\      |   |    | |     |  |\n");
	printf("| |       /   \\   |    |     |    | |      /   \\     |   |    | |_____|  |\n");
	printf("| |      /_____\\  |    |     |    | |     /_____\\    |   |    | |  \\    |\n");
	printf("| |____ /       \\ |___ |____ |____| |___ /       \\   |   |____| |   \\   |\n");
	printf("|________________________________________________________________________|\n");
	printf("|                                                                        |\n");
	printf("|                 Input your formula                                     |\n");
	printf("|                                                                        |\n");
	printf("|                    For example: 5+2                                    |\n");
	printf("==========================================================================\n");
	printf("\n");

	while (1) {
		for (int i = 0; i < FORMULA_LENGTH_; i++) {
			Input[i] = '\0';
			formula[i] = '\0';
		}
		token = 0;
		int r = read(fd_stdin, Input, FORMULA_LENGTH_);
		Input[r] = 0;
		if (strcmp(Input, "q") == 0) {
			break;
		}
		int test = InitFormula();
		if (!test) {
			printf("error!");
			continue;
		}
		double result = level1();
		if (test == 1)
			printf("result is : %d\n", (int)result);
		else if (test == 2) {
			char re[5];
			for (int i = 0; i < 5; i++) {
				int t = 1;
				for (int j = 0; j <= i; j++)
					t = t * 10;
				re[i] = (char)(result * t) % 10 + 48;
			}
			printf("result is : %d.%s\n", (int)result, re);
		}
	}
}

///////////////////////////GAME////////////////////////////////////////

///////////////////////Finger-Guessing/////////////////////////////////

int computer_game(int count)
{
	int result = 0;
	int num = count % 7;

	if (num == 1)
	{
		result = 1; //石头
	}
	else if (num == 2)
	{
		result = 0;//剪刀
	}
	else if (num == 3)
	{
		result = 1;//石头
	}
	else if (num == 4)
	{
		result = 2;//布
	}
	else if (num == 5)
	{
		result = 0;//剪刀
	}
	else if (num == 6)
	{
		result = 2;//布
	}
	else if (num == 0)
	{
		result = 1;//石头
	}
	return result;
}

void Guessing(fd_stdin, fd_stdout)
{
	int gamer = 1;			// 玩家出拳
	int computer = 0;		// 电脑出拳
	int result;				// 比赛结果
	int count = 0;

	char inputCmd[MAX_COMMAND_LEN];

	int r;

	printf("    *                                                                     \n");
	printf("    *     ~~~~  ** **** **  ~~~~                                          \n");
	printf("    *    ~~  **           **   ~~     Welcome!                            \n");
	printf("    *   ~~  **   ^^    ^^  **   ~~    Game-1:FingerGuessing               \n");
	printf("    *  ~~~~**     @    @    **~~~~~                                       \n");
	printf("    *      **    _______    **        RULES:                              \n");
	printf("    *      **    | * * |    **        PVE                                 \n");
	printf("    *      **    ~~~~~~~    **        Enter q to quit this program        \n");
	printf("    *       **      3      **                                             \n");
	printf("    *        **           **           GGGG    A    M  M EEEE              \n");
	printf("    *          ***********             G  __  A A   M\~M E___              \n");
	printf("    *                                  G  G  AAAAA  M  M E                 \n");
	printf("    *                                  GGGG A     A M  M EEEE              \n");
	printf("    *                                                                     \n");
	printf("    *    ********************************************************         \n");


	while (1) {
		count++;
		printf("\n");
		printf("Please enter your choice:\n");
		printf("A:Scissors\nB:Stone\nC:Cloth\nD:Ending game\n");

		r = read(fd_stdin, inputCmd, 70);
		inputCmd[r] = 0;
		gamer = inputCmd[0];


		if (gamer == 'Q' || gamer == 'q')
		{
			break;
		}
		else if (gamer == 'A' || gamer == 'a')
		{
			gamer = 4;
		}
		else if (gamer == 'B' || gamer == 'b')
		{
			gamer = 7;
		}
		else if (gamer == 'C' || gamer == 'c')
		{
			gamer = 10;
		}
		else if (gamer == 'D' || gamer == 'd')
		{
			break;
		}
		else
		{
			printf("Your choice is %c wrong!exiting...\n", gamer);
			break;
		}

		computer = computer_game(count);  // 产生随机数，得到电脑出拳
		result = (int)gamer + computer;  // gamer 为 char 类型，数学运算时要强制转换类型
		printf("Computer ");
		switch (computer)
		{
		case 0:printf("Scissors\n"); break; //4    1
		case 1:printf("Stone\n"); break; //7  2
		case 2:printf("Cloth\n"); break;   //10 3
		}
		printf("You ");
		switch (gamer)
		{
		case 4:printf("Scissors\n"); break;
		case 7:printf("Stone\n"); break;
		case 10:printf("Cloth\n"); break;
		}
		if (result == 6 || result == 7 || result == 11) printf("You Win!");
		else if (result == 5 || result == 9 || result == 10) printf("Computer Wins!\n");
		else printf("Draw!");
	}
}


///////////////////////////GoBang//////////////////////////////////////

struct Pos
{
	int x;
	int y;
};

void table_printf(int info)
{
	switch (info)
	{
	case 0:printf("+"); break;
	case 1:printf("x"); break;
	case 2:printf("o");
	}
}

void draw_table_for_gobang(int table[15][15], struct Pos pos)
{
	clear();
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (i == pos.x&&j == pos.y)table_printf(1);
			else table_printf(table[i][j]);
			printf(" ");
		}
		printf("\n");
	}
}

int judge_for_gobang(int table[15][15])
{
	for (int i = 0; i < 10; i++)
	{
		for (int j = 0; j < 10; j++)
		{
			if (table[i][j] == table[i + 1][j] && table[i][j] == table[i + 2][j] && table[i][j] == table[i + 3][j] && table[i][j] == table[i + 4][j])
			{
				if (table[i][j] == 1)return 1;
				else if (table[i][j] == 2)return 2;
			}
			if (table[i][j] == table[i][j + 1] && table[i][j] == table[i][j + 2] && table[i][j] == table[i][j + 3] && table[i][j] == table[i][j + 4])
			{
				if (table[i][j] == 1)return 1;
				else if (table[i][j] == 2)return 2;
			}
			if (table[i][j] == table[i + 1][j + 1] && table[i][j] == table[i + 2][j + 2] && table[i][j] == table[i + 3][j + 3] && table[i][j] == table[i + 4][j + 4])
			{
				if (table[i][j] == 1)return 1;
				else if (table[i][j] == 2)return 2;
			}
		}
		for (int j = 4; j < 15; j++)
		{
			if (table[i][j] == table[i + 1][j - 1] && table[i][j] == table[i + 2][j - 2] && table[i][j] == table[i + 4][j - 4] && table[i][j] == table[i + 3][j - 3])
			{
				if (table[i][j] == 1)return 1;
				else if (table[i][j] == 2)return 2;
			}
		}
	}
	return 0;
}

void gobang(fd_stdin, fd_stdout)
{
	int table[15][15] = { 0 };
	int d1 = 0, d2 = 0, d3 = 0, d4 = 0;
	char com = 0;
	struct Pos now;
	now.x = 7;
	now.y = 7;

	char inputCmd[MAX_COMMAND_LEN];

	while (1)
	{
		clear();
		printf("    *                                                                     \n");
		printf("    *     ~~~~  ** **** **  ~~~~                                          \n");
		printf("    *    ~~  **           **   ~~     Welcome!                            \n");
		printf("    *   ~~  **   ^^    ^^  **   ~~    Game-4:BoxMan               \n");
		printf("    *  ~~~~**     @    @    **~~~~~                                       \n");
		printf("    *      **    _______    **        RULES:                              \n");
		printf("    *      **    | * * |    **        s:DOWN d:RIGHT s:UP  a:LEFT q:QUIT      \n");
		printf("    *      **    ~~~~~~~    **        ILLUSTRATE:                             \n");
		printf("    *       **      3      **         #:WALL d:DESTINATION b:BOX  &:PEOPLE  \n");
		printf("    *        **           **           GGGG    A    M  M EEEE              \n");
		printf("    *          ***********             G  __  A A   MMMM E___              \n");
		printf("    *                                  G  G  AAAAA  M  M E                 \n");
		printf("    *                                  GGGG A     A M  M EEEE              \n");
		printf("    *                                                                     \n");
		printf("    *    ********************************************************         \n");

		int len = read(fd_stdin, inputCmd, 70);
		inputCmd[len] = 0;
		com = inputCmd[0];

		if (com == 'b')
		{
			draw_table_for_gobang(table, now);
			while (1)
			{
				len = read(fd_stdin, inputCmd, 70);
				inputCmd[len] = 0;
				com = inputCmd[0];

				switch (com)
				{
				case 'a':now.y -= 1;
					draw_table_for_gobang(table, now);
					break;
				case 's':now.x += 1;
					draw_table_for_gobang(table, now);
					break;
				case 'w':now.x -= 1;
					draw_table_for_gobang(table, now);
					break;
				case 'd':now.y += 1;
					draw_table_for_gobang(table, now);
					break;

				}
				if (com == 'j')
				{
					if (table[now.x][now.y] == 0)table[now.x][now.y] = 1;
					if (judge_for_gobang(table) == 1)
					{
						printf("You win!");
						break;
					}
					for (int i = -4; i < 4; i++)
					{
						if (table[now.x + i][now.y] == 1)d1 += 1;
						if (table[now.x + i][now.y + i] == 1)d2 += 1;
						if (table[now.x][now.y + i] == 1)d3 += 1;
						if (table[now.x - i][now.y + i] == 1)d4 += 1;
					}
					if (d1 >= d2 && d1 >= d3 && d1 >= d4)
					{
						for (int i = 1; i < 4; i++)
						{
							if (table[now.x + i][now.y] == 0)
							{
								table[now.x + i][now.y] = 2;
								break;
							}
							if (table[now.x - i][now.y] == 0)
							{
								table[now.x - i][now.y] = 2;
								break;
							}
						}
					}
					else if (d2 >= d1 && d2 >= d3 && d2 >= d4)
					{
						for (int i = 1; i < 4; i++)
						{
							if (table[now.x + i][now.y + i] == 0)
							{
								table[now.x + i][now.y + i] = 2;
								break;
							}
							if (table[now.x - i][now.y - i] == 0)
							{
								table[now.x - i][now.y - i] = 2;
								break;
							}
						}
					}
					else if (d3 >= d2 && d3 >= d1 && d3 >= d4)
					{
						for (int i = 1; i < 4; i++)
						{
							if (table[now.x][now.y + i] == 0)
							{
								table[now.x][now.y + i] = 2;
								break;
							}
							if (table[now.x][now.y - i] == 0)
							{
								table[now.x][now.y - i] = 2;
								break;
							}
						}
					}
					else if (d4 >= d2 && d4 >= d3 && d4 >= d1)
					{
						for (int i = 1; i < 4; i++)
						{
							if (table[now.x + i][now.y - i] == 0)
							{
								table[now.x + i][now.y - i] = 2;
								break;
							}
							if (table[now.x - i][now.y + i] == 0)
							{
								table[now.x - i][now.y + i] = 2;
								break;
							}
						}
					}
					draw_table_for_gobang(table, now);
					if (judge_for_gobang(table) == 2)
					{
						printf("You lose!");
						break;
					}
				}
			}
		}
		else if (com == 'q')break;
	}
}


////////////////////////MineSweeper////////////////////////////////////

void draw_table(int table[15][15], struct Pos pos)
{
	clear();

	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (i == pos.x&&j == pos.y)printf("o ");
			else
			{
				if (table[i][j] == -1)printf("+ ");
				else if (table[i][j] == 11)printf("x ");
				else if (table[i][j] == 10)printf("* ");
				else printf("%d ", table[i][j]);
			}
		}
		printf("\n");
	}
}

void check(int hide[15][15], int table[15][15], int x, int y)
{
	if (table[x + 1][y] == -1)
	{
		table[x + 1][y] = hide[x + 1][y];
		if (hide[x + 1][y] == 0)check(hide, table, x + 1, y);
	}
	if (table[x + 1][y + 1] == -1)
	{
		table[x + 1][y + 1] = hide[x + 1][y + 1];
		if (hide[x + 1][y + 1] == 0)check(hide, table, x + 1, y + 1);
	}
	if (table[x][y + 1] == -1)
	{
		table[x][y + 1] = hide[x][y + 1];
		if (hide[x][y + 1] == 0)check(hide, table, x, y + 1);
	}
	if (table[x - 1][y + 1] == -1)
	{
		table[x - 1][y + 1] = hide[x - 1][y + 1];
		if (hide[x - 1][y + 1] == 0)check(hide, table, x - 1, y + 1);
	}
	if (table[x - 1][y] == -1)
	{
		table[x - 1][y] = hide[x - 1][y];
		if (hide[x - 1][y] == 0)check(hide, table, x - 1, y);
	}
	if (table[x - 1][y - 1] == -1)
	{
		table[x - 1][y - 1] = hide[x - 1][y - 1];
		if (hide[x - 1][y - 1] == 0)check(hide, table, x - 1, y - 1);
	}
	if (table[x][y - 1] == -1)
	{
		table[x][y - 1] = hide[x][y - 1];
		if (hide[x][y - 1] == 0)check(hide, table, x, y - 1);
	}
	if (table[x + 1][y - 1] == -1)
	{
		table[x + 1][y - 1] = hide[x + 1][y - 1];
		if (hide[x + 1][y - 1] == 0)check(hide, table, x + 1, y - 1);
	}
}

int judge(int table[15][15])
{
	for (int i = 0; i < 15; i++)
	{
		for (int j = 0; j < 15; j++)
		{
			if (table[i][j] == -1)return 0;
		}
	}
	return 1;
}

void Minesweeper(fd_stdin, fd_stdout)
{
	int table[15][15] = { 0 };
	int hide[15][15] = { (0,0,0,10,0,10,10,0,10,0,0,0,0,0,10), (10,0,0,0,0,0,0,0,0,0,0,0,0,10,0), (0,0,0,0,0,0,10,10,10,0,0,0,0,0,0), (0,0,0,0,0,0,0,10,10,0,0,0,0,0,0), (10,0,0,0,0,0,0,0,0,0,0,0,10,0,0), (0,0,0,0,0,0,0,0,0,0,0,0,0,0,0), (0,0,0,0,0,0,10,0,0,0,10,0,0,0,10), (0,10,0,0,0,0,0,0,0,0,10,0,0,0,10), (0,0,0,0,0,0,0,0,0,0,0,10,0,0,0), (0,0,0,0,0,0,10,0,0,0,0,0,0,0,0), (0,0,0,10,0,10,0,10,0,10,10,10,0,10,0), (0,0,0,10,0,0,0,10,0,0,0,10,0,0,0), (0,0,0,0,0,10,0,0,0,10,0,0,0,0,0), (0,0,0,0,10,0,0,10,0,0,0,0,10,0,0), (0,0,0,0,0,10,0,0,0,10,0,0,10,0,0) };
	//int hide[15][15];
	int bottom[15][15] = { 0 };
	//int seed = 0;

	char com = 0;
	struct Pos now;
	now.x = 0;
	now.y = 0;

	char inputCmd[MAX_COMMAND_LEN];

	while (1)
	{
		clear();

		printf("    *                                                                     \n");
		printf("    *                                                \n");
		printf("    *             Welcome!                            \n");
		printf("    *             Game-4: Sweep               \n");
		printf("    *                                          \n");
		printf("    *             RULES:                              \n");
		printf("    *             s:DOWN d:RIGHT s:UP  a:LEFT       \n");
		printf("    *             j:do k:mark l:quick_do                              \n");
		printf("    *                   \n");
		printf("    *              press 'b' to begin      \n");
		printf("    *              or 'q' to quit                               \n");
		printf("    *                                                 \n");
		printf("    *                                             \n");
		printf("    *                                                                     \n");
		printf("    *    ********************************************************         \n");
		
		int len = read(fd_stdin, inputCmd, 70);
		inputCmd[len] = 0;
		com = inputCmd[0];

		if (com == 'b')
		{
			//printf("chose level(1`100):");
			//scanf_s("%d", &seed);
			//srand(seed);
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					table[i][j] = -1;
					//if (rand() % 256 <= 35)hide[i][j] = 10;
				}
			}

			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					if (hide[i][j] == 10)
					{
						if (hide[i + 1][j] != 10)hide[i + 1][j] += 1;
						if (hide[i + 1][j + 1] != 10)hide[i + 1][j + 1] += 1;
						if (hide[i][j + 1] != 10)hide[i][j + 1] += 1;
						if (hide[i - 1][j + 1] != 10)hide[i - 1][j + 1] += 1;
						if (hide[i - 1][j] != 10)hide[i - 1][j] += 1;
						if (hide[i - 1][j - 1] != 10)hide[i - 1][j - 1] += 1;
						if (hide[i][j - 1] != 10)hide[i][j - 1] += 1;
						if (hide[i + 1][j - 1] != 10)hide[i + 1][j - 1] += 1;
					}
				}
			}
			for (int i = 0; i < 15; i++)
			{
				for (int j = 0; j < 15; j++)
				{
					bottom[i][j] = hide[i][j];
				}
			}
			draw_table(table, now);
			while (1)
			{
				len = read(fd_stdin, inputCmd, 70);
				inputCmd[len] = 0;
				com = inputCmd[0];

				switch (com)
				{
				case 'a':now.y -= 1;
					draw_table(table, now);
					break;
				case 's':now.x += 1;
					draw_table(table, now);
					break;
				case 'w':now.x -= 1;
					draw_table(table, now);
					break;
				case 'd':now.y += 1;
					draw_table(table, now);
				}
				if (com == 'j')
				{
					if (table[now.x][now.y] == -1)
					{
						if (hide[now.x][now.y] != 10)
						{
							table[now.x][now.y] = hide[now.x][now.y];
							if (hide[now.x][now.y] == 0)check(hide, table, now.x, now.y);
							draw_table(table, now);
							if (judge(table) == 1)
							{
								printf("You win");
								break;
							}
						}
						else
						{
							table[now.x][now.y] = 10;
							draw_table(table, now);
							printf("You lose");
							break;
						}
					}
				}
				else if (com == 'k')
				{
					if (table[now.x][now.y] == -1)
					{
						table[now.x][now.y] = 11;
						bottom[now.x + 1][now.y] -= 1;
						bottom[now.x + 1][now.y + 1] -= 1;
						bottom[now.x][now.y + 1] -= 1;
						bottom[now.x - 1][now.y + 1] -= 1;
						bottom[now.x - 1][now.y] -= 1;
						bottom[now.x - 1][now.y - 1] -= 1;
						bottom[now.x][now.y - 1] -= 1;
						bottom[now.x + 1][now.y - 1] -= 1;
						draw_table(table, now);
						if (judge(table) == 1)
						{
							printf("You win");
							break;
						}
					}
				}
				else if (com == 'l')
				{
					if (table[now.x][now.y] < 10 && table[now.x][now.y]>0 && bottom[now.x][now.y] == 0)
					{
						check(hide, table, now.x, now.y);
						draw_table(table, now);
						if (judge(table) == 1)
						{
							printf("You win");
							break;
						}
					}
				}
			}
		}
		else if (com == 'q')break;
	}
	return 0;
}


/*****************************************************************************
*                                kernel_main
*****************************************************************************/
PUBLIC int kernel_main()
{
	disp_str("-----\"kernel_main\" begins-----\n");

	struct task* p_task;
	struct proc* p_proc = proc_table;
	char* p_task_stack = task_stack + STACK_SIZE_TOTAL;
	u16   selector_ldt = SELECTOR_LDT_FIRST;
	u8    privilege;
	u8    rpl;
	int   eflags;
	int   i, j;
	int   prio;
	for (i = 0; i < NR_TASKS + NR_PROCS; i++) {
		if (i < NR_TASKS) {     /* 任务 */
			p_task = task_table + i;
			privilege = PRIVILEGE_TASK;
			rpl = RPL_TASK;
			eflags = 0x1202; /* IF=1, IOPL=1, bit 2 is always 1 */
			prio = 15;
		}
		else {                  /* 用户进程 */
			p_task = user_proc_table + (i - NR_TASKS);
			privilege = PRIVILEGE_USER;
			rpl = RPL_USER;
			eflags = 0x202; /* IF=1, bit 2 is always 1 */
			prio = 5;
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
		p_proc->regs.cs = (0 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.ds = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.es = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.fs = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.ss = (8 & SA_RPL_MASK & SA_TI_MASK) | SA_TIL | rpl;
		p_proc->regs.gs = (SELECTOR_KERNEL_GS & SA_RPL_MASK) | rpl;

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

	p_proc_ready = proc_table;

	init_clock();
	init_keyboard();

	restart();

	while (1) {}
}


/*****************************************************************************
*                                get_ticks
*****************************************************************************/
PUBLIC int get_ticks()
{
	MESSAGE msg;
	reset_msg(&msg);
	msg.type = GET_TICKS;
	send_recv(BOTH, TASK_SYS, &msg);
	return msg.RETVAL;
}

////////////////////////TestA////////////////////////////////////
/////////////////////applications////////////////////////////////

void ShowCommands()
{
	clear();

	printf(" ==============================================================================\n");
	printf(" ==============================================================================\n");
	printf(" ==                                                                            \n");
	printf(" ==                        <-  Command List  ->                                \n");
	printf(" ==                                                                            \n");
	printf(" ==                                                                            \n");
	printf(" ==              1. help	       ----     Show Help                          \n");
	printf(" ==              2. Carlendar      ----     Start Carlendar                    \n");
	printf(" ==              3. Calculator     ----     Start Calculator                   \n");
	printf(" ==              4. Game1          ----     Play Finger Guessing               \n");
	printf(" ==              5. Game2          ----     Play GoBang                        \n");
	printf(" ==              6. Game3          ----     Play MineSweeper                   \n");
	printf(" ==                                                                            \n");
	printf(" ==                                                                            \n");
	printf(" ==                                                                            \n");
	printf(" ==============================================================================\n");
	printf(" ==============================================================================\n");
}


void TestA()
{
	char tty_name[] = "/dev_tty0";

	int fd;
	int i, n;
	char cmd[8];
	char buf[1024];
	char filename[120];

	char inputCmd[MAX_COMMAND_LEN];

	long int ii = 9999;

	printf("                                                                           \n"); while (ii-->0); ii = 9999;

	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("      ###            ###            ###            ###            ###      \n");
	printf("     #...#          #...#          #...#          #...#          #...#     \n");
	printf("     #.#.#          #.#.#          #.#.#          #.#.#          #.#.#     \n");
	printf("     #.#.#          #.#.#          #.#.#          #.#.#          #.#.#     \n");
	printf("     #...#          #...#          #...#          #...#          #...#     \n");
	printf("      ###            ###            ###            ###            ###      \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("###########################################################################\n");
	printf("#...#......#.##...#......#.##...#......##...#......#.##...#......#.##...#..\n");
	printf(".##.#...#......#.##...#......#.##...#......#...#...#......#.##...#......#.#\n\n");
	milli_delay(1000);
	clear();

	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("  ********                                                                 \n");
	printf(" ************                                                              \n");
	printf(" ####....#.                                                                \n");
	printf("..###.....##....                                                           \n");
	printf("##.......######      ###            ###            ###            ###      \n");
	printf("  ...........       #...#          #...#          #...#          #...#     \n");
	printf(" ##*#######         #.#.#          #.#.#          #.#.#          #.#.#     \n");
	printf("##*******######     #.#.#          #.#.#          #.#.#          #.#.#     \n");
	printf("#***.****.*###....  #...#          #...#          #...#          #...#     \n");
	printf(".**********##.....   ###            ###            ###            ###      \n");
	printf(".****    *****....                                                         \n");
	printf("###        ####                                                            \n");
	printf("####        ######                                                         \n");
	printf("###########################################################################\n");
	printf("#...#......#.##...#......#.##...#......##...#......#.##...#......#.##...#..\n");
	printf(".##.#...#......#.##...#......#.##...#......#...#...#......#.##...#......#.#\n\n");
	milli_delay(1000);
	clear();

	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                ********                                                   \n");
	printf("                ************                                               \n");
	printf("  ###     ###   ####....#.                                                 \n");
	printf("  ###     #   #..###.....##....                                            \n");
	printf("  ###     ##  ###.......######     ###            ###            ###       \n");
	printf("  ###     ##     ...........      #...#          #...#          #...#      \n");
	printf("  ##########    ##*#######        #.#.#          #.#.#          #.#.#      \n");
	printf("  #########  ####*******######    #.#.#          #.#.#          #.#.#      \n");
	printf("  ###       ...#***.****.*###.... #...#          #...#          #...#      \n");
	printf("  ###       ....**********##.....  ###            ###            ###       \n");
	printf("  ###       ....****    *****....                                          \n");
	printf("  ###         ####        ####                                             \n");
	printf("            ######        ######                                           \n");
	printf("###########################################################################\n");
	printf("#...#......#.##...#......#.##...#......##...#......#.##...#......#.##...#..\n");
	printf(".##.#...#......#.##...#......#.##...#......#...#...#......#.##...#......#.#\n\n");
	milli_delay(1000);
	clear();

	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                               ********                                    \n");
	printf("                               ************                                \n");
	printf("  ###     ###     #########    ####....#.                                  \n");
	printf("  ###     ###    ##########  #..###.....##....                             \n");
	printf("  ###     ###    ###     ##  ###.......######     ###             ###      \n");
	printf("  ###     ###    ###     ###    ...........      #...#           #...#     \n");
	printf("  ###########    ##########    ##*#######        #.#.#           #.#.#     \n");
	printf("  ###########    #########  ####*******######    #.#.#           #.#.#     \n");
	printf("  ###     ###    ###       ...#***.****.*###.... #...#           #...#     \n");
	printf("  ###     ###    ###       ....**********##.....  ###             ###      \n");
	printf("  ###     ###    ########  ....****    *****....                           \n");
	printf("  ###     ###     ########   ####        ####                              \n");
	printf("                           ######        ######                           \n");
	printf("###########################################################################\n");
	printf("#...#......#.##...#......#.##...#......##...#......#.##...#......#.##...#..\n");
	printf(".##.#...#......#.##...#......#.##...#......#...#...#......#.##...#......#.#\n\n");
	milli_delay(1000);
	clear();

	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                              ********                     \n");
	printf("                                              ************                 \n");
	printf("  ###     ###     #########     ###           ####....#.                   \n");
	printf("  ###     ###    ###########    ###         #..###.....##....              \n");
	printf("  ###     ###    ###     ###    ###         ###.......######       ###     \n");
	printf("  ###     ###    ###     ###    ###            ...........        #...#    \n");
	printf("  ###########    ###########    ###           ##*#######          #.#.#    \n");
	printf("  ###########    ###########    ###        ####*******######      #.#.#    \n");
	printf("  ###     ###    ###            ###       ...#***.****.*###....   #...#    \n");
	printf("  ###     ###    ###     ###    ###       ....**********##.....    ###     \n");
	printf("  ###     ###    ###########    ########  ....****    *****....            \n");
	printf("  ###     ###     #########     #########   ####        ####               \n");
	printf("                                          ######        ######             \n");
	printf("###########################################################################\n");
	printf("#...#......#.##...#......#.##...#......##...#......#.##...#......#.##...#..\n");
	printf(".##.#...#......#.##...#......#.##...#......#...#...#......#.##...#......#.#\n\n");
	milli_delay(1000);
	clear();

	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                             ********      \n");
	printf("                                                             ************  \n");
	printf("  ###     ###     #########     ###            ###           ####....#.    \n");
	printf("  ###     ###    ###########    ###            ###         #..###.....##...\n");
	printf("  ###     ###    ###     ###    ###            ###         ###.......######\n");
	printf("  ###     ###    ###     ###    ###            ###            ...........  \n");
	printf("  ###########    ###########    ###            ###           ##*#######    \n");
	printf("  ###########    ###########    ###            ###        ####*******######\n");
	printf("  ###     ###    ###            ###            ###       ...#***.****.*###.\n");
	printf("  ###     ###    ###     ###    ###            ###       ....**********##..\n");
	printf("  ###     ###    ###########    ###########    ##########....****    *****.\n");
	printf("  ###     ###     #########     ###########    ########### ####        ####\n");
	printf("                                                         ######        ####\n");
	printf("###########################################################################\n");
	printf("#...#......#.##...#......#.##...#......##...#......#.##...#......#.##...#..\n");
	printf(".##.#...#......#.##...#......#.##...#......#...#...#......#.##...#......#.#\n\n");
	milli_delay(1000);
	clear();

	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("                                                                           \n");
	printf("  ###     ###     #########     ###            ###             #########   \n");
	printf("  ###     ###    ###########    ###            ###            ###########  \n");
	printf("  ###     ###    ###     ###    ###            ###            ###     ###  \n");
	printf("  ###     ###    ###     ###    ###            ###            ###     ###  \n");
	printf("  ###########    ###########    ###            ###            ###     ###  \n");
	printf("  ###########    ###########    ###            ###            ###     ###  \n");
	printf("  ###     ###    ###            ###            ###            ###     ###  \n");
	printf("  ###     ###    ###     ###    ###            ###            ###     ###  \n");
	printf("  ###     ###    ###########    ###########    ###########    ###########  \n");
	printf("  ###     ###     #########     ###########    ###########     #########   \n");
	printf("                                                                           \n");
	printf("###########################################################################\n");
	printf("#...#......#.##...#......#.##...#......##...#......#.##...#......#.##...#..\n");
	printf(".##.#...#......#.##...#......#.##...#......#...#...#......#.##...#......#.#\n\n");
	milli_delay(1000);
	
	startAnimate();
	clear();

	printf(" ==============================================================================\n");
	printf(" ==============================================================================\n");
	printf(" ==                                                                            \n");
	printf(" ==                        <-  Command List  ->                                \n");
	printf(" ==                                                                            \n");
	printf(" ==                                                                            \n");
	printf(" ==              1. help	       ----     Show Help                          \n");
	printf(" ==              2. Carlendar      ----     Start Carlendar                    \n");
	printf(" ==              3. Calculator     ----     Start Calculator                   \n");
	printf(" ==              4. Game1          ----     Play Finger Guessing               \n");
	printf(" ==              5. Game2          ----     Play GoBang                        \n");
	printf(" ==              6. Game3          ----     Play MineSweeper                   \n");
	printf(" ==              7. Clear                                                      \n");
	printf(" ==                                                                            \n");
	printf(" ==                                                                            \n");
	printf(" ==============================================================================\n");
	printf(" ==============================================================================\n");

	int fd_stdin = open(tty_name, O_RDWR);
	assert(fd_stdin == 0);
	int fd_stdout = open(tty_name, O_RDWR);
	assert(fd_stdout == 1);


	while (1) {
		printf("\n\n\n command:");

		int r = read(fd_stdin, inputCmd, 70);
		inputCmd[r] = 0;
		
		if (strcmp(inputCmd, "Help") == 0 || strcmp(inputCmd, "help") == 0)
		{
			help();
		}

		else if (strcmp(inputCmd, "Carlendar") == 0 || strcmp(inputCmd, "carlendar") == 0)
		{
			clear();
			Carlendar(fd_stdin, fd_stdout);
		}

		else if (strcmp(inputCmd, "Calculator") == 0 || strcmp(inputCmd, "calculator") == 0)
		{
			Calculator(fd_stdin, fd_stdout);
		}

		else if (strcmp(inputCmd, "G1") == 0)
		{
			Guessing(fd_stdin, fd_stdout);
		}

		else if (strcmp(inputCmd, "G2") == 0)
		{
			gobang(fd_stdin, fd_stdout);
		}

		else if (strcmp(inputCmd, "G3") == 0)
		{
			Minesweeper(fd_stdin, fd_stdout);
		}

		else if (strcmp(inputCmd, "Clear") == 0)
		{
			clear();

			ShowCommands();

		}

		else
		{
			printf(" ==============================================================================\n");
			printf(" ==============================================================================\n");
			printf(" ==                                                                            \n");
			printf(" ==                                                                            \n");
			printf(" ==                                                                            \n");
			printf(" ==              <-  Wrong Command!                                            \n");
			printf(" ==                                                                            \n");
			printf(" ==                                                                            \n");
			printf(" ==                                                                            \n");
			printf(" ==              <-  Enter: help for Commands List                             \n");
			printf(" ==                                                                            \n");
			printf(" ==                                                                            \n");
			printf(" ==                                                                            \n");
			printf(" ==                                                                            \n");
			printf(" ==============================================================================\n");
			printf(" ==============================================================================\n");
		}

	}

}


////////////////////////TestB////////////////////////////////////
//////////////////////FileManage/////////////////////////////////

#define MAX_FILE_NUM 100
#define MAX_CONTENT_LEN 50
#define MAX_ARRAY_NUM 1000 
#define MAX_FILE_PER_LAYER 10
#define MAX_FILE_NAME_LENGTH 20

//文件ID计数器
int fileIDCount = 0;
int currentFileID = 0;

struct fileBlock {
	int fileID;
	int fileType;  //0 - 文本文件 , 1 - 文件夹
	int fatherID;
	int childrenNumber;
	int children[MAX_FILE_PER_LAYER];

	char content[MAX_CONTENT_LEN];
	char fileName[MAX_FILE_NAME_LENGTH];
};

struct fileBlock blocks[MAX_FILE_NUM];
int IDLog[MAX_FILE_NUM];

void initFileBlock(int fileID, char * fileName, int fileType) {
	blocks[fileID].fileID = fileID;
	strcpy(blocks[fileID].fileName, fileName);
	blocks[fileID].fileType = fileType;
	blocks[fileID].fatherID = currentFileID;
	blocks[fileID].childrenNumber = 0;
}

void toStr3(char * temp, int i) {
	if (i / 100 < 0)
		temp[0] = (char)48;
	else
		temp[0] = (char)(i / 100 + 48);
	if ((i % 100) / 10 < 0)
		temp[1] = '0';
	else
		temp[1] = (char)((i % 100) / 10 + 48);
	temp[2] = (char)(i % 10 + 48);
}

void WriteDisk(int len) {
	char temp[MAX_FILE_NUM * 150 + 103];
	int i = 0;
	temp[i] = '^';
	i++;
	toStr3(temp + i, fileIDCount);
	i = i + 3;
	temp[i] = '^';
	i++;
	for (int j = 0; j < MAX_FILE_NUM; j++) {
		if (IDLog[j] == 1) {
			toStr3(temp + i, blocks[j].fileID);
			i = i + 3;
			temp[i] = '^';
			i++;
			for (int h = 0; h < strlen(blocks[j].fileName); h++) {
				temp[i + h] = blocks[j].fileName[h];
				if (blocks[j].fileName[h] == '^')
					temp[i + h] = (char)1;
			}
			i = i + strlen(blocks[j].fileName);
			temp[i] = '^';
			i++;
			temp[i] = (char)(blocks[j].fileType + 48);
			i++;
			temp[i] = '^';
			i++;
			for (int h = 0; h < strlen(blocks[j].content); h++) {
				temp[i + h] = blocks[j].content[h];
				if (blocks[j].content[h] == '^')
					temp[i + h] = (char)1;
			}
			i = i + strlen(blocks[j].content);
			temp[i] = '^';
			i++;
			toStr3(temp + i, blocks[j].fatherID);
			i = i + 3;
			temp[i] = '^';
			i++;
			for (int m = 0; m < MAX_FILE_PER_LAYER; m++) {
				toStr3(temp + i, blocks[j].children[m]);
				i = i + 3;
			}
			temp[i] = '^';
			i++;
			toStr3(temp + i, blocks[j].childrenNumber);
			i = i + 3;
			temp[i] = '^';
			i++;
		}
	}
	int fd = 0;
	int n1 = 0;

	fd = open("ss", O_RDWR);
	assert(fd != -1);
	n1 = write(fd, temp, strlen(temp));
	assert(n1 == strlen(temp));

	close(fd);
}

int toInt(char * temp) {
	int result = 0;
	for (int i = 0; i < 3; i++)
		result = result * 10 + (int)temp[i] - 48;
	return result;
}

int ReadDisk() {
	char bufr[1000];
	int fd = 0;
	int n1 = 0;
	fd = open("ss", O_RDWR);
	assert(fd != -1);
	n1 = read(fd, bufr, 1000);
	assert(n1 == 1000);
	bufr[n1] = 0;
	int r = 1;
	fileIDCount = toInt(bufr + r);
	r = r + 4;
	for (int i = 0; i < fileIDCount; i++) {
		int ID = toInt(bufr + r);
		IDLog[ID] = 1;
		blocks[ID].fileID = ID;
		r = r + 4;
		for (int i = 0; i < MAX_FILE_NAME_LENGTH; i++) {
			if (bufr[r] == '^')
				break;
			else if (bufr[r] == (char)1)
				blocks[ID].fileName[i] = '^';
			else
				blocks[ID].fileName[i] = bufr[r];
			r++;
		}
		r++;
		blocks[ID].fileType = (int)bufr[r] - 48;
		r = r + 2;
		for (int j = 0; j < MAX_CONTENT_LEN; j++) {
			if (bufr[r] == '^')
				break;
			else if (bufr[r] == (char)1)
				blocks[ID].content[j] = '^';
			else
				blocks[ID].content[j] = bufr[r];
			r++;
		}
		r++;
		blocks[ID].fatherID = toInt(bufr + r);
		r = r + 4;
		for (int j = 0; j < MAX_FILE_PER_LAYER; j++) {
			blocks[ID].children[j] = toInt(bufr + r);
			r = r + 3;
		}
		r++;
		blocks[ID].childrenNumber = toInt(bufr + r);
		r = r + 4;
	}
	return n1;
}

void FSInit() {

	for (int i = 0; i < MAX_FILE_NUM; i++) {
		blocks[i].childrenNumber = 0;
		blocks[i].fileID = -2;
		IDLog[i] = '\0';
	}
	IDLog[0] = 1;
	blocks[0].fileID = 0;
	strcpy(blocks[0].fileName, "home");
	strcpy(blocks[0].content, "welcome to use file system!");
	blocks[0].fileType = 2;
	blocks[0].fatherID = 0;
	blocks[0].childrenNumber = 0;
	currentFileID = 0;
	fileIDCount = 1;
}

int CreateFile(char * fileName, int fileType) {
	if (blocks[currentFileID].childrenNumber == MAX_FILE_PER_LAYER) {
		printf("Sorry you cannot add more files in this layer");
		return 0;
	}
	else {
		for (int i = 0; i < blocks[currentFileID].childrenNumber; i++) {
			if (strcmp(blocks[blocks[currentFileID].children[i]].fileName, fileName) == 0) {
				printf("You have a file of same name!");
				return 0;
			}
		}
		fileIDCount++;
		int target = 0;
		for (int i = 0; i < MAX_FILE_NUM; i++) {
			if (IDLog[i] == 0) {
				target = i;
				break;
			}
		}
		initFileBlock(target, fileName, fileType);
		blocks[currentFileID].children[blocks[currentFileID].childrenNumber] = target;
		blocks[currentFileID].childrenNumber++;
		printf("Create file s% successful!", fileName);
		IDLog[target] = 1;
		return 1;
	}
}

void showFileList() {
	printf("-----------------------------------------\n");
	for (int i = 0; i < blocks[currentFileID].childrenNumber; i++) {
		printf("%s", blocks[blocks[currentFileID].children[i]].fileName);
		if (blocks[blocks[currentFileID].children[i]].fileType == 0) {
			printf(".txt");
		}
		else {
			printf(".fd ");
		}
		printf(" id:%d\n", blocks[blocks[currentFileID].children[i]].fileID);
	}
	printf("-----------------------------------------");
}

int SearchFile(char * name) {
	for (int i = 0; i < blocks[currentFileID].childrenNumber; i++) {
		if (strcmp(name, blocks[blocks[currentFileID].children[i]].fileName) == 0) {
			return blocks[currentFileID].children[i];
		}
	}
	return -2;
}

void ReturnFile(int ID) {
	currentFileID = blocks[ID].fatherID;
}

void DeleteFile(int ID) {
	if (blocks[ID].childrenNumber > 0) {
		for (int i = 0; i < blocks[ID].childrenNumber; i++) {
			DeleteFile(blocks[blocks[ID].children[i]].fileID);
		}
	}
	IDLog[ID] = 0;
	blocks[ID].fileID = -2;
	blocks[ID].childrenNumber = 0;
	for (int i = 0; i < MAX_CONTENT_LEN; i++)
		blocks[ID].content[i] = '\0';
	for (int i = 0; i < MAX_FILE_NAME_LENGTH; i++)
		blocks[ID].fileName[i] = '\0';
	blocks[ID].fileType = -1;
	for (int i = 0; i < MAX_FILE_PER_LAYER; i++)
		blocks[ID].children[i] = -1;
	blocks[ID].fatherID = -2;
	fileIDCount--;
}


void ShowMessage() {

	clear();

	printf(" ==============================================================================\n");
	printf(" ==============================================================================\n");
	printf(" ==                                                                            \n");
	printf(" ==              <-File Manage                                                 \n");
	printf(" ==                                                                            \n");
	printf(" ==              touch XXX	    ----     Create a new file named XXX           \n");
	printf(" ==              mkdir XXX      ----     Start Carlendar                       \n");
	printf(" ==              ls             ----     Show files                            \n");
	printf(" ==              cd XXX         ----     Enter the folder named XXX            \n");
	printf(" ==              cd ..          ----     Return to the superior level          \n");
	printf(" ==              rm XXX         ----     Remove the file named XXX             \n");
	printf(" ==              sv             ----     Save the system                       \n");
	printf(" ==              help           ----     Check Commands                        \n");
	printf(" ==                                                                            \n");
	printf(" ==                                                                            \n");
	printf(" ==============================================================================\n");
	printf(" ==============================================================================\n");

}



void TestB()
{
	int i, n;
	char tty_name[] = "/dev_tty1";
	char inputCmd[MAX_COMMAND_LEN];
	char _name[MAX_FILE_NAME_LENGTH];

	int fd_stdin = open(tty_name, O_RDWR);
	assert(fd_stdin == 0);
	int fd_stdout = open(tty_name, O_RDWR);
	assert(fd_stdout == 1);

	FSInit();

	int len = ReadDisk();

	ShowMessage();

	while (1) {
		for (int i = 0; i <= 127; i++)
			inputCmd[i] = '\0';
		for (int i = 0; i < MAX_FILE_NAME_LENGTH; i++)
			_name[i] = '\0';
		printf("\n/%s:", blocks[currentFileID].fileName);

		int r = read(fd_stdin, inputCmd, 70);
		inputCmd[r] = 0;
		assert(fd_stdin == 0);

		//touch
		if (inputCmd[0] == 't' && inputCmd[1] == 'o' && inputCmd[2] == 'u' && inputCmd[3] == 'c' && inputCmd[4] == 'h') {
			if (inputCmd[5] != ' ') {
				printf("enter the name like this : create XXX");
				continue;
			}
			for (int i = 0; i < MAX_FILE_NAME_LENGTH && i < r - 3; i++) {
				_name[i] = inputCmd[i + 6];
			}
			CreateFile(_name, 0);
		}

		//mkdir
		else if (inputCmd[0] == 'm' && inputCmd[1] == 'k' && inputCmd[2] == 'd' && inputCmd[3] == 'i' && inputCmd[4] == 'r') {
			if (inputCmd[5] != ' ') {
				printf("enter the name like this : mkdir XXX");
				continue;
			}
			char N[MAX_FILE_NAME_LENGTH];
			for (int i = 0; i < MAX_FILE_NAME_LENGTH && i < r - 3; i++) {
				_name[i] = inputCmd[i + 6];
			}
			CreateFile(_name, 1);
		}
		
		//ls
		else if (inputCmd[0] == 'l' && inputCmd[1] == 's') {
			showFileList();
		}

		//cd
		else if (inputCmd[0] == 'c' && inputCmd[1] == 'd') {
			//cd ..
			if (inputCmd[2] == ' ' && inputCmd[3] == '.' && inputCmd[4] == '.') {
				ReturnFile(currentFileID);
				continue;
			}
			else if (inputCmd[2] != ' ') {
				printf("enter the name like this : mt XXX");
				continue;
			}
			for (int i = 0; i < MAX_FILE_NAME_LENGTH && i < r - 3; i++) {
				_name[i] = inputCmd[i + 3];
			}
			printf("name: %s\n", _name);
			int ID = SearchFile(_name);
			if (ID >= 0) {
				if (blocks[ID].fileType == 1) {
					currentFileID = ID;
					continue;
				}
				else if (blocks[ID].fileType == 0) {
					while (1) {
						printf("input the character representing the method you want to operate:"
							"\nu --- update"
							"\nd --- detail of the content"
							"\nq --- quit\n");
						int r = read(fd_stdin, inputCmd, 70);
						inputCmd[r] = 0;
						if (strcmp(inputCmd, "u") == 0) {
							printf("input the text you want to write:\n");
							int r = read(fd_stdin, blocks[ID].content, MAX_CONTENT_LEN);
							blocks[ID].content[r] = 0;
						}
						else if (strcmp(inputCmd, "d") == 0) {
							printf("--------------------------------------------"
								"\n%s\n-------------------------------------\n", blocks[ID].content);
						}
						else if (strcmp(inputCmd, "q") == 0) {
							printf("would you like to save the change? y/n");
							int r = read(fd_stdin, inputCmd, 70);
							inputCmd[r] = 0;
							if (strcmp(inputCmd, "y") == 0) {
								printf("save changes!");
							}
							else {
								printf("quit without changing");
							}
							break;
						}
					}
				}
			}
			else
				printf("No such file!");
		}

		//rm
		else if (inputCmd[0] == 'r' && inputCmd[1] == 'm') {
			if (inputCmd[2] != ' ') {
				printf("enter the name like this : rm XXX");
				continue;
			}
			for (int i = 0; i < MAX_FILE_NAME_LENGTH && i < r - 3; i++) {
				_name[i] = inputCmd[i + 3];
			}
			int ID = SearchFile(_name);
			if (ID >= 0) {
				printf("delete successfully!\n");
				DeleteFile(ID);
				for (int i = 0; i < blocks[currentFileID].childrenNumber; i++) {
					if (ID == blocks[currentFileID].children[i]) {
						for (int j = i + 1; j < blocks[currentFileID].childrenNumber; j++) {
							blocks[currentFileID].children[i] = blocks[currentFileID].children[j];
						}
						blocks[currentFileID].childrenNumber--;
						break;
					}
				}
			}
			else
				printf("No such file!\n");
		}

		//sv
		else if (inputCmd[0] == 's' && inputCmd[1] == 'v') {
			WriteDisk(1000);
		}

		//help
		else if (strcmp(inputCmd, "help") == 0) {
			printf("\n\n");
			ShowMessage();
			printf("\n\n");
		}

		//Wrong Command
		else {
			printf("Wrong Command! Please check your input");
		}
	}

	assert(0); /* never arrive here */
}


////////////////////////TestC////////////////////////////////////
void TestC()
{
	//ProcessManage();
	spin("TestC");
}


/*****************************************************************************
*                                panic
*****************************************************************************/
PUBLIC void panic(const char *fmt, ...)
{
	int i;
	char buf[256];

	/* 4 is the size of fmt in the stack */
	va_list arg = (va_list)((char*)&fmt + 4);

	i = vsprintf(buf, fmt, arg);

	printl("%c !!panic!! %s", MAG_CH_PANIC, buf);

	/* should never arrive here */
	__asm__ __volatile__("ud2");
}



