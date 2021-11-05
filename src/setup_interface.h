void play_running(int chosen,int type);
void select_interface();
void main_interface();
void setting_interface();
void import_interface();
void get_name(char songname[][200],songptr songs,int count,int front)
{
	int A,B=front;
	for(A=0;A<5;A++)
	{
		if(B>count) B=0;
		strcpy(songname[A],songs[B].name);
		B++;
	}
}
song get_song(char songname[],songptr songs,int count)
{
	int A=0;
	for(A=0;A<=count;A++)
	{
		if (strcmp(songname,songs[A].name)==0) return songs[A];
	}
}
void update_data(int a[])
{
	extern int notes_speed;
	extern double notes_volume,music_volume,adjust_time; 
	a[0]=notes_volume*100;
	a[1]=music_volume*100;
	a[2]=6-notes_speed;
	a[3]=adjust_time*100;
	return;
}
void setting_interface()
{
	cleardevice();
	extern int notes_speed,screen_broad,screen_length;
	extern double notes_volume,music_volume,adjust_time; 
	char path_background[200],path_setting[200]; 
	char buf[80];
	char setting_name[4][10]={"音效音量","音乐音量","谱面流速","偏差调整"};
	int name_x[4];
	setfont(80, 0, "微软雅黑");
	FILE *setting_in,*setting_out;
	PIMAGE background_image=newimage();
	getcwd(buf,sizeof(buf));   
    sprintf(path_background,"%s\\assets\\background\\main.jpg",buf);
    sprintf(path_setting,"%s\\data\\setting.txt",buf);
    getimage(background_image,path_background);
    int tempWidth = getwidth(background_image), tempHeight = getheight(background_image);
    int i,current_stage=0;
	int tmpdata[4];
	putimage(0, 0,screen_length,screen_broad, background_image, 0, 0, tempWidth, tempHeight);
	update_data(tmpdata);
    for(i=0;i<4;i++)
    {
    	name_x[i]=screen_length*0.2*i+screen_length*0.2-textwidth(setting_name[i])*0.5;
    	setcolor(BLACK);
    	setbkmode(TRANSPARENT);
    	xyprintf(name_x[i]+2,screen_broad*0.3+2,setting_name[i]);
    	xyprintf(name_x[i]+2,screen_broad*0.6+2,"%d",tmpdata[i]);
    	if(i!=current_stage) xyprintf(name_x[i]+2,screen_broad*0.6+2,"%d",tmpdata[i]);
    	setcolor(WHITE);
    	xyprintf(name_x[i],screen_broad*0.3,setting_name[i]);
    	if(i!=current_stage) setbkmode(TRANSPARENT);
    	else setbkmode(OPAQUE);
   		xyprintf(name_x[i],screen_broad*0.6,"%d",tmpdata[i]);
	}
    	for (; is_run(); delay_fps(60)) 
	{
		key_msg keyMsg = { 0 };
		keyMsg = getkey();
		if(keyMsg.key==key_up&& keyMsg.msg == key_msg_up)
		{
			cleardevice();
			putimage(0, 0,screen_length,screen_broad, background_image, 0, 0, tempWidth, tempHeight);
			setting_in=fopen(path_setting,"r");
			setting_out=fopen(path_setting,"w");
			fscanf(setting_in,"%lf %lf %d %lf",&notes_volume,&music_volume,&notes_speed,&adjust_time);
			if(current_stage==0) notes_volume=((notes_volume+0.1)>1)?notes_volume:notes_volume+0.1;
			if(current_stage==1) music_volume=((music_volume+0.1)>1)?music_volume:music_volume+0.1;
			if(current_stage==2) notes_speed=((notes_speed-1)<1)?notes_speed:notes_speed-1;
			if(current_stage==3) adjust_time=((adjust_time+0.01)>1)?adjust_time:adjust_time+0.01;
			update_data(tmpdata);
			fprintf(setting_out,"%.1f %.1f %d %.2f",notes_volume,music_volume,notes_speed,adjust_time);
			fclose(setting_in);
			fclose(setting_out);
			 for(i=0;i<4;i++)
		    {
		    	name_x[i]=screen_length*0.2*i+screen_length*0.2-textwidth(setting_name[i])*0.5;
		    	setcolor(BLACK);
		    	setbkmode(TRANSPARENT);
		    	xyprintf(name_x[i]+2,screen_broad*0.3+2,setting_name[i]);
		    	xyprintf(name_x[i]+2,screen_broad*0.6+2,"%d",tmpdata[i]);
		    	if(i!=current_stage) xyprintf(name_x[i]+2,screen_broad*0.6+2,"%d",tmpdata[i]);
		    	setcolor(WHITE);
		    	xyprintf(name_x[i],screen_broad*0.3,setting_name[i]);
		    	if(i!=current_stage) setbkmode(TRANSPARENT);
		    	else setbkmode(OPAQUE);
		   		xyprintf(name_x[i],screen_broad*0.6,"%d",tmpdata[i]);
			}
		}
		if(keyMsg.key==key_down&& keyMsg.msg == key_msg_up)
		{
			cleardevice();
			putimage(0, 0,screen_length,screen_broad, background_image, 0, 0, tempWidth, tempHeight);
			setting_in=fopen(path_setting,"r");
			setting_out=fopen(path_setting,"w");
			fscanf(setting_in,"%lf %lf %d %lf",&notes_volume,&music_volume,&notes_speed,&adjust_time);
			if(current_stage==0) notes_volume=((notes_volume-0.1)<0)?notes_volume:notes_volume-0.1;
			if(current_stage==1) music_volume=((music_volume-0.1)<0)?music_volume:music_volume-0.1;
			if(current_stage==2) notes_speed=((notes_speed+1)>5)?notes_speed:notes_speed+1;
			if(current_stage==3) adjust_time=((adjust_time-0.01)<-1)?adjust_time:adjust_time-0.01;
			update_data(tmpdata);
			fprintf(setting_out,"%.1f %.1f %d %.2f",notes_volume,music_volume,notes_speed,adjust_time);
			fclose(setting_in);
			fclose(setting_out);
			 for(i=0;i<4;i++)
		    {
		    	name_x[i]=screen_length*0.2*i+screen_length*0.2-textwidth(setting_name[i])*0.5;
		    	setcolor(BLACK);
		    	setbkmode(TRANSPARENT);
		    	xyprintf(name_x[i]+2,screen_broad*0.3+2,setting_name[i]);
		    	xyprintf(name_x[i]+2,screen_broad*0.6+2,"%d",tmpdata[i]);
		    	if(i!=current_stage) xyprintf(name_x[i]+2,screen_broad*0.6+2,"%d",tmpdata[i]);
		    	setcolor(WHITE);
		    	xyprintf(name_x[i],screen_broad*0.3,setting_name[i]);
		    	if(i!=current_stage) setbkmode(TRANSPARENT);
		    	else setbkmode(OPAQUE);
		   		xyprintf(name_x[i],screen_broad*0.6,"%d",tmpdata[i]);
			}
		}
		if(keyMsg.key==key_left&& keyMsg.msg == key_msg_up)
		{
			cleardevice();
			putimage(0, 0,screen_length,screen_broad, background_image, 0, 0, tempWidth, tempHeight);
			current_stage=(current_stage+3)%4;
			putimage(0, 0,screen_length,screen_broad, background_image, 0, 0, tempWidth, tempHeight);
		    for(i=0;i<4;i++)
		    {
		    	name_x[i]=screen_length*0.2*i+screen_length*0.2-textwidth(setting_name[i])*0.5;
		    	setcolor(BLACK);
		    	setbkmode(TRANSPARENT);
		    	xyprintf(name_x[i]+2,screen_broad*0.3+2,setting_name[i]);
		    	xyprintf(name_x[i]+2,screen_broad*0.6+2,"%d",tmpdata[i]);
		    	if(i!=current_stage) xyprintf(name_x[i]+2,screen_broad*0.6+2,"%d",tmpdata[i]);
		    	setcolor(WHITE);
		    	xyprintf(name_x[i],screen_broad*0.3,setting_name[i]);
		    	if(i!=current_stage) setbkmode(TRANSPARENT);
		    	else setbkmode(OPAQUE);
		   		xyprintf(name_x[i],screen_broad*0.6,"%d",tmpdata[i]);
			}
		}
		if(keyMsg.key==key_right&& keyMsg.msg == key_msg_up)
		{
			cleardevice();
			putimage(0, 0,screen_length,screen_broad, background_image, 0, 0, tempWidth, tempHeight);
			current_stage=(current_stage+1)%4;
			putimage(0, 0,screen_length,screen_broad, background_image, 0, 0, tempWidth, tempHeight);
		    for(i=0;i<4;i++)
		    {
		    	name_x[i]=screen_length*0.2*i+screen_length*0.2-textwidth(setting_name[i])*0.5;
		    	setcolor(BLACK);
		    	setbkmode(TRANSPARENT);
		    	xyprintf(name_x[i]+2,screen_broad*0.3+2,setting_name[i]);
		    	xyprintf(name_x[i]+2,screen_broad*0.6+2,"%d",tmpdata[i]);
		    	if(i!=current_stage) xyprintf(name_x[i]+2,screen_broad*0.6+2,"%d",tmpdata[i]);
		    	setcolor(WHITE);
		    	xyprintf(name_x[i],screen_broad*0.3,setting_name[i]);
		    	if(i!=current_stage) setbkmode(TRANSPARENT);
		    	else setbkmode(OPAQUE);
		   		xyprintf(name_x[i],screen_broad*0.6,"%d",tmpdata[i]);
			}
		}
		if(keyMsg.key==key_esc&& keyMsg.msg == key_msg_down)
		{
			delimage(background_image);
			return;
		}
		if(keyMsg.key==key_enter&& keyMsg.msg == key_msg_down)
		{
			delimage(background_image);
			return;
		}
	}
}
void import_interface()
{
	char buf[80],path_music[200],path_songlist[200],path_score[200],path_oldname[200],path_oldpic[200],path_pic[200];
	extern int screen_broad,screen_length;
	int songcount,tmpname;
	int i,j,k;
	getcwd(buf,sizeof(buf)); 
	sprintf(path_songlist,"%s\\data\\songlist.txt",buf);
	
	FILE *songlist_in,*songlist_out,*score_out;
	songptr songs;
	songlist_in=fopen(path_songlist,"r");
	fscanf(songlist_in,"%d",&songcount);
	fgetc(songlist_in);
	songs=(songptr)malloc((songcount+1)*sizeof(song));
	for(i=0;i<songcount;i++)
	{
		fgets(songs[i].name,200,songlist_in);
	}
	extern MUSIC music; 
	setbkcolor(WHITE);
	setcolor(BLACK);
	int fontHeight = 20;
	setfont(fontHeight, 0, "楷体");
	setbkmode(TRANSPARENT);
	sys_edit editBox;
	editBox.create(true);					
	editBox.move(0, screen_broad*0.5);					
	int editTextHeight = 50;
	editBox.size(screen_length, screen_broad*0.5);	
	editBox.setbgcolor(CYAN);					
	editBox.setcolor(BLACK);					
	editBox.setfont(editTextHeight, 0, "楷体");	
	int maxLen = 200;
	editBox.setmaxlen(maxLen);		
	editBox.visable(true);
	editBox.setfocus();
	const int buffSize = 200;
	char strBuff[100] = "";
	int buffLen = 0;
	bool flag_press = false;
	char music_name[200];
	songlist_out=fopen(path_songlist,"w");
	for (; is_run(); delay_fps(60)) {
		cleardevice();
		xyprintf(100, 0, "请输入音乐文件路径，必须是MP3格式。");
		xyprintf(100, 20, "限制最大输入长度：%d",buffSize);
		if (keystate(key_enter)) {
			if (!flag_press) {
				editBox.gettext(buffSize, strBuff);
				buffLen = strlen(strBuff);
				editBox.settext("");
			}
			flag_press = true;
		}
		else {
			flag_press = false;
		}

		if (strBuff[0] != '\0') {
			for(i=buffLen;i>0;i--)
			{
			if(strBuff[i]!='3') strBuff[i]='\0';
			else break;
		}
		
			music.OpenFile(strBuff);
			if(music.IsOpen())
			{
				for(i=buffLen;i>0;i--)
				{
					if(strBuff[i] == '/' || strBuff[i] == '\\') break;
				}
				for(k=buffLen;k>0;k--)
				{
					if(strBuff[k] == '.') break;
				}
				strcpy(path_oldname,strBuff);
				for(j=i+1;j<k;j++) music_name[j-i-1]=strBuff[j];
				strBuff[j]='\0';
				strcpy(songs[songcount].name,music_name);
				sprintf(path_score,"%s\\data\\score\\%d.txt",buf,songcount+1);
				sprintf(path_music,"%s\\assets\\music\\%d.mp3",buf,songcount+1);
				sprintf(path_pic,"%s\\assets\\background\\%d.jpg",buf,songcount+1);
				for(i=0;i<buffLen;i++) strBuff[i]='\0';
				break;
			}
			
			else 
			{
				fprintf(songlist_out,"%d\n",songcount);
				for(i=0;i<songcount;i++)fprintf(songlist_out,"%s",songs[i].name);
				fprintf(songlist_out,"\n");
				fclose(songlist_in);
				fclose(songlist_out);
				fprintf(songlist_out,"注意换行符！"); 
				xyprintf(100, 60, "无法打开文件，有效的打开方式是用手机等录屏，之后用格式工厂分离MP3音频");
				xyprintf(100,80,"按任意键退出"); 
				flushkey();
				getch();   
				return;
			} 
		}
	}
	
	for (; is_run(); delay_fps(60)) {
		cleardevice();
		xyprintf(100, 0, "音乐导入成功！");
		xyprintf(100, 20, "请输入背景图片的文件路径，必须是jpg格式");
		xyprintf(100, 40, "限制最大输入长度：%d",buffSize);
		if (keystate(key_enter)) {
			if (!flag_press) {
				editBox.gettext(buffSize, strBuff);
				buffLen = strlen(strBuff);
				editBox.settext("");
			}
			flag_press = true;
		}
		else {
			flag_press = false;
		}
		if (strBuff[0] != '\0') {
			for(i=buffLen;i>0;i--)
			{
			if(strBuff[i]!='g') strBuff[i]='\0';
			else break;
		}
		strcpy(path_oldpic,strBuff);
		
		if((i=rename(path_oldpic,path_pic))==0&&(j=rename(path_oldname,path_music))==0)
		{
			fprintf(songlist_out,"%d\n",songcount+1);
			for(i=0;i<=songcount;i++)fprintf(songlist_out,"%s",songs[i].name);
			fprintf(songlist_out,"\n");
			fprintf(songlist_out,"注意换行符！"); 
			score_out=fopen(path_score,"w");
			fprintf(score_out,"0 N");
			fclose(score_out);
			fclose(songlist_in);
			fclose(songlist_out);
			music.Close();
			xyprintf(100, 60, "背景导入成功！按任意键开始制作铺面");
			flushkey();
			getch(); 
			break;
		}
		else
		{
			printf("%d %d",i,j);
			fprintf(songlist_out,"%d\n",songcount);
			for(i=0;i<songcount;i++)fprintf(songlist_out,"%s",songs[i].name);
			fprintf(songlist_out,"\n");
			fclose(songlist_in);
			fclose(songlist_out);
			fprintf(songlist_out,"注意换行符！"); 
			xyprintf(100, 60, "导入失败，按任意键退出");
			flushkey();
			getch();   
			return;
		}
		}
	}
	editBox.destory();
	play_running(songcount+1,1);
	free(songs); 
	return;
}
void main_interface()
{
	char interface_name[3][10]={"游玩","设置","导入"};
	int current_stage=0,i;
	char path_background[200]; 
	char buf[80];
	PIMAGE background_image=newimage();
	getcwd(buf,sizeof(buf));   
    sprintf(path_background,"%s\\assets\\background\\main.jpg",buf);
    getimage(background_image,path_background);
    int tempWidth = getwidth(background_image), tempHeight = getheight(background_image);
    putimage(0, 0,screen_length,screen_broad, background_image, 0, 0, tempWidth, tempHeight);
	setfont(100, 0, "微软雅黑");
	setcaption("韵律鼓点"); 
	for(i=0;i<3;i++)
	{
		if(i==current_stage)
		{
			setcolor(WHITE);
			setfontbkcolor(CYAN); 
			setbkmode(OPAQUE);
			xyprintf(screen_length*0.5-(textwidth(interface_name[i])*0.5),screen_broad*(i*0.2)+screen_broad*0.2,interface_name[i]);
		}
		else
		{
			setbkmode(TRANSPARENT);
			setcolor(BLACK);
			xyprintf(screen_length*0.5-(textwidth(interface_name[i])*0.5)+2,screen_broad*(i*0.2)+screen_broad*0.2+2,interface_name[i]);
			setcolor(WHITE);
			xyprintf(screen_length*0.5-(textwidth(interface_name[i])*0.5),screen_broad*(i*0.2)+screen_broad*0.2,interface_name[i]);
		}
	}
	
	for (; is_run(); delay_fps(60)) 
	{
		key_msg keyMsg = { 0 };
		keyMsg = getkey();
		if(keyMsg.key==key_up&& keyMsg.msg == key_msg_up)
		{
			cleardevice();
			putimage(0, 0,screen_length,screen_broad, background_image, 0, 0, tempWidth, tempHeight);
			current_stage=(current_stage+2)%3;
			for(i=0;i<3;i++)
			{
				if(i==current_stage)
				{
					setcolor(WHITE);
					setfontbkcolor(CYAN); 
					setbkmode(OPAQUE);
					xyprintf(screen_length*0.5-(textwidth(interface_name[i])*0.5),screen_broad*(i*0.2)+screen_broad*0.2,interface_name[i]);
				}
				else
				{
					setbkmode(TRANSPARENT);
					setcolor(BLACK);
					xyprintf(screen_length*0.5-(textwidth(interface_name[i])*0.5)+2,screen_broad*(i*0.2)+2+screen_broad*0.2,interface_name[i]);
					setcolor(WHITE);
					xyprintf(screen_length*0.5-(textwidth(interface_name[i])*0.5),screen_broad*(i*0.2)+screen_broad*0.2,interface_name[i]);
				}
			}
		}
		if(keyMsg.key==key_down&& keyMsg.msg == key_msg_up)
		{
			cleardevice();
			putimage(0, 0,screen_length,screen_broad, background_image, 0, 0, tempWidth, tempHeight);
			current_stage=(current_stage+1)%3;
			for(i=0;i<3;i++)
			{
				if(i==current_stage)
				{
					setcolor(WHITE);
					setfontbkcolor(CYAN); 
					setbkmode(OPAQUE);
					xyprintf(screen_length*0.5-(textwidth(interface_name[i])*0.5),screen_broad*(i*0.2)+screen_broad*0.2,interface_name[i]);
				}
				else
				{
					setbkmode(TRANSPARENT);
					setcolor(BLACK);
					xyprintf(screen_length*0.5-(textwidth(interface_name[i])*0.5)+2,screen_broad*(i*0.2)+2+screen_broad*0.2,interface_name[i]);
					setcolor(WHITE);
					xyprintf(screen_length*0.5-(textwidth(interface_name[i])*0.5),screen_broad*(i*0.2)+screen_broad*0.2,interface_name[i]);
				}
			}
		}
		if(keyMsg.key==key_enter&& keyMsg.msg == key_msg_down)
		{
			cleardevice();
			if(current_stage==0) select_interface();
			else if (current_stage==1) setting_interface();
			else import_interface();
			setfont(100, 0, "微软雅黑");
			putimage(0, 0,screen_length,screen_broad, background_image, 0, 0, tempWidth, tempHeight);
			for(i=0;i<3;i++)
			{
				if(i==current_stage)
				{
					setcolor(WHITE);
					setfontbkcolor(CYAN); 
					setbkmode(OPAQUE);
					xyprintf(screen_length*0.5-(textwidth(interface_name[i])*0.5),screen_broad*(i*0.2)+screen_broad*0.2,interface_name[i]);
				}
				else
				{
					setbkmode(TRANSPARENT);
					setcolor(BLACK);
					xyprintf(screen_length*0.5-(textwidth(interface_name[i])*0.5)+2,screen_broad*(i*0.2)+2+screen_broad*0.2,interface_name[i]);
					setcolor(WHITE);
					xyprintf(screen_length*0.5-(textwidth(interface_name[i])*0.5),screen_broad*(i*0.2)+screen_broad*0.2,interface_name[i]);
				}
			}
		}
		if(keyMsg.key==key_esc&& keyMsg.msg == key_msg_down)
		{
			delimage(background_image);
			closegraph();
			return;
		}
	}
}
int priority(char c)
{
	if(c=='P') return 3;
	if(c=='F') return 2;
	if(c=='C') return 1;
	return 0;
}

void play_running(int chosen,int type)
{
	extern int notes_front,notes_rear,notes_count,notes_flow,screen_broad,screen_length,notes_speed;
	extern int song_count,pure_count,far_count,lost_count,passed_count,combo,max_combo;
	extern double clear_score;
	extern double preparing_time;
	preparing_time=notes_speed+1;
	noteptr Notes;
	if(type==0)Notes=read_note(chosen);
	double now_time;
	int play_i,play_j,key_i,tmp_i,i,j;
	extern double elapse_time,start_time;
	extern int lastKeyState[9];
	extern int curKeyState[9];
	extern double music_volume;
	extern char path_drum[200];
	int tmpkey;
	char path_background[200],path_accuracy[200],path_music[200],path_notesout[200]; 
	char buf[80];
	int accuracy_y[5],accuracy_i;
	PIMAGE accuracy_image=newimage();
	PIMAGE background_image=newimage();
	extern MUSIC music;
	getcwd(buf,sizeof(buf));   
    sprintf(path_background,"%s\\assets\\background\\%d.jpg",buf,chosen);
    sprintf(path_music,"%s\\assets\\music\\%d.mp3",buf,chosen);
    music.OpenFile(path_music);
   
    PIMAGE drum_image=newimage();
    getimage(background_image,path_background,screen_length,screen_broad);
   	extern MUSIC hit_note[3][5];
    char path_hitnote[200];  
    int start=0;
    extern int drum_i;
    drum_i=0;
    for(i=0;i<3;i++)
    {
    	for(j=0;j<5;j++)	//每 个音符的击打音效都被存了5遍，是因为系统没法高速播放同一段音频，存5遍可以“错峰”播放 
    	{
    		sprintf(path_hitnote,"%s\\assets\\notes\\%d.%d.mp3",buf,i,j);
    		hit_note[i][j].OpenFile(path_hitnote);
    		hit_note[i][j].SetVolume(0);
    		hit_note[i][j].Play(0);	
		}	
	}

	for(key_i=0;key_i<9;key_i++)
	{
		lastKeyState[key_i]=KEY_UP;
		curKeyState[key_i]=KEY_UP;
	}
	
	for(tmp_i=0;tmp_i<5;tmp_i++)
	{
		accuracy_y[tmp_i]=notes_y+100-tmp_i*10;
	}
	accuracy_i=0;
	start_time=fclock();
	music.SetVolume(music_volume);
	int tempWidth = getwidth(background_image), tempHeight = getheight(background_image);
	if(type==0)
	{
		for(;!start||music.GetPlayStatus() != MUSIC_MODE_STOP;delay_fps(60))//和时间有关的都得写在这个for里面！！不要写别的地方 
		{
			cleardevice();
			setfont(100, 0, "微软雅黑");
			setfillcolor(CYAN);
			setcolor(WHITE);
			setbkmode(OPAQUE);
	    	putimage(0, 0,screen_length,screen_broad, background_image, 0, 0, tempWidth, tempHeight);
	    	if (chosen==0)xyprintf(20,20,"FG=蓝色，空格=紫色，HJ=红色"); 
	    	setfillcolor(EGERGB(220,220,220));
	    	bar(0,notes_y,screen_length,notes_y+100); 
			setcolor(EGERGB(0x0, 0x0, 0x0));	//设置绘画颜色
			circle(screen_length/10+50,notes_y+50, 50);
			setcolor(BLACK);
		    setbkmode(TRANSPARENT);
		    if(combo>0) xyprintf(screen_length*0.1+2,screen_broad*0.1+2,"%d combo",combo);
		    setcolor(WHITE);
		    if(combo>0) xyprintf(screen_length*0.1,screen_broad*0.1,"%d combo",combo);
		    setbkmode(OPAQUE);
		   	if(passed_count>0)xyprintf(screen_length*0.1,screen_broad*0.2,"%.2f",clear_score/(double)passed_count);
			if(drum_i==0)sprintf(path_drum,"%s\\assets\\drum\\3.png",buf);
			drum_i=(drum_i+1)%10; 
			now_time=fclock();
			elapse_time=now_time-start_time;
			if(elapse_time>preparing_time&&!start)
			{
				music.Play(0);
				start=1;
			}
			for(play_i=notes_front;play_i<notes_count;play_i++)
			{
				if(Notes[play_i].timing<elapse_time-0.13) 
				{
					sprintf(path_accuracy,"%s\\assets\\accuracy\\2.png",buf);
					getimage(accuracy_image,path_accuracy,0,0);
					accuracy_i=0;
					lost_count++;
					clear_score+=0;
					passed_count++;
					combo=0;
					notes_front++; 
				}
			}
			for(play_j=notes_rear;play_j<notes_count;play_j++)
			{
				if(Notes[play_j].timing-Notes[play_j].remain<elapse_time)
				{
					notes_rear++;
				}
			}
			tmpkey=timing_judgeing(Notes);
			if(tmpkey==-2) return;
			display(Notes);
			if(accuracy_i<4)  accuracy_i++;
			if(tmpkey!=-1)
			{
				sprintf(path_accuracy,"%s\\assets\\accuracy\\%d.png",buf,tmpkey);
				getimage(accuracy_image,path_accuracy,0,0);
				accuracy_i=0;
			}
			getimage(drum_image,path_drum);
		if(accuracy_image!=NULL)	putimage_withalpha(NULL,accuracy_image,screen_length*0.1,accuracy_y[accuracy_i]);
			putimage_withalpha(NULL,drum_image,screen_length*0.5-300,screen_broad-366);
		}
	}
	else
	{
		setcolor(WHITE);
		noteptr headnote=(noteptr)malloc(1000*sizeof(note));
		notes_count=0;
		sprintf(path_notesout,"%s\\data\\notes\\%d.txt",buf,chosen);
		for(;!start||music.GetPlayStatus() != MUSIC_MODE_STOP;delay_fps(60))//和时间有关的都得写在这个for里面！！不要写别的地方 
		{
			cleardevice();
	    	putimage(0, 0,screen_length,screen_broad, background_image, 0, 0, tempWidth, tempHeight);
	    	xyprintf(100, 20, "按esc重新开始播放，按enter键以完成铺面制作");
			
			if(drum_i==0)sprintf(path_drum,"%s\\assets\\drum\\3.png",buf);
			drum_i=(drum_i+1)%6; 
			now_time=fclock();
			elapse_time=now_time-start_time;
			if(elapse_time>preparing_time&&!start)
			{
				music.Play(0);
				start=1;	
			} 
			tmpkey=return_key(headnote,1);
			if(start) xyprintf(100, 40, "音乐正在播放");
			if(tmpkey==4)
			{
				xyprintf(100, 40, "音乐回溯");
				start=0;
				notes_count=0;
				start_time=fclock();
				now_time=fclock();
				elapse_time=now_time-start_time;
				music.Stop();
			 } 
			if(tmpkey==5)
			{
				break;
			}
			getimage(drum_image,path_drum);
			putimage_withalpha(NULL,drum_image,screen_length*0.5-300,screen_broad-366);
		}
		FILE *notes_out;
		notes_out=fopen(path_notesout,"w");
		fprintf(notes_out,"%d\n",notes_count);
		int put_i;
		for(put_i=0;put_i<notes_count;put_i++)
		{
			fprintf(notes_out,"%lf %c\n",headnote[put_i].timing,headnote[put_i].colorchar);
		}
		fclose(notes_out);
		free(headnote);
		return;
	}
	
	delimage(accuracy_image);
	for(i=0;i<3;i++)
    {
    	for(j=0;j<5;j++)
    	{
    		hit_note[i][j].Close();
		} 
	}
	music.Close();
	free(Notes);
	cleardevice();
	
	char path_score[200];
	int tmp_score;
	char tmp_status,status;
	FILE *score,*score_out;
	getcwd(buf,sizeof(buf));   
    sprintf(path_background,"%s\\assets\\background\\%d.jpg",buf,chosen);
    sprintf(path_score,"%s\\data\\score\\%d.txt",buf,chosen);
    score=fopen(path_score,"r");
    fscanf(score,"%d %c",&tmp_score,&tmp_status);
    fclose(score);
    if(pure_count==passed_count) status='P';
    else if(max_combo==passed_count) status='F';
    else status='C';
    tmp_status=(priority(status)>priority(tmp_status))?status:tmp_status;
    tmp_score=((int)(clear_score/(double)passed_count)>tmp_score)?((int)clear_score/(double)passed_count):tmp_score;
    score_out=fopen(path_score,"w");
    fprintf(score,"%d %c",tmp_score,tmp_status);
    fclose(score_out);
    getimage(background_image,path_background,screen_length,screen_broad);
   	setbkmode(TRANSPARENT);
	key_msg keyMsg = { 0 };
    cleardevice();
    putimage(0, 0,screen_length,screen_broad, background_image, 0, 0, tempWidth, tempHeight);
    setcolor(BLACK);
    setfont(screen_broad*0.1, 0, "微软雅黑");
    xyprintf(screen_length*0.3+1, screen_broad*0.2+1, "score: %.0f",clear_score/(double)passed_count);
	xyprintf(screen_length*0.3+1, screen_broad*0.3+1, "combo: %d",max_combo);
	xyprintf(screen_length*0.3+1, screen_broad*0.4+1, "pure: %d", pure_count);
	xyprintf(screen_length*0.3+1, screen_broad*0.5+1, "far: %d", far_count);
	xyprintf(screen_length*0.3+1, screen_broad*0.6+1, "lost: %d", lost_count);
	xyprintf(screen_length*0.3+1, screen_broad*0.7+1, "按任意键继续");
	setcolor(WHITE);
    xyprintf(screen_length*0.3, screen_broad*0.2, "score: %.0f",clear_score/(double)passed_count);
	xyprintf(screen_length*0.3, screen_broad*0.3, "combo: %d", max_combo);
	xyprintf(screen_length*0.3, screen_broad*0.4, "pure: %d", pure_count);
	xyprintf(screen_length*0.3, screen_broad*0.5, "far: %d", far_count);
	xyprintf(screen_length*0.3, screen_broad*0.6, "lost: %d", lost_count);
	xyprintf(screen_length*0.3+1, screen_broad*0.7+1, "按任意键继续");//写两遍一边是白的一遍是黑底用于描边 
	
	for(;;delay_fps(60))
	{
		if (kbmsg()) {
		keyMsg = getkey();
			if(keyMsg.msg==key_msg_down)
			{
				delimage(background_image);
				delimage(drum_image);
				return;
			}
		}
	}
} 
void select_interface()
{
	int max_textwidth=0;
	showmouse(false);
	setbkcolor(WHITE);
	FILE *songlist,*songscore;
	extern int song_count,pure_count,far_count,lost_count,passed_count,combo,max_combo,notes_front,notes_rear,notes_count;
	extern double clear_score;
	extern int song_front;
	extern double preparing_time;
	preparing_time=notes_speed+1;
	int song_i,i;
	int tempWidth,tempHeight,tmppriority;
	char path_songlist[200],path_background[200],path_banner[200],path_square[200],path_song[200],path_score[200],path_status[200],tmpscore[200];
	char tmp_buf[80];
	int start_t,tmp_bannerx,tmp_bannery,banner_x[10],banner_y[5][2][5],banner_i;
	PIMAGE square[5];
	char songname[5][200];
	pure_count=far_count=lost_count=passed_count=combo=max_combo=0;
	clear_score=0;
	int tmp_score;
	char tmp_status;
	song selected_song;
	getcwd(tmp_buf,sizeof(tmp_buf));   
	
	sprintf(path_square,"%s\\assets\\main\\song_select.png",tmp_buf);
	sprintf(path_banner,"%s\\assets\\main\\song_selected.png",tmp_buf);
	
	for(banner_i=0;banner_i<5;banner_i++)
	{
		 square[banner_i]=newimage();
		if(banner_i!=2) getimage(square[banner_i],path_square,0,0);
		else getimage(square[banner_i],path_banner,0,0);
	}
	
	PIMAGE background,bar_up,bar_down,status_image;
	
    sprintf(path_songlist,"%s\\data\\songlist.txt",tmp_buf);
	songlist=fopen(path_songlist,"r");
	
	fscanf(songlist,"%d",&song_count);
	fgetc(songlist);
	
	songptr songs;
	songs=(songptr)malloc((song_count+1)*sizeof(song));
	strcpy(songs[0].name,"新手指导");
	songs[0].id=0;
	
	for(song_i=1;song_i<=song_count;song_i++)
	{
		fgets(songs[song_i].name,200,songlist);
		songs[song_i].name[strlen(songs[song_i].name)-1]='\0';
		songs[song_i].id=song_i;
	}
	
	background=newimage();
	bar_up=newimage();
	bar_down=newimage();
	get_name(songname,songs,song_count,song_front);
	selected_song=get_song(songname[2],songs,song_count);
	sprintf(path_background,"%s\\assets\\background\\%d.jpg",tmp_buf,selected_song.id);
	getimage(background,path_background);
	getimage(bar_up,path_background);
	getimage(bar_down,path_background);
	tempWidth = getwidth(background);tempHeight = getheight(background);

	
	setfont(100, 0, "微软雅黑");
	setcolor(WHITE);
	setfontbkcolor(CYAN); 

	for(banner_i=0;banner_i<5;banner_i++)
	{
		max_textwidth=(textwidth(songname[banner_i])>max_textwidth)?textwidth(songname[banner_i]):max_textwidth;
	}
	
	for(tmp_bannerx=0;tmp_bannerx<10;tmp_bannerx++)
	{
		banner_x[tmp_bannerx]=(screen_length*0.05+100+1.5*max_textwidth)*((double)(tmp_bannerx)/9)-(100+1.5*max_textwidth);
	}
	
	for(tmp_bannery=0;tmp_bannery<5;tmp_bannery++)
	{
		for(start_t=0;start_t<2;start_t++)
		{
			banner_y[tmp_bannery][start_t][0]=((screen_broad*0.6)*((double)tmp_bannery/4)+(screen_broad*0.2))-50;
			for(tmp_bannerx=0;tmp_bannerx<5;tmp_bannerx++) 
				{
				banner_y[tmp_bannery][start_t][tmp_bannerx]=(start_t==0)?(banner_y[tmp_bannery][start_t][0]+(screen_broad*0.1+50)*((double)tmp_bannerx/4)):(banner_y[tmp_bannery][start_t][0]-(screen_broad*0.1+50)*((double)tmp_bannerx/4));
				}
		
		}
	}
	for(start_t=0;start_t<10;start_t++,delay_fps(60))
	{
		cleardevice();
		putimage(0, 0,screen_length,screen_broad, background, 0, 0, tempWidth, tempHeight);
		for(banner_i=0;banner_i<5;banner_i++)
		{
			setcolor(WHITE);
			if(banner_i!=2) setbkmode(TRANSPARENT);
			else setbkmode(OPAQUE);
			if(banner_i!=2) 
			{
				setcolor(BLACK);
				xyprintf(banner_x[start_t]+203,banner_y[banner_i][0][0],songname[banner_i]);
				setcolor(WHITE);
				xyprintf(banner_x[start_t]+200,banner_y[banner_i][0][0],songname[banner_i]);
			}
			else xyprintf(banner_x[start_t]+200,banner_y[banner_i][0][0],songname[banner_i]);
			if(banner_i!=2)putimage_withalpha(NULL,square[banner_i],banner_x[start_t],banner_y[banner_i][0][0]);
			else putimage_withalpha(NULL,square[banner_i],banner_x[start_t]-25,banner_y[banner_i][0][0]-25);
		}
	}
	status_image=newimage();
	sprintf(path_score,"%s\\data\\score\\%d.txt",tmp_buf,selected_song.id);
	songscore=fopen(path_score,"r");
	fscanf(songscore,"%d %c",&tmp_score,&tmp_status);
	tmppriority=priority(tmp_status);
	sprintf(tmpscore,"分数：%d",tmp_score);
	sprintf(path_status,"%s\\assets\\status\\%d.png",tmp_buf,tmppriority);
	if(tmp_status!='N') 
	{
		getimage(status_image,path_status);
		putimage_withalpha(NULL,status_image,screen_length-107,screen_broad*0.3);
	}
	setcolor(BLACK);
	xyprintf(screen_length-textwidth(tmpscore)+2,screen_broad*0.2+2,tmpscore);
	setcolor(WHITE);
	xyprintf(screen_length-textwidth(tmpscore),screen_broad*0.2,tmpscore);
	fclose(songscore);
	
		for (; is_run(); delay_fps(60)) 
	{
		key_msg keyMsg = { 0 };
		keyMsg = getkey();
		if(keyMsg.key==key_up&& keyMsg.msg == key_msg_up)
		{
			for(start_t=0;start_t<5;start_t++,delay_fps(60))
			{
				cleardevice();
				putimage(0, 0,screen_length,screen_broad, background, 0, 0, tempWidth, tempHeight);
				for(banner_i=0;banner_i<5;banner_i++)
				{
					setcolor(WHITE);
					if(banner_i!=2) setbkmode(TRANSPARENT);
					else setbkmode(OPAQUE);
					if(banner_i!=2) 
					{
						setcolor(BLACK);
						xyprintf(banner_x[9]+203,banner_y[banner_i][0][start_t],songname[banner_i]);
						setcolor(WHITE);
						xyprintf(banner_x[9]+200,banner_y[banner_i][0][start_t],songname[banner_i]);
					}
					else xyprintf(banner_x[9]+200,banner_y[banner_i][0][start_t],songname[banner_i]);
					if(banner_i!=2)putimage_withalpha(NULL,square[banner_i],banner_x[9],banner_y[banner_i][0][0]);
					else putimage_withalpha(NULL,square[banner_i],banner_x[9]-25,banner_y[banner_i][0][0]-25);
					putimage(0, 0,screen_length,screen_broad*0.15, bar_up, 0, 0, tempWidth, tempHeight*0.15);
					putimage(0, screen_broad*0.85,screen_length,screen_broad*0.15, bar_down, 0, tempHeight*0.85, tempWidth, tempHeight*0.15);
				}
			}
			song_front--;
			if(song_front<0) song_front=song_count;
			get_name(songname,songs,song_count,song_front);
			selected_song=get_song(songname[2],songs,song_count);
			sprintf(path_background,"%s\\assets\\background\\%d.jpg",tmp_buf,selected_song.id);
			getimage(background,path_background);
			getimage(bar_up,path_background);
			getimage(bar_down,path_background);
			tempWidth = getwidth(background);tempHeight = getheight(background);
			cleardevice();
			putimage(0, 0,screen_length,screen_broad, background, 0, 0, tempWidth, tempHeight);
			for(banner_i=0;banner_i<5;banner_i++)
				{
					setcolor(WHITE);
					if(banner_i!=2) setbkmode(TRANSPARENT);
					else setbkmode(OPAQUE);
					if(banner_i!=2) 
					{
						setcolor(BLACK);
						xyprintf(banner_x[9]+203,banner_y[banner_i][0][0],songname[banner_i]);
						setcolor(WHITE);
						xyprintf(banner_x[9]+200,banner_y[banner_i][0][0],songname[banner_i]);
					}
					else xyprintf(banner_x[9]+200,banner_y[banner_i][0][0],songname[banner_i]);
					if(banner_i!=2)putimage_withalpha(NULL,square[banner_i],banner_x[9],banner_y[banner_i][0][0]);
					else putimage_withalpha(NULL,square[banner_i],banner_x[9]-25,banner_y[banner_i][0][0]-25);
				}
			status_image=newimage();
			sprintf(path_score,"%s\\data\\score\\%d.txt",tmp_buf,selected_song.id);
			songscore=fopen(path_score,"r");
			fscanf(songscore,"%d %c",&tmp_score,&tmp_status);
			tmppriority=priority(tmp_status);
			sprintf(tmpscore,"分数：%d",tmp_score);
			sprintf(path_status,"%s\\assets\\status\\%d.png",tmp_buf,tmppriority);
			if(tmp_status!='N') 
			{
				getimage(status_image,path_status);
				putimage_withalpha(NULL,status_image,screen_length-107,screen_broad*0.3);
			}
			setcolor(BLACK);
			xyprintf(screen_length-textwidth(tmpscore)+2,screen_broad*0.2+2,tmpscore);
			setcolor(WHITE);
			xyprintf(screen_length-textwidth(tmpscore),screen_broad*0.2,tmpscore);
			fclose(songscore);
			}
		if(keyMsg.key==key_down&& keyMsg.msg == key_msg_up)
		{
			for(start_t=0;start_t<5;start_t++,delay_fps(60))
			{
				cleardevice();
				putimage(0, 0,screen_length,screen_broad, background, 0, 0, tempWidth, tempHeight);
				for(banner_i=0;banner_i<5;banner_i++)
				{
					setcolor(WHITE);
					if(banner_i!=2) setbkmode(TRANSPARENT);
					else setbkmode(OPAQUE);
					if(banner_i!=2) 
					{
						setcolor(BLACK);
						xyprintf(banner_x[9]+203,banner_y[banner_i][1][start_t],songname[banner_i]);
						setcolor(WHITE);
						xyprintf(banner_x[9]+200,banner_y[banner_i][1][start_t],songname[banner_i]);
					}
					else xyprintf(banner_x[9]+200,banner_y[banner_i][1][start_t],songname[banner_i]);
					if(banner_i!=2)putimage_withalpha(NULL,square[banner_i],banner_x[9],banner_y[banner_i][0][0]);
					else putimage_withalpha(NULL,square[banner_i],banner_x[9]-25,banner_y[banner_i][0][0]-25);
					putimage(0, 0,screen_length,screen_broad*0.15, bar_up, 0, 0, tempWidth, tempHeight*0.15);
					putimage(0, screen_broad*0.85,screen_length,screen_broad*0.15, bar_down, 0, tempHeight*0.85, tempWidth, tempHeight*0.15);
				}
			}
			song_front++;
			if(song_front>song_count) song_front=0;
			get_name(songname,songs,song_count,song_front);
			selected_song=get_song(songname[2],songs,song_count);
			sprintf(path_background,"%s\\assets\\background\\%d.jpg",tmp_buf,selected_song.id);
			getimage(background,path_background);
			getimage(bar_up,path_background);
			getimage(bar_down,path_background);
			tempWidth = getwidth(background);tempHeight = getheight(background);
			cleardevice();
			putimage(0, 0,screen_length,screen_broad, background, 0, 0, tempWidth, tempHeight);
			
			for(banner_i=0;banner_i<5;banner_i++)
			{
					setcolor(WHITE);
					if(banner_i!=2) setbkmode(TRANSPARENT);
					else setbkmode(OPAQUE);
					if(banner_i!=2) 
					{
						setcolor(BLACK);
						xyprintf(banner_x[9]+203,banner_y[banner_i][0][0],songname[banner_i]);
						setcolor(WHITE);
						xyprintf(banner_x[9]+200,banner_y[banner_i][0][0],songname[banner_i]);
					}
					else xyprintf(banner_x[9]+200,banner_y[banner_i][0][0],songname[banner_i]);
					if(banner_i!=2)putimage_withalpha(NULL,square[banner_i],banner_x[9],banner_y[banner_i][0][0]);
					else putimage_withalpha(NULL,square[banner_i],banner_x[9]-25,banner_y[banner_i][0][0]-25);
			}
			status_image=newimage();
			sprintf(path_score,"%s\\data\\score\\%d.txt",tmp_buf,selected_song.id);
			songscore=fopen(path_score,"r");
			fscanf(songscore,"%d %c",&tmp_score,&tmp_status);
			tmppriority=priority(tmp_status);
			sprintf(tmpscore,"分数：%d",tmp_score);
			sprintf(path_status,"%s\\assets\\status\\%d.png",tmp_buf,tmppriority);
			if(tmp_status!='N') 
			{
				getimage(status_image,path_status);
				putimage_withalpha(NULL,status_image,screen_length-107,screen_broad*0.3);
			}
			setcolor(BLACK);
			xyprintf(screen_length-textwidth(tmpscore)+2,screen_broad*0.2+2,tmpscore);
			setcolor(WHITE);
			xyprintf(screen_length-textwidth(tmpscore),screen_broad*0.2,tmpscore);
			fclose(songscore);
			}
		if(keyMsg.key==key_enter&& keyMsg.msg == key_msg_down)
		{
			for(start_t=9;start_t>=0;start_t--,delay_fps(60))
			{
				cleardevice();
				putimage(0, 0,screen_length,screen_broad, background, 0, 0, tempWidth, tempHeight);
				for(banner_i=0;banner_i<5;banner_i++)
				{
					setfont(100, 0, "微软雅黑");
					setcolor(WHITE);
					setfontbkcolor(CYAN); 
					xyprintf(banner_x[start_t]+200,banner_y[banner_i][0][0],songname[banner_i]);
					if(banner_i!=2)putimage_withalpha(NULL,square[banner_i],banner_x[start_t],banner_y[banner_i][0][0]);
					else putimage_withalpha(NULL,square[banner_i],banner_x[start_t]-25,banner_y[banner_i][0][0]-25);
				}
			 }	
			play_running(selected_song.id,0);	
			pure_count=far_count=lost_count=passed_count=combo=max_combo=0;
			clear_score=0;
			notes_front=notes_rear=notes_count=0;
			for(start_t=0;start_t<10;start_t++,delay_fps(60))
			{
				cleardevice();
				putimage(0, 0,screen_length,screen_broad, background, 0, 0, tempWidth, tempHeight);
				for(banner_i=0;banner_i<5;banner_i++)
				{
					setcolor(WHITE);
					if(banner_i!=2) setbkmode(TRANSPARENT);
					else setbkmode(OPAQUE);
					if(banner_i!=2) 
					{
						setcolor(BLACK);
						xyprintf(banner_x[start_t]+203,banner_y[banner_i][0][0],songname[banner_i]);
						setcolor(WHITE);
						xyprintf(banner_x[start_t]+200,banner_y[banner_i][0][0],songname[banner_i]);
					}
					else xyprintf(banner_x[start_t]+200,banner_y[banner_i][0][0],songname[banner_i]);
					if(banner_i!=2)putimage_withalpha(NULL,square[banner_i],banner_x[start_t],banner_y[banner_i][0][0]);
					else putimage_withalpha(NULL,square[banner_i],banner_x[start_t]-25,banner_y[banner_i][0][0]-25);
				}
			}
			status_image=newimage();
			sprintf(path_score,"%s\\data\\score\\%d.txt",tmp_buf,selected_song.id);
			songscore=fopen(path_score,"r");
			fscanf(songscore,"%d %c",&tmp_score,&tmp_status);
			tmppriority=priority(tmp_status);
			sprintf(tmpscore,"分数：%d",tmp_score);
			sprintf(path_status,"%s\\assets\\status\\%d.png",tmp_buf,tmppriority);
			if(tmp_status!='N') 
			{
				getimage(status_image,path_status);
				putimage_withalpha(NULL,status_image,screen_length-107,screen_broad*0.3);
			}
			setcolor(BLACK);
			xyprintf(screen_length-textwidth(tmpscore)+2,screen_broad*0.2+2,tmpscore);
			setcolor(WHITE);
			xyprintf(screen_length-textwidth(tmpscore),screen_broad*0.2,tmpscore);
			fclose(songscore);	
		}
		if(keyMsg.key==key_esc&& keyMsg.msg == key_msg_down)
		{
				for(start_t=9;start_t>=0;start_t--,delay_fps(60))
			{
				cleardevice();
				putimage(0, 0,screen_length,screen_broad, background, 0, 0, tempWidth, tempHeight);
				for(banner_i=0;banner_i<5;banner_i++)
				{
					setfont(100, 0, "微软雅黑");
					setcolor(WHITE);
					setfontbkcolor(CYAN); 
					xyprintf(banner_x[start_t]+200,banner_y[banner_i][0][0],songname[banner_i]);
					if(banner_i!=2)putimage_withalpha(NULL,square[banner_i],banner_x[start_t],banner_y[banner_i][0][0]);
					else putimage_withalpha(NULL,square[banner_i],banner_x[start_t]-25,banner_y[banner_i][0][0]-25);
				}
			 }	
			cleardevice();
			fclose(songlist);
			free(songs);
			for(i=0;i<5;i++) delimage(square[i]);
			delimage(background);
			delimage(bar_up);
			delimage(bar_down);
			delimage(status_image);
			return;
		}
	}
}

