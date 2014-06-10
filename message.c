/* unofficial gameplaySP kai
 *
 * Copyright (C) 2006 Exophase <exophase@gmail.com>
 * Copyright (C) 2007 takka <takka@tfact.net>
 *
 * This program is free software; you can redistribute it and/or
 * modify it under the terms of the GNU General Public License as
 * published by the Free Software Foundation; either version 2 of
 * the License, or (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the GNU
 * General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program; if not, write to the Free Software
 * Foundation, Inc., 51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA
 */

#include "common.h"

const char *message[MSG_END] =
{
    // MSG_BROWSER_HELP
    "Åõ:Select  Å~:Menu  Å :" FONT_UP_DIRECTORY,

    // MSG_MENU_DATE_FMT_0
    "%4d/%2d/%2d %-3s %2d:%02d",

    // MSG_MENU_DATE_FMT_1
    "%2d/%2d/%4d %-3s %2d:%02d",

    // MSG_MAIN_MENU_TITLE
    "Menu",

    // MSG_MAIN_MENU_0
    "Load state : SLOT %d",

    // MSG_MAIN_MENU_1
    "Save state : SLOT %d",

    // MSG_MAIN_MENU_2
    "Savestate details " FONT_R_TRIGGER,

    // MSG_MAIN_MENU_3
    "Screen capture : %s",

    // MSG_MAIN_MENU_4
    "Emulator options",

    // MSG_MAIN_MENU_5
    "Gamepad config",

    // MSG_MAIN_MENU_6
    "Analog stick config",

    // MSG_MAIN_MENU_7
    "Load game " FONT_L_TRIGGER,

    // MSG_MAIN_MENU_8
    "Reset",

    // MSG_MAIN_MENU_9
    "Return to game",

    // MSG_MAIN_MENU_10
    "Sleep",

    // MSG_MAIN_MENU_11
    "Exit TempGBA",

    // MSG_MAIN_MENU_HELP_0
    "Åõ:Load  " FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select slot",

    // MSG_MAIN_MENU_HELP_1
    "Åõ:Save  " FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select slot",

    // MSG_MAIN_MENU_HELP_2
    "Åõ:Sub menu  " FONT_R_TRIGGER ":Shortcut key",

    // MSG_MAIN_MENU_HELP_3
    "Åõ:Save Image  " FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select image format",

    // MSG_MAIN_MENU_HELP_4
    "Åõ:Sub menu",

    // MSG_MAIN_MENU_HELP_5
    "Åõ:Sub menu",

    // MSG_MAIN_MENU_HELP_6
    "Åõ:Sub menu",

    // MSG_MAIN_MENU_HELP_7
    "Åõ:File browser  " FONT_L_TRIGGER ":Shortcut key",

    // MSG_MAIN_MENU_HELP_8
    "Åõ:Reset game",

    // MSG_MAIN_MENU_HELP_9
    "Åõ:Return to game",

    // MSG_MAIN_MENU_HELP_10
    "Åõ:Sleep mode",

    // MSG_MAIN_MENU_HELP_11
    "Åõ:Exit",

    // MSG_OPTION_MENU_TITLE
    "Emulator options",

    // MSG_OPTION_MENU_0
    "Display mode    : %s",

    // MSG_OPTION_MENU_1
    "Magnification   : %d%%",

    // MSG_OPTION_MENU_2
    "Bilinear filter : %s",

    // MSG_OPTION_MENU_3
    "Frameskip type  : %s",

    // MSG_OPTION_MENU_4
    "Frameskip value : %d",

    // MSG_OPTION_MENU_5
    "CPU clock freq  : %s",

    // MSG_OPTION_MENU_6
    "Sound volume    : %s",

    // MSG_OPTION_MENU_7
    "Stack optimize  : %s",

    // MSG_OPTION_MENU_8
    "Boot from BIOS  : %s",

    // MSG_OPTION_MENU_9
    "Update backup   : %s",

    // MSG_OPTION_MENU_10
    "Language        : %s",

    // MSG_OPTION_MENU_11
    "Back",

    // MSG_OPTION_MENU_HELP_0
    FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select   all games",

    // MSG_OPTION_MENU_HELP_1
    FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select   all games",

    // MSG_OPTION_MENU_HELP_2
    FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select   all games",

    // MSG_OPTION_MENU_HELP_3
    FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select   each games",

    // MSG_OPTION_MENU_HELP_4
    FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select   each games",

    // MSG_OPTION_MENU_HELP_5
    FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select   each games",

    // MSG_OPTION_MENU_HELP_6
    FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select   all games",

    // MSG_OPTION_MENU_HELP_7
    FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select   all games",

    // MSG_OPTION_MENU_HELP_8
    FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select   all games",

    // MSG_OPTION_MENU_HELP_9
    FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select   all games",

    // MSG_OPTION_MENU_HELP_10
    FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select   all games",

    // MSG_OPTION_MENU_HELP_11
    "Åõ:Main menu",

    // MSG_STATE_MENU_DATE_FMT_0
    "%4d/%2d/%2d %-3s %2d:%02d:%02d",

    // MSG_STATE_MENU_DATE_FMT_1
    "%2d/%2d/%4d %-3s %2d:%02d:%02d",

    // MSG_STATE_MENU_DATE_NONE_0
    "----/--/-- --- --:--:--",

    // MSG_STATE_MENU_DATE_NONE_1
    "--/--/---- --- --:--:--",

    // MSG_STATE_MENU_STATE_NONE
    "No data in this slot",

    // MSG_STATE_MENU_TITLE
    "Savestate",

    // MSG_STATE_MENU_0
    "",

    // MSG_STATE_MENU_1
    "Load state from file",

    // MSG_STATE_MENU_2
    "Back",

    // MSG_STATE_MENU_HELP_0
    "Åõ:Execute  " FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select",

    // MSG_STATE_MENU_HELP_1
    "Åõ:File browser",

    // MSG_STATE_MENU_HELP_2
    "Åõ:Main menu",

    // MSG_PAD_MENU_TITLE
    "Gamepad config",

    // MSG_PAD_MENU_0
    "Å™Å@Å@ : %s",

    // MSG_PAD_MENU_1
    "Å´Å@Å@ : %s",

    // MSG_PAD_MENU_2
    "Å©Å@Å@ : %s",

    // MSG_PAD_MENU_3
    "Å®Å@Å@ : %s",

    // MSG_PAD_MENU_4
    "ÅõÅ@Å@ : %s",

    // MSG_PAD_MENU_5
    "Å~Å@Å@ : %s",

    // MSG_PAD_MENU_6
    "Å Å@Å@ : %s",

    // MSG_PAD_MENU_7
    "Å¢Å@Å@ : %s",

    // MSG_PAD_MENU_8
    FONT_L_TRIGGER "Å@Å@ : %s",

    // MSG_PAD_MENU_9
    FONT_R_TRIGGER "Å@Å@ : %s",

    // MSG_PAD_MENU_10
    "START  : %s",

    // MSG_PAD_MENU_11
    "SELECT : %s",

    // MSG_PAD_MENU_12
    "Back",

    // MSG_PAD_MENU_HELP_0
    FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select",

    // MSG_PAD_MENU_HELP_1
    "Åõ:Main menu",

    //PADÇÃê›íË ÉRÉìÉtÉBÉO

    // MSG_PAD_MENU_CFG_0
    "Å™",

    // MSG_PAD_MENU_CFG_1
    "Å´",

    // MSG_PAD_MENU_CFG_2
    "Å©",

    // MSG_PAD_MENU_CFG_3
    "Å®",

    // MSG_PAD_MENU_CFG_4
    "A",

    // MSG_PAD_MENU_CFG_5
    "B",

    // MSG_PAD_MENU_CFG_6
    "L",

    // MSG_PAD_MENU_CFG_7
    "R",

    // MSG_PAD_MENU_CFG_8
    "START",

    // MSG_PAD_MENU_CFG_9
    "SELECT",

    // MSG_PAD_MENU_CFG_10
    "menu",

    // MSG_PAD_MENU_CFG_11
    "fast forward",

    // MSG_PAD_MENU_CFG_12
    "load state",

    // MSG_PAD_MENU_CFG_13
    "save state",

    // MSG_PAD_MENU_CFG_14
    "RAPID FIRE A",

    // MSG_PAD_MENU_CFG_15
    "RAPID FIRE B",

    // MSG_PAD_MENU_CFG_16
    "RAPID FIRE L",

    // MSG_PAD_MENU_CFG_17
    "RAPID FIRE R",

    // MSG_PAD_MENU_CFG_18
    "show fps",

    // MSG_PAD_MENU_CFG_19
    "none",

    // MSG_A_PAD_MENU_TITLE
    "Analog stick config",

    // MSG_A_PAD_MENU_0
    "Analog Å™ : %s",

    // MSG_A_PAD_MENU_1
    "Analog Å´ : %s",

    // MSG_A_PAD_MENU_2
    "Analog Å© : %s",

    // MSG_A_PAD_MENU_3
    "Analog Å® : %s",

    // MSG_A_PAD_MENU_4
    "Enable analog input : %s",

    // MSG_A_PAD_MENU_5
    "Analog sensitivity  : %d",

    // MSG_A_PAD_MENU_6
    "Back",

    // MSG_A_PAD_MENU_HELP_0
    FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select",

    // MSG_A_PAD_MENU_HELP_1
    FONT_CURSOR_LEFT FONT_CURSOR_RIGHT ":Select",

    // MSG_A_PAD_MENU_HELP_2
    "Åõ:Main menu",

    // MSG_NON_LOAD_GAME
    "Game is not loaded",

    // MSG_DAYW_0
    "SUN",

    // MSG_DAYW_1
    "MON",

    // MSG_DAYW_2
    "TUE",

    // MSG_DAYW_3
    "WED",

    // MSG_DAYW_4
    "THU",

    // MSG_DAYW_5
    "FRI",

    // MSG_DAYW_6
    "SAT",

    // MSG_YES
    "YES",

    // MSG_NO
    "NO",

    // MSG_ON
    "ON",

    // MSG_OFF
    "OFF",

    // MSG_ENABLED
    "ENABLE",

    // MSG_DISABLED
    "DISABLED",

    // MSG_AUTO
    "AUTO",

    // MSG_MANUAL
    "MANUAL",

    // MSG_EXITONLY
    "Exit Only",

    // MSG_LOAD
    "LOAD",

    // MSG_SAVE
    "SAVE",

    // MSG_SCN_SCALED_NONE
    "100% GU",

    // MSG_SCN_SCALED_X15_GU
    "150% GU",

    // MSG_SCN_SCALED_X15_SW
    "150% SW",

    // MSG_SCN_SCALED_USER
    "USER GU",

    // MSG_LANG_JAPANESE
    "Japanese",

    // MSG_LANG_ENGLISH
    "English",

    // MSG_SS_DATE_FMT_0
    "%04d_%02d_%02d_%s%02d_%02d_%02d_%03d",

    // MSG_SS_DATE_FMT_1
    "%02d_%02d_%04d_%s%02d_%02d_%02d_%03d",

    // MSG_ERR_SET_DIR_0
    "ERROR [%s] Specified directory is invalid.",

    // MSG_ERR_SET_DIR_1
    "ERROR [%s] Not specified.",

    // MSG_ERR_SET_DIR_2
    "The error occurred. It's set as the following directories.\n%s",

    // png.c
    // MSG_ERR_SS_PNG_0
    "Could not allocate memory for PNG.",

    // MSG_ERR_SS_PNG_1
    "Could not enecode PNG image.",

    // memory.c
    // MSG_LOADING_ROM
    "Now Loading...",

    // MSG_SEARCHING_BACKUP_ID
    "Searching BACKUP ID",

    // main.c
    // MSG_GBA_SLEEP_MODE
    "SLEEP MODE",

    // MSG_ERR_LOAD_DIR_INI
    "Could not load dir.ini file.\nEverything is set as the following directory.\n%s",

    // MSG_ERR_BIOS_NONE
    "Could not load BIOS image file.",

    // MSG_ERR_LOAD_GAMEPACK
    "Could not load the game file.",

    // MSG_ERR_OPEN_GAMEPACK
    "Could not open the game file.",

    // MSG_ERR_START_CALLBACK_THREAD
    "Could not start the callback thread.",

    // sound.c
    // MSG_ERR_RESERVE_AUDIO_CHANNEL
    "Could not reserve audio channel.",

    // MSG_ERR_START_SOUND_THREAD
    "Could not start the sound thread.",

    // MSG_ERR_MALLOC
    "Could not allocate memory.",

    // MSG_ERR_CONT
    "Press any button to continue.",

    // MSG_ERR_QUIT
    "Press any button to exit.",

    // MSG_BLANK
    ""

};

