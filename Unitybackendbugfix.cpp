// Unitybackendbugfix.cpp: 定义控制台应用程序的入口点。
//

#include "stdafx.h"

using namespace std;


string path;
vector<string>allFiles;
vector<string>jsonPaths;

void GetFile(string path,vector<string>& files);
void SearchJson(const vector<string>& allFiles,/*out*/vector<string>&jsonFiles);
void ChangeUAPVersion(const vector<string>&jsonFiles);

int main(int argv,char *argc[])
{
	if (argv == 1)
	{
		cout << "Usage: Unitybackendfix.exe AppFolder" << endl;
		return 1;
	}
	else
	{
		path = argc[1];
		GetFile(path, allFiles);
		SearchJson(allFiles, jsonPaths);
		ChangeUAPVersion(jsonPaths);
	}
    return 0;
}
void GetFile(string path, vector<string>& files)
{
		//文件句柄
		long   hFile = 0;
		//文件信息
		struct _finddata_t fileinfo;
		string p;
		if ((hFile = _findfirst(p.assign(path).append("\\*").c_str(), &fileinfo)) != -1)
		{
			do
			{
				//如果是目录,迭代之
				//如果不是,加入列表
				if ((fileinfo.attrib &  _A_SUBDIR))
				{
					if (strcmp(fileinfo.name, ".") != 0 && strcmp(fileinfo.name, "..") != 0)
						GetFile(p.assign(path).append("\\").append(fileinfo.name), files);
				}
				else
				{
					files.push_back(p.assign(path).append("\\").append(fileinfo.name));
				}
			} while (_findnext(hFile, &fileinfo) == 0);
			_findclose(hFile);
		}
}
void SearchJson(const vector<string>& allFiles,/*out*/vector<string>&jsonFiles)
{
	for (string i : allFiles)
	{
		if (i.find("project.lock.json") != string::npos)
		{
			jsonFiles.push_back(i);
		}
	}
}
void ChangeUAPVersion(const vector<string>&jsonFiles)
{
	ifstream jsonInStream;
	for (string i : jsonFiles)
	{
		jsonInStream.open(i);
		if (jsonInStream.is_open())
		{
			stringstream buffer;
			buffer << jsonInStream.rdbuf();
			string text(buffer.str());
			regex pattern("UAP,Version=v[0-9\\.]*");

			//Search::
			//smatch versionMatch;
			//if (regex_search(text, versionMatch, pattern))
			//{
			//	cout << versionMatch[0] << endl;
			//}
			//auto wordsBegin = sregex_iterator(text.begin(), text.end(), pattern);
			//auto wordsEnd = sregex_iterator();
			//for (sregex_iterator i = wordsBegin; i != wordsEnd; ++i)
			//{
			//	smatch match = *i;
			//	string matchStr = match.str();
			//	cout << matchStr << endl;
			//}

			//Replace::
			smatch versionMatches;
			string replace = "UAP,Version=v10.0";
			string temp = regex_replace(text, pattern, replace);

			
			jsonInStream.close();
			ofstream jsonOutStream(i);
			if (jsonOutStream.is_open())
			{
				jsonOutStream << temp;
			}
			else
			{
				cout << "Writing Json Error" << endl;
				exit(-1);
			}
		}
		else
		{
			cout << "Reading Json Error" << endl;
			exit(1);
		}
	}
}