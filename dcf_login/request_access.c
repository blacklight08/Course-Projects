#include <stdio.h>
#include <ncurses.h>
#include <string.h>

User assign_username(User new);
User assign_password (User new);
void store(User new);

bool conditions (void){
		
	FILE *fp;
	int number;
	char decision='0';
	char TandC;
	fp = fopen("Terms and Conditions.txt","r");
	clear();
	do{	
		TandC=getc(fp);
		if(feof(fp)==0)
			printw("%c",TandC);
		refresh();
	}while(feof(fp)==0);	
	refresh();
	while((decision != 'y')||(decision != 'n')){
		scanw("%c",&decision);
		if(decision == 'y')
			return 1;
		else if(decision == 'n')
			return 0;
		else{
			printw("Illegal character...Please Re-Enter the correct Decision\n");
			refresh();
		}
	}
	fclose(fp);			
}

void new_form (void){
	User new;
	clear_all_screen();
	attron(A_UNDERLINE);
	mvprintw(4,(COLS-11)/3,"APPLICATION FORM");
	attroff(A_UNDERLINE);
	mvprintw(7,COLS/4,"Name: ");
	scanw("%s",new.name);
	mvprintw(8,COLS/4,"Roll No.: ");
	scanw("%s",new.roll);
	new = assign_username(new);	
	new = assign_password(new);
	store(new);	
	clear();
	attron(A_UNDERLINE);
	mvprintw(LINES/3,COLS/3,"Request has been sent to the Admin");
	attroff(A_UNDERLINE);
	attron(A_BOLD);
	mvprintw((LINES/3)+2,(COLS/3)+10,"Thankyou.. ");
	attroff(A_BOLD);
	refresh();
	sleep(3);
}

User assign_password (User new){
	char re_enter[10];
	mvprintw(10,COLS/4,"Password: ");
	refresh();	
	scanf("%s",new.pass);
	mvprintw(11,COLS/4,"Retype Password: ");
	refresh(); 	
	scanf("%s",re_enter);
	if(strcmp(re_enter,new.pass)==0)
		return new;
	else{
		mvprintw(15,COLS/4,"Passwords didnot match");
		refresh();
		sleep(2);
		clear_all_screen();
		attron(A_UNDERLINE);
		mvprintw(4,(COLS-11)/3,"APPLICATION FORM");
		attroff(A_UNDERLINE);
		mvprintw(7,COLS/4,"Name: %s\n",new.name);
		mvprintw(8,COLS/4,"Roll No.: %s\n",new.roll);
		mvprintw(9,COLS/4,"Username: %s\n",new.usr_name);
		assign_password(new);
	}
}

User assign_username(User new){
	User temp;
	FILE* fp;
	fp = fopen("Facts.txt","r");
	mvprintw(9,COLS/4,"Username: ");
	scanw("%s",new.usr_name);
	rewind(fp);
	while(feof(fp)==0){
		fscanf(fp,"%s%s%s%s",temp.name,temp.roll,temp.usr_name,temp.pass);
		if(strcmp(temp.usr_name,new.usr_name)==0){
			mvprintw(15,COLS/4,"Username already exists..Use a new name");
			refresh();
			sleep(3);
			clear_all_screen();
			attron(A_UNDERLINE);
			mvprintw(4,(COLS-11)/3,"APPLICATION FORM");
			attroff(A_UNDERLINE);
			mvprintw(7,COLS/4,"Name: %s\n",new.name);
			mvprintw(8,COLS/4,"Roll No.: %s\n",new.roll);
			fclose(fp);
			new=assign_username(new);
		}
	}	
return new;
}

void store(User new){
	FILE* fp;
	fp = fopen("Request.txt","a");
	fprintf(fp,"%s %s %s %s\n",new.name,new.roll,new.usr_name,encrypt(new.pass));
	fclose(fp);
}

