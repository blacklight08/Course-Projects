
#define MAX_COMP_T 10
#define MAX_COMP_P 2

typedef struct perm_comp_details_ {
  int pcomp_id,day;
  char *slot[5];
} perm_comp_details;

typedef struct temp_comp_details_ {
  int comp_id,duration_hrs,login_hr,login_min;
  char status;
  char *student_id;
} temp_comp_details;

//reads a file with temporary computers' status
int get_comp(char* user_name,int start_hr, int start_min,int needed_hrs) {
  int i,b;
  char buf;
  FILE *comp_fp;
  temp_comp_details comp[MAX_COMP_T];
  
  comp_fp= fopen("temp_comp.txt","r");
  for(i=0;i<MAX_COMP_T;i++) {
    fscanf(comp_fp,"%d%c%d%c%d%c%d%c",&comp[i].comp_id,&buf,&comp[i].duration_hrs,&buf,&comp[i].login_hr,&buf,&comp[i].login_min,&buf);
    fscanf(comp_fp,"%c%c",&comp[i].status,&buf);
    comp[i].student_id= (char*) malloc(15* sizeof(char));
    fscanf(comp_fp,"%s",comp[i].student_id);
    for(b=0;b<3;b++)
      fscanf(comp_fp,"%c",&buf);
  }
  fclose(comp_fp);
  for(i=0;i<MAX_COMP_T;i++) {
    if(comp[i].status=='y')
      return comp[i].comp_id;
    else if((comp[i].login_hr+comp[i].duration_hrs < start_hr) || (comp[i].login_hr+comp[i].duration_hrs == start_hr && comp[i].login_min<start_min)) {
      comp[i].status = 'y';
      return comp[i].comp_id;
    }
  }
  return 0;
}

//updates the temporary computers' status file
void update_file(int c, char* name, int hr, int min, int dur) {
  int i,b;
  char buf;
  FILE *comp_fp;
  temp_comp_details comp[MAX_COMP_T];
  
  c-=101;
  comp_fp= fopen("temp_comp.txt","r");
  for(i=0;i<MAX_COMP_T;i++) {
    fscanf(comp_fp,"%d%c%d%c%d%c%d%c",&comp[i].comp_id,&buf,&comp[i].duration_hrs,&buf,&comp[i].login_hr,&buf,&comp[i].login_min,&buf);
    fscanf(comp_fp,"%c%c",&comp[i].status,&buf);
    comp[i].student_id= (char*) malloc(15* sizeof(char));
    fscanf(comp_fp,"%s",comp[i].student_id);
    for(b=0;b<3;b++)
      fscanf(comp_fp,"%c",&buf);
  }
  fclose(comp_fp);
  comp[c].status= 'n';
  comp[c].student_id= name;
  comp[c].duration_hrs= dur; comp[c].login_hr= hr; comp[c].login_min= min;
  comp_fp= fopen("temp_comp.txt","w");
  for(i=0;i<MAX_COMP_T;i++) {
    fprintf(comp_fp,"%d,%d,%d,%d,%c,%s ;\n",comp[i].comp_id,comp[i].duration_hrs,comp[i].login_hr,comp[i].login_min,comp[i].status,comp[i].student_id);
  }
  fclose(comp_fp);
}

int get_compp(int day, int today, int sl) {
  int i,b,j=0,k,l;
  char buf;
  FILE *pcomp_fp;
  perm_comp_details comp[3*MAX_COMP_P];
  
  pcomp_fp= fopen("comp.txt","r");
  for(i=0;i<3*MAX_COMP_P;i++) {
    fscanf(pcomp_fp,"%d%c%d%c",&comp[i].pcomp_id,&buf,&comp[i].day,&buf);
    for(b=0;b<5;b++) {
      comp[i].slot[b]= (char*) malloc(15* sizeof(char));
      fscanf(pcomp_fp,"%s%c%c",comp[i].slot[b],&buf,&buf);
    }
    fscanf(pcomp_fp,"%c",&buf);
  }
  fclose(pcomp_fp);
  k= today-comp[0].day;  //updating the list everyday
  if(k>0) {
    for(i=0;i<3*MAX_COMP_P;i+=3) {
      for(j=0;j<3-k;j++) {
        comp[i+j].day= comp[i+j+k].day;
        for(b=0;b<5;b++)
          comp[i+j].slot[b]= comp[i+j+k].slot[b];
      }
      for(l=j;l<3;l++) {
        comp[i+l].day= today+l;
        for(b=0;b<5;b++)
          comp[i+l].slot[b]= "0";
      }
    }
    pcomp_fp= fopen("comp.txt","w");
    for(i=0;i<3*MAX_COMP_P;i++) {
      fprintf(pcomp_fp,"%d,%d,",comp[i].pcomp_id,comp[i].day);
      for(b=0;b<5;b++) {
        fprintf(pcomp_fp,"%s ,",comp[i].slot[b]);
      }
      fprintf(pcomp_fp,"\n");
    }
    fclose(pcomp_fp);
  }
  for(i=day;i<3*MAX_COMP_P;i+=3) {
    if(strlen(comp[i].slot[sl-1])==1)
      return comp[i].pcomp_id;
  }
  return 0;
}

void update_compp(int ci, char* sid, int day, int sl) {
  int i,b;
  char buf;
  FILE *pcomp_fp;
  perm_comp_details comp[3*MAX_COMP_P];
  
  pcomp_fp= fopen("comp.txt","r");
  for(i=0;i<3*MAX_COMP_P;i++) {
    fscanf(pcomp_fp,"%d%c%d%c",&comp[i].pcomp_id,&buf,&comp[i].day,&buf);
    for(b=0;b<5;b++) {
      comp[i].slot[b]= (char*) malloc(15* sizeof(char));
      fscanf(pcomp_fp,"%s%c%c",comp[i].slot[b],&buf,&buf);
    }
  }
  fclose(pcomp_fp);
  ci= 3*(ci-1)+day; sl--;
  comp[ci].slot[sl]= sid;
  pcomp_fp= fopen("comp.txt","w");
  for(i=0;i<3*MAX_COMP_P;i++) {
    fprintf(pcomp_fp,"%d,%d,",comp[i].pcomp_id,comp[i].day);
    for(b=0;b<5;b++) {
      fprintf(pcomp_fp,"%s ,",comp[i].slot[b]);
    }
    fprintf(pcomp_fp,"\n");
  }
  fclose(pcomp_fp);
}

int get_free_compp(int day, int cid, int sl) {
  int i,b,j=0,k,l;
  char buf;
  FILE *pcomp_fp;
  perm_comp_details comp[3*MAX_COMP_P];
  
  pcomp_fp= fopen("comp.txt","r");
  for(i=0;i<3*MAX_COMP_P;i++) {
    fscanf(pcomp_fp,"%d%c%d%c",&comp[i].pcomp_id,&buf,&comp[i].day,&buf);
    for(b=0;b<5;b++) {
      comp[i].slot[b]= (char*) malloc(6* sizeof(char));
      fscanf(pcomp_fp,"%s%c%c",comp[i].slot[b],&buf,&buf);
    }
    fscanf(pcomp_fp,"%c",&buf);
  }
  fclose(pcomp_fp);
  if(strlen(comp[3*cid+day-3].slot[sl-1])==1)
      return 1;
  return 0;
}

char* user_free_compp(int day, int cid, int sl) {
  int i,b,j=0,k,l;
  char buf;
  FILE *pcomp_fp;
  perm_comp_details comp[3*MAX_COMP_P];
  
  pcomp_fp= fopen("comp.txt","r");
  for(i=0;i<3*MAX_COMP_P;i++) {
    fscanf(pcomp_fp,"%d%c%d%c",&comp[i].pcomp_id,&buf,&comp[i].day,&buf);
    for(b=0;b<5;b++) {
      comp[i].slot[b]= (char*) malloc(6* sizeof(char));
      fscanf(pcomp_fp,"%s%c%c",comp[i].slot[b],&buf,&buf);
    }
    fscanf(pcomp_fp,"%c",&buf);
  }
  fclose(pcomp_fp);
  return comp[3*cid+day-3].slot[sl];
}

