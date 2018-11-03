#include <eosiolib/eosio.hpp>
#include <eosiolib/transaction.hpp>
#include <eosiolib/asset.hpp>
#include <string>

using eosio::action;
using eosio::contract;
using eosio::permission_level;
using std::string;

class sender : contract
{
  public:
    sender(account_name account) : contract(account) {}

    // private func
    eosio::symbol_type get_symbol(string sym)
    {
        eosio::symbol_type symb = eosio::string_to_symbol(4, sym.c_str());
        return symb;
    }

    template <typename CharT>
    static std::string to_hex(const CharT *d, uint32_t s)
    {
        std::string r;
        const char *to_hex = "0123456789abcdef";
        uint8_t *c = (uint8_t *)d;
        for (uint32_t i = 0; i < s; ++i)
        {
            (r += to_hex[(c[i] >> 4)]) += to_hex[(c[i] & 0x0f)];
        }
        return r;

        // std::string data = "hello";
        // checksum256 digest;
        // sha256(&data[0], data.size(), &digest);

        // std::string hexstr = to_hex(&digest, sizeof(digest));
        // print(hexstr);
        // // 2cf24dba5fb0a30e26e83b2ac5b9e29e1b161e5c1fa7425e73043362938b9824
    }
  
    // inline action
    void send(string message)
    {
        require_auth(_self);

        action(
            permission_level(_self, N(active)),
            N(recipient), N(receive),
            std::make_tuple(_self, message))
            .send();
    }

    // deferred transaction
    void spam(const string &msg_str, uint64_t interval, uint64_t index, uint32_t iterations)
    {
        if (index < iterations)
        {
            eosio::print(msg_str.c_str());
            // Iteration loop
            eosio::transaction tx;
            tx.actions.emplace_back(
                permission_level{_self, N(active)},
                _self, N(spam),
                std::make_tuple(msg_str, interval, ++index, iterations));
            tx.delay_sec = interval;
            tx.send(index, _self);
        }
        else
        {
            eosio::print("done");
        }
    }

    // deferred transaction with inline action
    void defertx(string message, uint64_t interval, uint64_t index, uint32_t iterations)
    {
        if (index < iterations)
        {
            require_auth(_self);

            // inline action to send to recipient
            action(
                permission_level(_self, N(active)),
                N(recipient), N(receive),
                std::make_tuple(_self, message))
                .send();

            // Schedule a transaction to do again
            eosio::transaction tx;
            tx.actions.emplace_back(
                permission_level{_self, N(active)},
                _self, N(defertx),
                std::make_tuple(message, interval, ++index, iterations));
            tx.delay_sec = interval;
            tx.send(_self + now(), _self); // needs a unique sender id so append current time
        }
        else
        {
            eosio::print("done deferred transaction");
        }
    }
};

EOSIO_ABI(sender, (send)(defertx)(spam))