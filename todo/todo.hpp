#include <eosiolib/eosio.hpp>
#include <eosiolib/print.hpp>
#include <string>

using namespace eosio;
using std::string;

class todo_service: public eosio::contract {

    public:
        using contract::contract;

        // @abi action
        void create(const account_name account,
                    uint64_t           id,
                    const string&      title);

        // @abi action
        void update(const account_name account,
                    uint64_t           id,
                    const string&      title);

        // @abi action
        void remove(const account_name account,
                    uint64_t           id);

        // @abi action
        void complete(const account_name account,
                      uint64_t           id);

        // @abi action
        void byuser(const account_name account);

        // @abi action
        void byid(const account_name account,
                  uint64_t           id);

        // @abi action
        void rangecreated(time less, time over);

    private:

        // @abi table users
        struct todo {
            account_name account;
            uint64_t     id;
            string       title;
            bool         completed;
            time         created_at;

            account_name primary_key() const { return account; }
            uint64_t     by_id() const { return id; }
            EOSLIB_SERIALIZE(todo, (account)(id)(title)(completed)(created_at))
        };

        typedef eosio::multi_index<
            N(todos), todo,
            indexed_by< N(id), const_mem_fun<todo, uint64_t, &todo::by_id> >
        > todo_table;
};

EOSIO_ABI(todo_service, (create)(update)(remove)(complete)(byuser)(byid)(rangecreated))