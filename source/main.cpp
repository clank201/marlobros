#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <3ds.h>
#include <sf2d.h>
//#include <iostream>
/*extern const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel;
  unsigned char	 pixel_data[];
} citra_img;

extern const struct {
  unsigned int 	 width;
  unsigned int 	 height;
  unsigned int 	 bytes_per_pixel;
  unsigned char	 pixel_data[];
} dice_img;
*/

s32 frames=0;
float testaccel=2;//no feu aixo a casa nens!
/*
void caiguda(){
	marlo.posy=marlo.posy+((testaccel/2)*(frames*frames));
}

void gravetat(extern personatge &marlo){
	float tempy=(marlo.posy+marlo.altura+1)/16f,tempx=posx/16f;
	int xblocinferior=(int)tempx,yblocinferior=(int)tempy;
	if(!map[xblocinferior][yblocinferior]->solid)caiguda();
	else frames=0;
}
/*/
struct personatge{
	s16 posx,posy;  //#nofloat
	float velx,vely,acelx,acely;
	s8 amplada,altura;
	bool saltant;
	//textura
	};
	
	struct solid{ //creem variable de tipus solid
		s32 posx,posy; //aixo cal?
		s8 tipus,altura,amplada;
		bool solid;
		//textura
	};
//tipus de blocs: 0-aire 1-bloc normal 2-bloc trencat 3-terra_1 4-terra_2... 
int main()
{
	//consoleInit(GFX_BOTTOM, NULL);
	// Set the random seed based on the time
	srand(time(NULL));
    
	sf2d_set_vblank_wait(true);
	sf2d_init();
	sf2d_set_clear_color(RGBA8(51, 204, 255, 0xFF));

	//sf2d_texture *tex1 = sf2d_create_texture_mem_RGBA8(dice_img.pixel_data, dice_img.width, dice_img.height, TEXFMT_RGBA8, SF2D_PLACE_RAM);
	u32 held;	
    const int ampladamapa=25*4,alturamapa=15, ampladaestandar=16, alturaestandar=16; 
	
	solid *mapa[ampladamapa+1][alturamapa+1];
	
	solid aire;
	aire.tipus=0;
	aire.amplada=ampladaestandar;
	aire.altura=alturaestandar;
	aire.solid=false;
	
	solid bloc_normal;
	bloc_normal.tipus=1;
	bloc_normal.amplada=ampladaestandar;
	bloc_normal.altura=alturaestandar;
	bloc_normal.solid=true;
	//textura
	
    solid bloc_trencat;
	bloc_trencat.tipus=2;
	bloc_trencat.amplada=ampladaestandar;
	bloc_trencat.altura=alturaestandar;
	bloc_trencat.solid=true;
	//textura
	
	solid terra_1;
	terra_1.tipus=3;
	terra_1.amplada=ampladaestandar;
	terra_1.altura=alturaestandar;
	terra_1.solid=true;
	//textura
	
	personatge marlo;
	marlo.amplada=ampladaestandar;
	marlo.altura=32;
	//textura
	
	personatge marlo_correr;
	marlo_correr.amplada=ampladaestandar;
	marlo_correr.altura=32;
	//textura
	
	/*personatge marlo_salt;
	marlo_salt.amplada=ampladaestandar;
	marlo_salt.altura=32;
	//textura */

	marlo.posx=5;
	marlo.posy=0;
			
	for (int i = 0; i != alturamapa; i++){
		for (int j = 0; j != ampladamapa; j++){
			mapa[j][i] = &aire;
		}
	}
	
	for (int i = alturamapa-5; i <= alturamapa; i++){//y	
		for (int j = 0; j <= ampladamapa; j++){//x
			if(j<=10 || j>=15)mapa[j][i] = &terra_1;
		}
	}
		
	mapa[10][alturamapa-8]=&bloc_normal;
	
	while (aptMainLoop()) {
        
        //gravetat();        
		
		float tempy=(marlo.posy+marlo.altura+1)/16,tempx=marlo.posx/16;
    	int xblocinferior=(int)tempx,yblocinferior=(int)tempy;
    	if(!mapa[xblocinferior][yblocinferior]->solid){
			//std::cout<<"Gravity YES"<<std::endl;
			marlo.posy=marlo.posy+((testaccel/2)*(frames*frames));
    	}
		else frames=0;
		
		hidScanInput();		
		held = hidKeysHeld();
		
		/*
		if (held & KEY_X) {
			saltar();
		} 
		if (held & KEY_Y) {
			correr();
		}*/
		if (held & KEY_START) {
			break;
		}
        if (held & KEY_RIGHT) {
			marlo.posx+=1;
		} 
		if (held & KEY_LEFT) {
			marlo.posx-=1;
		} 	
		if (held & KEY_UP) {
			testaccel+=0.1;
		} 
		if (held & KEY_DOWN) {
			testaccel-=0.1;
		} 
		        
		//renderitzar
		sf2d_start_frame(GFX_TOP, GFX_LEFT);
		
		for (int i = 0; i != alturamapa; i++){ //y
			for (int j = 0; j != 25; j++){ //!Auet 25 hauria de ser la zona que la camera abasteix
				if(mapa[j][i]->tipus) sf2d_draw_rectangle(j*16,i*16,mapa[j][i]->amplada,mapa[j][i]->altura, RGBA8(204, 102, 0, 0xFF));			
			}
		}
		
		sf2d_draw_rectangle(marlo.posx,marlo.posy,marlo.amplada,marlo.altura, RGBA8(51, 51, 255, 0xFF));
		
		sf2d_end_frame();

		sf2d_swapbuffers();
	}


	sf2d_fini();
	return 0;
}

//! Res de tot aixo hagues estat possible sense la col·laboració i exemples den clank201 i la llibreria d'en xerpi :D