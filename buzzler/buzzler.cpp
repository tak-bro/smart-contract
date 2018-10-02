#include<buzzler.hpp>

/*
 *  user actions
 */
void buzzler_service::createuser(const account_name account)
{
    // check buzzler server
    require_auth(_self);

    // check account on user_table
    auto itr = user_table.find(account);
    eosio_assert(itr == user_table.end(), "UserTable already has a user");

    // create user
    user_table.emplace(_self, [&](auto& p) {
        p.account    = account;
        p.buzz_token = 0;
        p.created_at = now();
    });

    // debug print
    print(name{account}, " user created");
}

void buzzler_service::updatetoken(const account_name account,
                                  const uint64_t     token)
{
    // check buzzler server
    require_auth(_self);

    // check account on user_table
    auto itr = user_table.find(account);
    eosio_assert(itr != user_table.end(), "UserTable does not has a user");

    // update user
    user_table.modify(itr, _self, [&](auto& p) {
        p.buzz_token = token;
    });

    // debug print
    print(name{account}, " modified");
}

/*
 *  post actions
 */
void buzzler_service::writepost(const uint64_t     id,
                                const account_name author,
                                const string       &post_hash)
{
    // check buzzler server
    require_auth(_self);

     // check account on user_table
    auto user_itr = user_table.find(author);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a author");

    // check id on post_table
    auto post_itr = post_table.find(id);
    eosio_assert(post_itr == post_table.end(), "PostTable already has same id");

    // create post
    post_table.emplace(_self, [&](auto& p) {
        p.id          = id;
        p.author      = author;
        p.post_hash   = post_hash;
        p.buzz_amount = 0;
        p.created_at  = now();
    });

    // debug print
    print("post#", id, " created");
}

void buzzler_service::updatepost(const uint64_t     id,
                                 const account_name author,
                                 const string       &post_hash,
                                 const uint32_t     buzz_amount,
                                 const uint32_t     like_count)
{
    // check buzzler server
    require_auth(_self);

    // check account on user_table
    auto itr = user_table.find(author);
    eosio_assert(itr != user_table.end(), "UserTable does not has a author");

    // check id on post_table
    auto post_itr = post_table.find(id);
    eosio_assert(post_itr != post_table.end(), "PostTable does not has id");

    // update post
    post_table.modify(post_itr, _self, [&](auto& p) {
        p.post_hash   = post_hash;
        p.buzz_amount = buzz_amount;
        p.like_count  = like_count;
    });

    // debug print
    print("post#", id, " updated");
}

void buzzler_service::deletepost(const uint64_t id)
{
    // check buzzler server
    require_auth(_self);

    // check id on post_table
    auto itr = post_table.find(id);
    eosio_assert(itr != post_table.end(), "PostTable does not has id");

    // delete post
    post_table.erase(itr);

    print("post#", id, " deleted");
}


void buzzler_service::postbyid(const uint64_t id)
{
    // check buzzler server
    require_auth(_self);

    // check id on post_table
    auto itr = post_table.find(id);
    eosio_assert(itr != post_table.end(), "PostTable does not has id");

    // print post by id
    print("id: ",          itr->id, ", ");
    print("author: ",      name{itr->author}, ", ");
    print("post_hash: ",   itr->post_hash.c_str(), ", ");
    print("buzz_amount: ", itr->buzz_amount, ", ");
    print("like_count: ",  itr->like_count, ", ");
    print("created_at: ",  itr->created_at);
}

void buzzler_service::postsbyuser(const account_name author)
{
    // check buzzler server
    require_auth(_self);

    // get post index by author
    auto author_index = post_table.get_index<N(author)>();
    auto post_itr = author_index.find(author);

    // print post by author
    for (; post_itr != author_index.end() && post_itr->author == author; ++post_itr){
        print("id: ", post_itr->id, ", ");
        print("author: ", name{post_itr->author}, ", ");
        print("post_hash: ", post_itr->post_hash.c_str(), ", ");
        print("buzz_amount: ", post_itr->buzz_amount, ", ");
        print("like_count: ", post_itr->like_count, ", ");
        print("created_at: ", post_itr->created_at, "\n");
    }
}


/*
 *  comment actions
 */
void buzzler_service::writecmt(const uint64_t     id,
                                   const uint64_t     post_id,
                                   const account_name author,
                                   const string       &comment_hash)
{
    // check buzzler server
    require_auth(_self);

    // check post on post_table
    auto post_itr = post_table.find(post_id);
    eosio_assert(post_itr != post_table.end(), "PostTable does not has a postid");

    // check id on comment_table
    auto comment_itr = comment_table.find(id);
    eosio_assert(comment_itr == comment_table.end(), "CommentTable already has same id");

    // create comment
    comment_table.emplace(_self, [&](auto& p) {
        p.id          = id;
        p.post_id     = post_id;
        p.author      = author;
        p.comment_hash   = comment_hash;
        p.buzz_amount = 0;
        p.created_at  = now();
        p.parent_id   = -1; // parent comment가 없을 경우 -1 설정
    });

    // debug print
    print("comment#", id, " created");
}

void buzzler_service::writerecmt(const uint64_t     id,
                                     const uint64_t     parent_id,
                                     const uint64_t     post_id,
                                     const account_name author,
                                     const string       &comment_hash)
{
    // check buzzler server
    require_auth(_self);

    // check post on post_table
    auto post_itr = post_table.find(post_id);
    eosio_assert(post_itr != post_table.end(), "PostTable does not has a postid");

    // check parent on comment_table
    auto parent_comment_itr = comment_table.find(parent_id);
    eosio_assert(parent_comment_itr != comment_table.end(), "CommentTable does not has a parent comment");

     // check id on comment_table
    auto comment_itr = comment_table.find(id);
    eosio_assert(comment_itr == comment_table.end(), "CommentTable already has same id");

    // create re-comment
    comment_table.emplace(_self, [&](auto& p) {
        p.id          = id;
        p.post_id     = post_id;
        p.author      = author;
        p.comment_hash   = comment_hash;
        p.buzz_amount = 0;
        p.created_at  = now();
        p.parent_id   = parent_id;
    });

    // debug print
    print("recomment#", id, " created");
}

void buzzler_service::updatecmt(const uint64_t     id,
                                    const account_name author,
                                    const string       &comment_hash,
                                    const uint32_t     buzz_amount,
                                    const uint32_t     like_count)
{
    // check buzzler server
    require_auth(_self);

    // check account on user_table
    auto itr = user_table.find(author);
    eosio_assert(itr != user_table.end(), "UserTable does not has a author");

    // check id on comment_table
    auto comment_itr = comment_table.find(id);
    eosio_assert(comment_itr != comment_table.end(), "CommentTable does not has id");

    // update post
    comment_table.modify(comment_itr, _self, [&](auto& p) {
        p.comment_hash = comment_hash;
        p.buzz_amount  = buzz_amount;
        p.like_count   = like_count;
    });

    // debug print
    print("comment#", id, " updated");
}

void buzzler_service::deletecmt(const uint64_t id)
{
    // check buzzler server
    require_auth(_self);

    // check id on comment_table
    auto itr = comment_table.find(id);
    eosio_assert(itr != comment_table.end(), "CommentTable does not has id");

    // delete post
    comment_table.erase(itr);

    print("comment#", id, " deleted");
}

void buzzler_service::cmtbyid(const uint64_t id)
{
    // check buzzler server
    require_auth(_self);

    // check id on comment_table
    auto itr = comment_table.find(id);
    eosio_assert(itr != comment_table.end(), "CommentTable does not has id");

    // print comment by id
    print("id: ",           itr->id, ", ");
    print("parent_id: ",    itr->parent_id, ", ");
    print("post_id: ",      itr->post_id, ", ");
    print("author: ",       name{itr->author}, ", ");
    print("comment_hash: ", itr->comment_hash.c_str(), ", ");
    print("buzz_amount: ",  itr->buzz_amount, ", ");
    print("like_count: ",   itr->like_count, ", ");
    print("created_at: ",   itr->created_at);
}

void buzzler_service::cmtsbypost(const uint64_t post_id)
{
    // check buzzler server
    require_auth(_self);

    // get post index by author
    auto post_index = comment_table.get_index<N(postid)>();
    auto comment_itr = post_index.find(post_id);

    // print post by author
    for (; comment_itr != post_index.end() && comment_itr->post_id == post_id; ++comment_itr) {
        print("id: ",           comment_itr->id, ", ");
        print("parent_id: ",    comment_itr->parent_id, ", ");
        print("post_id: ",      comment_itr->post_id, ", ");
        print("author: ",       name{comment_itr->author}, ", ");
        print("comment_hash: ", comment_itr->comment_hash.c_str(), ", ");
        print("buzz_amount: ",  comment_itr->buzz_amount, ", ");
        print("like_count: ",   comment_itr->like_count, ", ");
        print("created_at: ",  comment_itr->created_at);
    }
}