int sort_color(char c)
{
	if(c=='B') return 0;
	if(c=='T') return 1;
	if(c=='R') return 2;
}
noteptr read_note(int chosen) 
{
	extern double preparing_time,adjust_time;
    char path_data[200],path_note[200];  
	char tmp_buf[80];
	int bpm,score,count,count_i;
	char tmp_char;
	double tmp_timing;
	extern int notes_front,notes_y,screen_broad,notes_count,notes_speed;
	FILE *datain;
	
    getcwd(tmp_buf,sizeof(tmp_buf));   
    sprintf(path_data,"%s\\data\\notes\\%d.txt",tmp_buf,chosen);
    datain = fopen(path_data,"r");
	fscanf(datain,"%d",&count);
	
	noteptr notes;
	notes=(noteptr)malloc(count*sizeof(note));   
	notes_front=0;
	notes_rear=0;
	notes_count=count;
	
	for(count_i=0;count_i<count;count_i++)
	{
		fscanf(datain,"%lf %c",&tmp_timing,&tmp_char);
		notes[count_i].color=sort_color(tmp_char);
		notes[count_i].timing=tmp_timing+preparing_time+adjust_time;
		notes[count_i].x=screen_length;
		notes[count_i].y=notes_y;
		notes[count_i].remain=(double)notes_speed;
	}
	return notes;
    fclose(datain);
}

void display(noteptr notes) 
{
	char path_note[200],tmp_buf[80];
	getcwd(tmp_buf,sizeof(tmp_buf));  
	
	int display_i;
	extern int notes_flow,notes_front,notes_rear,notes_count;
	extern double elapse_time;
	if (notes_front>=notes_count) return;
	for(display_i=notes_rear-1;display_i>=notes_front;display_i--)
	{
		notes[display_i].remain=notes[display_i].timing-elapse_time;	
		if(notes[display_i].remain>0) notes_flow=((double)(notes[display_i].x-(double)screen_length*0.1)/(notes[display_i].remain*getfps())>0)?((double)(notes[display_i].x-(double)screen_length*0.1)/(notes[display_i].remain*getfps())):notes_flow;
		notes[display_i].x-=notes_flow;
		setcolor(EGERGB(255, 255, 255));	
		setfillcolor(EGERGB(255, 255, 255));
		setbkmode(OPAQUE);
		fillellipse(notes[display_i].x+50,notes[display_i].y+50,50,50); 
		if(notes[display_i].color==0) setfillcolor(EGERGB(112, 201, 191));
		if(notes[display_i].color==1) setfillcolor(EGERGB(117, 42, 120));
		if(notes[display_i].color==2) setfillcolor(EGERGB(233, 55, 44));
		fillellipse(notes[display_i].x+50,notes[display_i].y+50,40,40); 
	}
	return;
}

