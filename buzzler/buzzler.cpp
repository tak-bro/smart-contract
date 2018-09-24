#include<buzzler.hpp>

void buzzler_service::createuser(const account_name server,
                                 const account_name account)
{
    require_auth(server);

    // check account on user_table
    auto itr = user_table.find(account);
    eosio_assert(itr == user_table.end(), "Account already has a user");

    // create user
    user_table.emplace(account, [&](auto& p) {
        p.account    = account;
        p.buzz_token = 0;
        p.created_at = now();
    });

    // debug print
    print(name{account}, " user created");
}