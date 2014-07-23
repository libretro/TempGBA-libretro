
#include <stdio.h>
#include <string.h>
#include <stdint.h>
#include <pspthreadman.h>
#include <pspgu.h>
#include <pspdisplay.h>
#include "common.h"

static retro_log_printf_t log_cb;
static retro_video_refresh_t video_cb;
static retro_input_poll_t input_poll_cb;
static retro_environment_t environ_cb;

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
   init_gamepak_buffer();
   init_sound();
}

void retro_deinit()
{
   quit_gba();
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
   deinit_context_switch();

   update_backup();
   reset_gba();

   init_context_switch();
}


size_t retro_serialize_size()
{
   return SAVESTATE_SIZE;
}

bool retro_serialize(void *data, size_t size)
{
   if (size < SAVESTATE_SIZE)
      return false;

   gba_save_state(data);

   return true;
}

bool retro_unserialize(const void *data, size_t size)
{
   if (size < SAVESTATE_SIZE)
      return false;

   gba_load_state(data);

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

   gamepak_filename[0] = 0;

   if (load_gamepak(info->path) < 0)
   {
     error_msg("Could not load the game file.\n");
     return false;
   }

   reset_gba();

   init_context_switch();

   return true;
}


bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info)
{ return false; }

void retro_unload_game()
{
   deinit_context_switch();
   update_backup();
}

unsigned retro_get_region() { return RETRO_REGION_NTSC; }

void *retro_get_memory_data(unsigned id)
{
//   switch (id)
//   {
//   case RETRO_MEMORY_SAVE_RAM:
//      return gamepak_backup;
//   }

   return 0;
}

size_t retro_get_memory_size(unsigned id)
{
//   switch (id)
//   {
//   case RETRO_MEMORY_SAVE_RAM:
//      switch(backup_type)
//      {
//      case BACKUP_SRAM:
//         return sram_size;

//      case BACKUP_FLASH:
//         return flash_size;

//      case BACKUP_EEPROM:
//         return eeprom_size;

//      case BACKUP_NONE:
//         return 0x0;

//      default:
//         return 0x8000;
//      }
//   }

   return 0;
}

static void check_variables(void)
{

}

#include<psprtc.h>

void retro_run()
{
   bool updated = false;

   input_poll_cb();


   uint64_t start_tick, end_tick;
   sceRtcGetCurrentTick(&start_tick);


   switch_to_cpu_thread();


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
   void* const texture_vram_p = (void*)(0x04200000 - 256 * 256 * 2);
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
