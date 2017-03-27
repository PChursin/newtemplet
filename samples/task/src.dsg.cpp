/*$TET$header*/
#include <templet.hpp>
/*$TET$*/

using namespace TEMPLET;

class my_engine{
public:
	my_engine(int argc, char *argv[]);
	void run();
	void map();
};

#pragma templet ~test_msg

struct test_msg : message{
	bool access(actor*);
	void send(actor*);

/*$TET$test_msg$$data*/
/*$TET$*/
};

#pragma templet *generator+

struct generator : actor{
	generator(my_engine&){
/*$TET$generator$generator*/
/*$TET$*/
	}

	void delay(double);
	void at(int);
	void stop();

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
};

#pragma templet *receiver

struct receiver : actor{
	receiver(my_engine&){
/*$TET$receiver$receiver*/
/*$TET$*/
	}

	void delay(double);
	void at(int);
	void stop();

	void recv_test_msg(test_msg&m){
/*$TET$receiver$recv_test_msg*/
/*$TET$*/
	}

/*$TET$receiver$$code&data*/
/*$TET$*/
};

/*$TET$footer*/
/*$TET$*/
