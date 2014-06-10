
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

static SceUID cpu_thread_uid;
SceUID render_thread_uid;

static int cpu_loop(SceSize args, void* argp)
{
   sceKernelSleepThread();

   execute_arm_translate(reg[EXECUTE_CYCLES]);

   return 0;
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
   info->timing.fps = 60.0;
   info->timing.sample_rate = SOUND_FREQUENCY;
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
     error_msg(MSG[MSG_ERR_BIOS_NONE], CONFIRMATION_QUIT);
     return false;
   }

   init_gamepak_buffer();

   init_sound();

   gamepak_filename[0] = 0;

   if (load_gamepak(info->path) < 0)
   {
     error_msg(MSG[MSG_ERR_LOAD_GAMEPACK], CONFIRMATION_CONT);
     return false;
   }

   reset_gba();

   render_thread_uid = sceKernelGetThreadId();
   cpu_thread_uid = sceKernelCreateThread ("CPU loop", cpu_loop, 0x10, 0x10000, 0, NULL);
   sceKernelStartThread(cpu_thread_uid, 0, NULL);

   return true;
}


bool retro_load_game_special(unsigned game_type, const struct retro_game_info *info, size_t num_info)
{ return false; }

void retro_unload_game()
{}

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

void retro_run()
{
   bool updated = false;

   input_poll_cb();
   sceKernelWakeupThread(cpu_thread_uid);
   sceKernelSleepThread();

   render_audio();


   static unsigned int __attribute__((aligned(16))) d_list[32];
//   void* const texture_vram_p = (void*) (0x44200000 - (256 * 256)); // max VRAM address - frame size
   void* const texture_vram_p = (u16 *)(0x4000000 + (PSP_FRAME_SIZE * 2));

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
