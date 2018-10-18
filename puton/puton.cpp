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
        u.post_rows = empty_postrows;
    });

    // debug print
    print(name{account}, " user created");
}

/// POST ACTIONS
void puton_service::addpost(const account_name user, const string hash_value)
{
    // check user permission
    require_auth(user);

    // check account on user_table
    auto user_itr = user_table.find(user);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // get unique post_id from post_table
    uint64_t post_id = post_table.available_primary_key();

    // create post to post_table
    post_table.emplace(_self, [&](auto& p) {
        p.id = post_id;
        p.author = user;
        p.post_hash = hash_value;
        p.created_at = now();
        p.image_urls = empty_imagerows;
        p.comment_rows = empty_commentrows;
        p.like_cnt = 0;
        p.point = 0;
    });

    // update post_id to user's postrows 
    postrow row;
    user_table.modify(user_itr, _self, [&](auto& user) {
        row.post_id = post_id;
        user.post_rows.push_back(row);
    });

    // debug print
    print("post#", post_id, " created");
}

void puton_service::addimages(const account_name user, const string hash_value, std::vector<std::string> args)
{
    // check user permission
    require_auth(user);

    // check account on user_table
    auto user_itr = user_table.find(user);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // get unique post_id from post_table
    uint64_t post_id = post_table.available_primary_key();

    // push temp vector
    std::vector<std::string> image_urls;
    for (auto &arg : args) {
        image_urls.push_back(arg);
    }

    // create post to post_table
    post_table.emplace(_self, [&](auto& p) {
        p.id = post_id;
        p.author = user;
        p.post_hash = hash_value;
        p.created_at = now();
        p.comment_rows = empty_commentrows;
        p.like_cnt = 0;
        p.point = 0;
        p.image_urls = image_urls;
    });

    // update post_id to user's postrows
    postrow row;
    user_table.modify(user_itr, _self, [&](auto& user) {
        row.post_id = post_id;
        user.post_rows.push_back(row);
    });

    // debug print
    print("post# created", hash_value);
}

void puton_service::updatepost(const account_name author, const uint64_t id, const string to_update)
{
    // check user permission
    require_auth(author);

    // check account on user_table
    auto user_itr = user_table.find(author);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check post on post_table
    auto post_itr = post_table.find(id);
    eosio_assert(post_itr != post_table.end(), "PostTable does not has id");

    // update post_table
    post_table.modify(post_itr, _self, [&](auto &post) {
        post.post_hash = to_update;
    });

    // debug print
    print("post#", id, " updated");
}

void puton_service::updateimages(const account_name author, const uint64_t id, const string to_update, std::vector<std::string> args)
{
    // check user permission
    require_auth(author);

    // check account on user_table
    auto user_itr = user_table.find(author);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check post on post_table
    auto post_itr = post_table.find(id);
    eosio_assert(post_itr != post_table.end(), "PostTable does not has id");

    // push temp vector
    std::vector<std::string> image_urls;
    for (auto &arg : args) {
        image_urls.push_back(arg);
    }

    // update post_table
    post_table.modify(post_itr, _self, [&](auto &post) {
        post.post_hash = to_update;
        post.image_urls = image_urls;
    });

    // debug print
    print("post#", id, " updated");
}

void puton_service::likepost(const account_name user, const uint64_t id)
{
    // check user permission
    require_auth(user);

    // check post on post_table
    auto post_itr = post_table.find(id);
    eosio_assert(post_itr != post_table.end(), "PostTable does not has id");

    // update post_table
    post_table.modify(post_itr, _self, [&](auto &post) {
        post.like_cnt = post.like_cnt + 1;
        if (user != post.author) {
            post.point = post.point + 1;
        }
    });

    // debug print
    print("post#", id, " liked");
}

void puton_service::deletepost(const account_name author, const uint64_t id)
{
    // check user permission
    require_auth(author);

    // check id on post_table
    auto itr = post_table.find(id);
    eosio_assert(itr != post_table.end(), "PostTable does not has id");

    // delete post
    post_table.erase(itr);

    // debug print
    print("post#", id, " deleted");
}

/// ETC
void puton_service::printrandom(account_name author)
{
    // print random
    auto &random = random_gen::get_instance(author);
    uint32_t random_num = random.range(99999);
    print("random# ", random_num);
}
