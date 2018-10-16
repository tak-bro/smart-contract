#include <eosiolib/eosio.hpp> 
#include <string>
#include <random.cpp>

using namespace eosio; 
using namespace std;

random_gen random_gen::instance;

class style_service: public eosio::contract {

    public: 
        style_service(account_name self): contract::contract(self),
                                          user_table(self, self) {}

        // @abi action
        void createuser(const account_name account);

        // @abi action
        void getrandom(account_name author);

    private:
       // @abi table users 
        struct user {
            account_name account;
            time         created_at;

            auto primary_key() const { return account; }

            EOSLIB_SERIALIZE(user, (account)(created_at))
        };

          // define tables
        multi_index<N(users), user> user_table;
 };

EOSIO_ABI(style_service, (createuser)(getrandom))