/*--------------------------------------------------------------------------*/
/*  Copyright 2010-2016 Sergei Vostokin                                     */
/*                                                                          */
/*  Licensed under the Apache License, Version 2.0 (the "License");         */
/*  you may not use this file except in compliance with the License.        */
/*  You may obtain a copy of the License at                                 */
/*                                                                          */
/*  http://www.apache.org/licenses/LICENSE-2.0                              */
/*                                                                          */
/*  Unless required by applicable law or agreed to in writing, software     */
/*  distributed under the License is distributed on an "AS IS" BASIS,       */
/*  WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.*/
/*  See the License for the specific language governing permissions and     */
/*  limitations under the License.                                          */
/*--------------------------------------------------------------------------*/

#pragma once
#include <string>

// The TEMPLET domain-specific language: definition in C++

namespace dsl{

class message{
public:
	enum message_type{CALL,REPLY};
public:
	message(std::string name);
	message();
	~message();
public:
	message& name(std::string name);
	message& duplex();
	message& serilizable();
	message& content(std::string name, message_type);
	message& tag(std::string name, message_type);
};

class actor{
public:
	enum port_type{CLIENT,SERVER};
public:
	actor(string n);
	actor();
	~actor();
public:
	actor& port(std::string port_name, port_type, std::string message_name);
	actor& serilizable();
	actor& startable();
	actor& has_raw_ports();
};

}