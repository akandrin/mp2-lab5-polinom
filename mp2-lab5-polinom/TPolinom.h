#pragma once
#include "THeadList.h"
#include "TMonom.h"
#include <iostream>
#include <regex>
#include <string>

class TPolinom : public THeadList<TMonom> {
private :
	void InsFirst(TMonom value) { return __super::InsFirst(value); }
	void InsLast(TMonom value) { return __super::InsLast(value); }
	void InsCurr(TMonom value) { return __super::InsCurr(value); }
public:
	TPolinom() {
		TMonom aMonom;
		pHead->value = aMonom;
	}
	
	void AddMonom(const TMonom& theMonom) {
		if (pLast->value > theMonom) {
			InsLast(theMonom);
			return;
		}
		for (Reset(); !IsEnd(); GoNext()) {
			if (pCurr->value == theMonom) {
				pCurr->value += theMonom;
				if (pCurr->value.coef == 0)
					DelCurr();
				return;
			}
			if (theMonom > pCurr->value) {
				InsCurr(theMonom);
				return;
			}
		}

		InsFirst(theMonom);
	}
	
	TPolinom operator+(TPolinom thePolinom) const
	{
		TPolinom aResult = *this;
		thePolinom.Reset();
		aResult.Reset();
		while (!thePolinom.IsEnd())
		{
			if (aResult.pCurr->value > thePolinom.pCurr->value)
			{
				aResult.GoNext();
			}
			else if (aResult.pCurr->value < thePolinom.pCurr->value)
			{
				aResult.InsCurr(thePolinom.pCurr->value);
				thePolinom.GoNext();
			}
			else
			{
				aResult.pCurr->value.coef += thePolinom.pCurr->value.coef;
				if (aResult.pCurr->value.coef != 0)
				{
					aResult.GoNext();
				}
				else
				{
					aResult.DelCurr();
				}
				thePolinom.GoNext();
			}
		}
		return aResult;
	}
	
	template <class T>
	TPolinom operator*(T coef) const
	{
		if (coef == 0)
			return TPolinom();
		TPolinom aResult(*this);
		for (aResult.Reset(); !aResult.IsEnd(); aResult.GoNext()) {
			aResult.pCurr->value *= coef;
		}
		return aResult;
	}
	
	template <class T>
	TPolinom& operator*=(T coef) {
		return *this = *this * coef;
	}
	
	friend std::istream& operator>>(std::istream& in, TPolinom& thePolinom)
	{
		int num = 0;
		in >> num;
		int coef, x, y, z;
		for (int i = 0; i < num; ++i)
		{
			in >> coef;
			in >> x;
			in >> y;
			in >> z;
			TMonom aMonom(coef, x, y, z);
			thePolinom.AddMonom(aMonom);
		}
		return in;
	}
	
	friend std::ostream& operator<<(std::ostream& out, const TPolinom& thePolinom)
	{
		if (thePolinom.len == 0)
			return out << 0;
		if (thePolinom.pFirst != nullptr)
		{
			out << thePolinom.pFirst->value;
			
			for (auto current = thePolinom.pFirst->pNext; current != thePolinom.pStop; current = current->pNext)
			{
				out << (current->value.coef >= 0 ? "+" : "");
				out << current->value;
			}
		}		
		return out;
	}
};
