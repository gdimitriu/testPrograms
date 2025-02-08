/*
	Copyright 2000 Gabriel Dimitriu

	This file is part of Algorithms and Cpp.
	This is the implementation of a queue.

    Algorithms and C is free software; you can redistribute it 
	and/or modify it under the terms of the GNU General Public License 
	as published by the Free Software Foundation; either version 2 of 
	the License, or (at your option) any later version.

    Algorithms and C is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License
    along with Algorithms and Cpp; if not, write to the Free Software
    Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  
*/
#include<iostream.h>

class obiect
{
	int value;
public:
	obiect(int j) {value=j;}
	obiect() 
	{
		cout<<"Input the value.\n";
		cin>>value;
	}
	void print(){ cout<<"The value is "<<value<<"\n";}
};

class 	element:private obiect
{
public:
	element *anterieur;
	element():obiect() {}
	element(int i):obiect(i){}
	~element(){ print();}
};

class queue
{
	element *elem;
	element *derrier;
	int nr;
public:
	queue(){ nr=0;}
	void push();
	void pop();
};
int main()
{
	queue q;
	for(int i=0;i<3;i++) q.push();
	for(int i=0;i<3;i++) q.pop();
}
void queue::push()
{
	//push into queue
	elem=new element;
	elem->anterieur=derrier;
	derrier=elem;
	nr++;
}
void queue::pop()
{
	//pop from queue
	element *pelem;
	pelem=derrier;
	derrier=pelem->anterieur;
	delete pelem;
}