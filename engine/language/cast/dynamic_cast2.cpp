/////////////////////////////////////////////////////////////////////////////
// cast_operator_comparison.cpp                                                      
// Language:   C++                   
// Complier:    Visual Studio 2010, Xcode3.2.6 
// Platform:    MacBook Pro 2010
// Application:  none  
// Author:      Ider, Syracuse University  ider.cs@gmail.com
///////////////////////////////////////////////////////////////////////////

#include <string>
#include <iostream>
using namespace std;

class Parents
{
public:
	Parents(string n="Parent"){ name = n;}
	virtual ~Parents(){}

	virtual void Speak()
	{
		cout << "\tI am " << name << ", I love my children." << endl;
	}

	void Work()
	{
		cout << "\tI am " << name <<", I need to work for my family." << endl;;
	}

protected:
	string name;
};

class Children : public Parents
{
public:
	Children(string n="Child"):Parents(n){ }

	virtual ~Children(){}

	virtual void Speak()
	{
		cout << "\tI am " << name << ", I love my parents." << endl;
	}
	/*
	 **Children inherit Work() method from parents,
	 **it could be treated like part-time job.
	 */
	void Study()
	{
		cout << "\tI am " << name << ", I need to study for future." << endl;;
	}
	
private:
	//string name; //Inherit "name" member from Parents
};

class Stranger 
{
public:
	Stranger(string n="stranger"){name = n;}
	virtual ~Stranger(){}

	void Self_Introduce()
	{
		cout << "\tI am a stranger" << endl;
	}
	void Speak()
	{
		//cout << "I am a stranger" << endl;
		cout << "\tDo not talk to "<< name << ", who is a stranger." << endl;
	}

private:
	string name;
};

int main() {
	
	/******* cast from child class to base class *******/
	cout << "dynamic_cast from child class to base class:" << endl;
	Children * daughter_d = new Children("Daughter who pretend to be my mother");
	Parents * mother_d = dynamic_cast<Parents*> (daughter_d); //right, cast with polymorphism
	mother_d->Speak();
	mother_d->Work();
	//mother_d->Study(); //Error, no such method
	
	cout << "static_cast from child class to base class:" << endl;
	Children * son_s = new Children("Son who pretend to be my father");
	Parents * father_s = static_cast<Parents*> (son_s); //right, cast with polymorphism
	father_s->Speak();	
	father_s->Work();
	//father_s->Study(); //Error, no such method
	
	cout << endl;

    //return 0;
	
	/******* cast from base class to child class *******/	
	cout << "dynamic_cast from base class to child class:" << endl;
	Parents * father_d = new Parents("Father who pretend to be a my son");
	Children * son_d = dynamic_cast<Children*> (father_d); //no error, but not safe
	if (son_d)
	{
		son_d->Speak();
		son_d->Study();
	}
	else cout << "\t[null]" << endl;
	
	cout << "static_cast from base class to child class:" << endl;
	Parents * mother_s = new Parents("Mother who pretend to be a my daugher");
	Children * daughter_s = static_cast<Children*> (mother_s);  //no error, but not safe
	if (daughter_s)
	{
		daughter_s->Speak();
		daughter_s->Study();
	}
	else cout << "\t[null]" << endl;
	
	cout << endl;

    //return 0;
	
	/******* cast between non-related class *******/	
	cout << "dynamic_cast to non-related class:" << endl;
	Stranger* stranger_d = dynamic_cast<Stranger*> (daughter_d);
	if (stranger_d)
	{
		stranger_d->Self_Introduce();
		stranger_d->Speak();	
	}
	else cout <<"\t[null]"<<endl;
	
	//Stranger* stranger_s = static_cast<Stranger*> (son_s);    //Error, invalid cast
	
	cout << "reinterpret_cast to non-related class:" << endl;
	Stranger* stranger_r = reinterpret_cast<Stranger*> (son_s);
	if (stranger_r)
	{
		stranger_d->Self_Introduce();
		//stranger_d->Speak();	//This line would cause program crush,
		//as "name" could not be found corretly.
	}
	else cout << "\t[null]" << endl;

	cout << endl;

	/******* cas_ back*******/
	cout << "use dynamic_cast to cast back from dynamic_cast:" << endl;
	Children* child_d = dynamic_cast<Children*> (mother_d);
	if (child_d)
	{
		child_d->Speak();
		child_d->Work();
        child_d->Study();
	}
	else cout << "\t[null]" << endl;

	cout << "use dynamic_cast to cast back from static_cast:" << endl;
	Children* child_s = dynamic_cast<Children*> (father_s);
	if (child_s)
	{
		child_s->Speak();
		child_s->Work();
        child_s->Study();
	}
	else cout << "\t[null]" << endl;
	
    //cout<<typeid(stranger_r).name()<<endl;
    
	cout << "use dynamic_cast to cast back from reinterpret_cast:" << endl;
	Children* child_r = dynamic_cast<Children*> (stranger_r);
	if (child_r)
	{
		child_r->Speak();
		child_r->Work();
	}
	else cout << "\t[null]" << endl;
	
	delete daughter_d;
	delete son_s;
	delete father_d;
	delete mother_s;
	
	return 0;
}

/********************* Result *********************/

//dynamic_cast from child class to base class:
//	I am Daughter who pretend to be my mother, I love my parents.
//	I am Daughter who pretend to be my mother, I need to work for my family.
//static_cast from child class to base class:
//	I am Son who pretend to be my father, I love my parents.
//	I am Son who pretend to be my father, I need to work for my family.
//
//dynamic_cast from base class to child class:
//	[null]
//static_cast from base class to child class:
//	I am Mother who pretend to be a my daugher, I love my children.
//	I am Mother who pretend to be a my daugher, I need to study for future.
//
//dynamic_cast to non-related class:
//	[null]
//reinterpret_cast to non-related class:
//	I am a stranger
//
//use dynamic_cast to cast back from static_cast:
//	I am Son who pretend to be my father, I love my parents.
//	I am Son who pretend to be my father, I need to work for my family.
//use dynamic_cast to cast back from reinterpret_cast:
//	[null]
