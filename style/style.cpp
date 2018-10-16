#include<style.hpp>
#include<random.cpp>

void style_service::getrandom(account_name author)
{
    auto &random = random_gen::get_instance(author);
    // get random
    uint32_t random_num = random.range(99999999);

    print("random# ", random_num);
}

void style_service::createuser(const account_name account)
{
    // check buzzler server
    require_auth(_self);

    // check account on user_table
    auto itr = user_table.find(account);
    eosio_assert(itr == user_table.end(), "UserTable already has a user");

    // create user
    user_table.emplace(_self, [&](auto& p) {
        p.account    = account;
        p.created_at = now();
    });

    // debug print
    print(name{account}, " user created");
}