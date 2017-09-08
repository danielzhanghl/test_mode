#include <iostream>
#include "cpprest/json.h"
//export LD_LIBRARY_PATH=../lib
//g++ -g -O3   -std=c++11 -fPIC -I../include -L../lib  -lcpprest    test.cpp   -o  testjson

using namespace web;

// Demonstrates how to iterate over a JSON object.
void decode_object(const json::object&);

void IterateJSONValue()
{

    json::value obj = json::value::object();
    json::value sub_obj = json::value::object();
    json::object& object = obj.as_object();


	//prepare test data
    obj[U("name")] = json::value(U("John"));
    obj[U("surname")] = json::value(U("Smith"));
    obj[U("age")] = json::value(50);
    obj[U("vegetarian")] = json::value(true);

	//object
    sub_obj[U("home")] = json::value(U("home address"));
    sub_obj[U("work")] = json::value(U("work address"));
    obj[U("address")] = json::value(sub_obj);

	//array
    json::value arr = json::value::array();
    arr[0] = json::value("110");
    arr[1] = json::value("119");
    obj[U("Tel.")] = arr;


	decode_object(object);
}

void decode_value (const json::value& input_value)
{

	switch(input_value.type())
	{
		case json::value::value_type::Number: 
			printf("value is %d\n", input_value.as_integer() );
			break;
		case json::value::value_type::String: 
			printf("value is %s\n", input_value.as_string().c_str() );
			break;
		case json::value::value_type::Boolean: 
			printf("value is %d\n", input_value.as_bool() );
			break;
		case json::value::value_type::Object: 
			decode_object(input_value.as_object());
			break;
		case json::value::value_type::Array: 
			{
			const json::array& value_arr = input_value.as_array();
			int array_size = value_arr.size();
			for (int array_iter=0; array_iter<array_size;array_iter++)
			{
				decode_value(value_arr.at(array_iter));
			}
			break;
			}
		default:
			printf("value is unknow type");
	}
}

void decode_object(const json::object& object)
{
    int count = 0;
    for(auto iter = object.cbegin(); iter != object.cend(); ++iter)
    {

        const json::value &value = iter->second;
    	printf("key is %s\n", iter->first.c_str() );
		decode_value(value);

        count++;
    }

}

int main()
{

    printf("start ...\n" );
    IterateJSONValue();
}
