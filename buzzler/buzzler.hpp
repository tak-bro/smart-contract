#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

using namespace eosio;
using std::string;

class buzzler: public eosio::contract {

    public:
        using contract::contract;

        // @abi action
        void hello(account_name user);

        // @abi action
        void create(const account_name account,
                    const string&      nickname,
                    const string&      univ,
                    const string&      major);

    private:

        // @abi table users
        struct user {
            account_name account;
            string       nickname;
            string       univ;
            string       major;
            uint32_t     token;
            time         created_at;

            account_name primary_key() const { return account; }
            EOSLIB_SERIALIZE(user, (account)(nickname)(univ)(major)(token)(created_at))
        };

        typedef eosio::multi_index<N(users), user> user_table;
};

EOSIO_ABI(buzzler, (hello)(create))
