
#include "common.h"

#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <pspthreadman.h>
#include <pspgu.h>
#include <pspdisplay.h>
#include <stddef.h>

#define FROM_GU_POINTER(ptr)  ((void *)((uint32_t)(ptr)|0x44000000))
#define TO_GU_POINTER(ptr)    ((void *)((uint32_t)(ptr)&~0x44000000))

#define GBA_FRAME_TEXTURE     (void*)(0x04200000 - 256 * 256 * 2)
#define GBA_FRAME_TEXTURE_GU  FROM_GU_POINTER(GBA_FRAME_TEXTURE)

static unsigned int __attribute__((aligned(64))) d_list[2*1024];
static PspGeContext main_context_buffer;

typedef struct
{
   int bg_mode                      : 3;
   int reserved_cgb_mode            : 1;
   int display_frame_select         : 1;
   int h_blank_interval_free        : 1;
   int obj_character_vram_mapping   : 1;
   int forced_blank                 : 1;
   int screen_display_BG0           : 1;
   int screen_display_BG1           : 1;
   int screen_display_BG2           : 1;
   int screen_display_BG3           : 1;
   int screen_display_OBJ           : 1;
   int window0_display_flag         : 1;
   int window1_display_flag         : 1;
   int obj_window_display_flag      : 1;
} __attribute__((packed)) REG_DISPCNT_t;

typedef struct
{
   int swap_on                      : 1;
   int _unused                      : 15;
} __attribute__((packed)) REG_GREENSWAP_t;

typedef struct
{
   int v_blank_flag                 : 1;
   int h_blank_flag                 : 1;
   int v_counter_flag               : 1;
   int v_blank_irq_enable           : 1;
   int h_blank_irq_enable           : 1;
   int v_counter_irq_enable         : 1;

   uint8_t v_count_setting;
} __attribute__((packed)) REG_DISPSTAT_t;

struct
{
   REG_DISPCNT_t  lcd_control;
   REG_GREENSWAP_t green_swap;
   REG_DISPSTAT_t lcd_status;
   uint16_t REG_VCOUNT_t;
   uint16_t REG_BG0CNT_t;
   uint16_t REG_BG1CNT_t ;
   uint16_t REG_BG2CNT_t ;
   uint16_t REG_BG3CNT_t ;

   uint16_t REG_BG0HOFS_t ;
   uint16_t REG_BG0VOFS_t ;
   uint16_t REG_BG1HOFS_t ;
   uint16_t REG_BG1VOFS_t ;
   uint16_t REG_BG2HOFS_t ;
   uint16_t REG_BG2VOFS_t ;
   uint16_t REG_BG3HOFS_t ;
   uint16_t REG_BG3VOFS_t ;

   uint16_t REG_BG2PA_t ;
   uint16_t REG_BG2PB_t ;
   uint16_t REG_BG2PC_t ;
   uint16_t REG_BG2PD_t ;
   uint16_t REG_BG2X_L_t ;
   uint16_t REG_BG2X_H_t ;
   uint16_t REG_BG2Y_u_t;
   uint16_t REG_BG2Y_H_t ;

   uint16_t REG_BG3PA_t ;
   uint16_t REG_BG3PB_t ;
   uint16_t REG_BG3PC_t ;
   uint16_t REG_BG3PD_t ;
   uint16_t REG_BG3X_L_t ;
   uint16_t REG_BG3X_H_t ;
   uint16_t REG_BG3Y_L_t ;
   uint16_t REG_BG3Y_H_t ;

   uint16_t REG_WIN0H_t ;
   uint16_t REG_WIN1H_t ;
   uint16_t REG_WIN0V_t ;
   uint16_t REG_WIN1V_t ;
   uint16_t REG_WININ_t ;
   uint16_t REG_WINOUT_t ;
   uint32_t MOSAIC_t;

   uint16_t REG_BLDCNT_t ;
   uint16_t REG_BLDALPHA_t ;
   uint16_t REG_BLDY_t ;

}*gba_video_registers = (void*)io_registers;



void update_scanline_ge(void)
{

}

void update_frame_ge(void)
{


   int status = sceGuGetAllStatus();
   sceGeSaveContext(&main_context_buffer);

   sceGuStart(GU_DIRECT, d_list);
   sceGuDrawBufferList(GU_COLOR_5650, GBA_FRAME_TEXTURE_GU, 256);
   sceGuScissor(0,0,120,160);
   sceGuEnable(GU_SCISSOR_TEST);

   sceGuClearColor(0xFFFF0000);
   sceGuClear(GU_COLOR_BUFFER_BIT);
   sceGuFinish();


   sceGuSetAllStatus(status);
   sceGeRestoreContext(&main_context_buffer);
   sceGuClearColor(0x00000000);
}
