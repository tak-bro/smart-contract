#include<buzzler.hpp>

void buzzler::hello(account_name user) {
    print("Hello, ", name{user});
}

void buzzler::create(const account_name account,
                     const string&      nickname,
                     const string&      univ,
                     const string&      major) {
    require_auth(account);

    // check account on profile_table
    user_table users(_self, _self);
    auto itr = users.find(account);
    eosio_assert(itr == users.end(), "Account already has a user");

    // create profile
    users.emplace(account, [&](auto& p) {
        p.account  = account;
        p.nickname = nickname;
        p.univ     = univ;
        p.major    = major;
        p.token    = 0;
        p.created_at = now();
    });

    print(name{account}, " profile created");
}
