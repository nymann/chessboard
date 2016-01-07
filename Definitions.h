#pragma once

/* We are making a 10 by 12 array, with the intention of the following final layout.

X	X	X	X	X	X	X	X	X	X
X	r	n	b	q	k	b	n	r	X
X	p	p	p	p	p	p	p	p	X
X	 	 	 	 	 	 	 	 	X
X	 	 	 	 	 	 	 	 	X
X	 	 	 	 	 	 	 	 	X
X	 	 	 	 	 	 	 	 	X
X	 	 	 	 	 	 	 	 	X
X	P	P	P	P	P	P	P	P	X
X	R	N	B	Q	K	B	N	R	X
X	X	X	X	X	X	X	X	X	X
X	X	X	X	X	X	X	X	X	X

with the white pieces indicated by the capital letters.

Reasoning behind a 10 by 12 array, instead of a classic 8 by 8 array
Consider the following scenario:
8 by 8 array:
0	1	2	3	4	5	6	7
8	9	10	11	12	13	14	15
16	17	18	19	20	21	22	23
24	25	26	27	28	29	30	31
32	33	34	35	36	37	38	39
40	41	42	43	44	45	46	47
48	49	50	51	52	53	54	55
56	57	58	59	60	61	62	63

The way we would decide which squares the knight could move to in our array would be determined by: +-2*8 +-1,
+-8 +-2.. so in total 8 moves.

Let's say we have a knight on square nr. 62 on an empty board.
.. if you know the rules of chess, you would know that the
knight can move to square 45, 47 and 52.

But if we calculated the squares with the formula above.. we would get:
62+2*8+1=79, 62+2*8-1=77, 62-2*8+1=47, 62-2*8-1=45, 62+8+2=72, 62+8-2=68, 62-8+2=56, 62-8-2=52.
In total, 5 illegal moves.. we could hard code these cases (if pieceIsOnRankOne) { do something }, but that
would be rather trivial and the chance of missing a case high, resulting in a lot of debugging..

Instead we use a 10*12 array, like pictured above where X's indicates OFFBOARD.. this ensures, that we
can define the rules otherwise, fx. for the knight if we tested the same scenario again, this time the knight
is on square 97, like this, note that the rules change a bit, since we now have a border on our board (10 width):

X	X	X	X	X	X	X	X	X	X
X	X	X	X	X	X	X	X	X	X
X	21	22	23	24	25	26	27	28	X
X	31	32	33	34	35	36	37	38	X
X	41	42	43	44	45	46	47	48	X
X	51	52	53	54	55	56	57	58	X
X	61	62	63	64	65	66	67	68	X
X	71	72	73	74	75	76	77	78	X
X	81	82	83	84	85	86	87	88	X
X	91	92	93	94	95	96	N	98	X
X	X	X	X	X	X	X	X	X	X
X	X	X	X	X	X	X	X	X	X

97+2*10+1=118=X, 97+2*10-1=116=X, 97-2*10+1=78, 97-2*10-1=76, 97+10+2=109=X, 97+10-2=105=X, 97-10+2=91,
97-10-2=85.

This way of setting up the chessboard in programming is called a Mailbox board representation, more can
be read here https://chessprogramming.wikispaces.com/10x12+Board.
*/

#define SQUARES 120
#define F 99
enum { E, P, R, N, B, Q, K, p, r, n, b, q, k };
enum {WHITE, BLACK};
enum {WKC, WQC, BKC, BQC};

extern int board[120] = {
        F, F, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F,
        F, r, n, b, q, k, b, n, r, F,
        F, p, p, p, p, p, p, p, p, F,
        F, E, E, E, E, E, E, E, E, F,
        F, E, E, E, E, E, E, E, E, F,
        F, E, E, E, E, E, E, E, E, F,
        F, E, E, E, E, E, E, E, E, F,
        F, P, P, P, P, P, P, P, P, F,
        F, R, N, B, Q, K, B, N, R, F,
        F, F, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F
};

/*extern int board[120] = {
        F, F, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F,
        F, E, E, E, E, E, E, E, E, F,
        F, E, E, E, E, P, E, E, E, F,
        F, E, E, E, E, E, E, E, E, F,
        F, E, E, E, E, E, E, E, E, F,
        F, E, E, E, E, E, E, E, E, F,
        F, E, E, E, E, E, E, E, E, F,
        F, E, E, E, p, E, E, E, E, F,
        F, E, E, E, E, E, E, E, E, F,
        F, F, F, F, F, F, F, F, F, F,
        F, F, F, F, F, F, F, F, F, F
};*/

extern int halfMoves = 0;
extern int whiteQueensideCastle = 1;
extern int whiteKingsideCastle = 1;
extern int blackKingsideCastle = 1;
extern int blackQueensideCastle = 1;
extern int enPassantSquare = 0;
extern int halfMovesSinceEnPassantSquare = 0;