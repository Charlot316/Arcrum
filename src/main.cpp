#ifndef _HeadFileName_H
#define _HeadFileName_H
#include <stdio.h>
#include <graphics.h>//��Ҫ����EGEͼ�ο�,���ӣ�https://blog.csdn.net/qq_39151563/article/details/100161986 
#include <ege/sys_edit.h>//Ҳ��Ҫ����EGEͼ�ο�
#include <unistd.h> 
#include <string.h>
#include <stdlib.h>
#include <windows.h>
#include <math.h>
#include "public_variables.h"//������ֱ������ṹ���ͷ�ļ� 
#include "note_control.h"//�����������õ�ͷ�ļ� 
#include "keyboard_control.h"//���̿��� 
#include "setup_interface.h"//���ø��ֽ����ͷ�ļ� 
#endif    //_HeadFileName_H
int sort_color(char c);
noteptr read_note(int);
void display(noteptr notes); 
int sort_key(char c);
int return_key(noteptr notes,int type);
int timing_judgeing(noteptr notes);
void get_name(char songname[][200],songptr songs,int count,int front);
song get_song(char songname[],songptr songs,int count);
void main_interface();
int main()
{
	extern int screen_broad,screen_length,notes_front,notes_rear,notes_flow,notes_speed,pure_count,far_count,lost_count,passed_count;
	FILE *setting;
	char path_setting[200]; 
	char buf[80];
	extern double adjust_time;
	getcwd(buf,sizeof(buf));
    sprintf(path_setting,"%s\\data\\setting.txt",buf);
    setting=fopen(path_setting,"r");
    fscanf(setting,"%lf %lf %d %lf",&notes_volume,&music_volume,&notes_speed,&adjust_time);
    fclose(setting);
	notes_rear=0;
	screen_broad=1000; 
	screen_length=1280;
	extern int notes_y;
	notes_y=screen_broad*1/3;
	song_front=0;
	pure_count=far_count=lost_count=passed_count=0;
	initgraph(screen_length,screen_broad,0);
	setcaption("���ɹĵ�"); 
	main_interface();
	
}

