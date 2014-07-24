#include "video_ge.h"

void update_scanline_ge(void)
{

}

void update_frame_ge(void)
{
   int status = sceGuGetAllStatus();
   sceGeSaveContext(&main_context_buffer);

   sceGuStart(GU_DIRECT, d_list);
   sceGuDrawBufferList(GU_COLOR_5551, GBA_FRAME_TEXTURE_GU, 256);
   sceGuScissor(0,0,240,160);
   sceGuEnable(GU_SCISSOR_TEST);

   sceGuClearColor(0xFF008000);
   sceGuClear(GU_COLOR_BUFFER_BIT);
   sceGuFinish();


   sceGuSetAllStatus(status);
   sceGeRestoreContext(&main_context_buffer);
   sceGuClearColor(0x00000000);
}
