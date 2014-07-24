#ifndef VIDEO_GE_H
#define VIDEO_GE_H

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
   unsigned bg_mode                      : 3;
   unsigned reserved_cgb_mode            : 1;
   unsigned display_frame_select         : 1;
   unsigned h_blank_interval_free        : 1;
   unsigned obj_character_vram_mapping   : 1;
   unsigned forced_blank                 : 1;
   unsigned screen_display_BG0           : 1;
   unsigned screen_display_BG1           : 1;
   unsigned screen_display_BG2           : 1;
   unsigned screen_display_BG3           : 1;
   unsigned screen_display_OBJ           : 1;
   unsigned window0_display_flag         : 1;
   unsigned window1_display_flag         : 1;
   unsigned obj_window_display_flag      : 1;
} __attribute__((packed)) REG_DISPCNT_t;

typedef struct
{
   unsigned swap_on                      : 1;
   unsigned _dummy                       : 15;
} __attribute__((packed)) REG_GREENSWAP_t;

typedef struct
{
   unsigned v_blank_flag                 : 1;
   unsigned h_blank_flag                 : 1;
   unsigned v_counter_flag               : 1;
   unsigned v_blank_irq_enable           : 1;
   unsigned h_blank_irq_enable           : 1;
   unsigned v_counter_irq_enable         : 1;

   uint8_t v_count_setting;
} __attribute__((packed)) REG_DISPSTAT_t;

typedef struct
{
   uint8_t LY;
   uint8_t _dummy;
} __attribute__((packed)) REG_VCOUNT_t;

typedef struct
{
   unsigned priority                     : 2;
   unsigned character_base_block         : 2;
   unsigned _dummy                       : 2;
   unsigned mosaic                       : 1;
   unsigned palette_mode_256             : 1;

   unsigned screen_base_block            : 5;
   unsigned display_area_overflow        : 1;
   unsigned screen_size                  : 2;
} __attribute__((packed)) REG_BGxCNT_t;

typedef struct
{
   unsigned X                       : 9;
   unsigned _x_dummy                : 7;
   unsigned Y                       : 9;
   unsigned _y_dummy                : 7;
} __attribute__((packed)) REG_BGxOFS_t;

typedef struct
{
   unsigned value_times_256                   : 27;
   unsigned sign                              : 1;
} __attribute__((packed)) REG_BGxROTSCLREF_t;

typedef struct
{
   unsigned value_times_256                   : 15;
   unsigned sign                              : 1;
} __attribute__((packed)) REG_BGxROTSCLP_t;

typedef struct
{
   unsigned BG0_enable                   : 1;
   unsigned BG1_enable                   : 1;
   unsigned BG2_enable                   : 1;
   unsigned BG3_enable                   : 1;
   unsigned OBJ_enable                   : 1;
   unsigned color_effect_enable          : 1;
} __attribute__((packed)) REG_WINCNT_t;

typedef struct
{
   unsigned X                   : 4;
   unsigned Y                   : 4;
} __attribute__((packed)) REG_MOSAIC_t;

typedef struct
{
   unsigned BG0_src                   : 1;
   unsigned BG1_src                   : 1;
   unsigned BG2_src                   : 1;
   unsigned BG3_src                   : 1;
   unsigned OBJ_src                   : 1;
   unsigned BD_src                    : 1;
   unsigned effect                    : 2;

   unsigned BG0_dst                   : 1;
   unsigned BG1_dst                   : 1;
   unsigned BG2_dst                   : 1;
   unsigned BG3_dst                   : 1;
   unsigned OBJ_dst                   : 1;
   unsigned BD_dst                    : 1;
} __attribute__((packed)) REG_BLDCNT_t;

typedef struct
{
   unsigned src_coeff             : 5;
   unsigned _src_dummy            : 3;
   unsigned dst_coeff             : 5;
   unsigned _dst_dummy            : 3;
} __attribute__((packed)) REG_BLDALPHA_t;

typedef struct
{
   unsigned coeff                  : 5;
   unsigned _dummy                 : 27;
} __attribute__((packed)) REG_BLDY_t;

static struct
{
//0x4000000
   REG_DISPCNT_t lcd_control;
   REG_GREENSWAP_t green_swap;
   REG_DISPSTAT_t lcd_status;
   REG_VCOUNT_t v_count_reg;
   REG_BGxCNT_t BG0_control;
   REG_BGxCNT_t BG1_control;
   REG_BGxCNT_t BG2_control;
   REG_BGxCNT_t BG3_control;
//0x4000010
   REG_BGxOFS_t BG0_scroll;
   REG_BGxOFS_t BG1_scroll;
   REG_BGxOFS_t BG2_scroll;
   REG_BGxOFS_t BG3_scroll;
//0x4000020
   REG_BGxROTSCLP_t BG2_dx;
   REG_BGxROTSCLP_t BG2_dmx;
   REG_BGxROTSCLP_t BG2_dy;
   REG_BGxROTSCLP_t BG2_dmy;
   REG_BGxROTSCLREF_t BG2_rotscl_ref_X;
   REG_BGxROTSCLREF_t BG2_rotscl_ref_Y;
//0x4000030
   REG_BGxROTSCLP_t BG3_dx;
   REG_BGxROTSCLP_t BG3_dmx;
   REG_BGxROTSCLP_t BG3_dy;
   REG_BGxROTSCLP_t BG3_dmy;
   REG_BGxROTSCLREF_t BG3_rotscl_ref_X;
   REG_BGxROTSCLREF_t BG3_rotscl_ref_Y;
//0x4000040
   uint8_t WIN0_right;
   uint8_t WIN0_left;
   uint8_t WIN1_right;
   uint8_t WIN1_left;
   uint8_t WIN0_bottom;
   uint8_t WIN0_top;
   uint8_t WIN1_bottom;
   uint8_t WIN1_top;
   REG_WINCNT_t WIN0_control;
   REG_WINCNT_t WIN1_control;
   REG_WINCNT_t WIN_OUT_control;
   REG_WINCNT_t WIN_OBJ_control;
   REG_MOSAIC_t BG_mosaic;
   REG_MOSAIC_t OBJ_mosaic;
   uint16_t _dummy;
//0x4000050
   REG_BLDCNT_t blend_control;
   REG_BLDALPHA_t blend_alpha;
   REG_BLDY_t blend_luma;
} *const gba_video_registers = (void *const)io_registers;

#endif // VIDEO_GE_H
