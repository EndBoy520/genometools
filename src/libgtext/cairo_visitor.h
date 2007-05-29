/*
  Copyright (c) 2006-2007 Gordon Gremme <gremme@zbh.uni-hamburg.de>
  Copyright (c) 2006-2007 Center for Bioinformatics, University of Hamburg
  See LICENSE file or http://genometools.org/license.html for license details.
*/

#ifndef CAIRO_VISITOR_H
#define CAIRO_VISITOR_H

/* implements the ``genome visitor'' interface */
typedef struct CairoVisitor CairoVisitor;

#include <libgtext/genome_visitor.h>

const GenomeVisitorClass* cairo_visitor_class(void);
GenomeVisitor*            cairo_visitor_new(char *png_filename, int width,
                                            unsigned int number_of_tracks,
                                            unsigned long from,
                                            unsigned long to, Env*);

#endif
