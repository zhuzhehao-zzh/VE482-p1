#ifndef EXECUTE_H
#define EXECUTE_H

#include "macro.h"


int check_o_redirect(char args[][ARGUMENTLEN]);
void execute_pipe(char args[][ARGUMENTLEN], int index, int p[2], int bg, int num);
int execute(char args[][ARGUMENTLEN], int starting_point);


#endif
