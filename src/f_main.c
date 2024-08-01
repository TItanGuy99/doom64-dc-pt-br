/* f_main.c -- finale */
#include "doomdef.h"
#include "p_local.h"
#include "st_main.h"
#include "r_local.h"

#define T_NULL	        ""

// [Immorpher] New introduction text adapted from Doom 64 reloaded!
#define C_INTRO_TXT01	"Sobreviver ao veneno tem"
#define C_INTRO_TXT02	"levado a sanidade ao limite. Os"
#define C_INTRO_TXT03	"tratamentos dos medicos sao de pouco"
#define C_INTRO_TXT04	"ajuda. Pesadelos de tantos demonios"
#define C_INTRO_TXT05	"atravessando nao vao parar."
#define C_INTRO_TXT06	" "
#define C_INTRO_TXT07	"O posto avancado em Phobos foi deixado morto"
#define C_INTRO_TXT08	"em uma neblina nuclear. No entanto, o inferno"
#define C_INTRO_TXT09	"retornou. Algo distorceu a realidade e"
#define C_INTRO_TXT10	"ressuscitou carnificina em decomposicao"
#define C_INTRO_TXT11	"de volta a tecido horrivel."
#define C_INTRO_TXT12	" "
#define C_INTRO_TXT13	"As mutacoes sao devastadoras. Os"
#define C_INTRO_TXT14	"demonios retornaram ainda mais fortes"
#define C_INTRO_TXT15	"e mais violentos do que antes. Como"
#define C_INTRO_TXT16	"a unica pessoa que sobreviveu ao"
#define C_INTRO_TXT17	"terror, a missao e clara..."
#define C_INTRO_TXT18	" "
#define C_INTRO_TXT19	"EXTERMINIO IMPLACAVEL!"
#define C_INTRO_TXT20	"EXTERMINIO SEM MISERICORDIA!"

#define C_END1_TXT01	"Voce ri enquanto a"
#define C_END1_TXT02	"familiaridade da"
#define C_END1_TXT03	"situacao lhe ocorre."
#define C_END1_TXT04	"O portal para o dominio dos demonios"
#define C_END1_TXT05	"era muito acessivel."
#define C_END1_TXT06	"Voce percebe que os demonios zombam"
#define C_END1_TXT07	"de voce com seu convite."
#define C_END1_TXT08	"Isso nao importa..."
#define C_END1_TXT09	"Os demonios nascem como ratos"
#define C_END1_TXT10	"e voce tem o veneno classe AAA"
#define C_END1_TXT11	"da U.A.C. que eles desejam."
#define C_END1_TXT12	"Seu grito sedento por sangue"
#define C_END1_TXT13	"dissipa a neblina do teletransporte."
#define C_END1_TXT14	"Mais uma vez voce se encontra"
#define C_END1_TXT15	"no meio de..."

#define C_END2_TXT01	"O silencio vasto lembra"
#define C_END2_TXT02	"voce do necroterio militar."
#define C_END2_TXT03	" "
#define C_END2_TXT04	"Voce sabia que a instalacao"
#define C_END2_TXT05	"tinha um nivel classificado."
#define C_END2_TXT06	" "
#define C_END2_TXT07	"A U.A.C. tinha alguma boa"
#define C_END2_TXT08	"razao para esconder este lugar."
#define C_END2_TXT09	" "
#define C_END2_TXT10	"Voce se pergunta o que"
#define C_END2_TXT11	"poderia ser..."

#define C_END3_TXT01	"Voce sorri."
#define C_END3_TXT02	" "
#define C_END3_TXT03	"Que lugar estranho voce"
#define C_END3_TXT04	"encontrou?"
#define C_END3_TXT05	" "
#define C_END3_TXT06	"Os demonios nao esperavam"
#define C_END3_TXT07	"que voce sobrevivesse ate aqui."
#define C_END3_TXT08	"Voce sente a presenca demoniaca"
#define C_END3_TXT09	"esperando por voce..."
#define C_END3_TXT10	" "
#define C_END3_TXT11	"Deixe-os provar suas tripas!"

#define C_END4_TXT01	"Voce se contorce enquanto um odor"
#define C_END4_TXT02	"acido e estranho lhe atinge."
#define C_END4_TXT03	" "
#define C_END4_TXT04	"Mortes e carcacas de demonios!"
#define C_END4_TXT05	" "
#define C_END4_TXT06	"Nenhum pesadelo poderia ter"
#define C_END4_TXT07	"preparado voce para isso."
#define C_END4_TXT08	" "
#define C_END4_TXT09	"Voce percebe que este"
#define C_END4_TXT10	"lugar nao foi feito para"
#define C_END4_TXT11	"humanos vivos."

#define C_END5_TXT01	"Parabens!"
#define C_END5_TXT02	"Voce encontrou..."
#define C_END5_TXT03	" "
#define C_END5_TXT04	"CAOTICO"
#define C_END5_TXT05	" "
#define C_END5_TXT06	"Apenas os melhores colherao"
#define C_END5_TXT07	"suas recompensas."

#define C_END6_TXT01	"Finalmente..."
#define C_END6_TXT02	"A mae de todos os demonios"
#define C_END6_TXT03	"esta morta!"
#define C_END6_TXT04	" "
#define C_END6_TXT05	"O sangue escorre dos"
#define C_END6_TXT06	"seus olhos enquanto voce se mantem"
#define C_END6_TXT07	"em desafio."
#define C_END6_TXT08	" "
#define C_END6_TXT09	"Como o unico fuzileiro a"
#define C_END6_TXT10	"sobreviver ao massacre,"
#define C_END6_TXT11	"voce decide ficar"
#define C_END6_TXT12	"no Inferno e garantir que nenhum"
#define C_END6_TXT13	"demonio ressurja novamente."
#define C_END6_TXT14	" "
#define C_END6_TXT15	"Fim."

char *introcluster[] =   // [Immorpher] new intro text adapted from Doom 64 Manual and Doom 64 Reloaded
{
	C_INTRO_TXT01,
	C_INTRO_TXT02,
	C_INTRO_TXT03,
	C_INTRO_TXT04,
	C_INTRO_TXT05,
	C_INTRO_TXT06,
	C_INTRO_TXT07,
	C_INTRO_TXT08,
	C_INTRO_TXT09,
	C_INTRO_TXT10,
	C_INTRO_TXT11,
	C_INTRO_TXT12,
	C_INTRO_TXT13,
	C_INTRO_TXT14,
	C_INTRO_TXT15,
	C_INTRO_TXT16,
	C_INTRO_TXT17,
	C_INTRO_TXT18,
	C_INTRO_TXT19,
	C_INTRO_TXT20,
	T_NULL
};

char *endcluster1[] =   // 8005A2C0
{
	C_END1_TXT01,
	C_END1_TXT02,
	C_END1_TXT03,
	C_END1_TXT04,
	C_END1_TXT05,
	C_END1_TXT06,
	C_END1_TXT07,
	C_END1_TXT08,
	C_END1_TXT09,
	C_END1_TXT10,
	C_END1_TXT11,
	C_END1_TXT12,
	C_END1_TXT13,
	C_END1_TXT14,
	C_END1_TXT15,
	T_NULL
};

char *endcluster2[] =   // 8005A300
{
	C_END2_TXT01,
	C_END2_TXT02,
	C_END2_TXT03,
	C_END2_TXT04,
	C_END2_TXT05,
	C_END2_TXT06,
	C_END2_TXT07,
	C_END2_TXT08,
	C_END2_TXT09,
	C_END2_TXT10,
	C_END2_TXT11,
	T_NULL
};

char *endcluster3[] =   // 8005A330
{
	C_END3_TXT01,
	C_END3_TXT02,
	C_END3_TXT03,
	C_END3_TXT04,
	C_END3_TXT05,
	C_END3_TXT06,
	C_END3_TXT07,
	C_END3_TXT08,
	C_END3_TXT09,
	C_END3_TXT10,
	C_END3_TXT11,
	T_NULL
};

char *endcluster4[] =   // 8005A360
{
	C_END4_TXT01,
	C_END4_TXT02,
	C_END4_TXT03,
	C_END4_TXT04,
	C_END4_TXT05,
	C_END4_TXT06,
	C_END4_TXT07,
	C_END4_TXT08,
	C_END4_TXT09,
	C_END4_TXT10,
	C_END4_TXT11,
	T_NULL
};

char *endcluster5[] =   // 8005A390
{
	C_END5_TXT01,
	C_END5_TXT02,
	C_END5_TXT03,
	C_END5_TXT04,
	C_END5_TXT05,
	C_END5_TXT06,
	C_END5_TXT07,
	T_NULL
};

char *endcluster6[] =   // 8005A3B0
{
	C_END6_TXT01,
	C_END6_TXT02,
	C_END6_TXT03,
	C_END6_TXT04,
	C_END6_TXT05,
	C_END6_TXT06,
	C_END6_TXT07,
	C_END6_TXT08,
	C_END6_TXT09,
	C_END6_TXT10,
	C_END6_TXT11,
	C_END6_TXT12,
	C_END6_TXT13,
	C_END6_TXT14,
	C_END6_TXT15,
	T_NULL
};

//
// Character cast strings F_FINALE.C
//
#define CC_ZOMBIE	"Zombieman"
#define CC_SHOTGUN	"Cara da Espingarda"
#define CC_HEAVY	"Cara da Arma Pesada" // Inimigo Removido
#define CC_IMP		"Diabrete"
#define CC_NIMP		"Diabrete Pesadelo" // Novo Inimigo no Doom64
#define CC_DEMON	"Demonio Touros"
#define CC_SPECT	"Espectro" // Novo Inimigo no Doom64
#define CC_LOST		"Alma Perdida"
#define CC_CACO		"Cacodemonio"
#define CC_HELL		"Cavaleiro Infernal"
#define CC_BARON	"Barao do Inferno"
#define CC_ARACH	"Arachnotron"
#define CC_PAIN		"Elemental da Dor"
#define CC_REVEN	"Revenant" // Inimigo Removido
#define CC_MANCU	"Mancubus"
#define CC_ARCH		"Arqui-Vil" // Inimigo Removido
#define CC_SPIDER	"O Mestre Aranha" // Inimigo Removido
#define CC_CYBER	"O Cyberdemonio"
#define CC_MOTHER	"Demonio Mae"
#define CC_HERO		"Nosso Heroi"

//
// Final DOOM 2 animation
// Casting by id Software.
// in order of appearance
//
typedef struct
{
	char		*name;
	mobjtype_t	type;
} castinfo_t;

static castinfo_t	castorder[] = // 8005A3F0
{
	{ CC_ZOMBIE, MT_POSSESSED1 },// MT_POSSESSED
	{ CC_SHOTGUN, MT_POSSESSED2 },// MT_SHOTGUY
	//{ CC_HEAVY, MT_CHAINGUY },
	{ CC_IMP, MT_IMP1 },// MT_TROOP
	{ CC_NIMP, MT_IMP2 },// MT_TROOP2
	{ CC_DEMON, MT_DEMON1 },// MT_SERGEANT
	{ CC_SPECT, MT_DEMON2 },// MT_SERGEANT2
	{ CC_LOST, MT_SKULL },// MT_SKULL
	{ CC_CACO, MT_CACODEMON },// MT_HEAD
	{ CC_HELL, MT_BRUISER2 },// MT_KNIGHT
	{ CC_BARON, MT_BRUISER1 },// MT_BRUISER
	{ CC_ARACH, MT_BABY },// MT_BABY
	{ CC_PAIN, MT_PAIN },// MT_PAIN
	//{ CC_REVEN, MT_UNDEAD },
	{ CC_MANCU, MT_MANCUBUS },// MT_FATSO
	//{ CC_ARCH, MT_VILE },
	//{ CC_SPIDER, MT_SPIDER },
	{ CC_CYBER, MT_CYBORG },// MT_CYBORG
	{ CC_MOTHER, MT_RESURRECTOR },// MT_CYBORG
	{ CC_HERO, MT_PLAYER },// MT_PLAYER
	{ NULL, 0 }
};

typedef enum
{
	F_STAGE_FADEIN_BACKGROUD,
	F_STAGE_DRAWTEXT,
	F_STAGE_SCROLLTEXT,
	F_STAGE_FADEOUT_BACKGROUD,
	F_STAGE_CAST
} finalestage_t;

static int textypos;			// 800631F0
static int textline;			// 800631F4
static char **text;			    // 800631F8
static int textalpha;			// 800631FC

extern short SwapShort(short dat);

/*
=================
=
= F_StartIntermission
=
=================
*/

void F_StartIntermission(void) // 80002CD0
{
	if (nextmap == 1)
	{
		text = introcluster;
		textypos = 20;
	}
	else if ((gamemap == 8) && (nextmap == 9))
	{
		text = endcluster1;
		textypos = 15;
	}
	else if ((gamemap == 4) && (nextmap == 29))
	{
		text = endcluster2;
		textypos = 43;
	}
	else if ((gamemap == 12) && (nextmap == 30))
	{
		text = endcluster3;
		textypos = 43;
	}
	else if ((gamemap == 18) && (nextmap == 31))
	{
		text = endcluster4;
		textypos = 43;
	}
	else if ((gamemap == 1) && (nextmap == 32))
	{
		text = endcluster5;
		textypos = 71;
	}

	DrawerStatus = 2;
	textline = 0;
	textalpha = 0;
	
	S_StartMusic(116); // [Immorpher] Play menu music for intermission
}

/*
=================
=
= F_StopIntermission
=
=================
*/

void F_StopIntermission(void) // 80002E14
{
	S_StopMusic(); // [Immorpher] stop intermission music
	gamepaused = false;
	DrawerStatus = 0;
	I_WIPE_FadeOutScreen();
}

/*
=================
=
= F_TickerIntermission
=
=================
*/

int F_TickerIntermission(void) // 80002E44
{
	unsigned int buttons, oldbuttons, exit;

	gameaction = ga_nothing;
	P_CheckCheats();

	exit = gameaction;
	if (!gamepaused)
	{
	    buttons = ticbuttons[0] & 0xffff0000;
		oldbuttons = oldticbuttons[0] & 0xffff0000;

	    exit = ga_nothing;

		if(*text[textline])
		{
			textalpha += 8;
			if (textalpha > 255)
			{
				textalpha = 0;
				textline++;
			}
		}
		else if ((buttons != oldbuttons) && (buttons & (ALL_CBUTTONS|ALL_TRIG|PAD_A|PAD_B)))
		{
			exit = ga_exit;
		}
		
		 // [Immorpher] Speed up text intermission by pressing buttons
		if (buttons & (ALL_CBUTTONS|ALL_TRIG|PAD_A|PAD_B))
		{
			textalpha += 256;
		}
	}

	return exit;
}

/*
=================
=
= F_DrawerIntermission
=
=================
*/

void F_DrawerIntermission(void) // 80002F14
{
	int i, ypos;
	I_ClearFrame();

	//gDPPipeSync(GFX1++);
	//gDPSetCycleType(GFX1++, G_CYC_FILL);
	//gDPSetRenderMode(GFX1++,G_RM_NOOP,G_RM_NOOP2);
	//gDPSetColorImage(GFX1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, OS_K0_TO_PHYSICAL(cfb[vid_side]));
	// Fill borders with black
	//gDPSetFillColor(GFX1++, GPACK_RGBA5551(0,0,0,0) << 16 | GPACK_RGBA5551(0,0,0,0)) ;
	//gDPFillRectangle(GFX1++, 0, 0, SCREEN_WD-1, SCREEN_HT-1);

	M_DrawBackground(63, 25, 128, "EVIL", 0.00015f, 0);

	ypos = textypos;
	for(i = 0; i < textline; i++)
	{
		if(runintroduction) {
			ST_Message(20, ypos, text[i], 0xc0c0c0ff);
			//ST_DrawString(-1, ypos, text[i], 0xc0c0c0ff);
			ypos += 10;
		} else {
			ST_DrawString(-1, ypos, text[i], 0xc0c0c0ff);
			ypos += 14;
		}
	}

	if(runintroduction) {
		ST_Message(20, ypos, text[i], PACKRGBA(192, 192*textalpha/255, 192*textalpha/255, textalpha));
		//ST_DrawString(-1, ypos, text[i], textalpha | PACKRGBA(192, 192*textalpha/255, 192*textalpha/255, 0));
	} else {
		ST_DrawString(-1, ypos, text[i], PACKRGBA(192, 192*textalpha/255, 192*textalpha/255, textalpha));
	}

	if (MenuCall)
	{
		M_DrawOverlay(0, 0, 320, 240, 96);
		MenuCall();
	}

	I_DrawFrame();
}

static finalestage_t	finalestage;	// 80063200
static int				castnum;		// 80063204
static int				casttics;		// 80063208
static state_t         *caststate;		// 8006320C
static boolean			castdeath;		// 80063210
static int				castframes;		// 80063214
static int				castonmelee;	// 80063218
static int              castrotation;   // 8006321C
static int              castfadein;     // 80063220
static int              fadeinout;      // 80063224

/*
=================
=
= F_Start/Cast_Start
=
=================
*/

void F_Start(void) // 8000313C
{
	DrawerStatus = 3;
	finalestage = F_STAGE_FADEIN_BACKGROUD;
	fadeinout = 0;
	textypos = 15;
	textline = 0;
	textalpha = 0;
	castnum = 0;
	caststate = &states[mobjinfo[castorder[castnum].type].seestate];
	casttics = states[mobjinfo[castorder[castnum].type].seestate].tics;
	castdeath = false;
	castframes = 0;
	castonmelee = 0;
	castrotation = 0;
	castfadein = 0;

	S_StartMusic(113);
}


/*
=================
=
= F_Ticker/Cast_Ticker
=
=================
*/

int F_Ticker(void) // 80003258
{
	unsigned int buttons, oldbuttons;
	int	st, sfx;

	buttons = ticbuttons[0] = M_ButtonResponder(ticbuttons[0]);
	oldbuttons = oldticbuttons[0] & 0xffff0000;

	gameaction = ga_nothing;
	P_CheckCheats();

	if (gamepaused != 0)
	{
		return gameaction;
	}

	switch(finalestage)
	{
		case F_STAGE_FADEIN_BACKGROUD:
			fadeinout += 6;
			if (fadeinout > 160)
			{
				fadeinout = 160;
				finalestage = F_STAGE_DRAWTEXT;
			}
			break;

		case F_STAGE_DRAWTEXT:
			if (*endcluster6[textline])
			{
				textalpha += 8;
				if (textalpha > 255)
				{
					textalpha = 0;
					textline++;
				}
			}
			else
			{
				finalestage = F_STAGE_SCROLLTEXT;
			}
			break;

		case F_STAGE_SCROLLTEXT:
			textypos -= 1;
			if (textypos < -200)
			{
				finalestage = F_STAGE_FADEOUT_BACKGROUD;
			}
			break;

		case F_STAGE_FADEOUT_BACKGROUD:
			fadeinout -= 6;
			if (fadeinout < 0)
			{
				fadeinout = 0;
				finalestage = F_STAGE_CAST;
			}
			break;

		case F_STAGE_CAST:
			fadeinout += 6;
			if (fadeinout > 128)
			{
				fadeinout = 128;
			}

			if (castdeath == false)
			{
			    if (buttons != oldbuttons)
			    {
			        if (buttons & PAD_LEFT)
					{
						castrotation += 1;
						if (castrotation > 7) {
							castrotation = 0;
						}
					}
					else if (buttons & PAD_RIGHT)
					{
						castrotation -= 1;
						if (castrotation < 0) {
							castrotation = 7;
						}
					}
					else if (buttons & (ALL_CBUTTONS|ALL_TRIG|PAD_A|PAD_B))
					{
						S_StartSound(NULL, sfx_shotgun); // sfx_shotgn

						/* go into death frame */
						if (mobjinfo[castorder[castnum].type].deathsound)
							S_StartSound(NULL, mobjinfo[castorder[castnum].type].deathsound);

						caststate = &states[mobjinfo[castorder[castnum].type].deathstate];
						castframes = 0;
						castdeath = true;

						if(castorder[castnum].type == MT_CYBORG) {
							casttics = 10;
						}
						else {
							casttics = caststate->tics;
						}

					}
			    }
			}

			if (gametic > gamevbls)
			{
				if (castfadein < 192) {
					castfadein += 2;
				} else {
					castfadein = 255;
				}

				/* advance state*/
				if (--casttics > 0)
					return ga_nothing;  /* not time to change state yet */

				if (castdeath && caststate->nextstate == S_000) // S_NULL
				{
					/* switch from deathstate to next monster */
					castrotation = 0;
					castnum++;
					castfadein = 0;
					castdeath = false;

					if (castorder[castnum].name == NULL)
						castnum = 0;

					if (mobjinfo[castorder[castnum].type].seesound)
						S_StartSound(NULL, mobjinfo[castorder[castnum].type].seesound);

					caststate = &states[mobjinfo[castorder[castnum].type].seestate];
					castframes = 0;
				}

				st = caststate->nextstate;
				caststate = &states[st];

				if (castdeath == false)
				{
					castframes++;

					if (castframes == 12)
					{   /* go into attack frame */
						if (castonmelee)
							caststate = &states[mobjinfo[castorder[castnum].type].meleestate];
						else
							caststate = &states[mobjinfo[castorder[castnum].type].missilestate];

						castonmelee ^= 1;

						if (caststate == &states[S_000]) // S_NULL
						{
							if (castonmelee)
								caststate = &states[mobjinfo[castorder[castnum].type].meleestate];
							else
								caststate = &states[mobjinfo[castorder[castnum].type].missilestate];
						}
					}

					if (((castframes == 20) && (castorder[castnum].type == MT_MANCUBUS)) ||
						  castframes == 24 || caststate == &states[S_001])//S_PLAY
					{
						caststate = &states[mobjinfo[castorder[castnum].type].seestate];
						castframes = 0;
					}
				}

				casttics = caststate->tics;
				if (casttics == -1)
					casttics = TICRATE;

				/* sound hacks.... */
				st = ((uintptr_t)caststate - (uintptr_t)states) / sizeof(state_t);
				switch (st)
				{
					case S_007: // S_PLAY_ATK2
						sfx = sfx_sht2fire; // sfx_dshtgn
						break;

					case S_055: // S_SARG_ATK2
						sfx = sfx_sargatk; // sfx_sgtatk
						break;

					case S_084: // S_FATT_ATK8
					case S_086: // S_FATT_ATK5
					case S_088: // S_FATT_ATK2
						sfx = sfx_bdmissile; // sfx_firsht
						break;

					case S_109: // S_POSS_ATK2
						sfx = sfx_pistol;
						break;

					case S_138: // S_SPOS_ATK2
						sfx = sfx_shotgun; // sfx_shotgn
						break;

					case S_166:   // S_TROO_ATK3
						sfx = sfx_scratch; // sfx_claw
						break;

					case S_169: // S_TROO_ATK
					case S_199: // S_HEAD_ATK2
					case S_222: // S_BOSS_ATK2
					case S_243: // S_BOS2_ATK2
						sfx = sfx_bdmissile; // sfx_firsht
						break;

					case S_261: // S_SKULL_ATK2
						sfx = sfx_skullatk; // sfx_sklatk
						break;

					case S_288: // S_BSPI_ATK2
						sfx = sfx_plasma; // sfx_plasma
						break;

					case S_307: // S_CYBER_ATK2
					case S_309: // S_CYBER_ATK4
					case S_311: // S_CYBER_ATK6
						sfx = sfx_missile; // sfx_rlaunc
						break;

					case S_328: // S_PAIN_ATK3
						sfx = sfx_skullatk; // sfx_sklatk
						break;

					//case S_VILE_ATK2:
						//sfx = sfx_vilatk;
						//break;

					//case S_SKEL_FIST2:
						//sfx = sfx_skeswg;
						//break;

					//case S_SKEL_FIST4:
						//sfx = sfx_skepch;
						//break;

					//case S_SKEL_MISS2:
						//sfx = sfx_skeatk;
						//break;

					//case S_CPOS_ATK2:
					//case S_CPOS_ATK3:
					//case S_CPOS_ATK4:
						//sfx = sfx_pistol;
						//break;

					//case S_SPID_ATK2:
					//case S_SPID_ATK3:
						//sfx = sfx_pistol;
						//break;

					default:
						sfx = 0;
						break;
				}

				if (sfx)
					S_StartSound(NULL, sfx);
			}

			break;

		default:
			break;
	}

	return ga_nothing;
}

/*
=================
=
= F_Drawer/Cast_Drawer
=
=================
*/
void F_Drawer(void) // 800039DC
{
	int i, type, alpha, ypos;

	I_ClearFrame();

	switch(finalestage)
	{
		case F_STAGE_FADEIN_BACKGROUD:
		case F_STAGE_FADEOUT_BACKGROUD:
			M_DrawBackground(0, 0, fadeinout, "FINAL", 0.00015f, 0);
			break;

		case F_STAGE_DRAWTEXT:
		case F_STAGE_SCROLLTEXT:
			M_DrawBackground(0, 0, fadeinout, "FINAL", 0.00015f, 0);

			ypos = textypos;
			for(i = 0; i < textline; i++)
			{
				ST_DrawString(-1, ypos, endcluster6[i], 0xc0c0c0ff);
				ypos += 14;
			}

			ST_DrawString(-1, ypos, endcluster6[i], textalpha | 0xc0c0c000);
			break;

		case F_STAGE_CAST:
			M_DrawBackground(63, 25, fadeinout, "EVIL", 0.00015f, 0);

			type = castorder[castnum].type;

			if (type == MT_DEMON2){
				alpha = 48;
			}
			else {
				alpha = mobjinfo[type].alpha;
			}

			BufferedDrawSprite(type, caststate, castrotation,
							   PACKRGBA(castfadein, castfadein, castfadein, alpha), 160, 190);

			ST_DrawString(-1, 208, castorder[castnum].name, 0xC00000ff);
			break;

		default:
			break;
	}

	if (MenuCall)
	{
		M_DrawOverlay(0, 0, 320, 240, 96);
		MenuCall();
	}

	I_DrawFrame();
}

extern float *all_u;
extern float *all_v;
extern pvr_poly_hdr_t **headers_for_sprites;

static inline uint32_t np2(uint32_t v) {
	v--;
	v |= v >> 1;
	v |= v >> 2;
	v |= v >> 4;
	v |= v >> 8;
	v |= v >> 16;
	v++;
	return v;
}
extern pvr_ptr_t pvr_troo[MAX_CACHED_SPRITES];
extern pvr_poly_hdr_t hdr_troo[MAX_CACHED_SPRITES];
extern pvr_poly_cxt_t cxt_troo[MAX_CACHED_SPRITES];
extern uint8_t __attribute__((aligned(32))) tmptroo[256*256];
extern int lump_frame[575 + 310];
extern int used_lumps[575 + 310];
extern int used_lump_idx;
extern int del_idx;
extern int total_cached_vram;
extern int last_flush_frame;

typedef enum {
	sarg,
	playa,
	troo,
	boss,
	fatt,
	skul,
	pain,
	bspi,
	poss,
	head,
	cybr,
	rect,
	spec,
	ply1,
	ply2,
	nite,
	baro,
	zomb,
} finale_cast_t;

static int get_monster_start_lump(finale_cast_t monster) {
	switch (monster) {
		case sarg: return 349;
		case playa: return 398;
		case troo: return 450;
		case boss: return 520;
		case fatt: return 567;
		case skul: return 619;
		case pain: return 660;
		case bspi: return 689;
		case poss: return 727;
		case head: return 777;
		case cybr: return 819;
		case rect: return 877;

		case spec: return 1;
		case ply1: return 47;
		case ply2: return 97;
		case nite: return 147;
		case baro: return 215;
		case zomb: return 261;

		default: return -1;
	}
}

static int get_num_monster_lumps(finale_cast_t monster) {
	switch (monster) {
		case sarg: return 46;
		case playa: return 50;
		case troo: return 68;
		case boss: return 46;
		case fatt: return 51;
		case skul: return 40;
		case pain: return 28;
		case bspi: return 36;
		case poss: return 49;
		case head: return 41;
		case cybr: return 57;
		case rect: return 47;
		case spec: return 46;
		case ply1: return 50;
		case ply2: return 50;
		case nite: return 68;
		case baro: return 46;
		case zomb: return 49;
		default: return -1;
	}
}

static finale_cast_t get_monster(int lump) {
	if (lump >= 349 && lump <= 394) return sarg;
	else if (lump >= 398 && lump <= 447) return playa;
	else if (lump >= 450 && lump <= 517) return troo;
	else if (lump >= 520 && lump <= 565) return boss;
	else if (lump >= 567 && lump <= 617) return fatt;
	else if (lump >= 619 && lump <= 658) return skul;
	else if (lump >= 660 && lump <= 687) return pain;
	else if (lump >= 689 && lump <= 724) return bspi;
	else if (lump >= 727 && lump <= 775) return poss;
	else if (lump >= 777 && lump <= 817) return head;
	else if (lump >= 819 && lump <= 875) return cybr;
	else if (lump >= 877 && lump <= 923) return rect;

	else if (lump >= 1 && lump <= 46) return spec;
	else if (lump >= 47 && lump <= 96) return ply1;
	else if (lump >= 97 && lump <= 146) return ply2;
	else if (lump >= 147 && lump <= 214) return nite;
	else if (lump >= 215 && lump <= 260) return baro;
	else if (lump >= 261 && lump <= 309) return zomb;

	else return -1;
}

static finale_cast_t cached_yet = -1;

void BufferedDrawSprite(int type, state_t *state, int rotframe, int color, int xpos, int ypos) // 80003D1C
{
	float xl;
	float xh;
	float yl;
	float yh;
	float u0, v0, u1, v1;
	int wp2;
	int hp2;
	spritedef_t *sprdef;
	spriteframe_t *sprframe;
	int lump;
	boolean flip;

	byte *data;

	int compressed;
	int height;
	int width;
	int xoffs;
	int yoffs;

	pvr_vertex_t __attribute__((aligned(32))) verts[4];
	for (int vn = 0; vn < 4; vn++) {
		verts[vn].z = 5.0f;
		verts[vn].argb = (color & 0xff000000) | 0x00ffffff; // D64_PVR_PACK_COLOR(cr,255,255,255);
		verts[vn].oargb = 0xff000000; // PVR_PACK_COLOR(1.0, 0.0, 0.0, 0.0);
		verts[vn].flags = PVR_CMD_VERTEX;
	}
	verts[3].flags = PVR_CMD_VERTEX_EOL;

	// draw the current frame in the middle of the screen
	sprdef = &sprites[state->sprite];
	sprframe = &sprdef->spriteframes[state->frame & FF_FRAMEMASK];
	lump = sprframe->lump[rotframe];
	flip = (boolean)sprframe->flip[rotframe];

	data = W_CacheLumpNum(lump, PU_CACHE, dec_jag);

	compressed = SwapShort(((spriteN64_t*)data)->compressed);
	width = SwapShort(((spriteN64_t*)data)->width);
	height = SwapShort(((spriteN64_t*)data)->height);
	xoffs = SwapShort(((spriteN64_t*)data)->xoffs);
	yoffs = SwapShort(((spriteN64_t*)data)->yoffs);

	pvr_poly_hdr_t *theheader;

	if ((lump <= 348) || ((lump >= 924) && (lump <= 965))) {
		// pull in each side of sprite by half pixel
		// fix for filtering 'crud' around the edge due to lack of padding
		if(!flip) {
			u0 = all_u[lump] + halfinv1024;
			u1 = all_u[lump] + (((float)width - 0.5f)*inv1024);
		} else {
			u1 = all_u[lump] + halfinv1024;
			u0 = all_u[lump] + (((float)width - 0.5f)*inv1024);
		}
		v0 = all_v[lump] + halfinv1024;
		v1 = all_v[lump] + (((float)height-0.5f)*inv1024);
		
		theheader = headers_for_sprites[lump];
	} else {
		wp2 = np2(width);
		hp2 = np2(height);

		int external_pal = 0;
		if (compressed < 0) {
			int cmpsize = SwapShort(((spriteN64_t*)data)->cmpsize);
			if (cmpsize & 1) {
				external_pal = 1;
			}
		}

		finale_cast_t cur_monster = get_monster(lump);
		int monster_lump = lump;

		if (external_pal && mobjinfo[type].palette) {
			int newlumpnum;
			char *lumpname = W_GetNameForNum(lump);

			if (lumpname[0] == 'T') { // troo
				lumpname[0] = 'N';
				lumpname[1] = 'I';
				lumpname[2] = 'T';
				lumpname[3] = 'E';
			} else if(lumpname[0] == 'S') { // sarg
				lumpname[1] = 'P';
				lumpname[2] = 'E';
				lumpname[3] = 'C';
			} else if(lumpname[0] == 'B') { // boss
				lumpname[1] = 'A';
				lumpname[2] = 'R';
				lumpname[3] = 'O';
			} else if (lumpname[0] == 'P' && lumpname[1] == 'O') { // poss
				lumpname[0] = 'Z';
				lumpname[2] = 'M';
				lumpname[3] = 'B';
			}

			newlumpnum = W_S2_GetNumForName(lumpname);
			monster_lump = newlumpnum;

			cur_monster = get_monster(newlumpnum);
		}


		int start_mlump = get_monster_start_lump(cur_monster);

		// must cache every lump when a new monster is requested, they can't be loaded fast enough
		// if they reload every single frame
		if (cached_yet != cur_monster) {
			if (cached_yet != -1) {
				int num_mlump = get_num_monster_lumps(cached_yet);
				for (int i=0;i<num_mlump;i++) {
					if (pvr_troo[i]) {
						pvr_mem_free(pvr_troo[i]);
						pvr_troo[i] = 0;
					}
				}
			}
			cached_yet = cur_monster;
			

			int num_mlump = get_num_monster_lumps(cur_monster);
			for (int nm=0;nm<num_mlump;nm++) {
				void *mdata; void *msrc;
				int mwidth,mheight,mwp2,mhp2;
				if (start_mlump > 348) {
					mdata = W_CacheLumpNum(start_mlump + nm, PU_CACHE, dec_jag);
				} else {
					mdata = W_S2_CacheLumpNum(start_mlump + nm, PU_CACHE, dec_jag);
				}
				mwidth = SwapShort(((spriteN64_t*)mdata)->width);
				mheight = SwapShort(((spriteN64_t*)mdata)->height);
				mwp2 = np2(mwidth);
				mhp2 = np2(mheight);
				msrc = mdata + sizeof(spriteN64_t);
				pvr_troo[nm] = pvr_mem_malloc(mwp2*mhp2);
				pvr_poly_cxt_txr(&cxt_troo[nm], PVR_LIST_TR_POLY, PVR_TXRFMT_PAL8BPP | PVR_TXRFMT_8BPP_PAL(0) | PVR_TXRFMT_TWIDDLED, mwp2, mhp2, pvr_troo[nm], PVR_FILTER_NONE);
				pvr_poly_compile(&hdr_troo[nm], &cxt_troo[nm]);
				pvr_txr_load(msrc, pvr_troo[nm], mwp2*mhp2);
			}
		}

		theheader = &hdr_troo[monster_lump - start_mlump];

		if (!flip) {
			u0 = 0.0f;
			u1 = (float)width / (float)wp2;
		} else {
			u1 = 0.0f;
			u0 = (float)width / (float)wp2;
		}
		v0 = 0.0f;
		v1 = (float)height / (float)hp2;
	}
	
	if (!flip) {
		xl = (float)(xpos - xoffs) * (float)RES_RATIO;
		xh = xl + ((float)width * (float)RES_RATIO);
	} else {
		xh = (float)(xpos + xoffs) * (float)RES_RATIO;
		xl = xh - ((float)width * (float)RES_RATIO);
	}
	yl = (float)(ypos - yoffs) * (float)RES_RATIO;
	yh = yl + ((float)height * (float)RES_RATIO);
	
	pvr_vertex_t *vert = verts;
	vert->x = xl;
	vert->y = yh;
	vert->u = u0;
	vert->v = v1;
	vert++;

	vert->x = xl;
	vert->y = yl;
	vert->u = u0;
	vert->v = v0;
	vert++;

	vert->x = xh;
	vert->y = yh;
	vert->u = u1;
	vert->v = v1;
	vert++;

	vert->x = xh;
	vert->y = yl;
	vert->u = u1;
	vert->v = v0;

	pvr_list_prim(PVR_LIST_TR_POLY, theheader, sizeof(pvr_poly_hdr_t));
	pvr_list_prim(PVR_LIST_TR_POLY, &verts, sizeof(verts));

	globallump = -1;
}

/*
=================
=
= F_Stop/Cast_Stop
=
=================
*/

void F_Stop(void) // 80003220
{
	gamepaused = false;
	DrawerStatus = 0;
	S_StopMusic();
	I_WIPE_FadeOutScreen();
	int num_mlump = get_num_monster_lumps(cached_yet);
	for (int i=0;i<num_mlump;i++) {
		if (pvr_troo[i]) {
			pvr_mem_free(pvr_troo[i]);
			pvr_troo[i] = 0;
		}
	}
}
