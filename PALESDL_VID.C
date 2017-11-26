#include <stdlib.h>
#include <stdio.h>
#include <memory.h>

#include "PALESDL.H"

#include <SDL/SDL.h>

#include "PALESDL_IO.H"
#include "PALESDL.H"
#include "PALE48K.H"
#include "PALE96K.H"
#include "PALE128K.H"

#include "PALESDL_VID.H"

#include "PALEDOS_TEMP.H"

//#define VIDEO_METHOD SDL_SWSURFACE 
//|SDL_RESIZABLE
//|SDL_HWPALETTE
#define VIDEO_METHOD SDL_HWSURFACE|SDL_DOUBLEBUF|SDL_HWPALETTE
//|SDL_RLEACCEL 
//??
//|SDL_ASYNCBLIT  - for multiproc systems


int StretchEnable=0;    //Enables VIdeo Stretch function
unsigned char CRTC_reg[18];
unsigned int crtc_reg=0;
SDL_Surface *screen;

int trippy_mode = 0;
int isFullscreen = 0;

//int double_size = 1; //useDoubleSize
//int accurate_mode = 0;// useScanLineUpdates
//int double_buffer = 1;//  usePageFlipping

//  ONLY FOR SCALING
//  ONLY FOR SCALING
//  ONLY FOR SCALING
   /* Create a 32-bit surface with the bytes of each pixel in R,G,B,A order,
       as expected by OpenGL for textures */
    Uint32 rmask, gmask, bmask, amask;



SDL_Color LynxPalette[8] = {{0,0,0,0},{0,0,255,0},{255,0,0,0},{255,0,255,0}, \
        {0,255,0,0},{0,255,255,0},{255,255,0,0},{255,255,255,0}};

void clearcrtc()
{
        for(int f=0;f<18;f++)
                CRTC_reg[f]=0;
}

void SetPixel ( SDL_Surface* pSurface , int x , int y , Uint8 r, Uint8 g, Uint8 b)
{
  //convert color
  Uint32 col = SDL_MapRGB ( pSurface->format ,r ,g ,b ) ;
  //determine position
  char* pPosition = ( char* ) pSurface->pixels ;
  //offset by y
  pPosition += ( pSurface->pitch * y ) ;
  //offset by x
  pPosition += ( pSurface->format->BytesPerPixel * x ) ;
  //copy pixel data
  memcpy ( pPosition , &col , pSurface->format->BytesPerPixel ) ;
}





void video_fullscreen(int x)
{
	isFullscreen = x;
        
	if(x == 1)
        {
               //Do This twice to make sure w2k blacksout the border area
                if(useDoubleSize == 1)
		{
			if(hw_type == LYNX_HARDWARE_128)
				screen = SDL_SetVideoMode(1024,512, 8,  VIDEO_METHOD | SDL_FULLSCREEN);
			else
				screen = SDL_SetVideoMode(512,512, 8,  VIDEO_METHOD | SDL_FULLSCREEN);
		}
		else
		{
			if(hw_type == LYNX_HARDWARE_128)
				screen = SDL_SetVideoMode(512,256, 8,  VIDEO_METHOD | SDL_FULLSCREEN);
			else
				screen = SDL_SetVideoMode(256,256, 8,  VIDEO_METHOD | SDL_FULLSCREEN);
		}
        }
        else
        {
                if(useDoubleSize  == 1)
		{
			if(hw_type == LYNX_HARDWARE_128)
		                screen = SDL_SetVideoMode(1024,512, 8,  VIDEO_METHOD);
			else
		                screen = SDL_SetVideoMode(512,512, 8,  VIDEO_METHOD);
		}
		else
	        {
			if(hw_type == LYNX_HARDWARE_128)
			        screen = SDL_SetVideoMode(512,256, 8,  VIDEO_METHOD);
			else
			        screen = SDL_SetVideoMode(256,256, 8,  VIDEO_METHOD);
		}
        }
        SDL_DisplayFormat(screen);
        SDL_SetColors(screen, LynxPalette, 0, 8);
}




void set_screenres()
{
        //Initially the screen is NOT resizable
        if(useDoubleSize  == 1)
	{
			if(hw_type == LYNX_HARDWARE_128)
			       screen = SDL_SetVideoMode(1024,512, 8,  VIDEO_METHOD);
			else
			       screen = SDL_SetVideoMode(512,512, 8,  VIDEO_METHOD);
        }
	else
	{
		if(hw_type == LYNX_HARDWARE_128)
		        screen = SDL_SetVideoMode(512,256, 8,  VIDEO_METHOD);
		else
		        screen = SDL_SetVideoMode(256,256, 8,  VIDEO_METHOD);
        }
	if ( screen == NULL )
        {
        gui_error("Couldnt get Video MODE");
                exit(1);
    }

        if ( SDL_DisplayFormat(screen)==NULL )
        {
         gui_error("Couldnt get Video MODE");
             exit(1);
    }
        // Set palette
        SDL_SetColors(screen, LynxPalette, 0, 8);
}


void initialise_display(void){
    /* Initialize the SDL library (Video/Keyboard)*/
    if( SDL_Init(SDL_INIT_VIDEO | SDL_INIT_AUDIO | SDL_INIT_TIMER) < 0 ) {
         fprintf(stderr,"Couldn't initialize SDL: %s\n", SDL_GetError());
         gui_error("Couldnt get Video MODE");
        exit(1);
    }
        isFullscreen = 0;
	set_screenres();

//  ONLY FOR SCALING
//  ONLY FOR SCALING
//  ONLY FOR SCALING
    /* SDL interprets each pixel as a 32-bit number, so our masks must depend
       on the endianness (byte order) of the machine */
#if SDL_BYTEORDER == SDL_BIG_ENDIAN
    rmask = 0xff000000;
    gmask = 0x00ff0000;
    bmask = 0x0000ff00;
    amask = 0x000000ff;
#else
    rmask = 0x000000ff;
    gmask = 0x0000ff00;
    bmask = 0x00ff0000;
    amask = 0xff000000;
#endif
//  ONLY FOR SCALING
//  ONLY FOR SCALING
//  ONLY FOR SCALING

}


Uint8 getpixel(Uint16 offset, Uint8 bit)
{
        Uint8 colour;
        switch(hw_type)
        {
                case LYNX_HARDWARE_48:
                        colour=getpixel_48( offset,  bit);
                        break;
                case LYNX_HARDWARE_96:
                        colour=getpixel_48( offset,  bit);
                        break;
                case LYNX_HARDWARE_128:
                        colour=getpixel_128( offset,  bit);
                        break;
        }
        return colour;
}


#ifdef USE_SDL_LINUX










//  Current 


void end_frame()
{
	if(useScanlineUpdates == 0)
	{
		if(usePageFlipping == 1)
		{
		    SDL_Flip(screen);
		}
		else
		{
			if(useDoubleSize == 1)
			{
				if(hw_type == LYNX_HARDWARE_128)
					    SDL_UpdateRect(screen, 0,0,1024,512);
				else
					    SDL_UpdateRect(screen, 0,0,512,512);

			}
			else
			{
				if(hw_type == LYNX_HARDWARE_128)
					    SDL_UpdateRect(screen, 0,0,512,256);
				else
					    SDL_UpdateRect(screen, 0,0,256,256);
			}
		}
	}
}




//Returns ZERO if end of screen
int draw_scanline(int scanline)
{
	SDL_Rect retRect;
	Uint8 *bits, bank, skip, temp,temp2;
	unsigned int memy, memx, memy2;
	static int hor_disp_pix,hor_disp_bytes,vrt_disp_pix;
	int ret,line,scptr;
        static int vrt_disp_6845pixperchar,vrt_disp_chars;
	unsigned char *bnk2;
 	unsigned char scline[1024];
     	static int sync_width,vert_sync_pos;
	unsigned vid_start;

	

 
// FIXME - this next line works for the Level 9 adventures, but with artifact lines (the flashing pink mush is accurate)
// it is linked to the line blanking monostable variable
	if(((video_latch & 0x60)!=0x20))
	{
  	        if(!trippy_mode)
		{
			for(int wxa=0;wxa<hor_disp_pix ;wxa++)
		        {
			  scline[wxa]= 0 ;
			}
		}
		
		if(scanline>vrt_disp_pix)
		{
			//end_frame();
			//hor_disp_bytes=32;
			hor_disp_bytes=CRTC_reg[1];
			if(hor_disp_bytes>64)hor_disp_bytes=64;
	            	if(hor_disp_bytes<2)hor_disp_bytes=2;
	            	
			//hor_disp_pix=hor_disp_bytes*8;
			if(useDoubleSize == 1)
			{
					if(hw_type == LYNX_HARDWARE_128)
						hor_disp_pix = 1024;
					else
						hor_disp_pix = 512;
			}
			else			
			{
				if(hw_type == LYNX_HARDWARE_128)
					hor_disp_pix = 512;
				else
					hor_disp_pix = 256;
			}
		/*
			vrt_disp_6845pixperchar=CRTC_reg[9]+1;  //usually 3+1 = 4
			vrt_disp_chars=CRTC_reg[6];  //usually 3f, 40 in Pengo
			vrt_disp_pix=vrt_disp_chars*vrt_disp_6845pixperchar;
			if(vrt_disp_pix<32)vrt_disp_pix=32;
			if(vrt_disp_pix>256)vrt_disp_pix=256;
			
			if (CRTC_reg[3]>0x37)
				sync_width=(CRTC_reg[3]-0x37)/4;
			else
				sync_width=0;
			
			if (CRTC_reg[6]>0x3f)
				vert_sync_pos=(CRTC_reg[6]-0x3f)/4;
			else
				vert_sync_pos=0;
		*/
			vrt_disp_pix= 247;
	
			return(0);//end of frame
		}

		vid_start=(CRTC_reg[12]*256+CRTC_reg[13])*4 ;//0000 for 48/96  4000h for 128
		if(hw_type==LYNX_HARDWARE_128)
			vid_start=vid_start%0x4000;// for 128
		else
			vid_start=vid_start%0x2000;//for 4896,
 	    
			memy=scanline*hor_disp_bytes+vid_start;

		for(bank = 0;bank < 3;bank++)
		{
			skip = 0;

	if(hw_type == LYNX_HARDWARE_128)
	{
		//Important for CPM
                memy=memy%0x4000;
                if(show_allbanks==1)
                {
                        switch(bank)
                                        {
                                                case 0:
                                                        bnk2 =  (unsigned char *)&bank2[0x4000+memy];  //red
                                                        break;
                                                case 1:
                                                        bnk2 =  (unsigned char *)&bank2[0x0000+memy]; //blue
                                                        break;
                                		case 2:
                                                        if(show_alt_green==1)
                                        			bnk2 =  (unsigned char *)&bank2[0xc000+memy];  //alt green mirror
                                        		else
                                        			bnk2 =   (unsigned char *)&bank2[0x8000+memy];  //green mirror
                                                        break;
                                        }
                }
                else
                                                         skip =  1;
	}
	else
	{

		// Get (the start) pointer to the scanline LHS in the Lynx memory
		memy=memy%0x2000;
                switch(bank)
                {
                        case 0:
                            if(show_bank2==1)
                            {

                                    bnk2 = (unsigned char *)&bank2[0xa000+memy];//blue
                     
                            }
                            else
                                skip =  1;
                                break;          
                        case 1:
                            if(show_bank2==1)
                            {
                               
                                    bnk2 = (unsigned char *)&bank2[0xc000+memy];//red
                               
                            }
                            else
                                skip =  1;
                                break;
                        case 2:
                            if(show_bank3==1 )
                            {
                                //memy = memy %0x2000;
				
                                    if(show_alt_green==1)
                                    {
                                        bnk2 = (unsigned char *)&bank3[0xa000+memy];//alt green 
                                    }
                                    else
                                    {
                                        bnk2 = (unsigned char *)&bank3[0xc000+memy];//green 
                                    }
                              
                            }
                            else
                                skip =  1;
                            break;
                }
	}




	         // by here bnk2 holds the start of the scanline (8 bit pointer)


		temp = 7-bank;  // to get colours the correct way way round
		scptr = 0;
		for(int wx=0;wx<hor_disp_bytes;wx++)
		{
			for(int wx2=0;wx2<8;wx2++)
			{
		           if(skip == 0) 
			   {
			        temp2 = ( ((*(bnk2+wx)) << wx2 ) & 0x80 ) >> temp;
				scline[scptr++]+= temp2;
				if(useDoubleSize == 1)
					scline[scptr++]+= temp2;
			   }
			}
		}

  
		if(useDoubleSize == 1)
		{
		     memcpy(screen->pixels+(scanline*2*hor_disp_pix),scline,hor_disp_pix);
		     memcpy(screen->pixels+((scanline*2+1)*hor_disp_pix),scline,hor_disp_pix);
		}
		else
		{
		     memcpy((screen->pixels)+(scanline*hor_disp_pix),scline,hor_disp_pix);
		}


		if(useScanlineUpdates == 1)
		{
			if(useDoubleSize == 1)
			{
				SDL_UpdateRect(screen, 0,scanline,hor_disp_pix,2);
			}
			else
			{
				SDL_UpdateRect(screen, 0,scanline,hor_disp_pix,1);
			}
		}


             }

	}	
	return(1);
}      


#endif


#ifdef USE_SDL_LINUX_PIXEL

//Returns ZERO if end of screen
int draw_scanline(int scanline)
{
	SDL_Rect retRect;
	Uint8 *bits;
	int memy, memx;
	int ret,hor_disp_pix,hor_disp_bytes,vrt_disp_pix,line;


	if(((video_latch & 0x20)!=0x20))
//	if(((video_latch & 0x60)!=0x20))
	{
		if(hw_type != LYNX_HARDWARE_128) hor_disp_bytes=32;
		else hor_disp_bytes=64;
		vrt_disp_pix=248;

	
		if(scanline>vrt_disp_pix)
		{
			//Copy backbuffer to screen
			
                                                memcpy(screen->pixels,surface->pixels,256*256);
                                                
                                                //Then Blit them back to the Screen using scaling
//                                                retRect=sge_transform(surface2, screen, 
  //                                                                              0.0, (float)screen->w/(float)512,(float)screen->h/(float)256, 
    //                                                                            0,0,
      //                                                                          0,0,
        //                                                                        0);
          //                                      SDL_UpdateRect(screen, 0,0,screen->w,screen->h);


			
			//SDL_UpdateRect(screen, 0,0,512,512);
			SDL_UpdateRect(screen, 0,0,256,256);
			return(0);//end of frame
		}

//		bits=((Uint8 *)screen->pixels)+(scanline*1024); 
		bits=((Uint8 *)surface->pixels)+(scanline*256);  //(scanline*1024); 
		memy=scanline*hor_disp_bytes;
		for(memx=0;memx<hor_disp_bytes;memx++) {

		*((Uint8 *)(bits++)) = getpixel(memy + memx, 7);
//		if(hw_type != LYNX_HARDWARE_128) *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		*((Uint8 *)(bits++)) = getpixel(memy + memx, 6);
//		if(hw_type != LYNX_HARDWARE_128) *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		*((Uint8 *)(bits++)) = getpixel(memy+ memx, 5);
//		if(hw_type != LYNX_HARDWARE_128) *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		*((Uint8 *)(bits++)) = getpixel(memy+ memx, 4);
//		if(hw_type != LYNX_HARDWARE_128) *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		*((Uint8 *)(bits++)) = getpixel(memy+ memx, 3);
//		if(hw_type != LYNX_HARDWARE_128) *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		*((Uint8 *)(bits++)) = getpixel(memy+ memx, 2);
//		if(hw_type != LYNX_HARDWARE_128) *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		*((Uint8 *)(bits++)) = getpixel(memy+ memx, 1);
//		if(hw_type != LYNX_HARDWARE_128) *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		*((Uint8 *)(bits++)) = getpixel(memy+ memx, 0);
//		if(hw_type != LYNX_HARDWARE_128) *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));

		}
//		for(memx=0;memx<512;memx++)
//			*((Uint8 *)(bits++)) = *((Uint8 *)(bits-512));

   //memcpy(screen->pixels+memy,surface->pixels+memy,256);
	//	SDL_UpdateRect(screen, 0,scanline,256,1);
	}	
	return(1);
}      

#endif


/*
//Returns ZERO if end of screen
int draw_scanline(int scanline)
{
        SDL_Rect retRect;
        Uint8 *bits, *start_line;
        int memy, memx;
        unsigned int vidsize,vid_start,start_offset;
        int ret,hor_disp_pix,hor_disp_bytes,vrt_disp_pix,line,vrt_disp_6845pixperchar,vrt_disp_chars;
        float dest_1pix_height;
        int dest_height=256;
        int dest_width=512;
        char lbl[30];
        int sync_width,vert_sync_pos;


//      if(((video_latch & 0x22)!=0x20))
        if(((video_latch & 0x20)!=0x20))
        {
                hor_disp_bytes=CRTC_reg[1];
                if(hor_disp_bytes>64)hor_disp_bytes=64;
                if(hor_disp_bytes<2)hor_disp_bytes=2;
                hor_disp_pix=hor_disp_bytes*8;
                //32*8 = 256 for 4896   512 for 128
                vrt_disp_6845pixperchar=CRTC_reg[9]+1;  //usually 3+1 = 4
                vrt_disp_chars=CRTC_reg[6];  //usually 3f, 40 in Pengo
                vrt_disp_pix=vrt_disp_chars*vrt_disp_6845pixperchar;
if(vrt_disp_pix<32)vrt_disp_pix=32;
if(vrt_disp_pix>256)vrt_disp_pix=250;
                if (CRTC_reg[3]>0x37)
                        sync_width=(CRTC_reg[3]-0x37)/4;
                else
                        sync_width=0;
                if (CRTC_reg[6]>0x3f)
                        vert_sync_pos=(CRTC_reg[6]-0x3f)/4;
                else
                        vert_sync_pos=0;

        if(scanline>(vrt_disp_pix-1))
        {
                //Blank out last bit of display which doesnt get written
                //when there are only 252 lines
                //this can be changed once a stretch function is implemented
                if(scanline<255)
                {
                        while(scanline<255)
                        {
                                bits=((Uint8 *)screen->pixels+((scanline*1024)));
                                for(memx=0;memx<hor_disp_bytes;memx++)
                                {
                                        for(int x=0;x<8;x++)
                                        {
                                                *((Uint8 *)(bits++)) = 0;
                                                if(hw_type!=LYNX_HARDWARE_128)*((Uint8 *)(bits++)) =0;
                                        }
                                }
                                for(memx=0;memx<512;memx++) {
                                        *((Uint8 *)(bits++)) = *((Uint8 *)(bits-512));
                                }
                                if(!StretchEnable)
                                {
                                        SDL_UpdateRect(screen, 0,scanline*2,512,2);
                                }
                                scanline++;
                        }

                        if(StretchEnable)
                        {
                                                //SCALING SCALING SCALING SCALING SCALING SCALING 
                                                //SCALING SCALING SCALING SCALING SCALING SCALING 
                                                //SCALING SCALING SCALING SCALING SCALING SCALING 
                                                //SCALING SCALING SCALING SCALING SCALING SCALING 
                                                //Copy the pixels off to another (hidden) surface
                                                memcpy(surface->pixels,(const void *)screen->pixels,512*256);
                                                surface2=SDL_CreateRGBSurfaceFrom(surface->pixels, 512,256, 8, 512, 
                                                              rmask, gmask, bmask, amask);//dont seem to affect anything in 8bit mode
                                                
                                                //Then Blit them back to the Screen using scaling
                                                retRect=sge_transform(surface2, screen, 
                                                                                0.0, (float)screen->w/(float)512,(float)screen->h/(float)256, 
                                                                                0,0,
                                                                                0,0,
                                                                                0);
                                                SDL_UpdateRect(screen, 0,0,screen->w,screen->h);
                        }

                }

                return(0);//end of frame
        }
                //4000h for 128, 2000h for 48/96
        //      vidsize=hor_disp_bytes*vrt_disp_pix; //0x4000; horiz tot * (vert total*(char rast count +1))
                vid_start=(CRTC_reg[12]*256+CRTC_reg[13])*4 ;//0000 for 48/96  4000h for 128

                //if (vrt_disp_pix<10)vrt_disp_pix=10;
                //if(dest_height<vrt_disp_pix)dest_height=vrt_disp_pix+1;
                //dest_1pix_height=(float) dest_height /(float)vrt_disp_pix;

                //256 for 4896   512 for 128


if(hw_type!=LYNX_HARDWARE_128)
                vid_start=vid_start%0x2000;//for 4896, 4000 for 128
else
                vid_start=vid_start%0x4000;//for 4896, 4000 for 128

                start_offset=vid_start+(scanline*hor_disp_bytes);       //this is a CRTC register pete
                //start_offset=start_offset%0x4000;

//QUICK BODGE TO GET 128 MODE TO WORK WITH THIS SCALING STUFF
if(!StretchEnable)
                bits=((Uint8 *)screen->pixels+((scanline*1024)+sync_width));
else
                bits=((Uint8 *)screen->pixels+((scanline*512)+sync_width));

                start_line=bits;
                memy=start_offset;
                for(memx=0;memx<hor_disp_bytes;memx++) {
                        *((Uint8 *)(bits++)) = getpixel(memy + memx, 7);
if(hw_type!=LYNX_HARDWARE_128)                  *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
                        *((Uint8 *)(bits++)) = getpixel(memy + memx, 6);
if(hw_type!=LYNX_HARDWARE_128)                  *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
                        *((Uint8 *)(bits++)) = getpixel(memy+ memx, 5);
if(hw_type!=LYNX_HARDWARE_128)                  *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
                        *((Uint8 *)(bits++)) = getpixel(memy+ memx, 4);
if(hw_type!=LYNX_HARDWARE_128)                  *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
                        *((Uint8 *)(bits++)) = getpixel(memy+ memx, 3);
if(hw_type!=LYNX_HARDWARE_128)                  *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
                        *((Uint8 *)(bits++)) = getpixel(memy+ memx, 2);
if(hw_type!=LYNX_HARDWARE_128)                  *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
                        *((Uint8 *)(bits++)) = getpixel(memy+ memx, 1);
if(hw_type!=LYNX_HARDWARE_128)                  *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
                        *((Uint8 *)(bits++)) = getpixel(memy+ memx, 0);
if(hw_type!=LYNX_HARDWARE_128)                  *((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
                }

if(!StretchEnable)
{
                for(memx=0;memx<512;memx++)
                        *((Uint8 *)(bits++)) = *((Uint8 *)(bits-512)); // Scan double the vertical lines
            SDL_UpdateRect(screen, 0,scanline*2,512,2);
}
*/
/*
                        //SCALING SCALING SCALING SCALING SCALING SCALING 
                        //SCALING SCALING SCALING SCALING SCALING SCALING 
                        //SCALING SCALING SCALING SCALING SCALING SCALING 
                        //SCALING SCALING SCALING SCALING SCALING SCALING 
                        //Copy the pixels off to another (hidden) surface
                        memcpy(surface->pixels,(const void *)start_line,512);
                        surface2=SDL_CreateRGBSurfaceFrom(surface->pixels, 512,2, 8, 512, 
                                      rmask, gmask, bmask, amask);//dont seem to affect anything in 8bit mode
                        
                        //Then Blit them back to the Screen using scaling
                        retRect=sge_transform(surface2, screen, 
                                                        0.0, (float)screen->w/(float)512,(float)screen->h/(float)256, 
                                                        0,0,
                                                        0,(((float)scanline*(float)screen->h)/(float)256),
                                                        0);

                        SDL_UpdateRect(screen, retRect.x,retRect.y,retRect.w,retRect.h);
*/
/*

        }       
        return(1);
}      
*/


void query_6845(char *emu_query3,char *emu_query4)
{
        int ret,f,g;

        //Query the CRTC registers
        sprintf(emu_query3,"H TOT: %02x H DISP: %02x HS Pos: %02x HS Wid: %02x V TOT: %02x VT Adj: %02x V Disp: %02x VS Pos: %02x",
                CRTC_reg[0],
                CRTC_reg[1],
                CRTC_reg[2],
                CRTC_reg[3],
                CRTC_reg[4],
                CRTC_reg[5],
                CRTC_reg[6],
                CRTC_reg[7]);
                sprintf(emu_query4,"IntSkew: %02x MRastAddr: %02x CRS Start: %02x CRS End: %02x START: %04x CRS Addr: %04x LP: %04x",
                CRTC_reg[8],
                CRTC_reg[9],
                CRTC_reg[10],
                CRTC_reg[11],
                CRTC_reg[12]*256+CRTC_reg[13],
                CRTC_reg[14]*256+CRTC_reg[15],
                CRTC_reg[16]*256+CRTC_reg[17]);
        return;
}

int get_display_w()
{
        return(screen->w);
}
int get_display_h()
{
        return(screen->h);
}


void check_for_resize()
{
//    if(event.type==SDL_VIDEORESIZE)
//              video_resize(event.resize.w,event.resize.h,1);  
}

/*
unsigned int this_time,last_time,fps_counter;


void update_fps()
{
                //Every second update the fps counter
                this_time=SDL_GetTicks();
                if((this_time-last_time)>1000)
                {
                        //update_fps_counter( fps_counter );
                        fps_counter=0;
                        last_time=this_time;
                
                }
}
*/



/*  WORKS ISH for fullscreen
//Returns ZERO if end of screen
int draw_scanline(int scanline)
{
	SDL_Rect retRect;
	Uint8 *bits, *start_line;
	int memy, memx;
	unsigned int vidsize,vid_start,start_offset;
	int ret,hor_disp_pix,hor_disp_bytes,vrt_disp_pix,line,vrt_disp_6845pixperchar,vrt_disp_chars;
	float dest_1pix_height;
	int dest_height=256;
	int dest_width=512;
	char lbl[30];
	int sync_width,vert_sync_pos;


	if(((video_latch & 0x22)!=0x20))
//	if(((video_latch & 0x60)!=0x20))
	{
		hor_disp_bytes=CRTC_reg[1];
		if(hor_disp_bytes>64)hor_disp_bytes=64;
		if(hor_disp_bytes<2)hor_disp_bytes=2;
		hor_disp_pix=hor_disp_bytes*8;
		//32*8 = 256 for 4896   512 for 128
		vrt_disp_6845pixperchar=CRTC_reg[9]+1;	//usually 3+1 = 4
		vrt_disp_chars=CRTC_reg[6];  //usually 3f, 40 in Pengo
		vrt_disp_pix=vrt_disp_chars*vrt_disp_6845pixperchar;
if(vrt_disp_pix<32)vrt_disp_pix=32;
if(vrt_disp_pix>256)vrt_disp_pix=250;
		if (CRTC_reg[3]>0x37)
			sync_width=(CRTC_reg[3]-0x37)/4;
		else
			sync_width=0;
		if (CRTC_reg[6]>0x3f)
			vert_sync_pos=(CRTC_reg[6]-0x3f)/4;
		else
			vert_sync_pos=0;

	if(scanline>(vrt_disp_pix-1))
	{
		//Blank out last bit of display which doesnt get written
		//when there are only 252 lines
		//this can be changed once a stretch function is implemented
		if(scanline<255)
		{
			while(scanline<255)
			{
				bits=((Uint8 *)screen->pixels+((scanline*1024)));
				for(memx=0;memx<hor_disp_bytes;memx++)
				{
					for(int x=0;x<8;x++)
					{
						*((Uint8 *)(bits++)) = 0;
						//if(hw_type!=LYNX_HARDWARE_128)*((Uint8 *)(bits++)) =0;
					}
				}
				for(memx=0;memx<512;memx++) {
					*((Uint8 *)(bits++)) = *((Uint8 *)(bits-512));
				}
				if(!StretchEnable)
				{
  					SDL_UpdateRect(screen, 0,scanline*2,512,2);
  				}
				scanline++;
			}

			if(StretchEnable)
			{
						//SCALING SCALING SCALING SCALING SCALING SCALING 
						//SCALING SCALING SCALING SCALING SCALING SCALING 
						//SCALING SCALING SCALING SCALING SCALING SCALING 
						//SCALING SCALING SCALING SCALING SCALING SCALING 
						//Copy the pixels off to another (hidden) surface
						memcpy(surface->pixels,(const void *)screen->pixels,512*256);
						surface2=SDL_CreateRGBSurfaceFrom(surface->pixels, 512,256, 8, 512, 
			                                      rmask, gmask, bmask, amask);//dont seem to affect anything in 8bit mode
						
						//Then Blit them back to the Screen using scaling
						retRect=sge_transform(surface2, screen, 
										0.0, (float)screen->w/(float)512,(float)screen->h/(float)256, 
										0,0,
										0,0,
										0);
						SDL_UpdateRect(screen, 0,0,screen->w,screen->h);
			}

		}

		return(0);//end of frame
	}
		//4000h for 128, 2000h for 48/96
	//	vidsize=hor_disp_bytes*vrt_disp_pix; //0x4000; horiz tot * (vert total*(char rast count +1))
		vid_start=(CRTC_reg[12]*256+CRTC_reg[13])*4 ;//0000 for 48/96  4000h for 128

		//if (vrt_disp_pix<10)vrt_disp_pix=10;
		//if(dest_height<vrt_disp_pix)dest_height=vrt_disp_pix+1;
		//dest_1pix_height=(float) dest_height /(float)vrt_disp_pix;

		//256 for 4896   512 for 128


if(hw_type!=LYNX_HARDWARE_128)
		vid_start=vid_start%0x2000;//for 4896, 4000 for 128
else
		vid_start=vid_start%0x4000;//for 4896, 4000 for 128

		start_offset=vid_start+(scanline*hor_disp_bytes);	//this is a CRTC register pete
		//start_offset=start_offset%0x4000;

//QUICK BODGE TO GET 128 MODE TO WORK WITH THIS SCALING STUFF
if(!StretchEnable)
		bits=((Uint8 *)screen->pixels+((scanline*1024)+sync_width));
else
		bits=((Uint8 *)screen->pixels+((scanline*512)+sync_width));

		start_line=bits;
		memy=start_offset;
		for(memx=0;memx<hor_disp_bytes;memx++) {
//			*((Uint8 *)(bits++)) = getpixel(memy + memx, 7);
//if(hw_type!=LYNX_HARDWARE_128)			*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
			*((Uint8 *)(bits++)) = getpixel(memy + memx, 6);
//if(hw_type!=LYNX_HARDWARE_128)			*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
			*((Uint8 *)(bits++)) = getpixel(memy+ memx, 5);
//if(hw_type!=LYNX_HARDWARE_128)			*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
			*((Uint8 *)(bits++)) = getpixel(memy+ memx, 4);
//if(hw_type!=LYNX_HARDWARE_128)			*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
			*((Uint8 *)(bits++)) = getpixel(memy+ memx, 3);
//if(hw_type!=LYNX_HARDWARE_128)			*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
			*((Uint8 *)(bits++)) = getpixel(memy+ memx, 2);
//if(hw_type!=LYNX_HARDWARE_128)			*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
			*((Uint8 *)(bits++)) = getpixel(memy+ memx, 1);
//if(hw_type!=LYNX_HARDWARE_128)			*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
			*((Uint8 *)(bits++)) = getpixel(memy+ memx, 0);
//if(hw_type!=LYNX_HARDWARE_128)			*((Uint8 *)(bits++)) = *((Uint8 *)(bits-1));
		}

if(!StretchEnable)
{
		for(memx=0;memx<256;memx++)
			*((Uint8 *)(bits++)) = *((Uint8 *)(bits-512)); // Scan double the vertical lines
	    SDL_UpdateRect(screen, 0,scanline*2,256,2);
}



	}	
	return(1);
}      

*/

