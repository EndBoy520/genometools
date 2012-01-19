/*
  Copyright (c) 2010      Sascha Kastens <sascha.kastens@studium.uni-hamburg.de>
  Copyright (c) 2010-2011 Center for Bioinformatics, University of Hamburg

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

#ifndef MATCH_ITERATOR_BLAST_H
#define MATCH_ITERATOR_BLAST_H

#include "extended/match_iterator.h"

typedef struct GtMatchIteratorBlast GtMatchIteratorBlast;

typedef struct {
  char *seqid1, *seqid2;
  long double e_value;
  float bitscore;
  unsigned long ali_length;
} GtBlastMatchInfo;

GtMatchIterator* gt_match_iterator_blast_file_new(const char *matchfile,
                                                  GtError *err);

GtMatchIterator* gt_match_iterator_blastalln_process_new(const char *query,
                                            const char *db_name,
                                            float evalue,
                                            int word_size,
                                            int gapopen,
                                            int gapextend,
                                            int penalty,
                                            int reward,
                                            int xdrop_gap_final,
                                            GtError *err);

GtMatchIterator* gt_match_iterator_blastallp_process_new(const char *query,
                                            const char *db_name,
                                            float evalue,
                                            int word_size,
                                            int gapopen,
                                            int gapextend,
                                            int xdrop_gap_final,
                                            GtError *err);

GtMatchIterator* gt_match_iterator_blastn_process_new(const char *query,
                                         const char *db_name,
                                         float evalue,
                                         int word_size,
                                         int gapopen,
                                         int gapextend,
                                         int penalty,
                                         int reward,
                                         float perc_identity,
                                         int num_threads,
                                         float xdrop_gap_final,
                                         GtError *err);

GtMatchIterator* gt_match_iterator_blastp_process_new(const char *query,
                                         const char *db_name,
                                         float evalue,
                                         int word_size,
                                         int gapopen,
                                         int gapextend,
                                         int num_threads,
                                         float xdrop_gap_final,
                                         GtError *err);
#endif