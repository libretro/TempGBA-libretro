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

#ifndef VIDEO_H
#define VIDEO_H


#define GBA_SCREEN_WIDTH  (240)
#define GBA_SCREEN_HEIGHT (160)
//#define GBA_SCREEN_WIDTH  (256)
//#define GBA_SCREEN_HEIGHT (256)
#define GBA_LINE_SIZE     (256)

void update_scanline(void);

void clear_texture(u16 color);

extern s32 affine_reference_x[2];
extern s32 affine_reference_y[2];

typedef void (*tile_render_function)(u32 layer_number, u32 start, u32 end, void *dest_ptr);
typedef void (*bitmap_render_function)(u32 start, u32 end, void *dest_ptr);

typedef struct
{
  tile_render_function normal_render_base;
  tile_render_function normal_render_transparent;
  tile_render_function alpha_render_base;
  tile_render_function alpha_render_transparent;
  tile_render_function color16_render_base;
  tile_render_function color16_render_transparent;
  tile_render_function color32_render_base;
  tile_render_function color32_render_transparent;
} TileLayerRenderStruct;

typedef struct
{
  bitmap_render_function normal_render;
} BitmapLayerRenderStruct;


void video_write_savestate(void);
void video_read_savestate(void);

#ifdef HW_RENDER_TEST
void init_video_ge(void);
void update_scanline_ge(void);
void update_frame_ge(void);
#endif

#endif /* VIDEO_H */
