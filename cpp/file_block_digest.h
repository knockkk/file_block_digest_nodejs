#pragma once

#include <vector>
#include <string>

namespace file_block_digest
{

    struct BlockInfo
    {
        BlockInfo() {}

        uint32_t part_num; // 当前块序号，从1开始
        // TODO 无法使用uint64_t。最大为 2^32 - 1，支持的文件大小的 4 GB。
        // https://github.com/emscripten-core/emscripten/issues/13902
        uint32_t end_offset;       // 当前块结尾在文件中的下标
        std::string cumulate_sha1; // 当前累积sha1
    };

    struct FileDigestInfo
    {
        FileDigestInfo() {}

        std::vector<BlockInfo> parts;
    };

    int GetFileDigestInfo(const char *content, uint32_t content_size, FileDigestInfo *info);
}
