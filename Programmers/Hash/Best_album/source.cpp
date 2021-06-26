#include <string>
#include <vector>
#include <unordered_map>
#include <queue>
using namespace std;
struct song {
    song() : id(-1), play(-1) {}
    int id, play;
};
class genre {
public:
    // 장르에 곡 추가하는 기능.
    // 가장 재생 횟수가 많은 상위 2곡을 보유하는 기능이 포함됨.
    // 재생 횟수가 같은 곡 중에서는 고유번호가 낮은 곡이 우선되는데,
    // 곡 추가 시 고유번호가 낮은 것부터 넣으므로
    // 정렬 기준에서 '=' 조건을 제거하여 해결
    void Add(const int id, const int plays) {
        if (plays > songs[1].play) {
            songs[1].play = plays;
            songs[1].id = id;
            if (plays > songs[0].play)
                swap(songs[0], songs[1]);
        }
        play += plays;
    }
    int play;
    song songs[2];
};

vector<int> solution(vector<string> genres, vector<int> plays)
{
    // 장르를 키로 하는 해시에 값 추가
    unordered_map<string, genre> m;
    for (int i = 0; i < genres.size(); i++)
        m[genres[i]].Add(i, plays[i]);

    // 우선순위 큐를 이용하여 장르 별 총 재생 수 삽입
    struct ptype {
        ptype(const string& genreName, const int plays) : genre(genreName), play(plays) {}
        string genre;
        int play;
    };
    auto cmp = [](const ptype& a, const ptype& b) { return a.play < b.play; };
    priority_queue<ptype, vector<ptype>, decltype(cmp)> pq(cmp);
    for (auto iter : m)
        pq.push(ptype(iter.first, iter.second.play));
    
    // 우선순위 큐 순회
    vector<int> answer;
    while (!pq.empty()) {
        answer.emplace_back(m[pq.top().genre].songs[0].id);
        auto temp = m[pq.top().genre].songs[1].id;
        if (0 <= temp) answer.emplace_back(temp);   // 해당 장르에 1곡만 포함될 경우 고려
        pq.pop();
    }
    return answer;
}