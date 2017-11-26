#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include <ctype.h>

#include "PALESDL.H"
#include "PALEDISK.H"
#include "PALESDL_IO.H"
#include "PALETAPS.H"
#include "PALERAWTAPE.H"
#include "DOSFONTS.h"
#include "PALESDL_VID.H"
#include "PALEDOS_TEMP.H"

#ifdef USE_DOS
#include <conio.h>
#include <bios.h>
#include "PALEDOS_VID.H"
#include "PALEDOS_GUI.H"
#include "PALE_KEYS.H"
#include "keydrv.h"
#include "DOSDIR.H"
#include <graph.h>

char key[256];

#endif

#include "PALE48K.H"
#include "PALE96K.H"
#include "PALE128K.H"


int pressed;

extern int disas_bank;


void init_keys()
{
#ifdef USE_DOS    
    hook_keys(); 
#endif
   SDL_EnableKeyRepeat(0,0);     
}

void close_keys()
{
#ifdef USE_DOS    
    release_keys();
#endif
// SDL_EnableKeyRepeat(1,0);  //?  
}



void waitkeyup(Uint16 keytest)
{
        Uint8 *key;

	SDL_PumpEvents();
	key = SDL_GetKeyState(NULL);
	while(key[keytest])
	{
		SDL_PumpEvents();
		key = SDL_GetKeyState(NULL);
	}
}

Uint16 my_getkey()
{
        Uint8 *key;
	Uint16 kv;

	SDL_PumpEvents();
	key = SDL_GetKeyState(NULL);

	kv = 0;
	while(!key[kv] and kv < 256)
	{
		kv++;
	}
	if (kv == 256)
		return(0);
	waitkeyup(kv);
	return kv;
}


void update_keyrate()
{
        switch(hw_type)
        {
                case LYNX_HARDWARE_48:
                        update_keyrate48K();
                        break;
                case LYNX_HARDWARE_96:
                        update_keyrate96K();
                        break;
                case LYNX_HARDWARE_128:
                        update_keyrate128K();
                        break;
        }
}


void CheckKeys(void)
{
    Uint8 *key;
    int f;
    Uint8 mykey = 0;
     /* Only need a near pointer in the flat model */
    char *ptr;
    char name[200];
    static char lbl[2000];
    static char cmdresult[4000];
    static int key_toggle = 0;
        /* Clear all keypresses */
        z80ports_in[0x0080] = 0xFF;
        z80ports_in[0x0180] = 0xFF;
        z80ports_in[0x0280] = 0xFF;
        z80ports_in[0x0380] = 0xFF;
        z80ports_in[0x0480] = 0xFF;
        z80ports_in[0x0580] = 0xFF;
        z80ports_in[0x0680] = 0xFF;
        z80ports_in[0x0780] = 0xFF;
        z80ports_in[0x0880] = 0xFF;
        z80ports_in[0x0980] = 0xFF;

//if (key[SDLK_ESCAPE])finish_emu =1;
/*
for(f=0;f<256;f++)
{
    if(key[f])
        printf("%d ",f);
}
*/

	SDL_PumpEvents();
	key = SDL_GetKeyState(NULL);


        if (key[SDLK_F1])
        {
/* 		if(show_status)
	        {
	            waitkeyup(SDLK_F1);
	            generic_debug_var = (generic_debug_var + 1) % ??;
	        }
		else
		{
*/
	             show_help();	
//		}
        }
        if (key[SDLK_F2])
        {
            waitkeyup(SDLK_F2);
            if(show_status ==0)show_status = 1;
            else show_status = 0;
        }
        if (key[SDLK_F3])
        {
            waitkeyup(SDLK_F3);
            if(run_emu ==0)run_emu = 1;
            else run_emu = 0;
        }
        
        if (key[SDLK_F4])
        {
            waitkeyup(SDLK_F4);
            emu_speed = (emu_speed + 1) % 6;
            set_speed(emu_speed);
        }
        if (key[SDLK_F5])
        {
            my_move(0,10);
            my_print("\f0");
            my_paint(0,32,10,22);
            my_print("\f5");
            my_print("Machine Type:\n\n\f70 = 48\n");
            my_print("1 = 96\n");
            my_print("2 = 128\n");
            my_print("3 = 96D\n");
            my_print("4 = 128D\n");
            my_print("5 = n/a\n");
            my_print("6 = n/a\n\n");
            my_input("type: ",name);
            set_machine(atoi(name));
            initialise_display();
	
        }

        if (key[SDLK_F6])
        {
            my_filechooser("tap",name);
            set_t_mode(0);
            if(load_lynx_tap(name,cmdresult,0))
            {
                sprintf(lbl,"\nTape Loaded:\n%s\n",cmdresult);
                
                my_print("\f1");
                my_paint(0,30,0,20);
                my_print("\f7\a1");
                my_move(0,0);
                my_print(lbl);
            }
            my_input("\nPRESS RETURN ",name);
        }


        if (key[SDLK_F7])
        {
            my_filechooser("ldf",name);
            set_d_mode(0);
	    load_ldisk(0,name);
        }


	if (key[SDLK_F8]) 
	{
		waitkeyup(SDLK_F8);
		if (isFullscreen == 0)
		{
			video_fullscreen(1);
		}
		else
		{
			video_fullscreen(0);
		}
	}

        if (key[SDLK_F9])
        {
		if(show_status)
	        {
	            waitkeyup(SDLK_F9);
	            disas_bank = (disas_bank + 1) % 4;
	        }
		else
		{
	            my_move(0,10);
	            my_print("\f0");
	            my_paint(0,32,10,22);
	            my_print("\f5");
	            my_input("Save Filename: ",name);
		    	
	            set_t_mode(LSF_TAPES);
	            sprintf(lbl,"lsf/");
	   	    strcat(lbl,name);
		    if(save_LSF(lbl))
	            {
	                sprintf(lbl,"\nLSF Saved the LSF\n");
	                
	                my_print("\f1");
	                my_paint(0,30,0,20);
	                my_print("\f7\a1");
	                my_move(0,0);
	                
	                my_print(lbl);
	            }
	            my_input("\nPRESS RETURN ",name);
		}
        }
 
        if (key[SDLK_F10])
        {
		waitkeyup(SDLK_F10);
		if(show_status == 1)
		{
			if(show_memmap == 0)
				show_memmap= 1;
			else
				show_memmap= 0;
		}
		else
		{

            my_filechooser("lsf",name);
            set_t_mode(LSF_TAPES);
            if(load_LSF(name))
            {
                sprintf(lbl,"\nLSF Loaded\n");
                
                my_print("\f1");
                my_paint(0,30,0,20);
                my_print("\f7\a1");
                my_move(0,0);
                
                my_print(lbl);
            }
            my_input("\nPRESS RETURN ",name);
		}

        }
 


        if (key[SDLK_F11])
        {
    		waitkeyup(SDLK_F11);
                initialise_Lynx();
                return;
        } 

       if (key[SDLK_F12]) finish_emu=1;

        

      
        // Real Keyboard Table                          
        if (key[SDLK_1]) z80ports_in[0x0080] &= 0xFE;
//      if (key[SDLK_CAPSLOCK]) z80ports_in[0x0080] &= 0xF7; //NOT WORKING , LEADS TO REPEATING KEY

        if (key[SDLK_UP]) z80ports_in[0x0080] &= 0xEF;
        if (key[SDLK_DOWN]) z80ports_in[0x0080] &= 0xDF;
        if (key[SDLK_ESCAPE]) z80ports_in[0x0080] &= 0xBF;
        
        if ((key[SDLK_RSHIFT]) || (key[SDLK_LSHIFT])) z80ports_in[0x0080] &= 0x7F;

        if (key[SDLK_3]) z80ports_in[0x0180] &= 0xFE; // 01
        if (key[SDLK_4]) z80ports_in[0x0180] &= 0xFD;
// 02
        if (key[SDLK_e]) z80ports_in[0x0180] &= 0xFB;
// 04
        if (key[SDLK_x]) z80ports_in[0x0180] &= 0xF7;
// 08
        if (key[SDLK_d]) z80ports_in[0x0180] &= 0xEF;
// 10
    if (key[SDLK_c]) z80ports_in[0x0180] &= 0xDF; // 20
        if (key[SDLK_2]) z80ports_in[0x0280] &= 0xFE;
        if (key[SDLK_q]) z80ports_in[0x0280] &= 0xFD;
        if (key[SDLK_w]) z80ports_in[0x0280] &= 0xFB;
        if (key[SDLK_z]) z80ports_in[0x0280] &= 0xF7;
        if (key[SDLK_s]) z80ports_in[0x0280] &= 0xEF;
        if (key[SDLK_a]) z80ports_in[0x0280] &= 0xDF;
        if ((key[SDLK_RCTRL]) || (key[SDLK_LCTRL])) z80ports_in[0x0280] &= 0xBF;
        
        if (key[SDLK_5]) z80ports_in[0x0380] &= 0xFE;
        if (key[SDLK_r]) z80ports_in[0x0380] &= 0xFD;
        if (key[SDLK_t]) z80ports_in[0x0380] &= 0xFB;
        if (key[SDLK_v]) z80ports_in[0x0380] &= 0xF7;
        if (key[SDLK_g]) z80ports_in[0x0380] &= 0xEF;
        if (key[SDLK_f]) z80ports_in[0x0380] &= 0xDF;


        if (key[SDLK_6]) z80ports_in[0x0480] &= 0xFE;
        if (key[SDLK_y]) z80ports_in[0x0480] &= 0xFD;
        if (key[SDLK_h]) z80ports_in[0x0480] &= 0xFB;
        if (key[SDLK_SPACE]) z80ports_in[0x0480] &= 0xF7;
        if (key[SDLK_n]) z80ports_in[0x0480] &= 0xEF;
        if (key[SDLK_b]) z80ports_in[0x0480] &= 0xDF;

        if (key[SDLK_7]) z80ports_in[0x0580] &= 0xFE;
        if (key[SDLK_8]) z80ports_in[0x0580] &= 0xFD;
        if (key[SDLK_u]) z80ports_in[0x0580] &= 0xFB;
        if (key[SDLK_m]) z80ports_in[0x0580] &= 0xF7;
        if (key[SDLK_j]) z80ports_in[0x0580] &= 0xDF;

        if (key[SDLK_9]) z80ports_in[0x0680] &= 0xFE;
        if (key[SDLK_i]) z80ports_in[0x0680] &= 0xFD;
        if (key[SDLK_o]) z80ports_in[0x0680] &= 0xFB;
        if (key[SDLK_COMMA]) z80ports_in[0x0680] &= 0xF7;
        if (key[SDLK_k]) z80ports_in[0x0680] &= 0xDF;

        if (key[SDLK_0]) z80ports_in[0x0780] &= 0xFE;
        if (key[SDLK_p]) z80ports_in[0x0780] &= 0xFD;
        if (key[SDLK_l]) z80ports_in[0x0780] &= 0xFB;
        if (key[SDLK_PERIOD]) z80ports_in[0x0780] &= 0xF7;
        if (key[SDLK_SEMICOLON]) z80ports_in[0x0780] &= 0xDF;
        
        if (key[SDLK_MINUS]) z80ports_in[0x0880] &= 0xFE;
        if (key[SDLK_EQUALS]) z80ports_in[0x0880] &= 0xFD;
        if (key[SDLK_LEFTBRACKET]) z80ports_in[0x0880] &= 0xFB;
        if (key[SDLK_SLASH]) z80ports_in[0x0880] &= 0xF7;
        if (key[SDLK_QUOTE]) z80ports_in[0x0880] &= 0xDF;

        if (key[SDLK_BACKSPACE]) z80ports_in[0x0980] &= 0xFE;
        if (key[SDLK_RIGHTBRACKET]) z80ports_in[0x0980] &= 0xFD;        
        if (key[SDLK_LEFT]) z80ports_in[0x0980] &= 0xFB;
        if (key[SDLK_RETURN]) z80ports_in[0x0980] &= 0xF7;
        if (key[SDLK_RIGHT]) z80ports_in[0x0980] &= 0xDF;



}

void pump_key(char k)
{
        Uint8 *key;
        int f;
    //  int PUMP_DELAY=2000;
     //   int PUMP_DELAY=40;

      int PUMP_DELAY=80;


     k=tolower (k);
     
        // Real Keyboard Table                          
        if (k=='1') z80ports_in[0x0080] &= 0xFE;
//      if key[SDLK_CAPSLOCK]) z80ports_in[0x0080] &= 0xF7;
//      if key[SDLK_UP]) z80ports_in[0x0080] &= 0xEF;
//      if key[SDLK_DOWN]) z80ports_in[0x0080] &= 0xDF;
//      if key[SDLK_ESCAPE]) z80ports_in[0x0080] &= 0xBF;
        
        if(k=='\"')
        {
                z80ports_in[0x0080] &= 0x7F;//SHIFT
                z80ports_in[0x0280] &= 0xFE;// 2
        }

//      if ((key[SDLK_RSHIFT]) || (key[SDLK_LSHIFT])) z80ports_in[0x0080] &= 0x7F;

        if (k=='3') z80ports_in[0x0180] &= 0xFE; // 01
        if (k=='4') z80ports_in[0x0180] &= 0xFD;
// 02
        if (k=='e') z80ports_in[0x0180] &= 0xFB;
// 04
        if (k=='x') z80ports_in[0x0180] &= 0xF7;
// 08
        if (k=='d') z80ports_in[0x0180] &= 0xEF;
// 10
    if (k=='c') z80ports_in[0x0180] &= 0xDF; // 20
        if (k=='2') z80ports_in[0x0280] &= 0xFE;
        if (k=='q') z80ports_in[0x0280] &= 0xFD;
        if (k=='w') z80ports_in[0x0280] &= 0xFB;
        if (k=='z') z80ports_in[0x0280] &= 0xF7;
        if (k=='s') z80ports_in[0x0280] &= 0xEF;
        if (k=='a') z80ports_in[0x0280] &= 0xDF;
//      if ((key[SDLK_RCTRL]) || (key[SDLK_LCTRL])) z80ports_in[0x0280] &= 0xBF;
        
        if (k=='5') z80ports_in[0x0380] &= 0xFE;
        if (k=='r') z80ports_in[0x0380] &= 0xFD;
        if (k=='t') z80ports_in[0x0380] &= 0xFB;
        if (k=='v') z80ports_in[0x0380] &= 0xF7;
        if (k=='g') z80ports_in[0x0380] &= 0xEF;
        if (k=='f') z80ports_in[0x0380] &= 0xDF;


        if (k=='6') z80ports_in[0x0480] &= 0xFE;
        if (k=='y') z80ports_in[0x0480] &= 0xFD;
        if (k=='h') z80ports_in[0x0480] &= 0xFB;
        if (k==' ') z80ports_in[0x0480] &= 0xF7;
        if (k=='n') z80ports_in[0x0480] &= 0xEF;
        if (k=='b') z80ports_in[0x0480] &= 0xDF;

        if (k=='7') z80ports_in[0x0580] &= 0xFE;
        if (k=='8') z80ports_in[0x0580] &= 0xFD;
        if (k=='u') z80ports_in[0x0580] &= 0xFB;
        if (k=='m') z80ports_in[0x0580] &= 0xF7;
        if (k=='j') z80ports_in[0x0580] &= 0xDF;

        if (k=='9') z80ports_in[0x0680] &= 0xFE;
        if (k=='i') z80ports_in[0x0680] &= 0xFD;
        if (k=='o') z80ports_in[0x0680] &= 0xFB;
        if (k==',') z80ports_in[0x0680] &= 0xF7;
        if (k=='k') z80ports_in[0x0680] &= 0xDF;

        if (k=='0') z80ports_in[0x0780] &= 0xFE;
        if (k=='p') z80ports_in[0x0780] &= 0xFD;
        if (k=='l') z80ports_in[0x0780] &= 0xFB;
// unsure about these
        if (k=='.') z80ports_in[0x0780] &= 0xF7;
        if (k==';') z80ports_in[0x0780] &= 0xDF;
        
        if (k=='-') z80ports_in[0x0880] &= 0xFE;
//      if (key[SDLK_AT]) z80ports_in[0x0880] &= 0xFD;
        if (k=='(') z80ports_in[0x0880] &= 0xFB;
        if (k=='/') z80ports_in[0x0880] &= 0xF7;
        if (k==':') z80ports_in[0x0880] &= 0xDF;

//      if (key[SDLK_BACKSPACE]) z80ports_in[0x0980] &= 0xFE;
        if (k==')') z80ports_in[0x0980] &= 0xFD;        
//      if (key[SDLK_LEFT]) z80ports_in[0x0980] &= 0xFB;
        if (k=='\x0d') z80ports_in[0x0980] &= 0xF7;
//      if (key[SDLK_RIGHT]) z80ports_in[0x0980] &= 0xDF;

        //Make sure the keypress is recognised
        //in future check in the keyboard buffer on the ynx that they key gets there
        
        for(f=0;f<PUMP_DELAY;f++)
                z80_emulate(emu_cycles);


        // Clear all keypresses
        z80ports_in[0x0080] = 0xFF;
        z80ports_in[0x0180] = 0xFF;
        z80ports_in[0x0280] = 0xFF;
        z80ports_in[0x0380] = 0xFF;
        z80ports_in[0x0480] = 0xFF;
        z80ports_in[0x0580] = 0xFF;
        z80ports_in[0x0680] = 0xFF;
        z80ports_in[0x0780] = 0xFF;
        z80ports_in[0x0880] = 0xFF;
        z80ports_in[0x0980] = 0xFF;

        //Make sure the keypress is recognised
        //in future check in the keyboard buffer on the ynx that they key gets there
        for(f=0;f<PUMP_DELAY;f++)
                z80_emulate(emu_cycles);


}

void pump_string(char *s)
{
        int f;
        for(f=0;f<strlen(s);f++)
        {
                pump_key(s[f]);
        }
        for(f=0;f<100;f++)      //Give it time to settle
                z80_emulate(emu_cycles);

}

