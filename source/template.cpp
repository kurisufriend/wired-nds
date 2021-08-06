#include <nds.h>
#include <stdio.h>
#include <maxmod9.h>

#include "soundbank.h"
#include "soundbank_bin.h"

//image headers
#include "wsfwp.h" // entry-top
#include "mebious.h" // entry-bot

void startScreen();
void prepareAudio();
void prepareVideo();

mm_word samples[3] = {SFX_PSX_LAIN, SFX_WIRED};

int main(void)
{
	// init
	prepareVideo();
	prepareAudio();
	// init relevant stuff

	//initial scene
	startScreen();
	while(1)
	{
		swiWaitForVBlank();
		scanKeys();
		if (keysDown()&KEY_START) break;
	}
	mmUnloadEffect(SFX_PSX_LAIN);
	return 0;
}

void startScreen()
{
	// load main and sub bgs from memory
	bgInit(3, BgType_Bmp16, BgSize_B16_256x256, 0,0);
	decompress(wsfwpBitmap, BG_GFX,  LZ77Vram);

	bgInitSub(2, BgType_Bmp16, BgSize_B16_256x256, 0,0);
	decompress(mebiousBitmap, BG_GFX_SUB,  LZ77Vram);

	//play startscreen samples
	mmEffect(SFX_PSX_LAIN);
	mmEffect(SFX_WIRED);
}

void prepareAudio()
{
	mmInitDefaultMem( (mm_addr)soundbank_bin );
	
	for (int n = 0; n < (int)(sizeof(samples)/sizeof(samples[0])); n++)
	{
		mmLoadEffect(samples[n]);
	}
}

void prepareVideo()
{
	consoleDemoInit();
	// prepare displays
	videoSetMode(MODE_5_2D);
	videoSetModeSub(MODE_5_2D);
	vramSetBankA(VRAM_A_MAIN_BG);
}