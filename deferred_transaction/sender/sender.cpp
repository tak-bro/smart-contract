#include <eosiolib/eosio.hpp>
#include <eosiolib/transaction.hpp>
#include <string>

using std::string;
using eosio::contract;
using eosio::permission_level;
using eosio::action;

class sender : contract {
    public:
        sender(account_name account) : contract(account) {}

        // inline action
        void send(string message) {
            require_auth(_self);
            
            action(
                permission_level(_self, N(active)),
                N(recipient), N(receive),
                std::make_tuple(_self, message)
            ).send();
        }

       // deferred transaction 
		void spam(const string& msg_str, uint64_t interval, uint64_t index, uint32_t iterations) {
			if (index < iterations) {
                eosio::print(msg_str.c_str());
				// Iteration loop
				eosio::transaction tx;
				tx.actions.emplace_back(
					permission_level{_self, N(active)},
					_self,
					N(spam),
					std::make_tuple(msg_str, interval, ++index, iterations)
				);
				tx.delay_sec = interval;
				tx.send(index, _self);
			} else {
                eosio::print("done");
			}
		}

        // deferred transaction with inlike action
        void defertx(string message, uint64_t interval, uint64_t index, uint32_t iterations) {
            if (index < iterations) {
                require_auth(_self);

                // inline action to send to recipient
                action(
                    permission_level(_self, N(active)),
                    N(recipient), N(receive),
                    std::make_tuple(_self, message))
                .send();

				// Iteration loop
				eosio::transaction tx;
				tx.actions.emplace_back(
					permission_level{_self, N(active)},
					_self, N(defertx),
					std::make_tuple(message, interval, ++index, iterations)
				);
				tx.delay_sec = interval;
				tx.send(index, _self);

			} else {
                eosio::print("done deferred transaction");
			}
		}
};

EOSIO_ABI(sender, (send)(defertx)(spam))