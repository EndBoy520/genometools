/*
  Copyright (c) 2010 Stefan Kurtz <kurtz@zbh.uni-hamburg.de>
  Copyright (c) 2010 Center for Bioinformatics, University of Hamburg

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

#ifndef SFX_SUFFIXGETSET_H
#define SFX_SUFFIXGETSET_H

#include <stdio.h>
#include <inttypes.h>
#include "core/error_api.h"

typedef struct GtSuffixsortspace GtSuffixsortspace;

typedef struct
{
  uint32_t *uinttabsectionptr;
  unsigned long *ulongtabsectionptr;
} GtSuffixsortspace_exportptr;

GtSuffixsortspace *gt_suffixsortspace_new(unsigned long numofentries,
                                          unsigned long maxvalue,
                                          bool useuint);

GtSuffixsortspace *gt_suffixsortspace_new_fromfile(int filedesc,
                                                   const char *filename,
                                                   unsigned long numofentries,
                                                   unsigned long maxvalue,
                                                   bool useuint);

void gt_suffixsortspace_delete(GtSuffixsortspace *suffixsortspace,
                               bool checklongestdefined);

void gt_suffixsortspace_showrange(const GtSuffixsortspace *sssp,
                                  unsigned long subbucketleft,
                                  unsigned long width);

unsigned long gt_suffixsortspace_getdirect(const GtSuffixsortspace *sssp,
                                           unsigned long idx);

void gt_suffixsortspace_nooffsets(const GtSuffixsortspace *sssp);

void gt_suffixsortspace_updatelongest(GtSuffixsortspace *sssp,
                                      unsigned long idx);

void gt_suffixsortspace_setdirect(GtSuffixsortspace *sssp,
                                  unsigned long idx,
                                  unsigned long value);

void gt_suffixsortspace_exportptr(GtSuffixsortspace_exportptr *exportptr,
                                  unsigned long subbucketleft,
                                  GtSuffixsortspace *sssp);

unsigned long gt_suffixsortspace_get(const GtSuffixsortspace *sssp,
                                     unsigned long subbucketleft,
                                     unsigned long idx);

void gt_suffixsortspace_set(GtSuffixsortspace *sssp,
                            unsigned long subbucketleft,
                            unsigned long idx,
                            unsigned long value);

unsigned long gt_suffixsortspace_bucketleftidx_get(
                    const GtSuffixsortspace *sssp);

void gt_suffixsortspace_bucketleftidx_set(GtSuffixsortspace *sssp,
                                          unsigned long value);

void gt_suffixsortspace_sortspace_delete(GtSuffixsortspace *sssp);

void gt_suffixsortspace_partoffset_set(GtSuffixsortspace *sssp,
                                       unsigned long partoffset);

unsigned long *gt_suffixsortspace_ulong_get(const GtSuffixsortspace *sssp);

unsigned long gt_suffixsortspace_longest(const GtSuffixsortspace *sssp);

size_t gt_suffixsortspace_requiredspace(unsigned long numofentries,
                                        unsigned long maxvalue,
                                        bool useuint);

int gt_suffixsortspace_to_file (FILE *outfpsuftab,
                                const GtSuffixsortspace *sssp,
                                unsigned long numberofsuffixes,
                                GtError *err);
#endif
