#include <eosiolib/eosio.hpp> 
#include <string>

using namespace eosio; 
using namespace std;

class buzzler_service: public eosio::contract {

    public: 
        buzzler_service(account_name self): contract::contract(self),
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
                         const uint64_t     token);

        /*
         *  post actions
         */

        // @abi action
        void writepost(const uint64_t     id,
                       const account_name author,
                       const string&      post_hash);

        // @abi action
        void updatepost(const uint64_t     id,
                        const account_name author,
                        const string&      post_hash,
                        const uint32_t     buzz_amount,
                        const uint32_t     like_count);

        // @abi action
        void deletepost(const uint64_t id);

        // @abi action
        void postbyid(const uint64_t id);

        // @abi action
        void postsbyuser(const account_name author);

      private:

        // @abi table users 
        struct user {
            account_name account;
            uint64_t     buzz_token;
            time         created_at;

            auto primary_key() const { return account; }

            EOSLIB_SERIALIZE(user, (account)(buzz_token)(created_at))
        };

        // @abi table posts
        struct post {
            uint64_t     id;
            account_name author;
            string       post_hash;   // post 해쉬값(title, contents...)
            uint32_t     buzz_amount; // 보상 토근
            uint32_t     like_count; 
            time         created_at;

            auto     primary_key() const { return id; }
            uint64_t by_author()   const { return author; }

            EOSLIB_SERIALIZE(post, (id)(author)(post_hash)(buzz_amount)(like_count)(created_at))
        };

        // @abi table posts
        struct comment {
            uint64_t     id;
            uint64_t     parent_id;
            uint64_t     post_id;
            account_name author;
            string       comment_hash; // comment 해쉬값(contents...)
            uint32_t     buzz_amount;  // 보상 토근
            uint32_t     like_count; 
            time         created_at;

            auto     primary_key()  const { return id; }
            uint64_t by_parent_id() const { return parent_id; }
            uint64_t by_post_id()   const { return post_id; }

            EOSLIB_SERIALIZE(comment, (id)(parent_id)(post_id)(author)(comment_hash)(buzz_amount)(like_count)(created_at))
        };

        // define tables
        multi_index<N(users), user> user_table;
        multi_index<N(posts), post,
                    indexed_by<N(author), const_mem_fun<post, uint64_t, &post::by_author>>
        > post_table;
        multi_index<N(comments), comment,
                    indexed_by<N(parentid), const_mem_fun<comment, uint64_t, &comment::by_parent_id>>,
                    indexed_by<N(postid), const_mem_fun<comment, uint64_t, &comment::by_post_id>>
        > comment_table;
 };

EOSIO_ABI(buzzler_service, (createuser)(updatetoken)(writepost)(updatepost)(deletepost)(postbyid)(postsbyuser))