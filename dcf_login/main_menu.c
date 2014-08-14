#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <ncurses.h>

typedef struct User_{
	char name[15];
	char roll[10];
	char usr_name[10];
	char pass[20];
}User;

#include "functions.c"
#include "request_access.c"
#include "login_menu.c"
#include "ADMIN.c"

const char *student_list= "Facts.txt";

// function enables logging in
void login(void) {
	char name[10];
	char password[10];
	char real_password[10];
	char *n;
	WINDOW *popup_window_ptr;
	
	initscr();
	move(5,(COLS-12)/3);
	printw("%s","Please login");
	move(7,(COLS-12)/3);
	printw("%s", "Username: ");
	scanw("%s",name);
	move(9,(COLS-12)/3);
	printw("%s","Password: ");
	
	refresh();
	cbreak();
	noecho();
	
	if((n=fscan(name,'p')) != NULL) strncpy(real_password,un_encrypt(n),strlen(n)+1);
	
	scanw("%s",password);
	echo();
	nocbreak();
	refresh();
	
	popup_window_ptr = newwin(5,20,(LINES*2)/3,(COLS-12)/3);
	box(popup_window_ptr,'.','-');
	if(strcmp(password,real_password)==0) {
		mvwprintw(popup_window_ptr,2,2,"%s", "Logging in....\n");
		wrefresh(popup_window_ptr);
		sleep(1);
		login_screen(name);
		mvwprintw(popup_window_ptr,3,2,"%s", "Logging out....\n");
	}
	else if(!fscan(name,'p')) mvwprintw(popup_window_ptr,2,2,"%s","No user found.\n");
	else mvwprintw(popup_window_ptr,2,2,"%s","Wrong Password.\n");
	wrefresh(popup_window_ptr);
	
	sleep(1);
	endwin();
}

//logging in for Guest
void guest_access(void){
	int cho;
	char* list[] = {"rRequest account","iInstant booking","lLogout",0,};
	do{
		cho = getchoice("Guest Account Options:",list);
		switch(cho){
			case 'r':
			clear();
			attron(A_BOLD | A_UNDERLINE);
			mvprintw(LINES/3,COLS/3,"%s","Welcome to DCF Login_Systems\n");
			attroff(A_BOLD | A_UNDERLINE);
			bool value = conditions();
			if(value == 1)
				new_form();
			else
				break;
			break;

			case 'i':
			clear_all_screen();
			mvprintw(LINES-1,0,"Logged in as: Guest");
			inst_book("Guest");
			break;
	
			case 'l':
			break;
		}
	}while(cho!='l');
}
	
//logging in for adminstrator
void admin_entry(void){
	char* admin = malloc(sizeof(char));
	mvprintw(LINES/3,COLS/3,"%s","Password: ");
	noecho();
	scanw("%s",admin);
	if(strcmp(admin,fscan(admin,'a'))==0){
		mvprintw((LINES*2)/3,(COLS-12)/3,"Logging in ....\n");
		echo();refresh();
		sleep(1);
		ADMIN();
	}
	else {	
		
		mvprintw((LINES*2)/3,(COLS-12)/3,"Wrong Password!!\n");
		refresh();
		sleep(1);
	}
}
	
int main() {
  int choice;
  char *main_menu[] = {
  "lLogin",
  "gGuest Access",
  "aAdmin Access",
  "qQuit",
  0,
  };
  initscr();
  do{
    choice= getchoice("Options:",main_menu);
    switch(choice) {
      case 'q':
	break;
      case 'a':
	clear_all_screen();
	admin_entry();
	break;
      case 'l':
	clear_all_screen();
	login();
	break;
      case 'g':
	guest_access();
	
    }
  }
  while(choice!='q');
  endwin();
  exit(EXIT_SUCCESS);
}


