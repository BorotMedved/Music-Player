#include "window.h"
#include "common.h"

int main(int argc, char *argv[]){
	
	Graphics g = {0};
	
	App a = {0};
	
	size_t sC = 255;
	Song *s = calloc(sC, sizeof *s);
	
	const char *openPath = (argc > 1) ? argv[1] : NULL;
	
	initSDL(&a,&g,s, openPath);
	
	do{
		r(&a,&g,s);
		if(a.e == false){
			cU(&a,g.t,s);
			initSDL(&a,&g,s, openPath);
		}
	}while(a.e == true);
	
	return 0;
}