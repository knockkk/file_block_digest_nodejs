#include <stdio.h>
#include <iostream>
#include <sstream>
#include <fstream>
#include <vector>

#include "file_block_digest.h"

using namespace std;

string Readfile(const string &file_path)
{
    ifstream file(file_path.c_str());
    if (!file.is_open())
    {
        return "";
    }
    int len;
    file.seekg(0, ios::end);
    len = file.tellg();
    file.seekg(0, ios::beg);
    if (len == 0)
    {
        file.close();
        return "";
    }
    char *buf = new char[len];
    file.read(buf, len);
    file.close();
    string content(buf, len);
    delete[] buf;
    return content;
}

int main(int argc, char *argv[])
{
    if (argc < 2)
    {
        printf("Usage: %s <path>\n", argv[0]);
    }

    string content = Readfile("./file/sha_calc_demo.txt");

    file_block_digest::FileDigestInfo upload_info;
    file_block_digest::GetFileDigestInfo(content.c_str(), content.size(), &upload_info);

    printf("blocks: %zd\n", upload_info.parts.size());
    for (size_t i = 0; i < upload_info.parts.size(); ++i)
    {
        file_block_digest::BlockInfo &part = upload_info.parts[i];
        printf("part_num: %u cumulate_sha1: %s\n",
               part.part_num, part.cumulate_sha1.c_str());
    }

    return 0;
}