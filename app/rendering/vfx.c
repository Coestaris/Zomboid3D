//
// Created by maxim on 1/26/20.
//

#ifdef __GNUC__
#pragma implementation "vfx.h"
#endif
#include "vfx.h"

static float normpdf(float x, float sigma)
{
   return 0.39894f * expf(-0.5f * x * x / (sigma * sigma)) / sigma;
}

blurred_region_t* create_br(win_info_t* info, vec2 pos, vec2 size, vec2 back_tex_size)
{
   blurred_region_t* br = DEEPCARS_MALLOC(sizeof(blurred_region_t));
   br->x = pos.x;
   br->y = pos.y;
   br->w = size.x;
   br->h = size.y;

   br->visible = true;
   br->tex = NULL;
   br->back_tex = NULL;
   br->gray_color = NULL;

   GLuint indices[] = {
         0, 1, 3,
         1, 2, 3
   };

   br->transparency = 1;

   float x1 = br->x;
   float y1 = br->y;
   float x2 = br->x + br->w;
   float y2 = br->y + br->h;

   float half_w = info->w / 2.0f;
   float half_h = info->h / 2.0f;

   float data[4 * (2 + 2 + 2)] =
   {
      x2 - half_w, half_h - y2, x2 / (float)back_tex_size.x, - y2 / (float)back_tex_size.y, 1.0f, 1.0f,
      x2 - half_w, half_h - y1, x2 / (float)back_tex_size.x, - y1 / (float)back_tex_size.y, 1.0f, 0.0f,
      x1 - half_w, half_h - y1, x1 / (float)back_tex_size.x, - y1 / (float)back_tex_size.y, 0.0f, 0.0f,
      x1 - half_w, half_h - y2, x1 / (float)back_tex_size.x, - y2 / (float)back_tex_size.y, 0.0f, 1.0f,
   };

   GLuint ebo, vbo;
   GL_CALL(glGenVertexArrays(1, &br->vao));
   GL_CALL(glGenBuffers(1, &vbo));
   GL_CALL(glGenBuffers(1, &ebo));
   GL_CALL(glBindVertexArray(br->vao));

   GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, vbo));
   GL_CALL(glBufferData(GL_ARRAY_BUFFER, sizeof(data), data, GL_STATIC_DRAW));

   GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, ebo));
   GL_CALL(glBufferData(GL_ELEMENT_ARRAY_BUFFER, sizeof(indices), indices, GL_STATIC_DRAW));

   GL_CALL(glEnableVertexAttribArray(0));
   GL_CALL(glVertexAttribPointer(0, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) 0));

   GL_CALL(glEnableVertexAttribArray(1));
   GL_CALL(glVertexAttribPointer(1, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (2 * sizeof(float))));

   GL_CALL(glEnableVertexAttribArray(2));
   GL_CALL(glVertexAttribPointer(2, 2, GL_FLOAT, GL_FALSE, 6 * sizeof(float), (void*) (4 * sizeof(float))));

   GL_CALL(glBindBuffer(GL_ARRAY_BUFFER, 0));

   GL_CALL(glBindVertexArray(0));
   GL_CALL(glBindBuffer(GL_ELEMENT_ARRAY_BUFFER, 0));

   return br;
}

void free_br(blurred_region_t* br)
{
   //if(br->gray_color)
      //vec4_free(br->gray_color);
   DEEPCARS_FREE(br);
}

float* create_gaussian_kernel(float sigma, float* z, size_t* k_size, size_t len)
{
   *k_size = (len - 1) / 2;
   float* kernel = DEEPCARS_MALLOC(sizeof(float) * len);

   for (size_t j = 0; j <= *k_size; ++j)
   {
      kernel[*k_size + j] = kernel[*k_size - j] = normpdf(j, sigma);
   }

   *z = 0;
   for (size_t j = 0; j < len; j++)
   {
      *z += kernel[j];
   }
   return kernel;
}


