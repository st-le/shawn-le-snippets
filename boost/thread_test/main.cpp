#include <iostream>

#include <boost/thread.hpp>
#include <boost/thread/thread.hpp>

using namespace std;

struct callable
{
    void operator()() 
	{
		int i = 1 + 2;
	}
};

class myclass
{
public: 
	myclass();

	~myclass();

    void operator()() 
	{
		int i = 1 + 2;
	}
};


boost::thread copies_are_safe()
{
    callable x;
    return boost::thread(x);
} // x is destroyed, but the newly-created thread has a copy, so this is OK


boost::thread oops()
{
    callable x;
    return boost::thread(boost::ref(x));
} // x is destroyed, but the newly-created thread still has a reference
  // this leads to undefined behaviour

void find_the_question(int& the_answer)
{
	long int a=1, b=1, c=2;
	long int total = 0;
	for (int i=0; i<1000000000; i++)
	{
		a=a*c;
	}
	the_answer = total;
}



class BankAccount_mutex {
    boost::mutex mtx_;
    int balance_;
public:
    void Deposit(int amount) {
        mtx_.lock();
        balance_ += amount;
        mtx_.unlock();
    }
    void Withdraw(int amount) {
        mtx_.lock();
        balance_ -= amount;
        mtx_.unlock();
    }
    int GetBalance() {
        mtx_.lock();
        int b = balance_;
        mtx_.unlock();
        return balance_;
    }
};


class BankAccount{
    boost::mutex mtx_;
    int balance_;
public:
    void Deposit(int amount) {
        mtx_.lock();
        balance_ += amount;
        mtx_.unlock();
    }
    int Withdraw(int amount) {
        mtx_.lock();
        balance_ -= amount;
        mtx_.unlock();
		return 1;
    }
    int GetBalance() {
        mtx_.lock();
        int b = balance_;
        mtx_.unlock();
        return balance_;
    }
};

BankAccount JoesAccount;

void bankAgent()
{
    for (int i =10; i>0; --i) {
        //...
        JoesAccount.Deposit(500);
        //...
    }
}

void Joe() {
    for (int i =10; i>0; --i) {
        //...
        int myPocket = JoesAccount.Withdraw(100);
        std::cout << myPocket << std::endl;
        //...
    }
}



int main(int argc, char **argv)
{	
	oops();

	int num = 54;
	boost::thread my_thread_fun(find_the_question, num);
	//my_thread_fun.join();

	boost::thread::attributes attrs;
	
	int i=0;
	boost::thread my_thread_obj(myclass);

	// MUTEX example
	//...
    boost::thread thread1(bankAgent); // start concurrent execution of bankAgent
    boost::thread thread2(Joe); // start concurrent execution of Joe
    thread1.join();
    thread2.join();

	return 0;
}