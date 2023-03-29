#include "HTMLDecode.h"
#include "iostream"
#include "string"
#include "map"

using namespace std;

//��� ����� 39
// ��������� � ������� ������ array<pair>
const pair<string, char> DECODE_CHARS[] = {{"&quot;", '"'} , {"&apos;", '\''} , {"&lt;", '<'} , {"&gt;", '>'} , {"&amp;", '&'}};


// &&&lt - �� ��������
string HtmlDecode(string const& html)
{
    string decodedHtml = "";
    bool isReplaced = false;
    for (size_t i = 0; i < html.size(); i++)
    {
        if (html[i] != '&')
        {
            decodedHtml += html[i];
        }
        else
        {
            for (auto& strChDecode : DECODE_CHARS)
            {
                if (html.compare(i, strChDecode.first.size(), strChDecode.first) == 0)
                {
                    decodedHtml += strChDecode.second;
                    //�������� 1 ��� ��� ����� ���������� � i, � �� �� ���� �� i
                    i += strChDecode.first.size() - 1;
                    isReplaced = true;
                    break;
                }
            }
            if(!isReplaced) decodedHtml += html[i];
            isReplaced = false;
        }
    }
    return decodedHtml;
}
