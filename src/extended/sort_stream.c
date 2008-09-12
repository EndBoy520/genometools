/*
  Copyright (c) 2006-2008 Gordon Gremme <gremme@zbh.uni-hamburg.de>
  Copyright (c) 2006-2008 Center for Bioinformatics, University of Hamburg

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

#include <assert.h>
#include "extended/node_stream_rep.h"
#include "extended/sort_stream.h"

struct SortStream
{
  const GtNodeStream parent_instance;
  GtNodeStream *in_stream;
  unsigned long idx;
  GtArray *trees;
  bool sorted;
};

#define sort_stream_cast(GS)\
        gt_node_stream_cast(sort_stream_class(), GS);

static int sort_stream_next_tree(GtNodeStream *gs, GtGenomeNode **gn,
                                 GtError *err)
{
  SortStream *sort_stream;
  GtGenomeNode *node;
  int had_err = 0;
  gt_error_check(err);
  sort_stream = sort_stream_cast(gs);

  if (!sort_stream->sorted) {
    while (!(had_err = gt_node_stream_next(sort_stream->in_stream, &node,
                                               err)) && node) {
      gt_array_add(sort_stream->trees, node);
    }
    if (!had_err) {
      gt_genome_nodes_sort_stable(sort_stream->trees);
      sort_stream->sorted = true;
    }
  }

  if (!had_err) {
    assert(sort_stream->sorted);
    if (sort_stream->idx < gt_array_size(sort_stream->trees)) {
      *gn = *(GtGenomeNode**)
            gt_array_get(sort_stream->trees, sort_stream->idx);
      sort_stream->idx++;
      return 0;
    }
  }

  if (!had_err) {
    gt_array_reset(sort_stream->trees);
    *gn = NULL;
  }

  return had_err;
}

static void sort_stream_free(GtNodeStream *gs)
{
  unsigned long i;
  SortStream *sort_stream = sort_stream_cast(gs);
  for (i = sort_stream->idx; i < gt_array_size(sort_stream->trees); i++) {
    gt_genome_node_rec_delete(*(GtGenomeNode**)
                              gt_array_get(sort_stream->trees, i));
  }
  gt_array_delete(sort_stream->trees);
  gt_node_stream_delete(sort_stream->in_stream);
}

const GtNodeStreamClass* sort_stream_class(void)
{
  static const GtNodeStreamClass gsc = { sizeof (SortStream),
                                         sort_stream_next_tree,
                                         sort_stream_free };
  return &gsc;
}

GtNodeStream* sort_stream_new(GtNodeStream *in_stream)
{
  GtNodeStream *gs = gt_node_stream_create(sort_stream_class(), true);
  SortStream *sort_stream = sort_stream_cast(gs);
  assert(in_stream);
  sort_stream->in_stream = gt_node_stream_ref(in_stream);
  sort_stream->sorted = false;
  sort_stream->idx = 0;
  sort_stream->trees = gt_array_new(sizeof (GtGenomeNode*));
  return gs;
}
