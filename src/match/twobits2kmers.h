/*
  Copyright (c) 2011 Stefan Kurtz <kurtz@zbh.uni-hamburg.de>
  Copyright (c) 2011 Center for Bioinformatics, University of Hamburg

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

#ifndef TWOBITS2KMERS_H
#define TWOBITS2KMERS_H

#include "core/encseq_api.h"

typedef enum
{
  BSRS_stream_words,
  BSRS_stream_single,
  BSRS_reader_single,
  BSRS_stream_reader_single,
  BSRS_reader_multi,
  BSRS_stream_reader_multi,
  BSRS_stream_reader_multi3
} Bitstreamreadmode;

void gt_encseq_faststream(const GtEncseq *encseq,
                          Bitstreamreadmode bsrsmode,
                          unsigned int multiarg);
#endif
