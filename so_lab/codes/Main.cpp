#include <iostream>
#include <stdlib.h>
#include "LinkedList.h"

int main(){
	int max = 10;
	LinkedList* plist = new LinkedList();

	for (int i=0; i<max; i++){
		int num = rand()%max;
		plist->insert(num);
	}
	plist->print();
	plist->deleteAll();
	delete(plist);

	return 0;
}

