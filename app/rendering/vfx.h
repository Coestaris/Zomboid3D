//
// Created by maxim on 1/26/20.
//

#ifndef DEEPCARS_VFX_H
#define DEEPCARS_VFX_H

#include "../../lib/object_include.h"

typedef struct _blurred_region
{
   bool visible;

   float x, y;
   float w, h;
   float transparency;
   vec4 gray_color;

   texture_t* tex;
   texture_t* back_tex;

   GLuint vao;

} blurred_region_t;

float* create_gaussian_kernel(float sigma, float* z, size_t* k_size, size_t len);
blurred_region_t* create_br(win_info_t* info, vec2 pos, vec2 size, vec2 back_tex_size);
void free_br(blurred_region_t* br);
float surface_func(float x, float y);

#endif //DEEPCARS_VFX_H
