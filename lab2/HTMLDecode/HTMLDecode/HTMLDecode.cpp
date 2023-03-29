#include "HTMLDecode.h"
#include "iostream"
#include "string"
#include "map"

using namespace std;

//ЧТО ТАКОЕ 39
// поместеть в обычный массив array<pair>
const pair<string, char> DECODE_CHARS[] = {{"&quot;", '"'} , {"&apos;", '\''} , {"&lt;", '<'} , {"&gt;", '>'} , {"&amp;", '&'}};


// &&&lt - не работает
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
                    //вычитаем 1 так как поиск начинается с i, а не за один до i
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
