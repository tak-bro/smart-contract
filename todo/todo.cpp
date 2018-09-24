#include<todo.hpp>

void todo_service::create(account_name   author,
                          const uint64_t id,
                          const string&  title)
{
    todo_table todos(_self, _self);
    todos.emplace(author, [&](auto& todo) {
        todo.id = id;
        todo.title = title;
        todo.completed = 0;
    });

    print("todo#", id, " created");
}
 
void todo_service::complete(account_name   author,
                            const uint64_t id)
{
    todo_table todos(_self, _self);
    auto target = todos.find(id);
    eosio_assert(target != todos.end(), "Todo does not exist");

    todos.modify(target, author, [&](auto& todo) {
        todo.completed = 1;
    });

    print("todo#", id, " completed");
}
 
void todo_service::destroy(account_name   author,
                           const uint64_t id)
{
    todo_table todos(_self, _self);
    auto target = todos.find(id);
    todos.erase(target);

    print("todo#", id, " deleted");
}
 