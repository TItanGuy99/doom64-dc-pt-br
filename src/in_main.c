
/* in_main.c -- intermission */

#include "doomdef.h"
#include "st_main.h"
#include "r_local.h"

extern int nextmap;

#define T_NULL	    ""

#define MI_TXT01    "Area Inicial"
#define MI_TXT02    "Terraformador"
#define MI_TXT03    "Engenharia"
#define MI_TXT04    "Area de Retencao"
#define MI_TXT05    "Centro Tech"
#define MI_TXT06    "Quadrante Alpha"
#define MI_TXT07    "Lab Pesquisa"
#define MI_TXT08    "Ultimo Posto"
#define MI_TXT09    "Ainda Mais Simples"
#define MI_TXT10    "Sangramento"
#define MI_TXT11    "Nucleo do Terror"
#define MI_TXT12    "Altar da Dor"
#define MI_TXT13    "Cidadela Escura"
#define MI_TXT14    "Olho da Tempestade"
#define MI_TXT15    "Entradas Escuras"
#define MI_TXT16    "Fortaleza de Sangue"
#define MI_TXT17    "Cuidado Onde Pisa"
#define MI_TXT18    "Medo Criado"
#define MI_TXT19    "A Espiral"
#define MI_TXT20    "Colapso"
#define MI_TXT21    "Armadilhas"
#define MI_TXT22    "Ofertas Queimadas"
#define MI_TXT23    "Templo Profano"
#define MI_TXT24    "Sem Fuga"
#define MI_TXT25    "Gato e Rato"
#define MI_TXT26    "Nucleo Duro"
#define MI_TXT27    "Playground"
#define MI_TXT28    "A Absolucao"
#define MI_TXT29    "Posto Omega"
#define MI_TXT30    "O Covil"
#define MI_TXT31    "No Vazio"
#define MI_TXT32    "Agitado"
#define MI_TXT33    "TITULO"

mapinfo_t MapInfo[] = //8005A478
{
    {T_NULL , 0},
    {MI_TXT01 , 96},
    {MI_TXT02 , 97},
    {MI_TXT03 , 105},
    {MI_TXT04 , 104},
    {MI_TXT05 , 101},
    {MI_TXT06 , 107},
    {MI_TXT07 , 108},
    {MI_TXT08 , 110},
    {MI_TXT09 , 95},
    {MI_TXT10 , 98},
    {MI_TXT11 , 99},
    {MI_TXT12 , 102},
    {MI_TXT13 , 93},
    {MI_TXT14 , 106},
    {MI_TXT15 , 111},
    {MI_TXT16 , 97},
    {MI_TXT17 , 103},
    {MI_TXT18 , 94},
    {MI_TXT19 , 100},
    {MI_TXT20 , 112},
    {MI_TXT21 , 109},
    {MI_TXT22 , 101},
    {MI_TXT23 , 108},
    {MI_TXT24 , 98},
    {MI_TXT25 , 97},
    {MI_TXT26 , 98},
    {MI_TXT27 , 94},
    {MI_TXT28 , 99},
    {MI_TXT29 , 101},
    {MI_TXT30 , 102},
    {MI_TXT31 , 103},
    {MI_TXT32 , 104},
    {MI_TXT33 , 115},
    {T_NULL , 0}
};

typedef struct pstats_s
{
	int		killpercent;
	int		itempercent;
	int		secretpercent;
} pstats_t;

int			killvalue, itemvalue, secretvalue; // 800633B8, 800633BC, 800633C0
pstats_t	pstats; // 800633C4

// used to accelerate or skip a stage
int acceleratestage; // 800633B0
int nextstage;       // 800633B4

char timetext[16];  // 800633D0
int start_time;     // 80063390
int end_time;       // 80063394

void IN_Start(void) // 80004AF0
{
	int time;

    killvalue = itemvalue = secretvalue = -1;

    if (totalkills)
        pstats.killpercent = (players[0].killcount * 100) / totalkills;
    else
        pstats.killpercent = 100;

    if (totalitems)
        pstats.itempercent = (players[0].itemcount * 100) / totalitems;
    else
        pstats.itempercent = 100;

    if (totalsecret)
        pstats.secretpercent = (players[0].secretcount * 100) / totalsecret;
    else
        pstats.secretpercent = 100;

    time = (unsigned int)(end_time - start_time) / 60;

    if ((time / 60) < 60) {
        sprintf(timetext, "%2.2d:%2.2d", (time / 60), (time % 60));
    }
    else {
        D_memmove(timetext, "--:--");
    }

    nextstage = 0;
	acceleratestage = 0;
	last_ticon = 0;
	text_alpha = 255;

    if ((nextmap >= 2) && (nextmap < LASTLEVEL))
	{
		M_EncodePassword(Passwordbuff);
        CurPasswordSlot = 16;
	}

	S_StartMusic(114);
}

void IN_Stop(void) // 80004DB0
{
	S_StopMusic();

    if ((nextmap >= 2) && (nextmap < LASTLEVEL))
    {
        if (EnableExpPak) {
            MiniLoop(M_SavePakStart,M_SavePakStop,M_SavePakTicker,M_SavePakDrawer);
        }
    }

    I_WIPE_FadeOutScreen();
}

int IN_Ticker(void) // 80004E24
{
	boolean state;
	int buttons, oldbuttons;

    buttons = ticbuttons[0] & 0xffff0000;
    oldbuttons = oldticbuttons[0] & 0xffff0000;

    if ((buttons != oldbuttons) && (buttons & (PAD_A|PAD_B|PAD_START|ALL_TRIG|ALL_CBUTTONS)))
    {
        acceleratestage++;
        if (acceleratestage == 1)
        {
            killvalue = pstats.killpercent;
            itemvalue = pstats.itempercent;
            secretvalue = pstats.secretpercent;
            nextstage = 5;
            last_ticon = 0;
            S_StartSound(NULL, sfx_explode);
        }
        else if (acceleratestage >= 2)
        {
            S_StartSound(NULL, sfx_explode);
            return ga_exit;
        }
    }

    if (last_ticon)
    {
        if ((ticon - last_ticon) <= 90) // 3 * TICRATE
            return ga_nothing;
    }

    state = false;

    switch(nextstage)
    {
        case 0:
            S_StartSound(NULL, sfx_explode);
            nextstage = 1;
            break;

        case 1: // kills
            killvalue += 4;
            if (killvalue > pstats.killpercent)
            {
                S_StartSound(NULL, sfx_explode);
                killvalue = pstats.killpercent;
                last_ticon = ticon;
                nextstage = 2;
            }
            else {
                state = true;
            }
            break;

        case 2: // item
            itemvalue += 4;
            if (itemvalue > pstats.itempercent)
            {
                S_StartSound(NULL, sfx_explode);
                itemvalue = pstats.itempercent;
                last_ticon = ticon;
                nextstage = 3;
            }
            else {
                state = true;
            }
            break;

        case 3: // secret
            secretvalue += 4;
            if (secretvalue > pstats.secretpercent)
            {
                S_StartSound(NULL, sfx_explode);
                secretvalue = pstats.secretpercent;
                last_ticon = ticon;
                nextstage = 4;
            }
            else {
                state = true;
            }
            break;

        case 4:
            S_StartSound(NULL, sfx_explode);
            last_ticon = ticon;
            nextstage = 5;
            break;
    }

    if (!state && (acceleratestage == 0))
    {
        if (nextstage == 5) {
            acceleratestage = 1;
        }
    }

    // Play Sound sfx_pistol
    if (!(gametic & 3) && state)
    {
        S_StartSound(NULL, sfx_pistol);
    }

	return ga_nothing;
}

void IN_Drawer(void) // 80005164
{
	int i, c;
	char password[32];
	char *pbuff;

	I_ClearFrame();

	//gDPPipeSync(GFX1++);
	//gDPSetCycleType(GFX1++, G_CYC_FILL);
	//gDPSetRenderMode(GFX1++, G_RM_NOOP, G_RM_NOOP2);
	//gDPSetColorImage(GFX1++, G_IM_FMT_RGBA, G_IM_SIZ_16b, SCREEN_WD, OS_K0_TO_PHYSICAL(cfb[vid_side]));
	// Fill borders with black
    //gDPSetFillColor(GFX1++, GPACK_RGBA5551(0,0,0,0) << 16 | GPACK_RGBA5551(0,0,0,0)) ;
    //gDPFillRectangle(GFX1++, 0, 0, SCREEN_WD-1, SCREEN_HT-1);
pvr_set_bg_color(0,0,0);
pvr_fog_table_color(0.0f,0.0f,0.0f,0.0f);

	M_DrawBackground(63, 25, 128, "MAL", 0.00015f, 0);

	ST_DrawString(-1, 20, MapInfo[gamemap].name, PACKRGBA(255, 255, 255, text_alpha));

	ST_DrawString(-1, 36, "Finalizado", PACKRGBA(255, 255, 255, text_alpha));

    if ((nextstage > 0) && (killvalue > -1))
    {
        ST_DrawString(57, 60, "Mortes", PACKRGBA(192, 0, 0, text_alpha));
        ST_DrawString(248, 60, "%", PACKRGBA(192, 0, 0, text_alpha));
        ST_DrawNumber(210, 60, killvalue, 1, PACKRGBA(192, 0, 0, text_alpha));
    }

    if ((nextstage > 1) && (itemvalue > -1))
    {
        ST_DrawString(57, 78, "Itens", PACKRGBA(192, 0, 0, text_alpha));
        ST_DrawString(248, 78, "%", PACKRGBA(192, 0, 0, text_alpha));
        ST_DrawNumber(210, 78, itemvalue, 1, PACKRGBA(192, 0, 0, text_alpha));
    }

    if ((nextstage > 2) && (secretvalue > -1))
    {
        ST_DrawString(57, 99, "Segredos", PACKRGBA(192, 0, 0, text_alpha));
        ST_DrawString(248, 99, "%", PACKRGBA(192, 0, 0, text_alpha));
        ST_DrawNumber(210, 99, secretvalue, 1, PACKRGBA(192, 0, 0, text_alpha));
    }

    if ((nextstage > 3))
    {
        ST_DrawString(57, 120, "Tempo", PACKRGBA(192, 0, 0, text_alpha));
        ST_DrawString(210, 120, timetext, PACKRGBA(192, 0, 0, text_alpha));
    }

	if ((nextstage > 4) && (nextmap < LASTLEVEL))
	{
        ST_DrawString(-1, 145, "Entrando", PACKRGBA(255, 255, 255, text_alpha));
        ST_DrawString(-1, 161, MapInfo[nextmap].name, PACKRGBA(255, 255, 255, text_alpha));

        ST_DrawString(-1, 187, "Senha", PACKRGBA(255, 255, 255, text_alpha));

        pbuff = password;
		for (i = 0; i < 16; i++)
		{
            c = i & 3;
            if ((i < 0) && (c != 0)) {
                c -= 4;
            }
            if (c == 0) {
                *pbuff++ = ' ';
            }

			*pbuff++ = passwordChar[Passwordbuff[i]];
		}
		*pbuff = 0;

		ST_DrawString(-1, 203, password, PACKRGBA(255, 255, 255, text_alpha));
	}

	I_DrawFrame();
}
