#include <eosiolib/eosio.hpp>
#include <string>
#include <random.cpp>

using namespace eosio;
using namespace std;

// define singleton
random_gen random_gen::instance;

class buzzler_service : public eosio::contract
{

  public:
    buzzler_service(account_name self) : contract::contract(self),
                                         user_table(self, self),
                                         post_table(self, self),
                                         comment_table(self, self) {}

    /*
         *  user actions
         */

    // @abi action
    void createuser(const account_name account);

    // @abi action
    void updatetoken(const account_name account,
                     const uint64_t token);

    /*
         *  post actions
         */

    // @abi action
    void writepost(const uint64_t id,
                   const account_name author,
                   const string &post_hash);

    // @abi action
    void updatepost(const uint64_t id,
                    const account_name author,
                    const string &post_hash,
                    const uint32_t buzz_amount,
                    const uint32_t like_count);

    // @abi action
    void deletepost(const uint64_t id);

    // @abi action
    void postbyid(const uint64_t id);

    // @abi action
    void postsbyuser(const account_name author);

    /*
         *  comment actions
         */

    // @abi action
    void writecmt(const uint64_t id,
                  const uint64_t post_id,
                  const account_name author,
                  const string &comment_hash);

    // @abi action
    void writerecmt(const uint64_t id,
                    const uint64_t parent_id,
                    const uint64_t post_id,
                    const account_name author,
                    const string &comment_hash);

    // @abi action
    void updatecmt(const uint64_t id,
                   const account_name author,
                   const string &comment_hash,
                   const uint32_t buzz_amount,
                   const uint32_t like_count);

    // @abi action
    void deletecmt(const uint64_t id);

    // @abi action
    void cmtbyid(const uint64_t id);

    // @abi action
    void cmtsbypostid(const uint64_t post_id);

    /// ETC
    // @abi action
    void printrandom(account_name author); // for test

  private:
    // @abi table users
    struct user
    {
        account_name account;
        uint64_t buzz_token;
        time created_at;

        auto primary_key() const { return account; }

        EOSLIB_SERIALIZE(user, (account)(buzz_token)(created_at))
    };

    // @abi table posts
    struct post
    {
        uint64_t id;
        account_name author;
        string post_hash;     // post 해쉬값(title, contents...)
        uint32_t buzz_amount; // 보상 토근
        uint32_t like_count;
        time created_at;

        auto primary_key() const { return id; }
        uint64_t by_author() const { return author; }

        EOSLIB_SERIALIZE(post, (id)(author)(post_hash)(buzz_amount)(like_count)(created_at))
    };

    // @abi table comments
    struct comment
    {
        uint64_t id;
        uint64_t post_id;
        string comment_hash; // comment 해쉬값(contents...)
        account_name author;
        uint64_t parent_id;
        uint32_t buzz_amount; // 보상 토근
        uint32_t like_count;
        time created_at;

        auto primary_key() const { return id; }
        uint64_t by_postid() const { return post_id; }

        EOSLIB_SERIALIZE(comment, (id)(post_id)(comment_hash)(author)(parent_id)(buzz_amount)(like_count)(created_at))
    };

    // define tables
    multi_index<N(users), user> user_table;
    multi_index<N(posts), post,
                indexed_by<N(author), const_mem_fun<post, uint64_t, &post::by_author>>>
        post_table;
    multi_index<N(comments), comment,
                indexed_by<N(postid), const_mem_fun<comment, uint64_t, &comment::by_postid>>>
        comment_table;
};

EOSIO_ABI(buzzler_service, (createuser)(updatetoken)(writepost)(updatepost)(deletepost)(postbyid)(postsbyuser)(writecmt)(updatecmt)(deletecmt)(cmtbyid)(cmtsbypostid)(printrandom))