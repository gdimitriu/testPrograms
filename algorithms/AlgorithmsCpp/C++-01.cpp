/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Cpp.
	This is the implementation of operation with polinoms.

    Algorithms and Cpp is free software; you can redistribute it 
	and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation; either version 2 of 
	the License, or (at your option) any later version.

    Algorithms and Cpp is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Algorithms and Cpp; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/
#include<iostream.h>
class suma
{
	//this clas make the sum of the two elements
	protected:
		int val1;
		int val2;
	public:
		int rez;
	suma(){};
	suma(int tip1,int tip2)
	{
		val1=tip1;
		val2=tip2;
	}
	~suma(){};
	public:
		void adun()
		{
			rez=val1+val2;
		}
		void introduc()
		{
			cout<<"Input the first value val1=";
			cin>>val1;
			cout<<"Input the second value val2=";
			cin>>val2;
		}
		void printez()
		{
			cout<<"The sum is sum="<<val1<<"+"<<val2<<"="<<rez<<"\n";
		}
};

class numere: public suma
{
	//this class is derivated from suma and has product as a new operation
	public:
		int prod;
	numere(){};
	numere(int tip1,int tip2)
	{
		val1=tip1;
		val2=tip2;
	}
	public:
		void produs()
		{
			prod=val1*val2;
		}
		void printez()
		{
			cout<<"Suma is sum="<<val1<<"+"<<val2<<"="<<rez<<"\n";
			cout<<"The product is prod="<<val1<<"*"<<val2<<"="<<prod<<"\n";
		}
};
void test_sum()
{
	//function for test the class suma
	suma suma1,suma2;
	suma *suma3;
	suma1.introduc();
	suma2.introduc();
	suma1.adun();
	suma2.adun();
	suma1.printez();
	suma2.printez();
	suma3=new suma(suma1.rez,suma2.rez);
	suma3->adun();
	suma3->printez();
	delete suma3;
}
//function for testing the class numere
void test_numere()
{
	numere suma1,suma2;
	numere *suma3;
	suma1.introduc();
	suma2.introduc();
	suma1.adun();
	suma2.adun();
	suma1.produs();
	suma2.produs();
	suma1.printez();
	suma2.printez();
	suma3=new numere(suma1.rez,suma2.rez);
	suma3->adun();
	suma3->produs();
	suma3->printez();
	delete suma3;
}
int main()
{
 test_numere();
 test_sum();
 return 0;
}