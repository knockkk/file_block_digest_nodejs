#include <emscripten/bind.h>
#include <stdio.h>
#include <iostream>
#include <sstream>
#include <vector>

#include "file_block_digest.h"

using namespace emscripten;

file_block_digest::FileDigestInfo generateFileBlockDigest(std::string content)
{
    file_block_digest::FileDigestInfo upload_info;
    file_block_digest::GetFileDigestInfo(content.c_str(), content.size(), &upload_info);

    return upload_info;
}

EMSCRIPTEN_BINDINGS(module)
{
    class_<file_block_digest::BlockInfo>("BlockInfo")
        .property("part_num", &file_block_digest::BlockInfo::part_num)
        .property("end_offset", &file_block_digest::BlockInfo::end_offset)
        .property("cumulate_sha1", &file_block_digest::BlockInfo::cumulate_sha1);

    class_<file_block_digest::FileDigestInfo>("FileDigestInfo")
        .property("parts", &file_block_digest::FileDigestInfo::parts);

    register_vector<file_block_digest::BlockInfo>("FileDigestInfoVector");

    function("generateFileBlockDigest", &generateFileBlockDigest);
}
