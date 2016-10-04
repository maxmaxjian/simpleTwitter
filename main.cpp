#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#include <algorithm>

using std::vector;

using userid = int;
using followerid = int;
using followeeid = int;
using tweetid = int;

class Twitter {
public:
  Twitter() {
    tweets[1] = vector<tweetid>{1,2,3,4,5,6,7,8,9,10,11,12};
    tweets[2] = vector<tweetid>{100,200};
  }

  void postTweet(int userId, int tweetId) {
    tweets[userId].push_back(tweetId);
  }

  vector<int> getNewsFeed(int userId) {
    vector<int> twts;
    auto it = tweets.find(userId);
    auto ix = it->second.rbegin();
    for (size_t i = 0; i < 10; ++i) {
      twts.push_back(*ix);
      ++ix;
    }
    return twts;
  }

  void follow(int followerId, int followeeId) {
    if (followers.find(followeeId) == followers.end()) {
      followers[followeeId] = std::unordered_set<followerid>(followerId);
    }
    followers[followeeId].insert(followerId);
  }

  void unfollow(int followerId, int followeeId) {
    followers[followeeId].erase(followerId);
  }

  vector<int> getFollowers(int followeeId) {
    vector<int> result;
    for (auto it = followers[followeeId].begin(); it != followers[followeeId].end(); ++it) {
      result.push_back(*it);
    }
    return result;
  }

private:
  std::unordered_map<userid, vector<tweetid>> tweets;
  std::unordered_map<followeeid, std::unordered_set<followerid>> followers;
};

int main() {
  Twitter obj;
  obj.postTweet(1,15);
  vector<int> twts = obj.getNewsFeed(1);
  std::cout << "The latest 10 tweets are:\n";
  std::for_each(twts.begin(), twts.end(), [](int i){std::cout << i << " ";});
  std::cout << std::endl;

  auto flwers = obj.getFollowers(1);
  std::cout << "Before adding, the followers are:\n";
  std::for_each(flwers.begin(), flwers.end(), [](int i){std::cout << i << " ";});
  std::cout << std::endl;

  obj.follow(2, 1);
  flwers = obj.getFollowers(1);
  std::cout << "After adding, the followers are:\n";
  std::for_each(flwers.begin(), flwers.end(), [](int i){std::cout << i << " ";});
  std::cout << std::endl;

  obj.unfollow(2, 1);
  flwers = obj.getFollowers(1);
  std::cout << "After deleting, the followers are:\n";
  std::for_each(flwers.begin(), flwers.end(), [](int i){std::cout << i << " ";});
  std::cout << std::endl;
}
