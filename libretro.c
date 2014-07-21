
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <pspthreadman.h>
#include <pspgu.h>
#include "common.h"

static retro_log_printf_t log_cb;
static retro_video_refresh_t video_cb;
static retro_input_poll_t input_poll_cb;
static retro_environment_t environ_cb;

#ifdef SINGLE_THREAD
#else
#include "pspthreadman.h"
static SceUID main_thread;
static SceUID cpu_thread;

void switch_to_main_thread(void)
{
   sceKernelWakeupThread(main_thread);
   sceKernelSleepThread();
}

static inline void switch_to_cpu_thread(void)
{
   sceKernelWakeupThread(cpu_thread);
   sceKernelSleepThread();
}

static int cpu_thread_entry(SceSize args, void* argp)
{
   sceKernelSleepThread();

   execute_arm_translate(reg[EXECUTE_CYCLES]);

   return 0;
}

static inline void init_context_switch(void)
{
   main_thread = sceKernelGetThreadId();
   cpu_thread = sceKernelCreateThread ("CPU thread", cpu_thread_entry, 0x12, 0x20000, 0, NULL);
   sceKernelStartThread(cpu_thread, 0, NULL);
}

static inline void deinit_context_switch(void)
{
   sceKernelTerminateDeleteThread(cpu_thread);
}

#endif

void retro_get_system_info(struct retro_system_info *info)
{
   info->library_name = "TempGBA";
   info->library_version = "v0.0.1";
   info->need_fullpath = true;
   info->block_extract = true;
   info->valid_extensions = "zip|gba|bin|agb|gbz" ;
}


void retro_get_system_av_info(struct retro_system_av_info *info)
{
   info->geometry.base_width = GBA_SCREEN_WIDTH;
   info->geometry.base_height = GBA_SCREEN_HEIGHT;
   info->geometry.max_width = GBA_SCREEN_WIDTH;
   info->geometry.max_height = GBA_SCREEN_HEIGHT;
   info->geometry.aspect_ratio = 0;
   info->timing.fps = ((float) CPU_FREQUENCY) / (308 * 228 * 4); // 59.72750057 hz
   info->timing.sample_rate = SOUND_FREQUENCY;
//   info->timing.sample_rate = 32 * 1024;
}


void retro_init()
{
}

void retro_deinit()
{
}

void retro_set_environment(retro_environment_t cb)
{
   struct retro_log_callback log;

   environ_cb = cb;

   if (environ_cb(RETRO_ENVIRONMENT_GET_LOG_INTERFACE, &log))
      log_cb = log.log;
   else
      log_cb = NULL;
}

void retro_set_video_refresh(retro_video_refresh_t cb) { video_cb = cb; }
void retro_set_input_poll(retro_input_poll_t cb) { input_poll_cb = cb; }

void retro_set_controller_port_device(unsigned port, unsigned device) {}

void retro_reset()
{
#ifndef SINGLE_THREAD
   deinit_context_switch();
#endif

   reset_gba();

#ifndef SINGLE_THREAD
   init_context_switch();
#endif
}


size_t retro_serialize_size()
{
   return 0;
}

bool retro_serialize(void *data, size_t size)
{
   return true;
}

bool retro_unserialize(const void *data, size_t size)
{
   return true;
}

void retro_cheat_reset() {}
void retro_cheat_set(unsigned index, bool enabled, const char *code) {}

void error_msg(const char *text)
{
   if (log_cb)
      log_cb(RETRO_LOG_ERROR, text);
}

void info_msg(const char *text)
{
   if (log_cb)
      log_cb(RETRO_LOG_INFO, text);
}


#include "pspdisplay.h"

bool retro_load_game(const struct retro_game_info *info)
{
   enum retro_pixel_format fmt = RETRO_PIXEL_FORMAT_RGB565;
   if (!environ_cb(RETRO_ENVIRONMENT_SET_PIXEL_FORMAT, &fmt))
   {
      if (log_cb)
         log_cb(RETRO_LOG_INFO, "[TempGBA]: RGB565 is not supported.\n");
      return false;
   }

   // Copy the directory path of the executable into main_path
   getcwd(main_path, MAX_PATH);
   strcat(main_path, "/");
   strcpy(dir_save, main_path);

   char filename_bios[MAX_FILE];

   sprintf(filename_bios, "%sgba_bios.bin", main_path);

   if (load_bios(filename_bios) < 0)
   {
     error_msg("Could not load BIOS image file.\n");
     return false;
   }

   init_gamepak_buffer();

   init_sound();

   gamepak_filename[0] = 0;

   if (load_gamepak(info->path) < 0)
   {
     error_msg("Could not load the game file.\n");
     return false;
   }

   reset_gba();

#ifdef SINGLE_THREAD

#else
   init_context_switch();
#endif
   return true;
}


bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info)
{ return false; }

void retro_unload_game()
{
#ifndef SINGLE_THREAD
   deinit_context_switch();
#endif
}

unsigned retro_get_region() { return RETRO_REGION_NTSC; }

void *retro_get_memory_data(unsigned id)
{

   return 0;
}

size_t retro_get_memory_size(unsigned id)
{

   return 0;
}

static void check_variables(void)
{

}

#include<psprtc.h>

//void io_update_gba(u32 cycles);
//void resume_cpu_loop(void);
//void lookup_pc_changed(void);
void retro_run()
{
   bool updated = false;

   input_poll_cb();


   uint64_t start_tick, end_tick;
   sceRtcGetCurrentTick(&start_tick);


#ifdef SINGLE_THREAD
   static bool firstrun = true;
   static u32 mips_regs[32];
   __asm__ volatile (
   ".set      push         \n"
   ".set      noreorder    \n"
   " sw $s0, 0(%0)        \n"
   " sw $s1, 4(%0)        \n"
   " sw $s2, 8(%0)        \n"
   " sw $s3, 12(%0)        \n"
   " sw $s4, 16(%0)        \n"
   " sw $s5, 20(%0)        \n"
   " sw $s6, 24(%0)        \n"
   " sw $s7, 28(%0)        \n"
   " sw $a0, 32(%0)        \n"
   " sw $a1, 36(%0)        \n"
   " sw $a2, 40(%0)        \n"
   " sw $a3, 44(%0)        \n"
   " sw $gp, 48(%0)        \n"
   " sw $sp, 52(%0)        \n"
   " sw $fp, 56(%0)        \n"
   " sw $ra, 60(%0)        \n"
   ".set      pop          \n"
   ::"r"(mips_regs)
   );
   if(firstrun)
   {
      firstrun = false;
//   reg[CPU_HALT_STATE] = CPU_ACTIVE;
//   reg[CHANGED_PC_STATUS] = 0;
//   execute_arm_translate(reg[EXECUTE_CYCLES]);
   }
   else
   {
//      resume_cpu_loop();
//      io_update_gba(reg[EXECUTE_CYCLES]);
//      __asm__ volatile (
//      ".set      push         \n"
//      ".set      noreorder    \n"
//      " j lookup_pc \n"
//      " nop \n"
//      ".set      pop          \n");

//      __asm__ volatile (
//      ".set      push         \n"
//      ".set      noreorder    \n"
//      " lw $ra, 64(%0)        \n"
//      " addiu	$sp,$sp,-40 \n"
//      " jr $ra \n"
//      " nop \n"
//      ".set      pop          \n"
//      ::"r"(mips_regs));
   }



   __asm__ volatile (
   ".set      push         \n"
   ".set      noreorder    \n"
   ".global exit_cpu_loop  \n"
   "  exit_cpu_loop:       \n"
   ".set      pop          \n"
   );

   __asm__ volatile (
   ".set      push         \n"
   ".set      noreorder    \n"
//   ".set at \n"
   ".equ REG_R0,              (0 * 4)  \n"
   ".equ REG_R1,              (1 * 4)  \n"
   ".equ REG_R2,              (2 * 4)  \n"
   ".equ REG_R3,              (3 * 4)  \n"
   ".equ REG_R4,              (4 * 4)  \n"
   ".equ REG_R5,              (5 * 4)  \n"
   ".equ REG_R6,              (6 * 4)  \n"
   ".equ REG_R7,              (7 * 4)  \n"
   ".equ REG_R8,              (8 * 4)  \n"
   ".equ REG_R9,              (9 * 4)  \n"
   ".equ REG_R10,             (10 * 4)  \n"
   ".equ REG_R11,             (11 * 4)  \n"
   ".equ REG_R12,             (12 * 4)  \n"
   ".equ REG_R13,             (13 * 4)  \n"
   ".equ REG_R14,             (14 * 4)  \n"
   "sw $3,  REG_R0(%0)  \n"
   "sw $7,  REG_R1(%0)  \n"
   "sw $8,  REG_R2(%0)  \n"
   "sw $9,  REG_R3(%0)  \n"
   "sw $10, REG_R4(%0)  \n"
   "sw $11, REG_R5(%0)  \n"
   "sw $12, REG_R6(%0)  \n"
   "sw $13, REG_R7(%0)  \n"
   "sw $14, REG_R8(%0)  \n"
   "sw $15, REG_R9(%0)  \n"
   "sw $24, REG_R11(%0)  \n"
   "sw $25, REG_R12(%0)  \n"

   "sw $18, REG_R10(%0)  \n"
   "sw $28, REG_R13(%0)  \n"
   "sw $30, REG_R14(%0)  \n"
   ".set      pop          \n"
   ::"r"(reg));

   __asm__ volatile (
   ".set      push         \n"
   ".set      noreorder    \n"
//   "  addiu $sp, 0x2c        \n"
   " sw $ra, 64(%0)        \n"
   " lw $s0, 0(%0)        \n"
   " lw $s1, 4(%0)        \n"
   " lw $s2, 8(%0)        \n"
   " lw $s3, 12(%0)        \n"
   " lw $s4, 16(%0)        \n"
   " lw $s5, 20(%0)        \n"
   " lw $s6, 24(%0)        \n"
   " lw $s7, 28(%0)        \n"
   " lw $a0, 32(%0)        \n"
   " lw $a1, 36(%0)        \n"
   " lw $a2, 40(%0)        \n"
   " lw $a3, 44(%0)        \n"
   " lw $gp, 48(%0)        \n"
   " lw $sp, 52(%0)        \n"
   " lw $fp, 56(%0)        \n"
   " lw $ra, 60(%0)        \n"
   ".set      pop          \n"
   ::"r"(mips_regs)
   );
#else
   switch_to_cpu_thread();
#endif


   sceRtcGetCurrentTick(&end_tick);
//   printf("frame time : %u\n", (uint32_t)(end_tick - start_tick));
   static int frames = 0;
   static float total = 0.0;

   if ( frames >= 200)
      total += (end_tick - start_tick);

   if (frames++ == 400)
      printf("total : %f\n", total / 200.0);

   render_audio();


   static unsigned int __attribute__((aligned(16))) d_list[32];
//   void* const texture_vram_p = (void*) (0x44200000 - (256 * 256)); // max VRAM address - frame size

   void* const texture_vram_p = (u16 *)(0x04200000 - 256 * 256 * 2);
//   sceKernelDcacheWritebackRange(texture_vram_p, GBA_SCREEN_SIZE);

   sceGuStart(GU_DIRECT, d_list);

   sceGuTexImage(0, 256, 256, GBA_LINE_SIZE, texture_vram_p);
   sceGuTexMode(GU_PSM_5551, 0, 0, GU_FALSE);
   sceGuTexFunc(GU_TFX_REPLACE, GU_TCC_RGB);
   sceGuDisable(GU_BLEND);

   sceGuFinish();

   video_cb(texture_vram_p,GBA_SCREEN_WIDTH, GBA_SCREEN_HEIGHT, GBA_LINE_SIZE * 2);

   if (environ_cb(RETRO_ENVIRONMENT_GET_VARIABLE_UPDATE, &updated) && updated)
       check_variables();

}

unsigned retro_api_version() { return RETRO_API_VERSION; }
