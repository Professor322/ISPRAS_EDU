#define rand	pan_rand
#define pthread_equal(a,b)	((a)==(b))
#if defined(HAS_CODE) && defined(VERBOSE)
	#ifdef BFS_PAR
		bfs_printf("Pr: %d Tr: %d\n", II, t->forw);
	#else
		cpu_printf("Pr: %d Tr: %d\n", II, t->forw);
	#endif
#endif
	switch (t->forw) {
	default: Uerror("bad forward move");
	case 0:	/* if without executable clauses */
		continue;
	case 1: /* generic 'goto' or 'skip' */
		IfNotBlocked
		_m = 3; goto P999;
	case 2: /* generic 'else' */
		IfNotBlocked
		if (trpt->o_pm&1) continue;
		_m = 3; goto P999;

		 /* CLAIM ltl_0 */
	case 3: // STATE 1 - _spin_nvr.tmp:3 - [((step_count==(5*5)))] (6:0:0 - 1)
		
#if defined(VERI) && !defined(NP)
#if NCLAIMS>1
		{	static int reported1 = 0;
			if (verbose && !reported1)
			{	int nn = (int) ((Pclaim *)pptr(0))->_n;
				printf("depth %ld: Claim %s (%d), state %d (line %d)\n",
					depth, procname[spin_c_typ[nn]], nn, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported1 = 1;
				fflush(stdout);
		}	}
#else
		{	static int reported1 = 0;
			if (verbose && !reported1)
			{	printf("depth %d: Claim, state %d (line %d)\n",
					(int) depth, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported1 = 1;
				fflush(stdout);
		}	}
#endif
#endif
		reached[1][1] = 1;
		if (!((now.step_count==(5*5))))
			continue;
		/* merge: assert(!((step_count==(5*5))))(0, 2, 6) */
		reached[1][2] = 1;
		spin_assert( !((now.step_count==(5*5))), " !((step_count==(5*5)))", II, tt, t);
		/* merge: .(goto)(0, 7, 6) */
		reached[1][7] = 1;
		;
		_m = 3; goto P999; /* 2 */
	case 4: // STATE 10 - _spin_nvr.tmp:8 - [-end-] (0:0:0 - 1)
		
#if defined(VERI) && !defined(NP)
#if NCLAIMS>1
		{	static int reported10 = 0;
			if (verbose && !reported10)
			{	int nn = (int) ((Pclaim *)pptr(0))->_n;
				printf("depth %ld: Claim %s (%d), state %d (line %d)\n",
					depth, procname[spin_c_typ[nn]], nn, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported10 = 1;
				fflush(stdout);
		}	}
#else
		{	static int reported10 = 0;
			if (verbose && !reported10)
			{	printf("depth %d: Claim, state %d (line %d)\n",
					(int) depth, (int) ((Pclaim *)pptr(0))->_p, src_claim[ (int) ((Pclaim *)pptr(0))->_p ]);
				reported10 = 1;
				fflush(stdout);
		}	}
#endif
#endif
		reached[1][10] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */

		 /* PROC main */
	case 5: // STATE 1 - knight_problem_v2.pml:41 - [cur_i = 2] (0:72:4 - 1)
		IfNotBlocked
		reached[0][1] = 1;
		(trpt+1)->bup.ovals = grab_ints(4);
		(trpt+1)->bup.ovals[0] = now.cur_i;
		now.cur_i = 2;
#ifdef VAR_RANGES
		logval("cur_i", now.cur_i);
#endif
		;
		/* merge: cur_j = 2(72, 2, 72) */
		reached[0][2] = 1;
		(trpt+1)->bup.ovals[1] = now.cur_j;
		now.cur_j = 2;
#ifdef VAR_RANGES
		logval("cur_j", now.cur_j);
#endif
		;
		/* merge: field[((cur_i*5)+cur_j)] = 1(72, 3, 72) */
		reached[0][3] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]);
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = 1;
#ifdef VAR_RANGES
		logval("field[((cur_i*5)+cur_j)]", ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
#endif
		;
		/* merge: printf('field[%d], cur_i: %d, cur_j: %d, val: %d\\n',((cur_i*5)+cur_j),cur_i,cur_j,field[((cur_i*5)+cur_j)])(72, 4, 72) */
		reached[0][4] = 1;
		Printf("field[%d], cur_i: %d, cur_j: %d, val: %d\n", ((now.cur_i*5)+now.cur_j), now.cur_i, now.cur_j, ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
		/* merge: step_count = (step_count+1)(72, 5, 72) */
		reached[0][5] = 1;
		(trpt+1)->bup.ovals[3] = now.step_count;
		now.step_count = (now.step_count+1);
#ifdef VAR_RANGES
		logval("step_count", now.step_count);
#endif
		;
		/* merge: .(goto)(0, 73, 72) */
		reached[0][73] = 1;
		;
		_m = 3; goto P999; /* 5 */
	case 6: // STATE 8 - knight_problem_v2.pml:54 - [(((((((cur_i+2)>=0)&&((cur_i+2)<5))&&((cur_j+1)>=0))&&((cur_j+1)<5))&&(field[((((cur_i+2)*5)+cur_j)+1)]==0)))] (0:0:0 - 1)
		IfNotBlocked
		reached[0][8] = 1;
		if (!(((((((now.cur_i+2)>=0)&&((now.cur_i+2)<5))&&((now.cur_j+1)>=0))&&((now.cur_j+1)<5))&&(((int)now.field[ Index(((((now.cur_i+2)*5)+now.cur_j)+1), 25) ])==0))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 7: // STATE 9 - knight_problem_v2.pml:41 - [cur_i = (cur_i+2)] (0:72:4 - 1)
		IfNotBlocked
		reached[0][9] = 1;
		(trpt+1)->bup.ovals = grab_ints(4);
		(trpt+1)->bup.ovals[0] = now.cur_i;
		now.cur_i = (now.cur_i+2);
#ifdef VAR_RANGES
		logval("cur_i", now.cur_i);
#endif
		;
		/* merge: cur_j = (cur_j+1)(72, 10, 72) */
		reached[0][10] = 1;
		(trpt+1)->bup.ovals[1] = now.cur_j;
		now.cur_j = (now.cur_j+1);
#ifdef VAR_RANGES
		logval("cur_j", now.cur_j);
#endif
		;
		/* merge: field[((cur_i*5)+cur_j)] = 1(72, 11, 72) */
		reached[0][11] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]);
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = 1;
#ifdef VAR_RANGES
		logval("field[((cur_i*5)+cur_j)]", ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
#endif
		;
		/* merge: printf('field[%d], cur_i: %d, cur_j: %d, val: %d\\n',((cur_i*5)+cur_j),cur_i,cur_j,field[((cur_i*5)+cur_j)])(72, 12, 72) */
		reached[0][12] = 1;
		Printf("field[%d], cur_i: %d, cur_j: %d, val: %d\n", ((now.cur_i*5)+now.cur_j), now.cur_i, now.cur_j, ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
		/* merge: step_count = (step_count+1)(72, 13, 72) */
		reached[0][13] = 1;
		(trpt+1)->bup.ovals[3] = now.step_count;
		now.step_count = (now.step_count+1);
#ifdef VAR_RANGES
		logval("step_count", now.step_count);
#endif
		;
		/* merge: .(goto)(0, 73, 72) */
		reached[0][73] = 1;
		;
		_m = 3; goto P999; /* 5 */
	case 8: // STATE 16 - knight_problem_v2.pml:55 - [(((((((cur_i+1)>=0)&&((cur_i+1)<5))&&((cur_j+2)>=0))&&((cur_j+2)<5))&&(field[((((cur_i+1)*5)+cur_j)+2)]==0)))] (0:0:0 - 1)
		IfNotBlocked
		reached[0][16] = 1;
		if (!(((((((now.cur_i+1)>=0)&&((now.cur_i+1)<5))&&((now.cur_j+2)>=0))&&((now.cur_j+2)<5))&&(((int)now.field[ Index(((((now.cur_i+1)*5)+now.cur_j)+2), 25) ])==0))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 9: // STATE 17 - knight_problem_v2.pml:41 - [cur_i = (cur_i+1)] (0:72:4 - 1)
		IfNotBlocked
		reached[0][17] = 1;
		(trpt+1)->bup.ovals = grab_ints(4);
		(trpt+1)->bup.ovals[0] = now.cur_i;
		now.cur_i = (now.cur_i+1);
#ifdef VAR_RANGES
		logval("cur_i", now.cur_i);
#endif
		;
		/* merge: cur_j = (cur_j+2)(72, 18, 72) */
		reached[0][18] = 1;
		(trpt+1)->bup.ovals[1] = now.cur_j;
		now.cur_j = (now.cur_j+2);
#ifdef VAR_RANGES
		logval("cur_j", now.cur_j);
#endif
		;
		/* merge: field[((cur_i*5)+cur_j)] = 1(72, 19, 72) */
		reached[0][19] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]);
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = 1;
#ifdef VAR_RANGES
		logval("field[((cur_i*5)+cur_j)]", ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
#endif
		;
		/* merge: printf('field[%d], cur_i: %d, cur_j: %d, val: %d\\n',((cur_i*5)+cur_j),cur_i,cur_j,field[((cur_i*5)+cur_j)])(72, 20, 72) */
		reached[0][20] = 1;
		Printf("field[%d], cur_i: %d, cur_j: %d, val: %d\n", ((now.cur_i*5)+now.cur_j), now.cur_i, now.cur_j, ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
		/* merge: step_count = (step_count+1)(72, 21, 72) */
		reached[0][21] = 1;
		(trpt+1)->bup.ovals[3] = now.step_count;
		now.step_count = (now.step_count+1);
#ifdef VAR_RANGES
		logval("step_count", now.step_count);
#endif
		;
		/* merge: .(goto)(0, 73, 72) */
		reached[0][73] = 1;
		;
		_m = 3; goto P999; /* 5 */
	case 10: // STATE 24 - knight_problem_v2.pml:56 - [(((((((cur_i+-(1))>=0)&&((cur_i+-(1))<5))&&((cur_j+2)>=0))&&((cur_j+2)<5))&&(field[((((cur_i+ -(1))*5)+cur_j)+2)]==0)))] (0:0:0 - 1)
		IfNotBlocked
		reached[0][24] = 1;
		if (!(((((((now.cur_i+ -(1))>=0)&&((now.cur_i+ -(1))<5))&&((now.cur_j+2)>=0))&&((now.cur_j+2)<5))&&(((int)now.field[ Index(((((now.cur_i+ -(1))*5)+now.cur_j)+2), 25) ])==0))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 11: // STATE 25 - knight_problem_v2.pml:41 - [cur_i = (cur_i+-(1))] (0:72:4 - 1)
		IfNotBlocked
		reached[0][25] = 1;
		(trpt+1)->bup.ovals = grab_ints(4);
		(trpt+1)->bup.ovals[0] = now.cur_i;
		now.cur_i = (now.cur_i+ -(1));
#ifdef VAR_RANGES
		logval("cur_i", now.cur_i);
#endif
		;
		/* merge: cur_j = (cur_j+2)(72, 26, 72) */
		reached[0][26] = 1;
		(trpt+1)->bup.ovals[1] = now.cur_j;
		now.cur_j = (now.cur_j+2);
#ifdef VAR_RANGES
		logval("cur_j", now.cur_j);
#endif
		;
		/* merge: field[((cur_i*5)+cur_j)] = 1(72, 27, 72) */
		reached[0][27] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]);
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = 1;
#ifdef VAR_RANGES
		logval("field[((cur_i*5)+cur_j)]", ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
#endif
		;
		/* merge: printf('field[%d], cur_i: %d, cur_j: %d, val: %d\\n',((cur_i*5)+cur_j),cur_i,cur_j,field[((cur_i*5)+cur_j)])(72, 28, 72) */
		reached[0][28] = 1;
		Printf("field[%d], cur_i: %d, cur_j: %d, val: %d\n", ((now.cur_i*5)+now.cur_j), now.cur_i, now.cur_j, ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
		/* merge: step_count = (step_count+1)(72, 29, 72) */
		reached[0][29] = 1;
		(trpt+1)->bup.ovals[3] = now.step_count;
		now.step_count = (now.step_count+1);
#ifdef VAR_RANGES
		logval("step_count", now.step_count);
#endif
		;
		/* merge: .(goto)(0, 73, 72) */
		reached[0][73] = 1;
		;
		_m = 3; goto P999; /* 5 */
	case 12: // STATE 32 - knight_problem_v2.pml:57 - [(((((((cur_i+-(2))>=0)&&((cur_i+-(2))<5))&&((cur_j+1)>=0))&&((cur_j+1)<5))&&(field[((((cur_i+ -(2))*5)+cur_j)+1)]==0)))] (0:0:0 - 1)
		IfNotBlocked
		reached[0][32] = 1;
		if (!(((((((now.cur_i+ -(2))>=0)&&((now.cur_i+ -(2))<5))&&((now.cur_j+1)>=0))&&((now.cur_j+1)<5))&&(((int)now.field[ Index(((((now.cur_i+ -(2))*5)+now.cur_j)+1), 25) ])==0))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 13: // STATE 33 - knight_problem_v2.pml:41 - [cur_i = (cur_i+-(2))] (0:72:4 - 1)
		IfNotBlocked
		reached[0][33] = 1;
		(trpt+1)->bup.ovals = grab_ints(4);
		(trpt+1)->bup.ovals[0] = now.cur_i;
		now.cur_i = (now.cur_i+ -(2));
#ifdef VAR_RANGES
		logval("cur_i", now.cur_i);
#endif
		;
		/* merge: cur_j = (cur_j+1)(72, 34, 72) */
		reached[0][34] = 1;
		(trpt+1)->bup.ovals[1] = now.cur_j;
		now.cur_j = (now.cur_j+1);
#ifdef VAR_RANGES
		logval("cur_j", now.cur_j);
#endif
		;
		/* merge: field[((cur_i*5)+cur_j)] = 1(72, 35, 72) */
		reached[0][35] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]);
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = 1;
#ifdef VAR_RANGES
		logval("field[((cur_i*5)+cur_j)]", ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
#endif
		;
		/* merge: printf('field[%d], cur_i: %d, cur_j: %d, val: %d\\n',((cur_i*5)+cur_j),cur_i,cur_j,field[((cur_i*5)+cur_j)])(72, 36, 72) */
		reached[0][36] = 1;
		Printf("field[%d], cur_i: %d, cur_j: %d, val: %d\n", ((now.cur_i*5)+now.cur_j), now.cur_i, now.cur_j, ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
		/* merge: step_count = (step_count+1)(72, 37, 72) */
		reached[0][37] = 1;
		(trpt+1)->bup.ovals[3] = now.step_count;
		now.step_count = (now.step_count+1);
#ifdef VAR_RANGES
		logval("step_count", now.step_count);
#endif
		;
		/* merge: .(goto)(0, 73, 72) */
		reached[0][73] = 1;
		;
		_m = 3; goto P999; /* 5 */
	case 14: // STATE 40 - knight_problem_v2.pml:58 - [(((((((cur_i+-(2))>=0)&&((cur_i+-(2))<5))&&((cur_j+-(1))>=0))&&((cur_j+-(1))<5))&&(field[((((cur_i+ -(2))*5)+cur_j)+ -(1))]==0)))] (0:0:0 - 1)
		IfNotBlocked
		reached[0][40] = 1;
		if (!(((((((now.cur_i+ -(2))>=0)&&((now.cur_i+ -(2))<5))&&((now.cur_j+ -(1))>=0))&&((now.cur_j+ -(1))<5))&&(((int)now.field[ Index(((((now.cur_i+ -(2))*5)+now.cur_j)+ -(1)), 25) ])==0))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 15: // STATE 41 - knight_problem_v2.pml:41 - [cur_i = (cur_i+-(2))] (0:72:4 - 1)
		IfNotBlocked
		reached[0][41] = 1;
		(trpt+1)->bup.ovals = grab_ints(4);
		(trpt+1)->bup.ovals[0] = now.cur_i;
		now.cur_i = (now.cur_i+ -(2));
#ifdef VAR_RANGES
		logval("cur_i", now.cur_i);
#endif
		;
		/* merge: cur_j = (cur_j+-(1))(72, 42, 72) */
		reached[0][42] = 1;
		(trpt+1)->bup.ovals[1] = now.cur_j;
		now.cur_j = (now.cur_j+ -(1));
#ifdef VAR_RANGES
		logval("cur_j", now.cur_j);
#endif
		;
		/* merge: field[((cur_i*5)+cur_j)] = 1(72, 43, 72) */
		reached[0][43] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]);
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = 1;
#ifdef VAR_RANGES
		logval("field[((cur_i*5)+cur_j)]", ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
#endif
		;
		/* merge: printf('field[%d], cur_i: %d, cur_j: %d, val: %d\\n',((cur_i*5)+cur_j),cur_i,cur_j,field[((cur_i*5)+cur_j)])(72, 44, 72) */
		reached[0][44] = 1;
		Printf("field[%d], cur_i: %d, cur_j: %d, val: %d\n", ((now.cur_i*5)+now.cur_j), now.cur_i, now.cur_j, ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
		/* merge: step_count = (step_count+1)(72, 45, 72) */
		reached[0][45] = 1;
		(trpt+1)->bup.ovals[3] = now.step_count;
		now.step_count = (now.step_count+1);
#ifdef VAR_RANGES
		logval("step_count", now.step_count);
#endif
		;
		/* merge: .(goto)(0, 73, 72) */
		reached[0][73] = 1;
		;
		_m = 3; goto P999; /* 5 */
	case 16: // STATE 48 - knight_problem_v2.pml:59 - [(((((((cur_i+-(1))>=0)&&((cur_i+-(1))<5))&&((cur_j+-(2))>=0))&&((cur_j+-(2))<5))&&(field[((((cur_i+ -(1))*5)+cur_j)+ -(2))]==0)))] (0:0:0 - 1)
		IfNotBlocked
		reached[0][48] = 1;
		if (!(((((((now.cur_i+ -(1))>=0)&&((now.cur_i+ -(1))<5))&&((now.cur_j+ -(2))>=0))&&((now.cur_j+ -(2))<5))&&(((int)now.field[ Index(((((now.cur_i+ -(1))*5)+now.cur_j)+ -(2)), 25) ])==0))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 17: // STATE 49 - knight_problem_v2.pml:41 - [cur_i = (cur_i+-(1))] (0:72:4 - 1)
		IfNotBlocked
		reached[0][49] = 1;
		(trpt+1)->bup.ovals = grab_ints(4);
		(trpt+1)->bup.ovals[0] = now.cur_i;
		now.cur_i = (now.cur_i+ -(1));
#ifdef VAR_RANGES
		logval("cur_i", now.cur_i);
#endif
		;
		/* merge: cur_j = (cur_j+-(2))(72, 50, 72) */
		reached[0][50] = 1;
		(trpt+1)->bup.ovals[1] = now.cur_j;
		now.cur_j = (now.cur_j+ -(2));
#ifdef VAR_RANGES
		logval("cur_j", now.cur_j);
#endif
		;
		/* merge: field[((cur_i*5)+cur_j)] = 1(72, 51, 72) */
		reached[0][51] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]);
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = 1;
#ifdef VAR_RANGES
		logval("field[((cur_i*5)+cur_j)]", ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
#endif
		;
		/* merge: printf('field[%d], cur_i: %d, cur_j: %d, val: %d\\n',((cur_i*5)+cur_j),cur_i,cur_j,field[((cur_i*5)+cur_j)])(72, 52, 72) */
		reached[0][52] = 1;
		Printf("field[%d], cur_i: %d, cur_j: %d, val: %d\n", ((now.cur_i*5)+now.cur_j), now.cur_i, now.cur_j, ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
		/* merge: step_count = (step_count+1)(72, 53, 72) */
		reached[0][53] = 1;
		(trpt+1)->bup.ovals[3] = now.step_count;
		now.step_count = (now.step_count+1);
#ifdef VAR_RANGES
		logval("step_count", now.step_count);
#endif
		;
		/* merge: .(goto)(0, 73, 72) */
		reached[0][73] = 1;
		;
		_m = 3; goto P999; /* 5 */
	case 18: // STATE 56 - knight_problem_v2.pml:60 - [(((((((cur_i+1)>=0)&&((cur_i+1)<5))&&((cur_j+-(2))>=0))&&((cur_j+-(2))<5))&&(field[((((cur_i+1)*5)+cur_j)+ -(2))]==0)))] (0:0:0 - 1)
		IfNotBlocked
		reached[0][56] = 1;
		if (!(((((((now.cur_i+1)>=0)&&((now.cur_i+1)<5))&&((now.cur_j+ -(2))>=0))&&((now.cur_j+ -(2))<5))&&(((int)now.field[ Index(((((now.cur_i+1)*5)+now.cur_j)+ -(2)), 25) ])==0))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 19: // STATE 57 - knight_problem_v2.pml:41 - [cur_i = (cur_i+1)] (0:72:4 - 1)
		IfNotBlocked
		reached[0][57] = 1;
		(trpt+1)->bup.ovals = grab_ints(4);
		(trpt+1)->bup.ovals[0] = now.cur_i;
		now.cur_i = (now.cur_i+1);
#ifdef VAR_RANGES
		logval("cur_i", now.cur_i);
#endif
		;
		/* merge: cur_j = (cur_j+-(2))(72, 58, 72) */
		reached[0][58] = 1;
		(trpt+1)->bup.ovals[1] = now.cur_j;
		now.cur_j = (now.cur_j+ -(2));
#ifdef VAR_RANGES
		logval("cur_j", now.cur_j);
#endif
		;
		/* merge: field[((cur_i*5)+cur_j)] = 1(72, 59, 72) */
		reached[0][59] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]);
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = 1;
#ifdef VAR_RANGES
		logval("field[((cur_i*5)+cur_j)]", ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
#endif
		;
		/* merge: printf('field[%d], cur_i: %d, cur_j: %d, val: %d\\n',((cur_i*5)+cur_j),cur_i,cur_j,field[((cur_i*5)+cur_j)])(72, 60, 72) */
		reached[0][60] = 1;
		Printf("field[%d], cur_i: %d, cur_j: %d, val: %d\n", ((now.cur_i*5)+now.cur_j), now.cur_i, now.cur_j, ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
		/* merge: step_count = (step_count+1)(72, 61, 72) */
		reached[0][61] = 1;
		(trpt+1)->bup.ovals[3] = now.step_count;
		now.step_count = (now.step_count+1);
#ifdef VAR_RANGES
		logval("step_count", now.step_count);
#endif
		;
		/* merge: .(goto)(0, 73, 72) */
		reached[0][73] = 1;
		;
		_m = 3; goto P999; /* 5 */
	case 20: // STATE 64 - knight_problem_v2.pml:61 - [(((((((cur_i+2)>=0)&&((cur_i+2)<5))&&((cur_j+-(1))>=0))&&((cur_j+-(1))<5))&&(field[((((cur_i+2)*5)+cur_j)+ -(1))]==0)))] (0:0:0 - 1)
		IfNotBlocked
		reached[0][64] = 1;
		if (!(((((((now.cur_i+2)>=0)&&((now.cur_i+2)<5))&&((now.cur_j+ -(1))>=0))&&((now.cur_j+ -(1))<5))&&(((int)now.field[ Index(((((now.cur_i+2)*5)+now.cur_j)+ -(1)), 25) ])==0))))
			continue;
		_m = 3; goto P999; /* 0 */
	case 21: // STATE 65 - knight_problem_v2.pml:41 - [cur_i = (cur_i+2)] (0:72:4 - 1)
		IfNotBlocked
		reached[0][65] = 1;
		(trpt+1)->bup.ovals = grab_ints(4);
		(trpt+1)->bup.ovals[0] = now.cur_i;
		now.cur_i = (now.cur_i+2);
#ifdef VAR_RANGES
		logval("cur_i", now.cur_i);
#endif
		;
		/* merge: cur_j = (cur_j+-(1))(72, 66, 72) */
		reached[0][66] = 1;
		(trpt+1)->bup.ovals[1] = now.cur_j;
		now.cur_j = (now.cur_j+ -(1));
#ifdef VAR_RANGES
		logval("cur_j", now.cur_j);
#endif
		;
		/* merge: field[((cur_i*5)+cur_j)] = 1(72, 67, 72) */
		reached[0][67] = 1;
		(trpt+1)->bup.ovals[2] = ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]);
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = 1;
#ifdef VAR_RANGES
		logval("field[((cur_i*5)+cur_j)]", ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
#endif
		;
		/* merge: printf('field[%d], cur_i: %d, cur_j: %d, val: %d\\n',((cur_i*5)+cur_j),cur_i,cur_j,field[((cur_i*5)+cur_j)])(72, 68, 72) */
		reached[0][68] = 1;
		Printf("field[%d], cur_i: %d, cur_j: %d, val: %d\n", ((now.cur_i*5)+now.cur_j), now.cur_i, now.cur_j, ((int)now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ]));
		/* merge: step_count = (step_count+1)(72, 69, 72) */
		reached[0][69] = 1;
		(trpt+1)->bup.ovals[3] = now.step_count;
		now.step_count = (now.step_count+1);
#ifdef VAR_RANGES
		logval("step_count", now.step_count);
#endif
		;
		/* merge: .(goto)(0, 73, 72) */
		reached[0][73] = 1;
		;
		_m = 3; goto P999; /* 5 */
	case 22: // STATE 75 - knight_problem_v2.pml:63 - [-end-] (0:0:0 - 1)
		IfNotBlocked
		reached[0][75] = 1;
		if (!delproc(1, II)) continue;
		_m = 3; goto P999; /* 0 */
	case  _T5:	/* np_ */
		if (!((!(trpt->o_pm&4) && !(trpt->tau&128))))
			continue;
		/* else fall through */
	case  _T2:	/* true */
		_m = 3; goto P999;
#undef rand
	}

