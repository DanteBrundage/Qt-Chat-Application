#include "messages.h"

Messages::Messages()
{

}

void Messages::append(QString message)
{
    this->insertRows(this->rowCount(), 1);
    this->setData(index(this->rowCount()-1), message.trimmed());
}
