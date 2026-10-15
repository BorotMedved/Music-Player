#include "window.h"
#include "common.h"

int main(){
	
	Graphics g = {0};
	
	App a = {0};
	
	size_t sC = 255;
	Song *s = calloc(sC, sizeof *s);
	
	initSDL(&a,&g,s);
	
	while(1){
		r(&a,&g,s);
	}
	return 0;
}