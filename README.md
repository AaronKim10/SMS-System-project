# Aaron Kim
# SMS-System-project

Purpose: The purpose of this project is to pack and unpack lines of GMU-SMS text in order to save bandwidth. This system is similar to the
SMS 7-bit packing system, except that it packs 6-bit characters in an array.

The following table is the modified ASCII table used for this system. All printable ASCII characters that are NOT shown in this table will
bre translated to the "#" character. All non-printable ASCII characters will be translated to NULL.

Table 1 - The George Mason University Standard Code for Information Interchange (GMUSCII)
Dec     Hex   Char	Dec     Hex   Char	Dec  Hex   Char	 Dec  Hex   Char
0       00    NULL	 16     10      G	  32   20     W	   48    30     ,
1       01      .	   17     11      H	  33   21     X	   49    31     -
2       02      /	   18     12      I	  34   22     Y	   50    32     0
3       03      :	   19     13      J	  35   23     Z	   51    33     1
4       04      ;	   20     14      K	  36   24   Space  52    34     2
5       05      <	   21     15      L	  37   25     !	   53    35     3
6       06      =	   22     16      M	  38   26     "	   54    36     4
7       07      >	   23     17      N	  39   27     #	   55    37     5
8       08      ?	   24     18      O	  40   28     $	   56    38     6
9       09      @	   25     19      P	  41   29     %	   57    39     7
10      0A      A	   26     1A      Q	  42   2A     &	   58    3A     8
11      0B      B	   27     1B      R	  43   2B     '	   59    3B     9
12      0C      C	   28     1C      S	  44   2C     (	   60    3C     [
13      0D      D	   29     1D      T	  45   2D     )	   61    3D     \
14      0E      E	   30     1E      U	  46   2E     *	   62    3E     ]
15      0F      F	   31     1F      V	  47   2F     +	   63    3F     _
