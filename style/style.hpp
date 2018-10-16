#include <string>
#include <vector>
#include <eosiolib/eosio.hpp> 
#include <random.cpp>

using namespace eosio; 
using namespace std;

// define singleton
random_gen random_gen::instance;

// struct post for user_table
struct postrow {
    uint32_t id = 0;
    string post_hash = "";
    time created_at = 0;
};

class style_service: public eosio::contract {

    public: 
        style_service(account_name self): contract::contract(self),
                                          user_table(self, self),
                                          post_table(self, self) {}

        /// USER ACTIONS
        // @abi action 
        void createuser(const account_name account);

        /// POST ACTIONS
        // @abi action 
        void addpost(const account_name author, const string hash_value);

        /// ETC
        // @abi action
        void getrandom(account_name author);

    private:
        // @abi table users 
        struct user {
            account_name account;
            time created_at;

            auto primary_key() const { return account; }

            EOSLIB_SERIALIZE(user, (account)(created_at))
        };

        // @abi table posts
        struct post {
            account_name author;
            uint32_t last_id;
            std::vector<postrow> post_rows;

            auto primary_key() const { return author; }

            EOSLIB_SERIALIZE(post, (author)(last_id)(post_rows))
        };

        // define tables
        multi_index<N(users), user> user_table;
        multi_index<N(posts), post> post_table;
 };

EOSIO_ABI(style_service, (createuser)(addpost)(getrandom))