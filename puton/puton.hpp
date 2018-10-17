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
    uint64_t post_id = 0;
};

// struct comment for post_table
struct commentrow {
    uint64_t comment_id = 0;
};

class puton_service: public eosio::contract {

    public: 
        puton_service(account_name self): contract::contract(self),
                                          user_table(self, self),
                                          post_table(self, self) {}

        /// USER ACTIONS
        // @abi action 
        void createuser(const account_name account);

        /// POST ACTIONS
        // @abi action 
        void addpost(const account_name author, const string hash_value);

        // @abi action 
        void updatepost(const account_name author, const uint32_t id, const string to_update);

         // @abi action
        void deletepost(const account_name author, const uint64_t id);

        // @abi action
        void addimages(const account_name author, const string hash_value, std::vector<std::string> args);

        /// ETC
        // @abi action
        void printrandom(account_name author); // for test

    private:

        // @abi table users 
        struct user {
            account_name account;
            std::vector<postrow> written_rows;

            auto primary_key() const { return account; }

            EOSLIB_SERIALIZE(user, (account)(written_rows))
        };

        // @abi table posts
        struct post {
            uint64_t id;
            account_name author;
            std::string post_hash;
            std::vector<std::string> image_urls;
            std::vector<commentrow> comment_rows;
            uint8_t like_cnt;
            time created_at;

            auto primary_key() const { return id; }

            EOSLIB_SERIALIZE(post, (id)(author)(post_hash)(image_urls)(comment_rows)(like_cnt)(created_at))
        };

        // define tables
        multi_index<N(users), user> user_table;
        multi_index<N(posts), post> post_table;

        // private variable
        std::vector<postrow> empty_postrows;
        std::vector<commentrow> empty_commentrows;
        std::vector<string> empty_imagerows;
 };

EOSIO_ABI(puton_service, (createuser)(addpost)(addimages)(updatepost)(deletepost)(printrandom))