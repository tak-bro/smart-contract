#include<buzzler.hpp>

void buzzler_service::createuser(const account_name account)
{
    // check buzzler server
    require_auth(_self);

    // check account on user_table
    auto itr = user_table.find(account);
    eosio_assert(itr == user_table.end(), "Account already has a user");

    // create user
    user_table.emplace(_self, [&](auto& p) {
        p.account    = account;
        p.buzz_token = 0;
        p.created_at = now();
    });

    // debug print
    print(name{account}, " user created");
}

void buzzler_service::updatetoken(const account_name account,
                                  const uint64_t     token)
{
    // check buzzler server
    require_auth(_self);

    // check account on user_table
    auto itr = user_table.find(account);
    eosio_assert(itr != user_table.end(), "Account does not has a user");

    // update user
    user_table.modify(itr, _self, [&](auto& p) {
        p.buzz_token    = token;
    });

    // debug print
    print(name{account}, " modified");
}