#include<time.h>
#include"comp_scan.c"
#include"2d_move.c"
#define Q_LINE 20

void inst_book(char *student_id);
void advance_book(char* student_id);
void change_pswd(char* student_id);

char *login_menu[] = {
  "bBook Computer Quick",
  "cChange Password",
  "aAdvance booking",
  "lLogout",
  0,
};

void clear_login_screen(char* name) {
  clear();
  mvprintw(2,COLS/3,"%s","DCF Login Systems");
  mvprintw(LINES-1,0,"Logged in as: %s (%s)",name,fscan(name,'n'));//
  refresh();
}

int get_confirm() {
  int confirmed=0;
  char first_char;
  mvprintw(Q_LINE,5,"Continue?('n' to cancel)");
  clrtoeol();
  refresh();
  cbreak();
  first_char=getch();
  if(first_char=='y'||first_char=='\n') {
    confirmed=1;
  }
  nocbreak();
  if(!confirmed) {
    mvprintw(Q_LINE,1,"  Cancelled");
    clrtoeol();
    refresh();
    sleep(1);
  }
  return confirmed;
}

    //main screen function
void login_screen(char* student_id) {
  int choice;
  char* name;
  
  name= "fscan(student_id,'n')";
  initscr();
  do{
    choice= getchoice("name",login_menu);
    switch(choice) {
      case 'l':
	break;
      case 'b':
	clear_login_screen(student_id);
	inst_book(student_id);
	break;
      case 'a':
	clear_login_screen(student_id);
	advance_book(student_id);
	break;
      case 'c':
	clear_login_screen(student_id);
	change_pswd(student_id);
	break;
    }
  }
  while(choice!='l');
  endwin();
}

void inst_book(char *student_id) {
  int c;
  char buff[100];
  struct tm tim;
  time_t now= time(0);
  
  tim= *(localtime(&now));
  strftime (buff, 100, "%d/%m/%Y %H:%M:%S", &tim);
  initscr();
  mvprintw(0,40,buff);
  
  c= get_comp(student_id,tim.tm_hour,tim.tm_min,1);
  if(c==0)
    mvprintw(9,10,"Sorry! All computers booked at the moment");
  else {
    tim.tm_hour ++;
    strftime (buff, 100, "%d/%m/%Y %H:%M:%S", &tim);
    mvprintw(9,10,"Successfully booked comp_id = %d under user_id \"%s\"\n\t\tuptill %s",c,student_id,buff);
  }
  refresh();
  if(!get_confirm())
    return;
  if(c!=0)
    update_file(c,student_id,tim.tm_hour-1,tim.tm_min,1);
}

void check_status(char* student_id) {
  int day,sl,size=0,c,com,choice;
  char **options,buff[15];
  struct tm tim,today;
  time_t now= time(0);
  
  options= malloc(100*sizeof(char*));
  for(c=0;c<100;c++)
    options[c]= malloc(20*sizeof(char));
  today= tim = *(localtime(&now));
  
  for(com=1;com<=MAX_COMP_P;com++) {
    now= time(0);
    tim= *(localtime(&now));
    for(day=0;day<3;day++) {
      if(day!=0)
      now+= 60*60*24;
      tim= *(localtime(&now));
      for(sl=0;sl<5;sl++) {
        c= get_free_compp(day,com,sl+1);
        if(c!=0) {
          strcpy(options[2*size],"Comp id: ");
          options[2*size][8]= com+48;
          strftime(buff,15,"%d/%m/%y" ,&tim);
          strcpy(options[2*size+1],"Slot no.  ");
          options[2*size+1][8]= sl+49;
          strcat(options[2*size+1],buff);
	      size++;
        }
      }
    }
  }
  int a=0;
  choice= getchoice2D(options,size,2);
  if(!get_confirm())
    return;
  if(choice!='q') {
    for(com=1;com<=MAX_COMP_P;com++)
      for(day=0;day<3;day++)
	for(sl=0;sl<5;sl++) {
	  c= get_free_compp(day,com,sl+1);
	  if(c!=0) {
	    if(a==choice)
	      update_compp(com,student_id,day,sl+1);
	    a++;
	  }
	}
  }
  endwin();
}

void adv_book(char* student_id) {
  int c,day,slot;
  char buff[100];
  struct tm tim;
  time_t now= time(0);
  
  tim = *(localtime(&now));
  strftime(buff, 100, "%d/%m/%Y %H:%M:%S", &tim);
  initscr();
  mvprintw(0,40,buff);
  mvprintw(17,0,"\tYou can book only for 2 days from today (also today) and \n\tfor any 5 slots of each day");
  mvprintw(5,10,"Enter number of days from today");
  move(7,10);
  scanw("%d",&day); mvprintw(7,15,"days from now with slot ");
  scanw("%d",&slot);
  
  if(!(day<3 && slot<6))
    mvprintw(10,10,"The booking doesnt exist for the given slot or day");
  else {
    c= get_compp(day,tim.tm_yday, slot);
    now+= 60*60*24*day;
    tim= *(localtime(&now));
    if(c==0)
      mvprintw(13,10,"Sorry! All computers booked at the given time");
    else {
      strftime(buff,100, "%d/%m/%y",&tim);
      mvprintw(13,10,"Successfully booked comp_id = %d under user_id \"%s\"\n\ton slot %d of %s",c,student_id,slot,buff);
    }
  }
  refresh();
  if(!get_confirm())
    return;
  if(c!=0)
    update_compp(c,student_id,day,slot);
}

void advance_book(char* student_id) {
  char* adbook_menu[] = {
    "cCheck free computers",
    "iInput slot details",
    "bBack",
    0,
  };
  int choice;
  char* name;
  
  name = fscan(student_id,'n');
  initscr();
  do{
    choice= getchoice(name,adbook_menu);
    switch(choice) {
      case 'b':
        break;
      case 'c':
	check_status(student_id);
	break;
      case 'i':
    clear_login_screen(student_id);
	adv_book(student_id);
	break;
    }
  }
  while(choice!='b');
  endwin();
}

void change_pswd(char* student_id) {
  char ps1[8],ps2[8];
  
  noecho();
  mvprintw(7,10,"Please type new password: ");
  scanw("%s",ps1);
  mvprintw(9,10,"Please renter the password: ");
  scanw("%s",ps2);
  if(strcmp(ps1,ps2)==0) {
    if(!get_confirm())
      return;
   pswdf_change(student_id,ps1);
    mvprintw(11,10,"Successfully changed");
  }
  else
    mvprintw(11,10,"Passwords mismatch! Try again");
  if(!get_confirm())
    return;
}




// Functions from admin account
void book_manage() {
  int day,sl,size=0,c=0,com,choice,menu_choice;
  int day_n,com_n,sl_n;
  char **options,buff[15],*user_id;
  char* menu[] = {"dDelete booking",
    "cChange booking",
    "bBack",
    0,
  };
  struct tm tim,today;
  time_t now= time(0);
  
  user_id= malloc(15*sizeof(char));
  options= malloc(200*sizeof(char*));
  for(c=0;c<100;c++)
    options[c]= malloc(20*sizeof(char));
  today= tim = *(localtime(&now));
  
  for(com=1;com<=MAX_COMP_P;com++) {
    now= time(0);
    tim= *(localtime(&now));
    for(day=0;day<3;day++) {
      if(day!=0)
      now+= 60*60*24;
      tim= *(localtime(&now));
      for(sl=0;sl<5;sl++) {
        user_id= user_free_compp(day,com,sl);
        strcpy(options[3*size],"Comp id: ");
        options[3*size][8]= com+48;
        strftime(buff,15,"%d/%m/%y" ,&tim);
        strcpy(options[3*size+1],"Slot no.  ");
        options[3*size+1][8]= sl+49;
        strcat(options[3*size+1],buff);
        strcpy(options[3*size+2],"User: ");
        strcat(options[3*size+2],user_id);
	    size++;
      }
    }
  }
  c=0;
  choice= getchoice2D(options,size,3);
  if(choice!='q') {
    for(com=1;com<=MAX_COMP_P;com++)
      for(day=0;day<3;day++)
	for(sl=0;sl<5;sl++) {
	  if(c==choice) {
	    day_n=day; sl_n= sl+1; com_n=com;
	  }
	  c++;
	}
  }
  clear_all_screen();
    menu_choice= getchoice("What to do you want to do with selected computer",menu);
    switch(menu_choice){
      case 'b':
	break;
      case 'd':
	if(!get_confirm())
	  return;
	else
	  update_compp(com_n,"0",day_n,sl_n);
	break;
      case 'c':
	mvprintw(13,10,"Enter user name: ");
	scanw("%s",user_id);
	if(!get_confirm())
	  return;
	update_compp(com_n,user_id,day_n,sl_n);
	break;
    }
  endwin();
}
