#define N 5
#define START_I 2
#define START_J 2

//create moves
#define MOVE_X_0  2
#define MOVE_X_1  1
#define MOVE_X_2 -1
#define MOVE_X_3 -2
#define MOVE_X_4 -2
#define MOVE_X_5 -1
#define MOVE_X_6  1
#define MOVE_X_7  2


#define MOVE_Y_0  1
#define MOVE_Y_1  2
#define MOVE_Y_2  2
#define MOVE_Y_3  1
#define MOVE_Y_4 -1
#define MOVE_Y_5 -2
#define MOVE_Y_6 -2
#define MOVE_Y_7 -1

//create field
bit field[N*N] = 0;
//create step_counter
int step_count = 0;

//init current position
int cur_i;
int cur_j;

//bound check
//#define boundaries(x, y) x >= 0 && x < N && y >= 0 && y < N && field[x * N + y] == 0



inline change_state(new_cur_i, new_cur_j) {
	atomic {
		cur_i = new_cur_i;
		cur_j = new_cur_j;
		field[cur_i * N + cur_j] = 1;
		printf("field[%d], cur_i: %d, cur_j: %d, val: %d\n", cur_i * N + cur_j, cur_i, cur_j, field[cur_i * N + cur_j]);
		step_count = step_count + 1;
	}
}


active proctype main() {
	//set start_field as visited
	change_state(START_I, START_J);
	do
	:: cur_i + MOVE_X_0 >= 0 && cur_i + MOVE_X_0 < N && cur_j + MOVE_Y_0 >= 0 && cur_j + MOVE_Y_0 < N && field[(cur_i + MOVE_X_0) * N + cur_j + MOVE_Y_0] == 0 -> change_state(cur_i + MOVE_X_0, cur_j + MOVE_Y_0);
	:: cur_i + MOVE_X_1 >= 0 && cur_i + MOVE_X_1 < N && cur_j + MOVE_Y_1 >= 0 && cur_j + MOVE_Y_1 < N && field[(cur_i + MOVE_X_1) * N + cur_j + MOVE_Y_1] == 0 -> change_state(cur_i + MOVE_X_1, cur_j + MOVE_Y_1);
	:: cur_i + MOVE_X_2 >= 0 && cur_i + MOVE_X_2 < N && cur_j + MOVE_Y_2 >= 0 && cur_j + MOVE_Y_2 < N && field[(cur_i + MOVE_X_2) * N + cur_j + MOVE_Y_2] == 0 -> change_state(cur_i + MOVE_X_2, cur_j + MOVE_Y_2);
	:: cur_i + MOVE_X_3 >= 0 && cur_i + MOVE_X_3 < N && cur_j + MOVE_Y_3 >= 0 && cur_j + MOVE_Y_3 < N && field[(cur_i + MOVE_X_3) * N + cur_j + MOVE_Y_3] == 0  -> change_state(cur_i + MOVE_X_3, cur_j + MOVE_Y_3);
	:: cur_i + MOVE_X_4 >= 0 && cur_i + MOVE_X_4 < N && cur_j + MOVE_Y_4 >= 0 && cur_j + MOVE_Y_4 < N && field[(cur_i + MOVE_X_4) * N + cur_j + MOVE_Y_4] == 0 -> change_state(cur_i + MOVE_X_4, cur_j + MOVE_Y_4);
	:: cur_i + MOVE_X_5 >= 0 && cur_i + MOVE_X_5 < N && cur_j + MOVE_Y_5 >= 0 && cur_j + MOVE_Y_5 < N && field[(cur_i + MOVE_X_5) * N + cur_j + MOVE_Y_5] == 0  -> change_state(cur_i + MOVE_X_5, cur_j + MOVE_Y_5);
	:: cur_i + MOVE_X_6 >= 0 && cur_i + MOVE_X_6 < N && cur_j + MOVE_Y_6 >= 0 && cur_j + MOVE_Y_6 < N && field[(cur_i + MOVE_X_6) * N + cur_j + MOVE_Y_6] == 0 -> change_state(cur_i + MOVE_X_6, cur_j + MOVE_Y_6);
	:: cur_i + MOVE_X_7 >= 0 && cur_i + MOVE_X_7 < N && cur_j + MOVE_Y_7 >= 0 && cur_j + MOVE_Y_7 < N && field[(cur_i + MOVE_X_7) * N + cur_j + MOVE_Y_7] == 0  -> change_state(cur_i + MOVE_X_7, cur_j + MOVE_Y_7);
	od
}

ltl {
	!<>(step_count == N * N)
}
