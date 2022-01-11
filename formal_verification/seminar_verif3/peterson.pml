bool flag[2] = {0, 0};
bool turn = 0;

active [2] proctype P() {
	byte i = _pid;
	NCS:	printf("NCS\n"); 
	SET:	flag[i] = 1; turn = i;
	TST:	!(flag[1 - i] == 1 && turn == i);
	CRS:	printf("CRS\n");
	RST:	flag[i] = 0; goto NCS;
}

ltl Correct {
      [](!(P[0]@CRS && P[1]@CRS)) && //mutual exclusion 
      [](P[0]@SET -> <>P[0]@CRS) && //livness 0
      [](P[1]@SET -> <>P[1]@CRS) //livness 1
	 
  }
