#include "node.hpp"

node* node::getnext()
{
    return next;
}



node::node(string userid, string data)
{
    next = nullptr;
    name = userid;
    encryptedpassword = data;
}

void node::setnext(node* newnext)
{
    this->next = newnext;
}

