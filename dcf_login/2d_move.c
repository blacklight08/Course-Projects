
//moving in 2 dimensions and pages
void draw_2Dmenu(char *options[], int page, int current_hcol, int current_hrow, int start_row, int start_col,int set) {
  int i=0,j=0,c=0,current_col=0,current_row=0;
  char **option_ptr;
  
  clear_all_screen();
  option_ptr = options;
  j= 4*set*(page-1);
  while(i<4) {
    if(current_col==current_hcol && current_row==current_hrow) {
      mvaddch(start_row+current_row, start_col + current_col-3, ACS_ULCORNER);
      mvaddch(start_row+current_row, start_col+current_col+20, ACS_URCORNER);
      mvaddch(start_row+current_row+3, start_col+current_col-3, ACS_LLCORNER);
      mvaddch(start_row+current_row+3, start_col+current_col+20, ACS_LRCORNER);
    }
    else {
      mvaddch(start_row+current_row, start_col+current_col-3, ' ');
      mvaddch(start_row+current_row, start_col+current_col+20, ' ');
      mvaddch(start_row+current_row+3, start_col+current_col-3, ' ');
      mvaddch(start_row+current_row+3, start_col+current_col+20, ' ');
    }
    for(c=0;c<set;c++)
      mvprintw(start_row+current_row+1+c, start_col+current_col,"%s", options[j+c]);
    if(i%2==0) current_col+=25;
    else {
      current_row+=8;
      current_col-=25;
    }
    i++;j+=set;
  }
  mvprintw(start_row+13, start_col, "'Press PgUp or PgDn to move pages, Page no. %d\n\t\t'q' to Quit",page);
  refresh();
}

int getchoice2D(char *choices[],int size, int set) {
  int selected_col=0,selected_row=0,selected_page=1;
  int max_col =0,max_row = 8,max_page= size/4+1;
  int start_screenrow = MESSAGE_LINE, start_screencol = 10;
  char **option;
  int selected;
  int key=0;
  
  option = choices;
  max_col=25;
  if(selected_page>=max_page)
    selected_page=0;
  if(selected_col>=max_col)
    selected_col=0;
  clear_all_screen();
  
  keypad(stdscr,TRUE);
  cbreak();
  noecho();
  key=0;
  while(key!='q' && key!=KEY_ENTER && key != '\n') {
    if(key==KEY_PPAGE) {
      if(selected_page<=1)
        selected_page=max_page;
      else
        selected_page--;
    }
    if(key==KEY_NPAGE) {
      if(selected_page>=max_page)
        selected_page=1;
      else
        selected_page++;
    }
    if(key==KEY_LEFT) {
      if(selected_col==0)
	selected_col = max_col;
      else
	selected_col-=25;
    }
    if(key==KEY_RIGHT) {
      if(selected_col >= (max_col-1))
	selected_col = 0;
      else
	selected_col+=25;
    }
    if(key==KEY_UP) {
      if(selected_row==0)
	selected_row = max_row;
      else
	selected_row-=8;
    }
    if(key==KEY_DOWN) {
      if(selected_row >= (max_row-1))
	selected_row = 0;
      else
	selected_row+=8;
    }
    selected= 4*selected_page+selected_row/4+selected_col/25-4;
    draw_2Dmenu(choices,selected_page, selected_col, selected_row, start_screenrow, start_screencol,set);
    key = getch();
  }
  keypad(stdscr,FALSE);
  nocbreak();
  echo();
  
  if(key=='q')
    selected='q';
  return(selected);
}

