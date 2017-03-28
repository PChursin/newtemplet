/*$TET$header*/
#include <templet.hpp>
/*$TET$*/

using namespace TEMPLET;

struct my_engine : engine{
	my_engine(int argc, char *argv[]){
		::init(this, argc, argv);
	}
	void run(){ TEMPLET::run(this); }
	void map(){ TEMPLET::map(this); }
};

enum MESSAGE_TAGS{ MES_test_msg, START };

#pragma templet ~test_msg

struct test_msg : message{
	test_msg(actor*a, engine*e){
		::init(this, e);
		_actor = a;
	}

	bool access(actor*a){
		return TEMPLET::access(this, a);
	}

	void send(actor*a){
		TEMPLET::send(this, a, MES_test_msg);
	}

/*$TET$test_msg$$data*/
/*$TET$*/
};

#pragma templet *generator+

struct generator : actor{
	generator(my_engine&e){
		::init(this, &e, generator_recv_adapter);
		::init(&_start, &e);
		::send(&_start, this, START);
/*$TET$generator$generator*/
/*$TET$*/
	}

	void at(int _at){ TEMPLET::at(this, _at); }
	void delay(double t){ TEMPLET::delay(this, t); }
	void stop(){ TEMPLET::stop(this); }

	static void generator_recv_adapter (actor*a, message*m, int tag){
		switch(tag){
			case MES_test_msg: ((generator*)a)->recv_test_msg(*((test_msg*)m)); break;
			case START: ((generator*)a)->start(); break;
		}
	}

	void start(){
/*$TET$generator$start*/
/*$TET$*/
	}

	void recv_test_msg(test_msg&m){
/*$TET$generator$recv_test_msg*/
/*$TET$*/
	}

/*$TET$generator$$code&data*/
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

	void at(int _at){ TEMPLET::at(this, _at); }
	void delay(double t){ TEMPLET::delay(this, t); }
	void stop(){ TEMPLET::stop(this); }

	static void receiver_recv_adapter (actor*a, message*m, int tag){
		switch(tag){
			case MES_test_msg: ((receiver*)a)->recv_test_msg(*((test_msg*)m)); break;
		}
	}

	void recv_test_msg(test_msg&m){
/*$TET$receiver$recv_test_msg*/
/*$TET$*/
	}

/*$TET$receiver$$code&data*/
/*$TET$*/
};

/*$TET$footer*/
/*$TET$*/
