#include "window.h"
#include "common.h"

int main(){
	
	Graphics g = {0};
	
	App a = {0};
	
	size_t sC = 255;
	Song *s = calloc(sC, sizeof *s);
	
	initSDL(&a,&g,s);
	
	do{
		r(&a,&g,s);
		if(a.e == false){
			cU(&a,g.t,s);
			initSDL(&a,&g,s);
		}
	}while(a.e == true);
	
	return 0;
}