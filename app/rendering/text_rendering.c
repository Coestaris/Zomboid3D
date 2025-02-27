//
// Created by maxim on 1/22/20.
//

#ifdef __GNUC__
#pragma implementation "text_rendering.h"
#endif
#include "text_rendering.h"

#include "../../lib/resources/font.h"
#include "../../lib/object_include.h"
#include "../../lib/resources/rmanager.h"
#include "shader_setup.h"

static font_t* default_font;
static font_t* monospace_font;
mat4 primitive_proj;

static void bind_default_font(font_t* font, void* data)
{
   struct _font_data fd = *(struct _font_data*)data;
   //sh_set_vec4(UNIFORM_FONT.color, fd.color);
   sh_set_vec3(UNIFORM_FONT.borderColor, fd.border_color);
   sh_set_vec4v(UNIFORM_FONT.params,
                fd.color_off, fd.color_k,
                fd.back_off, fd.back_k);
   t_bind(font->texture, UNIFORM_FONT.tex);
}

void draw_default_string(uint8_t depth, font_data_t* data, vec2 pos, vec2 scale, char* str)
{
   gr_pq_push_string(depth, default_font, pos, scale, str, data);
}

inline void draw_monospace_string(uint8_t depth, font_data_t* data, vec2 pos, vec2 scale, char* str)
{
   gr_pq_push_string(depth, monospace_font, pos, scale, str, data);
}

void init_fonts(win_info_t* info)
{
   shader_t* font_shader = setup_font(primitive_proj);
   
   default_font = rm_getn(FONT, "default");
   default_font->bind_func = bind_default_font;
   default_font->win = win;

   monospace_font = rm_getn(FONT, "monospace");
   monospace_font->bind_func = bind_default_font;
   monospace_font->win = win;
}



