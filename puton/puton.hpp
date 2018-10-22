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

// struct cmt for post_table
struct cmtrow {
    uint16_t cmt_id = 0;
    account_name author = 0;
    string cmt_hash = "";
    time created_at = 0;
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
        void updatepost(const account_name author, const uint64_t id, const string to_update);

        // @abi action 
        void updateimages(const account_name author, const uint64_t id, const string to_update, std::vector<std::string> args);

        // @abi action 
        void likepost(const account_name user, const uint64_t id);

        // @abi action 
        void cancellike(const account_name user, const uint64_t id);

         // @abi action
        void deletepost(const account_name author, const uint64_t id);

        // @abi action
        void addimages(const account_name author, const string hash_value, std::vector<std::string> args);

        /// COMMENT ACTIONS
        // @abi action
        void addcmt(const account_name author, const uint64_t post_id, const string hash_value);

        // @abi action 
        void updatecmt(const account_name author, const uint64_t post_id, const uint16_t cmt_id, const string to_update);

        // @abi action
        void deletecmt(const account_name author, const uint64_t post_id, const uint16_t cmt_id);

        /// ETC
        // @abi action
        void printrandom(account_name author); // for test

    private:

        // @abi table users 
        struct user {
            account_name account;
            std::vector<postrow> liked_rows;

            auto primary_key() const { return account; }

            EOSLIB_SERIALIZE(user, (account)(liked_rows))
        };

        // @abi table posts
        struct post {
            uint64_t id;
            account_name author;
            std::string post_hash;
            std::vector<std::string> image_urls;
            std::vector<cmtrow> cmt_rows;
            uint16_t last_id; // for cmt
            uint16_t like_cnt;
            uint16_t point;
            time created_at;

            auto primary_key() const { return id; }

            EOSLIB_SERIALIZE(post, (id)(author)(post_hash)(image_urls)(cmt_rows)(last_id)(like_cnt)(point)(created_at))
        };

        // define tables
        multi_index<N(users), user> user_table;
        multi_index<N(posts), post> post_table;

        // private variable
        std::vector<postrow> empty_postrows;
        std::vector<cmtrow> empty_cmtrows;
        std::vector<string> empty_imagerows;

        // private method
        bool checkLiked(const std::vector<postrow>& liked_rows, const uint64_t id);
 };

EOSIO_ABI(puton_service, (createuser)(addpost)(addimages)(updatepost)(likepost)(cancellike)(updateimages)(deletepost)(printrandom)(addcmt)(updatecmt)(deletecmt))