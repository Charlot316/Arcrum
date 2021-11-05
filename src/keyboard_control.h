void select_interface();
int sort_key(char c)
{
	switch(c)
	{
		case 'F': return 0;break;
		case 'f': return 0;break;
		case 'G': return 0;break;
		case 'g': return 0;break;
		case 'H': return 2;break;
		case 'h': return 2;break;
		case 'J': return 2;break;
		case 'j': return 2;break;
		case ' ': return 1;break; 
		default : return -1;break;
	}
}
char return_color(int c)
{
	if(c==0) return 'B';
	if(c==1) return 'T';
	if(c==2) return 'R';
}

int return_key(noteptr notes,int type)
{
	extern int lastKeyState[9],curKeyState[9],notes_front,notes_count;
	extern MUSIC music;
	extern double elapse_time,preparing_time;
	extern MUSIC hit_note[3][5];
	extern int hitnote_j[3],drum_i;
	extern char path_drum[200];
	char buf[80];
	getcwd(buf,sizeof(buf));  
	int key_i,i;
	for(key_i=0;key_i<9;key_i++)
		{
			lastKeyState[key_i]=curKeyState[key_i];
		}
		
	key_msg keyMsg = { 0 };
	if (kbmsg()) {
		keyMsg = getkey();
			if(keyMsg.msg==key_msg_down)
			{
				if(sort_key(keyMsg.key)!=-1)
				{
					curKeyState[sort_key(keyMsg.key)]=KEY_DOWN;
					if (lastKeyState[sort_key(keyMsg.key)] == KEY_UP && curKeyState[sort_key(keyMsg.key)]  == KEY_DOWN)
					{
						if (sort_key(keyMsg.key)>=0&&sort_key(keyMsg.key)<=2)
						{
							hit_note[sort_key(keyMsg.key)][hitnote_j[sort_key(keyMsg.key)]].SetVolume(notes_volume);
							hit_note[sort_key(keyMsg.key)][hitnote_j[sort_key(keyMsg.key)]].Play(0);
							if(hitnote_j[sort_key(keyMsg.key)]<4)hitnote_j[sort_key(keyMsg.key)]++;
							else hitnote_j[sort_key(keyMsg.key)]=0;
							drum_i=1;
							if(type==1)
							{
								notes[notes_count].colorchar=return_color(sort_key(keyMsg.key));
								notes[notes_count].timing=elapse_time-preparing_time;
								printf("%d %c %lf\n",notes_count,notes[notes_count].colorchar,notes[notes_count].timing);
								notes_count++;
								sprintf(path_drum,"%s\\assets\\drum\\%d.png",buf,sort_key(keyMsg.key));
							}
							if(type==0)
							{
							sprintf(path_drum,"%s\\assets\\drum\\%d.png",buf,sort_key(keyMsg.key));
							return sort_key(keyMsg.key);
							}
						}
					}
				}
				if(keyMsg.key==key_esc) 
				{
					if(type==0)
					{
					free(notes);
					music.Stop();
					music.Close();	
					} 
					return 4;
				}
				if(keyMsg.key==key_enter&&type==1) 
				{
					music.Stop();
					music.Close();
					return 5;
				}
			}
			if(keyMsg.msg==key_msg_up)
			{
				if(sort_key(keyMsg.key)!=-1)
				{
					curKeyState[sort_key(keyMsg.key)]=KEY_UP;
				}
			}
		}
	return -1;
}
int timing_judgeing(noteptr notes)
{
	extern double elapse_time;
	extern int notes_front,notes_count;
	int tmpkey;
	double dt;
	extern int pure_count,far_count,lost_count,passed_count,combo,max_combo;
	extern double clear_score;
	if (notes_front>=notes_count) return -1;
	if((tmpkey=return_key(notes,0))!=-1&&(tmpkey!=4))
	{
		
		if(tmpkey==notes[notes_front].color)
		{
			
			dt=fabs(elapse_time-notes[notes_front].timing);
			if(dt<=0.05) {
				notes_front++;
				pure_count++; 
				clear_score+=100;
				passed_count++;
				combo++;
				max_combo=(max_combo>combo)?max_combo:combo;
				return PU;
				
			}
			else if(dt<=0.1) 
			{
				notes_front++;
				far_count++;
				clear_score+=50;
				passed_count++;
				combo++;
				max_combo=(max_combo>combo)?max_combo:combo;
				return FA;
			}
			else if(dt<=0.12)
			{
				notes_front++;
				lost_count++;
				clear_score+=0;
				passed_count++;
				combo=0;
				return LO;
				
			 } 
			else return -1;
		} 
	}
	if (tmpkey==4) return -2;
	return -1;
}
