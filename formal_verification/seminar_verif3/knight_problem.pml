#define N 8
#define I 0
#define J 0
#define STATUS false

//set the field with -1
int field[N * N] = -1;
#define FIELD field
//set possible moves
int move_x[8];
int move_y[8];
#define MOVE_X move_x
#define MOVE_Y move_y

//set current position of the knight
int cur_i = I;
int cur_j = J;
int step_idx = 0;

#define CUR_I  cur_i
#define CUR_J  cur_j
#define STEP_IDX step_idx

proctype change_state(int move_idx) {
	CUR_I = CUR_J + MOVE_X[move_idx];
	CUR_J = CUR_J + MOVE_Y[move_idx];

	int field_idx = CUR_I * N + CUR_J;

	FIELD[field_idx] = STEP_IDX;
	if
        :: STEP_IDX < N * N - 1 -> STEP_IDX = STEP_IDX + 1; printf("%d * %d + %d = %d\n", CUR_I, N, CUR_J, field_idx);	printf("field[%d] = %d\n", field_idx, FIELD[field_idx]);
	:: STEP_IDX >= N * N - 1 -> run status_check(); run init_arr(); STEP_IDX = 1; FIELD[I * N + J] = 0;
	fi
	
	
}

#define boundaries(x, y) x >= 0 && x < N && y >= 0 && y < N && field[x * N + y] == -1;

init {
	move_x[0] =  1;
	move_x[1] = -1;
	move_x[2] =  2;
	move_x[3] =  2;
	move_x[4] = -2;
	move_x[5] = -2;
	move_x[6] = -1;
	move_x[7] =  1;
	
	move_y[0] =  2;
	move_y[1] =  2;
	move_y[2] =  1;
	move_y[3] = -1;
	move_y[4] =  1;
	move_y[5] = -1;
	move_y[6] = -2;
	move_y[7] = -2;
	run main();
}



proctype status_check() {
	int i = 0;
	bool is_ok = true;
	do
	:: i < N * N ->  if
			 :: FIELD[i] == -1 -> is_ok = false;
			 fi
			 i++;
	:: else break;
	od
	//STATUS = is_ok;
	printf("STATUS: %d\n", STATUS);
}


proctype init_arr() {
	int i = 0;
	bool is_ok = true;
	do
	:: i < N * N ->  FIELD[i] = -1; i++;
	:: else break;
	od
}

proctype main() {
	field[I * N + J] = step_idx; step_idx = step_idx + 1;
	do
	:: boundaries(cur_i + move_x[0], cur_j + move_y[0]) -> run change_state(0); 
	:: boundaries(cur_i + move_x[1], cur_j + move_y[1]) -> run change_state(1); 
	:: boundaries(cur_i + move_x[2], cur_j + move_y[2]) -> run change_state(2); 
	:: boundaries(cur_i + move_x[3], cur_j + move_y[3]) -> run change_state(3); 
	:: boundaries(cur_i + move_x[4], cur_j + move_y[4]) -> run change_state(4); 
	:: boundaries(cur_i + move_x[5], cur_j + move_y[5]) -> run change_state(5); 
	:: boundaries(cur_i + move_x[6], cur_j + move_y[6]) -> run change_state(6); 
	:: boundaries(cur_i + move_x[7], cur_j + move_y[7]) -> run change_state(7); 
	od
}	

ltl {
	!(<>STATUS == true)	
}
