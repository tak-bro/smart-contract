#include<eosiolib/eosio.hpp>
#include<string>

class recipient : eosio::contract {
    public:
        recipient(account_name account) : eosio::contract(account) {}

        void receive(account_name account, std::string message) {
            // require_auth2(account, N(eosio.code));
            require_auth(account);
            eosio::print(eosio::name{account}, ", ", eosio::name{_self}, ", ", message.c_str());
        }
};

EOSIO_ABI(recipient, (receive))