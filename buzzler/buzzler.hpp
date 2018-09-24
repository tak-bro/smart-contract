#include <eosiolib/eosio.hpp> 
#include <string>

using namespace eosio; 
using namespace std;

class buzzler_service: public eosio::contract {

    public: 
        buzzler_service(account_name self): contract::contract(self),
                                            user_table(self, self) {}

        // @abi action
        void createuser(const account_name account);

        // @abi action
        void updatetoken(const account_name account,
                         const uint64_t     token);

    private:

        // @abi table users i64
        struct user {
            account_name account;
            uint64_t     buzz_token;
            time         created_at;

            auto primary_key() const { return account; }

            EOSLIB_SERIALIZE(user, (account)(buzz_token)(created_at))
        };

        multi_index<N(users), user> user_table;
 };

EOSIO_ABI(buzzler_service, (createuser)(updatetoken))