/*
  Copyright (c) 2007 Sascha Steinbiss <ssteinbiss@stud.zbh.uni-hamburg.de>
  Copyright (c) 2007 Center for Bioinformatics, University of Hamburg

  Permission to use, copy, modify, and distribute this software for any
  purpose with or without fee is hereby granted, provided that the above
  copyright notice and this permission notice appear in all copies.

  THE SOFTWARE IS PROVIDED "AS IS" AND THE AUTHOR DISCLAIMS ALL WARRANTIES
  WITH REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF
  MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR
  ANY SPECIAL, DIRECT, INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES
  WHATSOEVER RESULTING FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN
  ACTION OF CONTRACT, NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF
  OR IN CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

#include "core/ma.h"
#include "annotationsketch/color.h"

GT_Color* gt_color_new(double red, double green, double blue)
{
  GT_Color *color = ma_malloc(sizeof *color);
  color->red = red;
  color->green = green;
  color->blue = blue;
  return color;
}

void gt_color_set(GT_Color *color, double red, double green, double blue)
{
  assert(color);
  color->red = red;
  color->green = green;
  color->blue = blue;
}

bool gt_color_equals(const GT_Color *c1, const GT_Color *c2)
{
  assert(c1 && c2);
  return ((c1->red == c2->red) && (c1->green == c2->green) &&
          (c1->blue == c2->blue));
}

void gt_color_delete(GT_Color *color)
{
  if (!color) return;
  ma_free(color);
}
