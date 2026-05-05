#include <iostream>
#include <vector>
#include <string>
#include <algorithm>
#include <cstdio>

using namespace std;

// use curl to get the website data
string fetchData(string url) {
    string cmd = "curl -s \"" + url + "\"";
    string result;
    char buffer[128];
    
    FILE* pipe = popen(cmd.c_str(), "r");
    if (!pipe) return "";
    
    while (fgets(buffer, sizeof(buffer), pipe) != nullptr) {
        result += buffer;
    }
    pclose(pipe);
    
    return result;
}

// Find the value in JSON
string getValue(string json, string key) {
    string lookFor = "\"" + key + "\":";
    size_t pos = json.find(lookFor);
    if (pos == string::npos) return "";
    
    pos = pos + lookFor.length();
    
    
    while (pos < json.length() && json[pos] == ' ') pos++;
    
 
    if (json[pos] == '"') {
        pos++;
        size_t end = json.find("\"", pos);
        if (end != string::npos) {
            return json.substr(pos, end - pos);
        }
    }

    else if (json[pos] >= '0' && json[pos] <= '9') {
        size_t start = pos;
        while (pos < json.length() && json[pos] >= '0' && json[pos] <= '9') {
            pos++;
        }
        return json.substr(start, pos - start);
    }
    
    return "";
}

// Helper that is used to convert string to int
int toInt(string s) {
    if (s.empty()) return 0;
    return stoi(s);
}

// Extracting all the article objects from the JSON
vector<string> extractArticles(string json) {
    vector<string> articles;
    
    size_t dataPos = json.find("\"data\":[");
    if (dataPos == string::npos) return articles;
    
    size_t arrayStart = json.find("[", dataPos);
    if (arrayStart == string::npos) return articles;
    
    int braces = 0;
    size_t startPos = string::npos;
    
    for (size_t i = arrayStart + 1; i < json.length(); i++) {
        if (json[i] == '{') {
            if (braces == 0) {
                startPos = i;
            }
            braces++;
        }
        else if (json[i] == '}') {
            braces--;
            if (braces == 0 && startPos != string::npos) {
                articles.push_back(json.substr(startPos, i - startPos + 1));
                startPos = string::npos;
            }
        }
        else if (json[i] == ']' && braces == 0) {
            break;
        }
    }
    
    return articles;
}

struct Article {
    string title;
    int comments;
};

bool compareArticles(Article a, Article b) {
    if (a.comments != b.comments) {
        return a.comments > b.comments;
    }
    return a.title > b.title;
}

vector<string> topArticles(int limit) {
    vector<Article> validArticles;
    int page = 1;
    int total = 1;
    
    while (page <= total) {
        string url = "https://jsonmock.hackerrank.com/api/articles?page=" + to_string(page);
        string response = fetchData(url);
        
        if (response.empty()) break;
        
        if (page == 1) {
            string totalStr = getValue(response, "total_pages");
            if (!totalStr.empty()) {
                total = toInt(totalStr);
            }
        }
 
        vector<string> articles = extractArticles(response);
        //each article is processed here
        for (string a : articles) {
            string title = getValue(a, "title");
            string storyTitle = getValue(a, "story_title");
            string commentsStr = getValue(a, "num_comments");
            
       
            if (title == "null") title = "";
            if (storyTitle == "null") storyTitle = "";
            if (commentsStr.empty()) commentsStr = "0";
            
            // Determine the article name
            string articleTitle;
            if (!title.empty()) {
                articleTitle = title;
            } else if (!storyTitle.empty()) {
                articleTitle = storyTitle;
            } else {
                continue;
            }
            
            // the article is saved here
            Article temp;
            temp.title = articleTitle;
            temp.comments = toInt(commentsStr);
            validArticles.push_back(temp);
        }
        
        page++;
    }
    
   
    sort(validArticles.begin(), validArticles.end(), compareArticles);
    
    //  top results
    vector<string> result;
    int takeCount = min(limit, (int)validArticles.size());
    for (int i = 0; i < takeCount; i++) {
        result.push_back(validArticles[i].title);
    }
    
    return result;
}

int main() {
    vector<string> top = topArticles(2);
    
    for (string name : top) {
        cout << name << endl;
    }
    
    return 0;
}