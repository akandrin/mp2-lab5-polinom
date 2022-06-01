#pragma once
#include "TList.h"

template <class T>
class THeadList : public TList<T> {
protected:
	TNode<T>* pHead;
private:
	void initialize()
	{
		pHead = new TNode<T>();
		pHead->pNext = pHead;
		pStop = pHead;
		pLast = pFirst = pHead;
		pCurr = pHead;
		pPrev = nullptr;
		len = 0;
	}

protected:
	void nulify() override
	{
		__super::nulify();
		pHead = nullptr;
	}
public:
	THeadList() {
		initialize();
	}
	
	~THeadList() {
		TList<T>::pStop = nullptr;
		if (TList<T>::pLast != nullptr)
			TList<T>::pLast->pNext = TList<T>::pStop;
		if (pHead != nullptr) {
			if (pHead->pNext == pHead) {
				TList<T>::pFirst = TList<T>::pLast = nullptr;
			}
			else {
				TList<T>::pFirst = pHead->pNext;
			}
		}
		delete pHead;
	}
	
	THeadList(const THeadList& theList)
		: TList<T>::TList(theList)
	{
		pHead = new TNode<T>(theList.pHead->value, pFirst);
		pStop = pHead;
		pCurr = pHead;
		pPrev = nullptr;

		if (pLast != NULL)
			pLast->pNext = pStop;
	}

	THeadList& operator=(THeadList theList)
	{
		pFirst = theList.pFirst;
		pLast = theList.pLast;
		pStop = theList.pStop;
		pCurr = theList.pCurr;
		pPrev = theList.pPrev;
		len = theList.len;


		pHead = theList.pHead;

		theList.nulify();

		return *this;
	}
	
	void InsFirst(T val) {
		TList<T>::InsFirst(val);
		pHead->pNext = TList<T>::pFirst;
	}
	
	void DelFirst() override {
		TList<T>::DelFirst();
		pHead->pNext = TList<T>::pFirst;
	}
};
