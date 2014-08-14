#include <ncurses.h>
#define start 4

void print_mmenu(char* opt[100],int highlight,int i,int rows,int cols){
	int j;
	for(j = 1; j <=i; j++){
		if(highlight == j ){
			attron(A_BOLD | A_UNDERLINE);
      			mvaddch(rows, COLS/5, ACS_LARROW);
      			mvaddch(rows, (4*COLS/5), ACS_RARROW);
      			attroff(A_BOLD | A_UNDERLINE);
		}
		mvprintw(rows,cols ,"%s", opt[j-1]);
		rows++;
	}
	refresh();
}

getoption(int n , char* options[n]){
	int i,highlight=1,c,choice=0;
	char x;
	print_mmenu(options,highlight,n,LINES-n-2,COLS/5 + 5);
	keypad(stdscr,TRUE);
	cbreak();
	noecho();
	while(1){
		c = getch();
		for(i=0;i<n;i++){
			mvprintw(LINES-n-2+i,COLS/5," ");
			mvprintw(LINES-n-2+i,(4*COLS)/5," ");
			refresh();
		}
		switch(c){
			case KEY_UP:
			if(highlight == 1)
			highlight = n;
			else
			--highlight;
			break;

			case KEY_DOWN:
			if(highlight == n)
			highlight = 1;
			else 
			++highlight;
			break;
		
			case 10:
			choice = highlight;
			break;
			}
		print_mmenu(options,highlight,n,LINES-n-2,COLS/5 +5);	
		if(choice != 0) break;
	}
	keypad(stdscr,FALSE);
	cbreak();
	echo();	
	return highlight;
}

getandprint(char* a,char* name[100],char* roll[100],char* usr[100],char* psswd[100],int x){
	FILE* fp2;
	int i1,highlight=x,choice = 0,c;
	fp2 = fopen(a,"r");
	for(i1=0;feof(fp2)==0;i1++)
		fscanf(fp2,"%s %s %s %s",name[i1],roll[i1],usr[i1],psswd[i1]);
	i1--;
	fclose(fp2);
	clear_all_screen();
	mvprintw(start,(COLS)/5 + 5,"NAME:");
	mvprintw(start,(COLS)/5 +20,"ROLL_NO:");
	mvprintw(start,(COLS)/5 + 35,"USER_NAME");
	print_mmenu(name,highlight,i1,6,(COLS)/5 +5);
	print_mmenu(roll,highlight,i1,6,(COLS)/5 + 20);
	print_mmenu(usr,highlight,i1,6,(COLS)/5 + 35);
	mvprintw(LINES-1,COLS-25,"Press q to exit");
	keypad(stdscr,TRUE);
	cbreak();
	noecho();
	while(1){
		c = getch();
		switch(c){
			case KEY_UP:
			if(highlight == 1)
			highlight = i1;
			else
			--highlight;
			break;

			case KEY_DOWN:
			if(highlight == i1)
			highlight = 1;
			else 
			++highlight;
			break;
		
			case 10:
			choice = highlight;
			break;

			case 113:
			highlight = 113;
			keypad(stdscr,FALSE);
			cbreak();echo();
			return highlight;
			}
		clear_all_screen();
		mvprintw(LINES-1,COLS-25,"Press q to exit");
		mvprintw(start,(COLS)/5 +5,"NAME:");
		mvprintw(start,(COLS)/5 + 20,"ROLL_NO:");
		mvprintw(start,(COLS)/5 + 35,"USER_NAME");
		print_mmenu(name,highlight,i1,6,(COLS)/5 + 5);
		print_mmenu(roll,highlight,i1,6,(COLS)/5 + 20);
		print_mmenu(usr,highlight,i1,6,(COLS)/5 + 35);
		if(choice != 0) break;
	}
	keypad(stdscr,FALSE);
	cbreak();
	echo();
	return highlight;	
}
void acc_manage(void){
	char* menu[] = {"uView all the User accounts in DCF",
			"cChange ADMIN password",
			"vView requests for new accounts",
			"bGo Back",
			0
			};
	char *admin=malloc(sizeof(char)) , *a1=malloc(sizeof(char)) , *a2=malloc(sizeof(char));
	int choice;
	do{
		choice = getchoice("Account management Options:",menu);
		switch(choice){
			case 'u':
			clear_all_screen();
			int x1=1,count1,y1;
			char **name1,**roll1,**usr1,**psswd1;
			name1 = (char**)malloc(100*sizeof(char*));
			roll1 = (char**)malloc(100*sizeof(char*));
			usr1 = (char**)malloc(100*sizeof(char*));
			psswd1 = (char**)malloc(100*sizeof(char*));
			for(count1=0;count1<100;count1++){
				name1[count1] = (char*)malloc(100*sizeof(char));
				roll1[count1] = (char*)malloc(100*sizeof(char));
				usr1[count1] = (char*)malloc(100*sizeof(char));
				psswd1[count1] = (char*)malloc(100*sizeof(char));
			}
			LABEL1: x1 = getandprint("Facts.txt",name1,roll1,usr1,psswd1,x1);
			if(x1==113) break;
			char* options1[5] = {"Delete user account","Change user password","Go back","Back to main menu",0}; 
			y1 = getoption(4,options1);
			if(y1==4) break;
			if(y1==3) goto LABEL1;
			if(y1==1){
				User user1;
				strncpy(user1.name,name1[x1-1],strlen(name1[x1-1])+1);
				strncpy(user1.roll,roll1[x1-1],strlen(roll1[x1-1])+1);
				strncpy(user1.usr_name,usr1[x1-1],strlen(usr1[x1-1])+1);
				strncpy(user1.pass,psswd1[x1-1],strlen(psswd1[x1-1])+1);
				del_account(user1,"Facts.txt");
			}
			if(y1==2){
				clear_all_screen();
				User user1;
				strncpy(user1.name,name1[x1-1],strlen(name1[x1-1])+1);
				strncpy(user1.roll,roll1[x1-1],strlen(roll1[x1-1])+1);
				strncpy(user1.usr_name,usr1[x1-1],strlen(usr1[x1-1])+1);
				strncpy(user1.pass,psswd1[x1-1],strlen(psswd1[x1-1])+1);
				del_account(user1,"Facts.txt");
				mvprintw(LINES/3 + 2,COLS/5,"No spaces should be present in the password if present only the first word is considered");
				mvprintw(LINES/3 + 4,COLS/3,"Enter new password: ");
				noecho();
				scanw("%s",a1);
				mvprintw(LINES/3 + 5,COLS/3,"Renter new password: ");
				scanw("%s",a2);
				if(strcmp(a1,a2)==0){
					pswdf_change(user1.name,a1);
					mvprintw((LINES*2)/3,(COLS-12)/3,"Password change successful!!!");
					echo();refresh();sleep(1);
				}
				else { mvprintw((LINES*2)/3,(COLS-12)/3,"Passwords do not match"); echo();refresh(); sleep(1);}
			}
			break;

			case 'c':
			clear_all_screen();
			mvprintw(LINES/3,COLS/3,"Enter current password: ");
			noecho();
			scanw("%s",admin);
			echo();
			if(strcmp(admin,fscan(admin,'a'))==0){
				mvprintw(LINES/3 + 2,COLS/5,"No spaces should be present in the password if present only the first word is considered");
				mvprintw(LINES/3 + 4,COLS/3,"Enter new password: ");
				noecho();
				scanw("%s",a1);
				mvprintw(LINES/3 + 5,COLS/3,"Renter new password: ");
				scanw("%s",a2);
				if(strcmp(a1,a2)==0){
					FILE* fp = fopen("data.txt","r+");
					int i;
					i = strlen(admin) - strlen(a1);
					fseek ( fp , 0 , SEEK_SET );
					fprintf(fp,"%s",a1);
					for(;i>0;i--)	fprintf(fp," ");
					fclose(fp);
					mvprintw((LINES*2)/3,(COLS-12)/3,"Password change successful!!!");
					echo();refresh();
					sleep(1);
				}
				else	{ mvprintw((LINES*2)/3,(COLS-12)/3,"Passwords do not match"); echo();refresh(); sleep(1);}
			}
			else {
				mvprintw((LINES*2)/3,(COLS-12)/3,"Wrong Password!!\n");
				refresh();
				sleep(1);
			}	
			break;

			case 'v':
			clear_all_screen();
			int x=1,count,y;
			char **name,**roll,**usr,**psswd;
			name = (char**)malloc(100*sizeof(char*));
			roll = (char**)malloc(100*sizeof(char*));
			usr = (char**)malloc(100*sizeof(char*));
			psswd = (char**)malloc(100*sizeof(char*));
			for(count=0;count<100;count++){
				name[count] = (char*)malloc(100*sizeof(char));
				roll[count] = (char*)malloc(100*sizeof(char));
				usr[count] = (char*)malloc(100*sizeof(char));
				psswd[count] = (char*)malloc(100*sizeof(char));
			}
			LABEL:x = getandprint("Request.txt",name,roll,usr,psswd,x);
			if(x==113) break;
			char* options[5]={"Delete request","Accept request","Go back","Back to main menu",0};
			y = getoption(4,options);
			if(y==4) break;
			if(y==3) goto LABEL;
			if(y==1){
				User user;
				strncpy(user.name,name[x-1],strlen(name[x-1])+1);
				strncpy(user.roll,roll[x-1],strlen(roll[x-1])+1);
				strncpy(user.usr_name,usr[x-1],strlen(usr[x-1])+1);
				strncpy(user.pass,psswd[x-1],strlen(psswd[x-1])+1);
				del_account(user,"Request.txt");
			}
			if(y==2){
				User user;
				strncpy(user.name,name[x-1],strlen(name[x-1])+1);
				strncpy(user.roll,roll[x-1],strlen(roll[x-1])+1);
				strncpy(user.usr_name,usr[x-1],strlen(usr[x-1])+1);
				strncpy(user.pass,psswd[x-1],strlen(psswd[x-1])+1);
				del_account(user,"Request.txt");
				update_req(user);
			}
			break;
			
			case 'b':
			clear_all_screen();
			break;
		}
	}while(choice != 'b');
}

//booking management options code written in login_menu.c as related to
//computer booking and stuff

void ADMIN(void){
	char* menu[] = {"aAccounts management",
		      "bBooking resource management",
		      "lLogout",
		      0
		      };
	int choice;
	do{
		choice = getchoice("ADMIN Options:",menu);
		switch(choice){
			case 'a':
			acc_manage();
			break;

			case 'b':
			book_manage();
			break;

			case 'l':
			clear_all_screen();
			break;
		}
	}while(choice != 'l');
}

