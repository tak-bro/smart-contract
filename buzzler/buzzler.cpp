#include<buzzler.hpp>

void buzzler::hello(account_name user)
{
    print("Hello, ", name{user});
}

void buzzler::create(const account_name account,
                     const string&      nickname,
                     const string&      univ,
                     const string&      major)
{
    require_auth(account);

    // check account on user_table
    user_table users(_self, _self);
    auto itr = users.find(account);
    eosio_assert(itr == users.end(), "Account already has a user");

    // create user
    users.emplace(account, [&](auto& p) {
        p.account  = account;
        p.nickname = nickname;
        p.univ     = univ;
        p.major    = major;
        p.token    = 0;
        p.created_at = now();
    });

    // debug print
    print(name{account}, " user created");
}

void buzzler::update(const account_name account,
                     const string&      nickname,
                     const string&      univ,
                     const string&      major,
                     uint32_t     token)
{
    require_auth(account);

    // check account on user_table
    user_table users(_self, _self);
    auto itr = users.find(account);
    eosio_assert(itr != users.end(), "Account does not has a user");

    // update user
    users.modify(itr, account, [&](auto& p) {
        p.nickname = nickname;
        p.univ     = univ;
        p.major    = major;
        p.token    = token;
    });

    // debug print
    print(name{account}, " modified");
}

void buzzler::remove(const account_name account)
{
    require_auth(account);

    // check account on user_table
    user_table users(_self, _self);
    auto itr = users.find(account);
    eosio_assert(itr != users.end(), "Account does not has a user");

    // remove user
    users.erase(itr);

    // debug print
    print(name{account}, " user removed");
}

void buzzler::getuser(const account_name account)
{
    user_table users(_self, _self);
    auto itr = users.find(account);

    eosio_assert(itr != users.end(), "Account does not has a user");

    // print user
    print("Account: ", name{itr->account}, ", ");
    print("Nickname: ", itr->nickname.c_str(), ", ");
    print("Univ: ", itr->univ.c_str(), ", ");
    print("Major: ", itr->major.c_str(), ", ");
    print("Token: ", itr->token);
}
