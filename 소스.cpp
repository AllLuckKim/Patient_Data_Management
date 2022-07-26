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
			//�� ���ڰ� ���� ���� ��
			if (a[i] != b[i]) {
				//�� �ټ����� ��
				if (a[i][0] >= '0' && a[i][0] <= '9' && b[i][0] >= '0' && b[i][0] <= '9') {
					//�� 0���� ��¥ ��
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
					//���� ���� ��
					if (a_num == b_num) {
						//0�� �� ���� �� �ڷ�
						return a[i].size() > b[i].size();
					}
					//���� �ٸ� ��
					else {
						// 3 , 12 �� 12 < 3�� ŭ
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

				//�� �� �ϳ��� ������ ��
				else if ((a[i][0] >= '0' && a[i][0] <= '9') || (b[i][0] >= '0' && b[i][0] <= '9')) {
					return a[i] < b[i];
				}

				//�Ѵ� ������ ��
				else if (((a[i][0] >= 0x61 && a[i][0] <= 0x7A) || (a[i][0] >= 0x41 && a[i][0] <= 0x5A)) &&
					((b[i][0] >= 0x61 && b[i][0] <= 0x7A) || (b[i][0] >= 0x41 && b[i][0] <= 0x5A))) // �� �� ����
				{
					return a[i] < b[i];
				}
				else if ((a[i][0] >= 0XAC00 && a[i][0] <= 0xD7A3) && (b[i][0] >= 0xAC00 && b[i][0] <= 0xD7A3)) //�� �� �ѱ�
				{
					return a[i][0] < b[i][0];;
				}

				else if (((a[i][0] >= 0x61 && a[i][0] <= 0x7A) || (a[i][0] >= 0x41 && a[i][0] <= 0x5A))) //a�� ����
					
						return true;
					

				else if (((b[i][0] >= 0x61 && b[i][0] <= 0x7A) || (b[i][0] >= 0x41 && b[i][0] <= 0x5A))) // b�� ����
					
						return false;
					
					



			}
		}

		//���� �� �ִ� ��������� �Ȱ��� �� ������ ���� ������ ����
		return a.size() < b.size();
	}
	
};

int main() {
	locale::global(std::locale("kor"));
	wcout.imbue(std::locale("kor"));
	/* ������ */
	set<vector<wstring>, Compare> se;		// ��������, �⺻ �� : less<int>
	//set<int, greater<int>> set;		//��������
	unsigned int N;
	cin >> N;
	set<vector<wstring>>::iterator iter;
	

	for (int i = 0; i < N; i++) {
		wstring s;
		wcin >> s;
		vector<wstring> temp;
		wstring s_temp;
		for (int j = 0; j < s.size(); j++) {
			//����
			if (s[j] >= '0' && s[j] <= '9')
				s_temp += s[j];
			//���� �� ��
			else {
				//���ڰ� �̹� ����Ǿ� ���� ��
				if (s_temp != L"")
					temp.push_back(s_temp);
				s_temp = s[j];
				temp.push_back(s_temp);
				s_temp = L"";//�� �ʱ�ȭ
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

	/* ����, ���� */

	
	return 0;
}


/*
int main() {
	locale::global(std::locale("kor"));
	wcout.imbue(std::locale("kor"));
	
	vector<wstring> v;
	vector<wstring>::iterator iter;

	wchar_t *p;

	v.push_back(L"1��");
	v.push_back(L"2��");
	v.push_back(L"3��");
	v.push_back(L"4��");
	v.push_back(L"111��");
	v.push_back(L"03��");
	v.push_back(L"11��");
	v.push_back(L"10��");
	v.push_back(L"1��$#@321");
	v.push_back(L"1Av��7");
	sort(v.begin(), v.end(), Compare.operator());
	for (iter = v.begin(); iter != v.end(); iter++)
		wcout << (*iter) << "\n";
	p = &(v[0][0]);
	
	wcout << *p << endl;
	
	return 0;


}
*/