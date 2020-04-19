#include <bits/stdc++.h>
using namespace std;
typedef long long ll;

//Funtion which implements GET Command
string GET(unordered_map<string, string> &keyValue, unordered_map<string, time_t> &expireTime, string &key) {
	//If key is present in the hashmap
	if(keyValue.find(key) != keyValue.end()) {
		
		//To Get current time
		time_t currTime = time(NULL);
		
		//if there is expire time for the key and it is higher than current time
		if(expireTime[key] != -1 && currTime > expireTime[key]) {
			
			//Remove the key from hashmaps
			keyValue.erase(key);
			expireTime.erase(key);
			return "nil";
		}
		//Else Return Value
		return keyValue[key];
	}
	
	//If key is not present
	else
		return "nil";
}

//Funtion which implements SET Command
string SET(unordered_map<string, string> &keyValue, unordered_map<string, time_t> &expireTime, string &key, string &value) {
	//If key is present in hashmap
	if(keyValue.find(key) != keyValue.end()) {
		
		//Change the existing values in hashmap
		keyValue[key] = value;
		expireTime[key] = -1;
	}
	//If key is not present in hashmap
	else {
		
		//Create new key, value and expire time in hashmap
		keyValue.insert(make_pair(key, value));
		expireTime.insert(make_pair(key, -1));
	}
	
	//Value is successfully set
	return "OK";
}

//Funtion which implements EXPIRE Command
int EXPIRE(unordered_map<string, time_t> &expireTime, string &key, int sec) {
	
	//If the key is not present in hashmap
	if(expireTime.find(key) == expireTime.end())
		return 0; //key is not present
		
	//Change the expire time of key 
	expireTime[key] = time(NULL) + sec;
	return 1; //key is present
}

//Funtion which implements ZADD Command
int ZADD(unordered_map<string, set<pair<ll, string> > > &keySortedSet, unordered_map<string, unordered_map<string, ll> > &keyValueScore, string &key, vector<pair<ll, string> > &addList) {
	
	//If the key is not present
	if(keySortedSet.find(key) == keySortedSet.end()) {
		
		//Add the score and members in both the hashmaps
		for(auto &it : addList) {
			keySortedSet[key].insert(make_pair(it.first, it.second));
			keyValueScore[key].insert(make_pair(it.second, it.first));
		}
		
		//Return number of members added
		return addList.size();
	}
	
	//Loop through all the members
	for(auto &it : addList) {
		
		//If the member does not exist then just add it
		if(keyValueScore[key].find(it.second) == keyValueScore[key].end()) {
			keySortedSet[key].insert(make_pair(it.first, it.second));
			keyValueScore[key].insert(make_pair(it.second, it.first));
		}
		//If the member already exist then remove it and add it with new score
		else {
			auto iterator = keyValueScore[key].find(it.second);
			keySortedSet[key].erase(make_pair(iterator->second, iterator->first));
			keyValueScore[key].erase(iterator);
			keySortedSet[key].insert(make_pair(it.first, it.second));
			keyValueScore[key].insert(make_pair(it.second, it.first));
		}
	}
	//Return number of members added
	return addList.size();
}

//Funtion which implements ZRANGE Command
void ZRANGE(unordered_map<string, set<pair<ll, string> > > &keySortedSet, string &key, ll start, ll end, int withScore) {
	//Change value of start if it is negative
	if(start < 0)
		start = max(0LL, (ll)keySortedSet[key].size() + start);
	//Change value of end if it is negative
	if(end < 0)
		end = min(keySortedSet[key].size() - 1, keySortedSet[key].size() + end);
	int index = 0;
	
	//Loop through all the members of key
	for(auto &it : keySortedSet[key]) {
		//If they are not in the range
		if(index < start)
			continue;
		if(index > end)
			break;
		index++;
		
		//Print accordingly with or without score
		if(withScore)
			cout<<it.first<<" "<<it.second<<endl;
		else
			cout<<it.second<<endl;
	}
}

//Funtion which implements ZRANK Command
string ZRANK(unordered_map<string, set<pair<ll, string> > > &keySortedSet, unordered_map<string, unordered_map<string, ll> > &keyValueScore, string &key, string &value) {
	int index = 0;
	
	//Loop through all the members of key
	for(auto &it : keySortedSet[key]) {
		
		//If we get the required member then return its index
		if(it.first == keyValueScore[key][value] && it.second == value)
			return to_string(index);
		index++;
	} 
	
	//If key is not present
	return "nil";
}

int main() {
	
	//Hashmap of key Value pairs
	unordered_map<string, string> keyValue;
	
	//Hashmap of key and their expire times
	unordered_map<string, time_t> expireTime;
	
	//Hashmap of key and sorted set(score and member)
	unordered_map<string, set<pair<ll, string> > > keySortedSet;
	
	//Hashmap of kay and hashmap of member and score
	unordered_map<string, unordered_map<string, ll> > keyValueScore;
	
	//String to take command name as input
	string command; 
	
	//Loop till commands are given by the user
	while(cin >> command) {
		if(command == "GET") {
			string key;
			cin>>key;
			cout<<GET(keyValue, expireTime, key)<<endl;
		}
		else if(command == "SET") {
			string key, value;
			cin>>key>>value;
			cout<<SET(keyValue, expireTime, key, value)<<endl;
		}
		else if(command == "EXPIRE") {
			string key;
			cin>>key;
			int sec;
			cin>>sec;
			cout<<EXPIRE(expireTime, key, sec)<<endl;
		}
		else if(command == "ZADD") {
			string key;
			cin>>key;
			ll score;
			string value, input;
			//To store all the score and members provided by the user
			vector<pair<ll, string> > addList;
			
			//Take input as a line as number of members are not given
			getline(cin, input);
			
			//Change input into string stream
			stringstream ss(input);
			
			//Loop to add all the members with score in vector
			while(ss >> score >> value)
				addList.push_back(make_pair(score, value));
			cout<<ZADD(keySortedSet, keyValueScore, key, addList)<<endl;	
		}
		else if(command == "ZRANGE") {
			string key;
			cin>>key;
			ll start, end;
			cin>>start>>end;
			string withScore;
			
			//Take rest of the input as line to check whether withscore is present or not
			getline(cin, withScore);
			
			//If withscore is not present
			if(withScore == "")
				ZRANGE(keySortedSet, key, start, end, 0);
			//If withscore is present
			else
				ZRANGE(keySortedSet, key, start, end, 1);
		}
		else if(command == "ZRANK") {
			string key, value;
			cin>>key>>value;
			cout<<ZRANK(keySortedSet, keyValueScore, key, value)<<endl;
		}
		
		//Command to Exit from the program
		else if(command == "QUIT")
			break;
			
		//If the command is not recognized
		else
			cout<<"If this command exits, then it is not implemented in this code yet..."<<endl;
	}
}
