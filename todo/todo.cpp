#include<todo.hpp>

void todo_service::create(account_name author, const uint64_t id, const string& title) {
    todo_repository.emplace(author, [&](auto& todo) {
        todo.id = id;
        todo.title = title;
        todo.completed = 0;
    });
    print("todo#", id, " created");
}
 
void todo_service::complete(account_name author, const uint64_t id) {
    auto target = todo_repository.find(id);
    eosio_assert(target != todo_repository.end(), "Todo does not exist");
    todo_repository.modify(target, author, [&](auto& todo) {
        todo.completed = 1;
    });
    print("todo#", id, " completed");
}
 
void todo_service::destroy(account_name author, const uint64_t id) {
    auto target = todo_repository.find(id);
    todo_repository.erase(target);
    print("todo#", id, " deleted");
}
 