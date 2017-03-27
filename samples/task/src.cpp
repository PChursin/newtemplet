/*$TET$header*/
#include <iostream>
#include <templet.hpp>
/*$TET$*/

using namespace TEMPLET;

struct my_engine : engine{
	my_engine(int argc, char *argv[]){
		::init(this, argc, argv);
	}
	void run(){ ::run(this); }
	void map(){ ::map(this); }
};

enum MES_TAGS{ MES_test_msg, START };

#pragma templet ~test_msg

struct test_msg : message{
	test_msg(actor*a, engine*e){
		::init(this, e);
	}

	bool access(actor*a){
		return ::access(this, a);
	}

	void send(actor*a){
		::send(this, a, MES_test_msg);
	}

/*$TET$test_msg$$data*/
	test_msg() { _sending = false; c = 0; _actor = 0; _tag = 0;}
	char c;
/*$TET$*/
};

#pragma templet *generator+

struct generator : actor{
	generator(my_engine&e){
		::init(this, &e, generator_recv_adapter);
		::init(&_start, &e);
		::send(&_start, this, MES_TAGS::START);
/*$TET$generator$generator*/
/*$TET$*/
	}

	void at(int _at){ ::at(this, _at); }
	void delay(double t){ ::delay(this, t); }
	void stop(){ ::stop(this); }

	friend void generator_recv_adapter (actor*a, message*m, int tag){
		switch(tag){
			case MES_TAGS::MES_test_msg: ((generator*)a)->recv_test_msg(*((test_msg*)m)); break;
			case MES_TAGS::START: ((generator*)a)->start(); break;
		}
	}

	void start(){
/*$TET$generator$start*/
		msgs = new test_msg * [n_msg];
		int i = 0;
		while (flag && i < n_msg)
		//while(flag)
		{
			//test_msg* m = new test_msg();
			//msgs[i] = m;
			//m->c = i;
			//m->send(rec);

			msgs[i] = new test_msg();
			msgs[i]->c = i;
			msgs[i]->send(rec);
			std::cout << "Sent message " << i++ << std::endl;
		}
		generated = i;
		stop();
/*$TET$*/
	}

	void recv_test_msg(test_msg&m){
/*$TET$generator$recv_test_msg*/
		flag = false;
		for (int j = 0; j < generated; j++)
			delete msgs[j];
		delete[] msgs;
		stop();
/*$TET$*/
	}

/*$TET$generator$$code&data*/
	const int n_msg = 20;
	int generated = 0;
	test_msg ** msgs;
	bool flag = true;
	actor* rec;
/*$TET$*/
	message _start;
};

#pragma templet *receiver

struct receiver : actor{
	receiver(my_engine&e){
		::init(this, &e, receiver_recv_adapter);
/*$TET$receiver$receiver*/
/*$TET$*/
	}

	void at(int _at){ ::at(this, _at); }
	void delay(double t){ ::delay(this, t); }
	void stop(){ ::stop(this); }

	friend void receiver_recv_adapter (actor*a, message*m, int tag){
		switch(tag){
			case MES_TAGS::MES_test_msg: ((receiver*)a)->recv_test_msg(*((test_msg*)m)); break;
		}
	}

	void recv_test_msg(test_msg&m){
/*$TET$receiver$recv_test_msg*/
		std::cout << (int) m.c << std::endl;
		if (m.c == 0)
		{
			m.send(gen);
			std::cout << "Stop sent" << std::endl;
		}
/*$TET$*/
	}

/*$TET$receiver$$code&data*/
	actor* gen;
/*$TET$*/
};

/*$TET$footer*/
int main(int argc, char * argv[])
{
	{
		my_engine e(argc, argv);
		generator g(e);
		receiver r(e);
		g.rec = &r;
		r.gen = &g;
		e.run();
	}
	return 0;
}
/*$TET$*/
