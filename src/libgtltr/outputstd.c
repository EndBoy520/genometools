/*
  Copyright (c) 2007 David Ellinghaus <dellinghaus@zbh.uni-hamburg.de>
  Copyright (c) 2007 Center for Bioinformatics, University of Hamburg
  See LICENSE file or http://genometools.org/license.html for license details.
*/

#include "libgtcore/env.h"
#include "libgtmatch/sarr-def.h"
#include "libgtmatch/encseq-def.h"
#include "libgtmatch/readmode-def.h"
#include "libgtmatch/pos2seqnum.pr"
#include "libgtmatch/symboldef.h"
#include "libgtmatch/alphabet.pr"
#include "libgtmatch/intcode-def.h"
#include "libgtmatch/sfx-mappedstr.pr"

#include "ltrharvest-opt.h"

/*
   The following function prints the predicted LTR retrotransposon
   results to stdout.
 */
/* CAUTION: For output the positions will be decreased by one,
 *          since normally in annotation first base in sequence
 *          is position 1 instead of 0.
 */
int showinfoiffoundfullLTRs(LTRharvestoptions *lo,
    const Sequentialsuffixarrayreader *ssar,
    Env *env)
{
  LTRboundaries *boundaries;
  unsigned long h,
                i;
  unsigned int contignumber;
  Seqpos offset;
  unsigned long numofdbsequences =
     numofdbsequencesSequentialsuffixarrayreader(ssar);
  const Uchar *characters;
  const Encodedsequence *encseq =
     encseqSequentialsuffixarrayreader(ssar);

  /* in order to get to visible dna characters */
  characters = getcharactersAlphabet(
                 alphabetSequentialsuffixarrayreader(ssar));
  Seqpos *markpos = NULL;

  /* calculate markpos array for sequence offset */
  if ( numofdbsequences > 1)
  {
    markpos = encseq2markpositions(
	encseqSequentialsuffixarrayreader(ssar),
	numofdbsequencesSequentialsuffixarrayreader(ssar),
	env);
    if (markpos == NULL)
    {
      return -1;
    }
  }

  if (lo->longoutput)
  {
    if (lo->arrayLTRboundaries.nextfreeLTRboundaries == 0)
    {
      printf("No full LTR-pair predicted.\n");
    }
    else
    {
      printf("# predictions are reported in the following way\n");
      printf("# s(ret) e(ret) l(ret) ");
      printf("s(lLTR) e(lLTR) l(lLTR)");
      if (lo->minlengthTSD > (unsigned long) 1)
      {
	printf(" TSD l(TSD)");
      }
      if (lo->motif.allowedmismatches < (unsigned int)4)
      {
	printf(" m(lLTR)");
      }
      printf(" s(rLTR) e(rLTR) l(rLTR)");
      if (lo->minlengthTSD > (unsigned long) 1)
      {
	printf(" TSD l(TSD)");
      }
      if (lo->motif.allowedmismatches < (unsigned int)4)
      {
	printf(" m(rLTR)");
      }
      printf(" sim(LTRs)");
      printf(" seq-nr");
      printf("\n# where:\n");
      printf("# s = starting position\n");
      printf("# e = ending position\n");
      printf("# l = length\n");
      if (lo->motif.allowedmismatches < (unsigned int)4)
      {
	printf("# m = motif\n");
      }
      printf("# ret = LTR-retrotransposon\n");
      printf("# lLTR = left LTR\n");
      printf("# rLTR = right LTR\n");
      if (lo->minlengthTSD > (unsigned long) 1)
      {
	printf("# TSD = target site duplication\n");
      }
      printf("# sim = similarity\n");
      printf("# seq-nr = sequence number\n");

      /* print output sorted by contignumber*/
      for (h = 0; h < numofdbsequences; h++)
      {
	for (i = 0; i < lo->arrayLTRboundaries.nextfreeLTRboundaries; i++)
	{
	  boundaries = &(lo->arrayLTRboundaries.spaceLTRboundaries[i]);
	  contignumber = boundaries->contignumber;
	  if ( (!boundaries->skipped) && (unsigned long)contignumber == h)
	  {
	    if ( contignumber == 0)
	    {
	      offset = (Seqpos)0;
	    }
	    else
	    {
	      offset = markpos[contignumber-1]+(Seqpos)1;
	    }
            /* increase positions by 1 */
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast(boundaries->leftLTR_5 -offset + (Seqpos)1));
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast(boundaries->rightLTR_3 -offset  + (Seqpos)1));
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast((boundaries->rightLTR_3 - boundaries->leftLTR_5 + 1)));
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast(boundaries->leftLTR_5 -offset  + (Seqpos)1));
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast(boundaries->leftLTR_3 -offset  + (Seqpos)1));
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast((boundaries->leftLTR_3 - boundaries->leftLTR_5 + (Seqpos)1)));
	    if (lo->minlengthTSD > (unsigned long) 1)
	    {
	      Seqpos j;

	      for (j = 0; j < boundaries->lenleftTSD; j++)
	      {
		printf("%c",
		 characters[getencodedchar(encseq,
		    boundaries->leftLTR_5 - boundaries->lenleftTSD + j,
		    Forwardmode)]);
	      }
	      printf("  " FormatSeqpos "  ",
	             PRINTSeqposcast(boundaries->lenleftTSD));
	    }
	    if (lo->motif.allowedmismatches < (unsigned int)4)
	    {
	      printf("%c%c..%c%c  ",
		  characters[getencodedchar(encseq,
                                 boundaries->leftLTR_5,
				 Forwardmode)],
		  characters[getencodedchar(encseq,
                                 boundaries->leftLTR_5+(Seqpos)1,
				 Forwardmode)],
		  characters[getencodedchar(encseq,
                                 boundaries->leftLTR_3-(Seqpos)1,
				 Forwardmode)],
		  characters[getencodedchar(encseq,
                                 boundaries->leftLTR_3,
				 Forwardmode)] );
		  /*
		  virtualtree->alpha.characters[
		  *(sequence + boundaries->leftLTR_5)],
		  virtualtree->alpha.characters[
		  *(sequence + boundaries->leftLTR_5+1)],
		  virtualtree->alpha.characters[
		  *(sequence + boundaries->leftLTR_3-1)],
		  virtualtree->alpha.characters[
		  *(sequence + boundaries->leftLTR_3)] );
	          */
	    }
	    /* increase by 1 */
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast(boundaries->rightLTR_5 -offset + (Seqpos)1));
	    /* increase by 1 */
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast(boundaries->rightLTR_3 -offset + (Seqpos)1));
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast((boundaries->rightLTR_3 - boundaries->rightLTR_5 + 1)));
	    if (lo->minlengthTSD > (unsigned long) 1)
	    {
	      Seqpos j;

	      for (j = 0; j < boundaries->lenrightTSD; j++)
	      {
		printf("%c", characters[getencodedchar(encseq,
		    boundaries->rightLTR_3 + j + 1,
		    Forwardmode)]);
	      }
	      printf("  " FormatSeqpos "  ",
	             PRINTSeqposcast(boundaries->lenrightTSD));
	    }
	    if (lo->motif.allowedmismatches < (unsigned int)4)
	    {
	      printf("%c%c..%c%c",
		  characters[getencodedchar(encseq,
                                 boundaries->rightLTR_5,
				 Forwardmode)],
		  characters[getencodedchar(encseq,
			         boundaries->rightLTR_5+(Seqpos)1,
				 Forwardmode)],
		  characters[getencodedchar(encseq,
			         boundaries->rightLTR_3-(Seqpos)1,
				 Forwardmode)],
		  characters[getencodedchar(encseq,
			         boundaries->rightLTR_3,
				 Forwardmode)] );
		  /*
		  virtualtree->alpha.characters[
		  *(sequence + boundaries->rightLTR_5)],
		  virtualtree->alpha.characters[
		  *(sequence + boundaries->rightLTR_5+1)],
		  virtualtree->alpha.characters[
		  *(sequence + boundaries->rightLTR_3-1)],
		  virtualtree->alpha.characters[
		  *(sequence + boundaries->rightLTR_3)] );
	          */
	    }
	    /* print similarity */
	    printf("  %.2f", boundaries->similarity);
	    /* print sequence number */
	    printf("  %u\n", contignumber);
	  }
	}
      }
    }
  }
  /* short output */
  else
  {
    if (lo->arrayLTRboundaries.nextfreeLTRboundaries == 0)
    {
      /* nothing */
    }
    else
    {
      /* print short output of full length LTR-retrotransposon(s) */
      printf("# predictions are reported in the following way\n");
      printf("# s(ret) e(ret) l(ret) s(lLTR) e(lLTR) l(lLTR)"
	  " s(rLTR) e(rLTR) l(rLTR) sim(LTRs) seq-nr \n");
      printf("# where:\n");
      printf("# s = starting position\n");
      printf("# e = ending position\n");
      printf("# l = length\n");
      printf("# ret = LTR-retrotransposon\n");
      printf("# lLTR = left LTR\n");
      printf("# rLTR = right LTR\n");
      printf("# sim = similarity\n");
      printf("# seq-nr = sequence number\n");

      /* print output sorted by contignumber*/
      for (h = 0; h < numofdbsequences; h++)
      {
	for (i = 0; i < lo->arrayLTRboundaries.nextfreeLTRboundaries; i++)
	{
	  boundaries = &(lo->arrayLTRboundaries.spaceLTRboundaries[i]);
	  contignumber = boundaries->contignumber;
	  if ( (!boundaries->skipped) && contignumber == h)
	  {
	    if ( contignumber == 0)
	    {
	      offset = (Seqpos)0;
	    }
	    else
	    {
	      offset = markpos[contignumber-1]+(Seqpos)1;
	    }

            /* increase positions by 1 */
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast( boundaries->leftLTR_5 -offset + (Seqpos)1));
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast( boundaries->rightLTR_3 -offset + (Seqpos)1));
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast( (boundaries->rightLTR_3 - boundaries->leftLTR_5 +
		                  (Seqpos)1)));
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast( boundaries->leftLTR_5 -offset + (Seqpos)1));
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast( boundaries->leftLTR_3 -offset + (Seqpos)1));
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast( (boundaries->leftLTR_3 - boundaries->leftLTR_5 +
		                  (Seqpos)1)));
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast( boundaries->rightLTR_5 -offset + (Seqpos)1));
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast( boundaries->rightLTR_3 -offset + (Seqpos)1));
	    printf(FormatSeqpos "  ",
		PRINTSeqposcast( (boundaries->rightLTR_3 - boundaries->rightLTR_5 +
		                  (Seqpos)1)));
	    /* print similarity */
	    printf("%.2f  ", boundaries->similarity);
	    /* print sequence number */
	    printf("%u\n", contignumber);
	  }
	}
      }
    }
  }

  if ( numofdbsequences > 1)
  {
    FREESPACE(markpos);
  }
  return 0;
}
