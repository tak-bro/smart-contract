#include <eosiolib/eosio.hpp> 
#include <string>

using namespace eosio; 
using namespace std;

class todo_service: public eosio::contract {

    public: 
        using contract::contract;

        // @abi action
        void create(account_name   author,
                    const uint64_t id,
                    const string&  title);

        // @abi action
        void complete(account_name   author,
                      const uint64_t id);

        // @abi action
        void destroy(account_name   author,
                     const uint64_t id);

    private:
        // @abi table todos i64
        struct todo {
            uint64_t id;
            string   title;
            uint64_t completed;

            auto primary_key() const { return id; }

            EOSLIB_SERIALIZE(todo, (id)(title)(completed))
        };

        typedef eosio::multi_index<N(todos), todo> todo_table;
 };

EOSIO_ABI(todo_service, (create)(complete)(destroy))