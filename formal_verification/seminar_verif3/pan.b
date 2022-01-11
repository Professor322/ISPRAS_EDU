	switch (t->back) {
	default: Uerror("bad return move");
	case  0: goto R999; /* nothing to undo */

		 /* CLAIM ltl_0 */
;
		
	case 3: // STATE 1
		goto R999;

	case 4: // STATE 10
		;
		p_restor(II);
		;
		;
		goto R999;

		 /* PROC main */

	case 5: // STATE 5
		;
		now.step_count = trpt->bup.ovals[3];
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = trpt->bup.ovals[2];
		now.cur_j = trpt->bup.ovals[1];
		now.cur_i = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 4);
		goto R999;
;
		;
		
	case 7: // STATE 13
		;
		now.step_count = trpt->bup.ovals[3];
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = trpt->bup.ovals[2];
		now.cur_j = trpt->bup.ovals[1];
		now.cur_i = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 4);
		goto R999;
;
		;
		
	case 9: // STATE 21
		;
		now.step_count = trpt->bup.ovals[3];
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = trpt->bup.ovals[2];
		now.cur_j = trpt->bup.ovals[1];
		now.cur_i = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 4);
		goto R999;
;
		;
		
	case 11: // STATE 29
		;
		now.step_count = trpt->bup.ovals[3];
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = trpt->bup.ovals[2];
		now.cur_j = trpt->bup.ovals[1];
		now.cur_i = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 4);
		goto R999;
;
		;
		
	case 13: // STATE 37
		;
		now.step_count = trpt->bup.ovals[3];
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = trpt->bup.ovals[2];
		now.cur_j = trpt->bup.ovals[1];
		now.cur_i = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 4);
		goto R999;
;
		;
		
	case 15: // STATE 45
		;
		now.step_count = trpt->bup.ovals[3];
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = trpt->bup.ovals[2];
		now.cur_j = trpt->bup.ovals[1];
		now.cur_i = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 4);
		goto R999;
;
		;
		
	case 17: // STATE 53
		;
		now.step_count = trpt->bup.ovals[3];
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = trpt->bup.ovals[2];
		now.cur_j = trpt->bup.ovals[1];
		now.cur_i = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 4);
		goto R999;
;
		;
		
	case 19: // STATE 61
		;
		now.step_count = trpt->bup.ovals[3];
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = trpt->bup.ovals[2];
		now.cur_j = trpt->bup.ovals[1];
		now.cur_i = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 4);
		goto R999;
;
		;
		
	case 21: // STATE 69
		;
		now.step_count = trpt->bup.ovals[3];
		now.field[ Index(((now.cur_i*5)+now.cur_j), 25) ] = trpt->bup.ovals[2];
		now.cur_j = trpt->bup.ovals[1];
		now.cur_i = trpt->bup.ovals[0];
		;
		ungrab_ints(trpt->bup.ovals, 4);
		goto R999;

	case 22: // STATE 75
		;
		p_restor(II);
		;
		;
		goto R999;
	}

