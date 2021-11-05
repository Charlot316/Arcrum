typedef struct notenode{
	double timing;
	char colorchar;
	int color;
	int x;
	int y;
	double remain;
	struct notenode *next;
}note,*noteptr;

typedef struct songnode{
	char name[200];
	int id;
	int x;
	int y;
}song,*songptr;

enum KeyState
{
	KEY_UP,
	KEY_DOWN
};

enum Accuracy
{
	PU,FA,LO
};

MUSIC music;
int song_count;
int song_front;
int lastKeyState[9];
int curKeyState[9];
int screen_broad,screen_length;
int notes_y;
int notes_front,notes_rear,notes_count;
int notes_flow;
int notes_speed;
double clear_score;
int pure_count,far_count,lost_count,passed_count;
double elapse_time,start_time;
double preparing_time; 
double adjust_time;
MUSIC hit_note[3][5];
int hitnote_j[3]={0,0,0};
int combo,max_combo;
char path_drum[200];
int drum_i;
double music_volume,notes_volume;
