#include<puton.hpp>

void puton_service::getrandom(account_name author)
{
    auto &random = random_gen::get_instance(author);
    // get random
    uint32_t random_num = random.range(99999999);

    print("random# ", random_num);
}

void puton_service::addpost(const account_name user, const string hash_value)
{
    // check puton server
    require_auth(_self);

    // check account on user_table
    auto user_itr = user_table.find(user);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // set postrow
    postrow row;
    row.post_hash = hash_value;
    row.created_at = now();

    // add post to post_table
    auto itr = post_table.find(user);
    if (itr == post_table.cend()) {
        post_table.emplace(_self, [&](auto &post) {
            row.id = 1;
            post.author = user;
            post.last_id = row.id;
            post.post_rows.push_back(row);
        });
    } else {
        post_table.modify(itr, _self, [&](auto &post) {
            row.id = post.last_id + 1;
            post.author = user;
            post.last_id = row.id;
            post.post_rows.push_back(row);
        });
    }

    print(name{user}, "'s post added #", row.id);
}

void puton_service::updatepost(const account_name author, const uint32_t id, const string to_update)
{
    // check puton server
    require_auth(_self);

    // check account on user_table
    auto user_itr = user_table.find(author);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check post on post_table
    auto post_itr = post_table.find(author);
    eosio_assert(post_itr != post_table.end(), "PostTable does not has a author");

    // update post row
    bool isFound = false;
    post_table.modify(post_itr, _self, [&](auto &item) {
        for (int i = 0; i < item.post_rows.size(); i++) {
            if (item.post_rows[i].id == id) {
                item.post_rows[i].post_hash = to_update;
                isFound = true;
                break;
            }
        }
    });

    // debug print
    eosio_assert(isFound, "Could not found post");
    print(name{author}, "'s post updated #", id);
}

void puton_service::createuser(const account_name account)
{
    // check puton server
    require_auth(_self);

    // check account on user_table
    auto itr = user_table.find(account);
    eosio_assert(itr == user_table.end(), "UserTable already has a user");

    // create user
    user_table.emplace(_self, [&](auto& p) {
        p.account    = account;
        p.created_at = now();
    });

    // debug print
    print(name{account}, " user created");
}