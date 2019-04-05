class Twitter {
public:
    unordered_map<int,vector<pair<int,unsigned long long int>>> news;
    unsigned long long int timeStamp;
    unordered_map<int,set<int>> following;
    /** Initialize your data structure here. */
    Twitter():news(),timeStamp(0),following() {
        
    }
    
    /** Compose a new tweet. */
    void postTweet(int userID, int tweetID) {
        if (news.find(userID) == news.end())
            news[userID] = vector<pair<int,unsigned long long int>>();
        news[userID].push_back(pair<int,unsigned long long int>(tweetID,timeStamp));
        ++timeStamp;
    }
    
    /** Retrieve the 10 most recent tweet ids in the user's news feed. Each item in the news feed must be posted by users who the user followed or by the user herself. Tweets must be ordered from most recent to least recent. */
    vector<int> getNewsFeed(int userID) {
        vector<vector<pair<int,unsigned long long int>>::reverse_iterator> iters, ends;
        if (news.find(userID) != news.end()) {
            iters.push_back(news[userID].rbegin());
            ends.push_back(news[userID].rend());
        }
        if (following.find(userID) != following.end()) {
            for (set<int>::iterator i = following[userID].begin(); i != following[userID].end(); ++i)
                if (news.find(*i) != news.end()) {
                    iters.push_back(news[*i].rbegin());
                    ends.push_back(news[*i].rend());
                }
        }
        
        vector<int> output;
        int maxIndex = 0;
        while (output.size() < 10 && !iters.empty()) {
            maxIndex = 0;
            for (int i = 1; i < iters.size(); ++i)
                if (iters[i]->second > iters[maxIndex]->second)
                    maxIndex = i;
            output.push_back(iters[maxIndex]->first);
            ++iters[maxIndex];
            if (iters[maxIndex] == ends[maxIndex]) {
                iters.erase(iters.begin()+maxIndex);
                ends.erase(ends.begin()+maxIndex);
            }
        }
        return output;
    }
    /** Follower follows a followee. If the operation is invalid, it should be a no-op. */
    void follow(int followerID, int followeeID) {
        if(followerID == followeeID)
            return;
        if (following.find(followerID) == following.end())
            following[followerID] = set<int>();
        following[followerID].insert(followeeID);
    }
    /** Follower unfollows a followee. If the operation is invalid, it should be a no-op. */
    void unfollow(int followerID, int followeeID) {
        if (following.find(followerID) != following.end() && following[followerID].find(followeeID) != following[followerID].end())
            following[followerID].erase(following[followerID].find(followeeID));
    }
};

/**
 * Your Twitter object will be instantiated and called as such:
 * Twitter obj = new Twitter();
 * obj.postTweet(userId,tweetId);
 * vector<int> param_2 = obj.getNewsFeed(userId);
 * obj.follow(followerId,followeeId);
 * obj.unfollow(followerId,followeeId);
 */