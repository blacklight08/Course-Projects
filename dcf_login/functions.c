#define MESSAGE_LINE 6
#define ERROR_LINE 22
#define Q_LINE 20
#define PROMPT_LINE 18
#define LEN 15
void clear_all_screen(void);
void draw_menu(char *options[], int highlight, int start_row,int start_col);

void clear_all_screen() {
  clear();
  mvprintw(2,(COLS-11)/3,"%s","DCF Login Systems");
  mvprintw(LINES-1, 0, "Created be team C_U_");
  refresh();
}
//
//
//
//
void draw_menu(char *options[], int current_hightlight, int start_row, int start_col) {
  int current_row=0;
  char **option_ptr;
  char *txt_ptr;
  
  option_ptr = options;
  while(*option_ptr) {
    if(current_row==current_hightlight) {
      attron(A_BOLD | A_UNDERLINE);
      mvaddch(start_row + current_row, start_col-3, ACS_LARROW);
      mvaddch(start_row + current_row, start_col+40, ACS_RARROW);
      attroff(A_BOLD | A_UNDERLINE);
    }
    else {
      mvaddch(start_row + current_row, start_col-3, ' ');
      mvaddch(start_row+current_row, start_col+40, ' ');
    }
    txt_ptr = options[current_row];
    txt_ptr++;
    mvprintw(start_row+current_row, start_col,"%s", txt_ptr);
    current_row++;
    option_ptr++;
  }
  mvprintw(start_row+current_row+3, (start_col*2/3), "Use Up and Down arrow buttons for movement and press Enter to select the option");
  refresh();
}
//
//
//
//
int getchoice(char *heading, char *choices[]) {
  int selected_row=0;
  int max_row = 0;
  int start_screenrow = MESSAGE_LINE, start_screencol = (COLS-strlen(heading)-2)/3;
  char **option;
  int selected;
  int key=0;
  
  option = choices;
  while(*option) {
    max_row++;
    option++;
  }
  if(selected_row>=max_row)
    selected_row=0;
  clear_all_screen();
  mvprintw(start_screenrow-2, start_screencol, heading);
  
  keypad(stdscr,TRUE);
  cbreak();
  noecho();
  key=0;
  while(key!='q' && key!=KEY_ENTER && key != '\n') {
    if(key==KEY_UP) {
      if(selected_row==0)
	selected_row = max_row-1;
      else
	selected_row--;
    }
    if(key==KEY_DOWN) {
      if(selected_row == (max_row-1))
	selected_row = 0;
      else
	selected_row++;
    }
    selected = *choices[selected_row];
    draw_menu(choices, selected_row, start_screenrow, start_screencol);
    key = getch();
  }
  keypad(stdscr,FALSE);
  nocbreak();
  echo();
  
  if(key=='q')
    selected='q';
  return(selected);
}
//
//
//
//

char* fscan(char *name, char type) {
  	FILE *student_fp;
	User temp;
	char* str= malloc(15*sizeof(char));
	char* ac_name = malloc(20*sizeof(char));
	if(type == 'a'){
		student_fp = fopen("data.txt","r");
		fscanf(student_fp,"%s",str);
		fclose(student_fp);
		return str;
	}
	else{
		student_fp = fopen("Facts.txt","r");
		while(feof(student_fp)==0){
			fscanf(student_fp,"%s%s%s%s",ac_name,temp.roll,temp.usr_name,str);
				if(strcmp(temp.usr_name,name)==0){
					if(type == 'p')					
						return str;
					else if(type == 'n')
						return  ac_name;
				}
		}
		return NULL;
	}
}



void update_req(User given){
	FILE* fp1;
	FILE* fp2;
	int count;
	User temp;
	fp1 = fopen("Request.txt","r");
	fp2 = fopen("Temp.txt","w");
	fseek(fp2,0,SEEK_SET);
	while(feof(fp1)==0){
		fscanf(fp1,"%s%s%s%s",temp.name,temp.roll,temp.usr_name,temp.pass);
		if(strcmp(temp.usr_name,given.usr_name)!=0)
			if(feof(fp1)==0)
				fprintf(fp2,"%s %s %s %s\n",temp.name,temp.roll,temp.usr_name,(temp.pass));
	}
	fclose(fp1);
	fclose(fp2);
	fp1 = fopen("Request.txt","w");
	fp2 = fopen("Temp.txt","r");
	while(feof(fp2)==0){
		fscanf(fp2,"%s%s%s%s",temp.name,temp.roll,temp.usr_name,temp.pass);
		if(feof(fp2)==0)
			fprintf(fp1,"%s %s %s %s\n",temp.name,temp.roll,temp.usr_name,(temp.pass));
	}
	fclose(fp1);
	fclose(fp2);
	fp1 = fopen("Temp.txt","w");
	fclose(fp1);
	fp1 = fopen("Facts.txt","a");
	fprintf(fp1,"%s %s %s %s\n",given.name,given.roll,given.usr_name,(given.pass));
	fclose(fp1);
}

void del_account(User given,char* file_name){
	FILE* fp1;
	FILE* fp2;
	int count;
	User temp;
	fp1 = fopen(file_name,"r");
	fp2 = fopen("Temp.txt","w");
	fseek(fp2,0,SEEK_SET);
	while(feof(fp1)==0){
		fscanf(fp1,"%s%s%s%s",temp.name,temp.roll,temp.usr_name,temp.pass);
		if(strcmp(temp.usr_name,given.usr_name)!=0)
			if(feof(fp1)==0)
				fprintf(fp2,"%s %s %s %s\n",temp.name,temp.roll,temp.usr_name,temp.pass);
	}
	fclose(fp1);
	fclose(fp2);
	fp1 = fopen(file_name,"w");
	fp2 = fopen("Temp.txt","r");
	while(feof(fp2)==0){
		fscanf(fp2,"%s%s%s%s",temp.name,temp.roll,temp.usr_name,temp.pass);
		if(feof(fp2)==0)
			fprintf(fp1,"%s %s %s %s\n",temp.name,temp.roll,temp.usr_name,temp.pass);
	}
	fclose(fp1);
	fclose(fp2);
	fp1 = fopen("Temp.txt","w");
	fclose(fp1);
}


char* encrypt (char* pass){
	char* en_pass;
	int pass_no;
	int count;
	en_pass = (char*) malloc(LEN*sizeof(char));
	for(count=0;count<strlen(pass);count++){
		pass_no = (int)pass[count];
		en_pass[count] = (char)(pass_no + 1);
	}
	en_pass[count]='\0';
return en_pass;
}

char* un_encrypt (char* en_pass){
	char* pass;
	int en_pass_no;
	int count;
	pass = (char*) malloc(LEN*sizeof(char));
	for(count=0;count<strlen(en_pass);count++){
		en_pass_no = (int)en_pass[count];
		pass[count] = (char)(en_pass_no - 1);
	}
	en_pass[count]='\0';
return pass;
}

void pswdf_change(char* usr_name,char* pass){
	FILE* fp1;
	FILE* fp2;
	int count;
	User temp;
	fp1 = fopen("Facts.txt","r");
	fp2 = fopen("Temp.txt","w");
	fseek(fp2,0,SEEK_SET);
	while(feof(fp1)==0){
		fscanf(fp1,"%s%s%s%s",temp.name,temp.roll,temp.usr_name,temp.pass);
		if(strcmp(temp.usr_name,usr_name)==0){
			if(feof(fp1)==0)
				fprintf(fp2,"%s %s %s %s\n",temp.name,temp.roll,temp.usr_name,encrypt(pass));
		}		
		else
			if(feof(fp1)==0)
				fprintf(fp2,"%s %s %s %s\n",temp.name,temp.roll,temp.usr_name,(temp.pass));
	}
	fclose(fp1);
	fclose(fp2);
	fp1 = fopen("Facts.txt","w");
	fp2 = fopen("Temp.txt","r");
	while(feof(fp2)==0){
		fscanf(fp2,"%s%s%s%s",temp.name,temp.roll,temp.usr_name,temp.pass);
		if(feof(fp2)==0)
			fprintf(fp1,"%s %s %s %s\n",temp.name,temp.roll,temp.usr_name,(temp.pass));
	}
	fclose(fp1);
	fclose(fp2);
	fp1 = fopen("Temp.txt","w");
	fclose(fp1);
}
