// rmq-test.cpp : Defines the entry point for the console application.
//
#include "iostream"
#include "SimpleAmqpClient/SimpleAmqpClient.h"
#include "json.hpp"
#include <QtCore>

/*#pragma warning(disable : 4996)
#pragma warning(disable : 1593)
#pragma warning(disable : 0067) */

using namespace std;
using namespace AmqpClient;
using json = nlohmann::json;

int main()
{
    const string uri = "amqp://guest:guest@localhost:5672";
    //const string uri = "amqp://jetson:1111@10.0.111.10:5672";
    string queue = "modem_queue";
    cout << "Starting receiving messages from " << uri << " queue: " << queue << endl;

    bool ready = true;

    while (ready) {
        //Channel::ptr_t connection = Channel::Create("localhost", 5672, "guest", "guest", "/");
        Channel::ptr_t connection = Channel::Open(AmqpClient::Channel::OpenOpts::FromUri(uri));


        string consumer_tag = connection->BasicConsume(queue, "", true, true);
        Envelope::ptr_t received = connection->BasicConsumeMessage(consumer_tag);

        json parsed_json = json::parse( received->Message()->Body() );

//        cout << received->Message()->Body() << endl;

        int bottom_right_x = parsed_json["object"]["bbox"]["bottomrightx"];
        int bottom_right_y = parsed_json["object"]["bbox"]["bottomrighty"];
        int top_left_x = parsed_json["object"]["bbox"]["topleftx"];
        int top_left_y = parsed_json["object"]["bbox"]["toplefty"];
        cout << "top left x:" << top_left_x << "top left y:" << top_left_y << endl;
        cout << "bottom right x:" << bottom_right_x << "bottom right y:" << bottom_right_y << endl;

    }

//    return 0;
}
