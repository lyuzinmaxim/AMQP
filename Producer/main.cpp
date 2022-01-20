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
    string queue = "modem_queue";

    cout << "Starting receiving messages from " << uri << " queue: " << queue << endl;
    bool ready = true;
    while (ready) {
        Channel::ptr_t connection = Channel::Open(AmqpClient::Channel::OpenOpts::FromUri(uri));

        BasicMessage::ptr_t outgoing_message = BasicMessage::Create();
        string message = "Hello from laptop!";
        outgoing_message->Body(message);
        connection->BasicPublish("modem_exchange","modem", outgoing_message);
        ready = false;
    }

    return 0;
}
