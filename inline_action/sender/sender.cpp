#include<eosiolib/eosio.hpp>
#include<string>

using std::string;
using eosio::contract;
using eosio::permission_level;
using eosio::action;

class sender : contract {
    public:
        sender(account_name account) : contract(account) {}

        void send(account_name account, string message) {
            require_auth(_self);
            
            action(
                permission_level(account, N(active)),
                N(recipient), N(receive),
                std::make_tuple(_self, message)
            ).send();
        }
};

EOSIO_ABI(sender, (send))