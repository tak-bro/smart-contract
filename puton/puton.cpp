#include<puton.hpp>

/// USER ACTIONS
void puton_service::createuser(const account_name account)
{
    // check puton server
    require_auth(_self);

    // check account on user_table
    auto itr = user_table.find(account);
    eosio_assert(itr == user_table.end(), "UserTable already has a user");

    // create user
    user_table.emplace(_self, [&](auto& u) {
        u.account = account;
        u.written_rows = empty_postrows;
    });

    // debug print
    print(name{account}, " user created");
}

/// POST ACTIONS
void puton_service::addpost(const account_name user, const string hash_value)
{
    // check puton server
    require_auth(_self);

    // check account on user_table
    auto user_itr = user_table.find(user);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // get post_id from user_table
    uint64_t post_id = post_table.available_primary_key();

    // create post to post_table
    post_table.emplace(_self, [&](auto& p) {
        p.id = post_id;
        p.author = user;
        p.post_hash = hash_value;
        p.created_at = now();
        p.comment_rows = empty_commentrows;
        p.like_cnt = 0;
    });

    // update post_id to user's postrows 
    postrow row;
    user_table.modify(user_itr, _self, [&](auto& user) {
        row.post_id = post_id;
        user.written_rows.push_back(row);
    });

    // debug print
    print("post#", post_id, " created");
}

// void puton_service::updatepost(const account_name author, const uint32_t id, const string to_update)
// {
//     // check puton server
//     require_auth(_self);

//     // check account on user_table
//     auto user_itr = user_table.find(author);
//     eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

//     // check post on post_table
//     auto post_itr = post_table.find(author);
//     eosio_assert(post_itr != post_table.end(), "PostTable does not has a author");

//     // update post row
//     bool isFound = false;
//     post_table.modify(post_itr, _self, [&](auto &item) {
//         for (int i = 0; i < item.post_rows.size(); i++) {
//             if (item.post_rows[i].id == id) {
//                 item.post_rows[i].post_hash = to_update;
//                 isFound = true;
//                 break;
//             }
//         }
//     });

//     // debug print
//     eosio_assert(isFound, "Could not found post");
//     print(name{author}, "'s post updated #", id);
// }


/// ETC
void puton_service::printrandom(account_name author)
{
    // print random
    auto &random = random_gen::get_instance(author);
    uint32_t random_num = random.range(99999);
    print("random# ", random_num);
}

