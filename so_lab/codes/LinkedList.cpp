#include "LinkedList.h"
LinkedList::LinkedList(){
	_phead = nullptr;
}
void LinkedList::insert(int n){
	if(_phead == nullptr){
		_phead = new ListNode();
		_phead->_value = n;
		return;
	}
	else{
		ListNode* pn = new ListNode();
		pn->_value = n;
		ListNode* pnode = _phead;
		while (pnode->_pnext != nullptr && pnode->_pnext->_value < n){
			pnode = pnode->_pnext;
		}
		if(pnode->_pnext != nullptr && pnode->_value > n){
			pn->_pnext = _phead;
			_phead = pn;
		}
		if(pnode->_pnext == nullptr){
			pnode->_pnext = pn;
		} else{
			pn->_pnext = pnode->_pnext;
			pnode->_pnext = pn;
		}
	}
}
void LinkedList::print(void){
	ListNode* pnodes = _phead;
	while(pnodes->_pnext != nullptr){
		std::cout << pnodes->_value << " ";
		pnodes = pnodes->_pnext;
	}
}
void LinkedList::deleteAll(void){
	if (_phead != nullptr){
		deleteNodes(_phead);
	}
}
void LinkedList::deleteNodes(ListNode *pn) {
	if(pn->_pnext != nullptr){
		deleteNodes(pn->_pnext);
	}
	delete(pn);
}
