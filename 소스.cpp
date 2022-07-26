#include <iostream>
#include <vector>
#include <string>
#include <locale>
#include <cstdlib>
#include <algorithm>
#include <cstdio>



using namespace std;
#include <set>
struct Compare {
	bool operator() (const vector<wstring> &a, const vector<wstring> &b) const
	{
		int min_size = min(a.size(), b.size());

		for (int i = 0; i < min_size; i++) {
			//두 문자가 같지 않을 때
			if (a[i] != b[i]) {
				//둘 다숫자일 때
				if (a[i][0] >= '0' && a[i][0] <= '9' && b[i][0] >= '0' && b[i][0] <= '9') {
					//앞 0없앤 진짜 수
					wstring a_num = L"";
					wstring b_num = L"";
					for (int j = 0; j < a[i].size(); j++) {
						if (a[i][j] != '0') {
							a_num = a[i].substr(j);
							break;
						}
					}
					for (int j = 0; j < b[i].size(); j++) {
						if (b[i][j] != '0') {
							b_num = b[i].substr(j);
							break;
						}
					}
					//수가 같을 때
					if (a_num == b_num) {
						//0이 더 많은 수 뒤로
						return a[i].size() > b[i].size();
					}
					//수가 다를 때
					else {
						// 3 , 12 비교 12 < 3이 큼
						if (a_num.size() < b_num.size())
							return true;
						else if (a_num.size() > b_num.size())
							return false;
						else {
							if (a_num < b_num)
								return true;
							return false;
						}
					}
				}

				//둘 중 하나가 숫자일 때
				else if ((a[i][0] >= '0' && a[i][0] <= '9') || (b[i][0] >= '0' && b[i][0] <= '9')) {
					return a[i] < b[i];
				}

				//둘다 영어일 때
				else if (((a[i][0] >= 0x61 && a[i][0] <= 0x7A) || (a[i][0] >= 0x41 && a[i][0] <= 0x5A)) &&
					((b[i][0] >= 0x61 && b[i][0] <= 0x7A) || (b[i][0] >= 0x41 && b[i][0] <= 0x5A))) // 둘 다 영어
				{
					return a[i] < b[i];
				}
				else if ((a[i][0] >= 0XAC00 && a[i][0] <= 0xD7A3) && (b[i][0] >= 0xAC00 && b[i][0] <= 0xD7A3)) //둘 다 한글
				{
					return a[i][0] < b[i][0];;
				}

				else if (((a[i][0] >= 0x61 && a[i][0] <= 0x7A) || (a[i][0] >= 0x41 && a[i][0] <= 0x5A))) //a가 영어
					
						return true;
					

				else if (((b[i][0] >= 0x61 && b[i][0] <= 0x7A) || (b[i][0] >= 0x41 && b[i][0] <= 0x5A))) // b가 영어
					
						return false;
					
					



			}
		}

		//비교할 수 있는 사이즈까지 똑같을 때 사이즈 작은 순으로 정렬
		return a.size() < b.size();
	}
	
};

int main() {
	locale::global(std::locale("kor"));
	wcout.imbue(std::locale("kor"));
	/* 생성자 */
	set<vector<wstring>, Compare> se;		// 오름차순, 기본 값 : less<int>
	//set<int, greater<int>> set;		//내림차순
	unsigned int N;
	cin >> N;
	set<vector<wstring>>::iterator iter;
	

	for (int i = 0; i < N; i++) {
		wstring s;
		wcin >> s;
		vector<wstring> temp;
		wstring s_temp;
		for (int j = 0; j < s.size(); j++) {
			//숫자
			if (s[j] >= '0' && s[j] <= '9')
				s_temp += s[j];
			//숫자 이 외
			else {
				//숫자가 이미 저장되어 있을 때
				if (s_temp != L"")
					temp.push_back(s_temp);
				s_temp = s[j];
				temp.push_back(s_temp);
				s_temp = L"";//수 초기화
			}
		}
		if (s_temp != L"")
			temp.push_back(s_temp);
		se.insert(temp);
	}
	wcout << endl;
	for (iter = se.begin(); iter != se.end(); ++iter) 
	{
		
		auto iter_v = (*iter).begin();
		
		
		wstring s_temp;
		for (auto iter_v = (*iter).begin(); iter_v != (*iter).end(); ++iter_v)
		{
			wcout << (*iter_v);
		}
		wcout << endl;
		
		
	}

	/* 삽입, 삭제 */

	
	return 0;
}


/*
int main() {
	locale::global(std::locale("kor"));
	wcout.imbue(std::locale("kor"));
	
	vector<wstring> v;
	vector<wstring>::iterator iter;

	wchar_t *p;

	v.push_back(L"1번");
	v.push_back(L"2번");
	v.push_back(L"3번");
	v.push_back(L"4번");
	v.push_back(L"111번");
	v.push_back(L"03번");
	v.push_back(L"11번");
	v.push_back(L"10번");
	v.push_back(L"1ㅊ$#@321");
	v.push_back(L"1Av가7");
	sort(v.begin(), v.end(), Compare.operator());
	for (iter = v.begin(); iter != v.end(); iter++)
		wcout << (*iter) << "\n";
	p = &(v[0][0]);
	
	wcout << *p << endl;
	
	return 0;


}
*/