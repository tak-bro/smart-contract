#include<puton.hpp>

// const uint64_t THREE_DAYS = 3 * 86400; // 3days
const uint64_t THREE_DAYS = 1 * 60; // 1 minutes

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
        u.liked_rows = empty_postrows;
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
        p.cmt_rows = empty_cmtrows;
        p.like_cnt = 0;
        p.point = 0;
        p.last_id = 0;
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
        p.cmt_rows = empty_cmtrows;
        p.like_cnt = 0;
        p.point = 0;
        p.image_urls = image_urls;
        p.last_id = 0;
    });

    // debug print
    print("post#", post_id, " created");
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

bool puton_service::checkLiked(const std::vector<postrow> &rows, const uint64_t id)
{
    // binary search
    int left = 0;
    int right = rows.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (rows[mid].post_id < id) {
            left = mid + 1;
        } else if (id < rows[mid].post_id) {
            right = mid - 1;
        } else {
            return true;
        }
    }
    return false;
}

int puton_service::getLikedIndex(const std::vector<postrow> &rows, const uint64_t id)
{
    // binary search
    int left = 0;
    int right = rows.size() - 1;

    while (left <= right) {
        int mid = left + (right - left) / 2;
        if (rows[mid].post_id < id) {
            left = mid + 1;
        } else if (id < rows[mid].post_id) {
            right = mid - 1;
        } else {
            return mid;
        }
    }
    return -1;
}

void puton_service::likepost(const account_name user, const uint64_t id)
{
    // check user permission
    require_auth(user);

    // check post on post_table
    auto post_itr = post_table.find(id);
    eosio_assert(post_itr != post_table.end(), "PostTable does not has id");

    // check account on user_table
    auto user_itr = user_table.find(user);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check liked
    bool alreadyLiked = checkLiked(user_itr->liked_rows, id);
    eosio_assert(!alreadyLiked, "already liked");

    // update post_table
    post_table.modify(post_itr, _self, [&](auto &post) {
        post.like_cnt = post.like_cnt + 1;
        // calculate time range
        if (user != post.author && post.created_at + THREE_DAYS > now()) {
            post.point = post.point + 1;
        } else {
            print("written more than 3 days ago\n");
        }
    });

    // update post_id to user's liked_rows 
    postrow row;
    user_table.modify(user_itr, _self, [&](auto& user) {
        row.post_id = id;
        user.liked_rows.push_back(row);
    });

    // debug print
    print("post#", id, " liked");
}

void puton_service::cancellike(const account_name user, const uint64_t id)
{
    // check user permission
    require_auth(user);

    // check post on post_table
    auto post_itr = post_table.find(id);
    eosio_assert(post_itr != post_table.end(), "PostTable does not has id");

    // check account on user_table
    auto user_itr = user_table.find(user);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check liked
    int likedIndex = getLikedIndex(user_itr->liked_rows, id);
    eosio_assert(likedIndex > -1, "The user did not like this post");

    // update liked_rows of user
    user_table.modify(user_itr, _self, [&](auto &user) {
        if (likedIndex > -1) {
            user.liked_rows.erase(user.liked_rows.begin() + likedIndex);
        }
    });

    // update post_table
    post_table.modify(post_itr, _self, [&](auto &post) {
        post.like_cnt = post.like_cnt - 1;
        // calculate time range
        if (user != post.author && post.created_at + THREE_DAYS > now()) {
            post.point = post.point - 1;
        } else {
            print("written more than 3 days ago\n");
        }
    });

    // debug print
    print("cancel like post#", id);
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

/// COMMENT ACTION
void puton_service::addcmt(const account_name author, const uint64_t post_id, const string hash_value)
{
    // check user permission
    require_auth(author);

    // check account on user_table
    auto user_itr = user_table.find(author);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check id on post_table
    auto itr = post_table.find(post_id);
    eosio_assert(itr != post_table.end(), "PostTable does not has id");

    // set cmtrow
    cmtrow row;
    row.author = author;
    row.cmt_hash = hash_value;
    row.created_at = now();

    // add cmt to post row
    post_table.modify(itr, _self, [&](auto &post) {
        row.cmt_id = post.last_id + 1;
        post.last_id = row.cmt_id;
        post.cmt_rows.push_back(row);

        // add point to post 
        if (author != post.author && post.created_at + THREE_DAYS > now()) {
            post.point = post.point + 1;
        } else {
            print("written more than 3 days ago\n");
        }
    });

    print("comment added to post#", itr->id);
}

void puton_service::updatecmt(const account_name author, const uint64_t post_id, const uint16_t cmt_id, const string to_update)
{
    // check user permission
    require_auth(author);

    // check account on user_table
    auto user_itr = user_table.find(author);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check id on post_table
    auto itr = post_table.find(post_id);
    eosio_assert(itr != post_table.end(), "PostTable does not has id");

    // update cmt row
    bool isFound = false;
    post_table.modify(itr, _self, [&](auto &post) {
        for (int i = 0; i < post.cmt_rows.size(); i++) {
            if (post.cmt_rows[i].cmt_id == cmt_id) {
                // check cmt author
                eosio_assert(post.cmt_rows[i].author == author, "Not the author of this cmt");
                post.cmt_rows[i].cmt_hash = to_update;
                isFound = true;
                break;
            }
        }
    });

    // debug print
    eosio_assert(isFound, "Could not found cmt");
    print("comment updated");
}

void puton_service::deletecmt(const account_name author, const uint64_t post_id, const uint16_t cmt_id)
{
    // check user permission
    require_auth(author);

    // check account on user_table
    auto user_itr = user_table.find(author);
    eosio_assert(user_itr != user_table.end(), "UserTable does not has a user");

    // check id on post_table
    auto itr = post_table.find(post_id);
    eosio_assert(itr != post_table.end(), "PostTable does not has id");

    // update cmt row
    bool isFound = false;
    post_table.modify(itr, _self, [&](auto &post) {
        for (int i = 0; i < post.cmt_rows.size(); i++) {
            if (post.cmt_rows[i].cmt_id == cmt_id) {
                // check cmt author
                eosio_assert(post.cmt_rows[i].author == author, "Not the author of this cmt");
                post.cmt_rows.erase(post.cmt_rows.begin() + i);
                isFound = true;

                // add point to post
                if (author != post.author && post.created_at + THREE_DAYS > now()) {
                    post.point = post.point - 1;
                } else {
                    print("written more than 3 days ago\n");
                }
                break;
            }
        }
    });

    // debug print
    eosio_assert(isFound, "Could not found cmt");
    print("comment deleted");
}

/// ETC
void puton_service::printrandom(account_name author)
{
    // print random
    auto &random = random_gen::get_instance(author);
    uint32_t random_num = random.range(99999);
    print("random# ", random_num);
}

