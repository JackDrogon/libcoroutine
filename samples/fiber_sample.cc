#include <iostream>

#include "fiber.hh"
#include "scheduler.hh"

using namespace std;

static Scheduler sche;

void foo()
{
	cout << "foo" << endl;
	sche.Yield();
	cout << "foo" << endl;
	sche.Yield();
	cout << "foo" << endl;
	sche.Yield();
	cout << "foo" << endl;
}

void bar()
{
	cout << "bar" << endl;
	cout << "Current fiber: " << sche.Current() << endl;
	sche.Yield();
	cout << "bar" << endl;
	sche.Yield();
	cout << "bar" << endl;
	sche.Yield();
	cout << "bar" << endl;
}

void run()
{
	Fiber f1(&sche, foo);
	Fiber f2(&sche, bar);

	cout << "main start" << endl;
	while (f1.Status() && f2.Status()) {
		f1.Resume();
		f2.Resume();
	}
}

int main() { run(); }
