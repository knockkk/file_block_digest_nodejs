#include "file_block_digest.h"

#include <string.h>
#include <sstream>

#include "sha1.h"

#define SHA1_LENGTH 20
// 固定2M
#define SHA1_BLOCK_SIZE 2097152

namespace file_block_digest
{

    static std::string StrToHex(const char *src, size_t len)
    {
        std::stringstream ss;
        char hex[3] = {0};
        for (size_t i = 0; i < len; ++i)
        {
            snprintf(hex, sizeof(hex), "%02x", (unsigned char)(src[i]));
            ss << hex;
        }
        return ss.str();
    }

    static std::string SHA1State(SHA_CTX *ctx)
    {
        return StrToHex((char *)&ctx->h0, SHA1_LENGTH);
    }

    static std::string SHA1Final(SHA_CTX *ctx)
    {
        unsigned char tmp[SHA1_LENGTH];
        SHA1_Final(tmp, ctx);
        return StrToHex((char *)tmp, SHA1_LENGTH);
    }

    int GetFileDigestInfo(const char *content, uint32_t content_size, FileDigestInfo *info)
    {
        if (content == NULL || content_size == 0)
        {
            return -1;
        }

        SHA_CTX ctx;
        SHA1_Init(&ctx);

        uint32_t i = 1;
        uint64_t beg_offset = 0;
        const uint32_t total_block = (content_size - 1) / SHA1_BLOCK_SIZE + 1;
        for (; i <= total_block; ++i)
        {
            info->parts.push_back(BlockInfo());
            BlockInfo &part = info->parts.back();
            part.part_num = i;

            if (i * SHA1_BLOCK_SIZE > content_size)
            {
                // last block
                part.end_offset = content_size;
            }
            else
            {
                part.end_offset = i * SHA1_BLOCK_SIZE;
            }
            beg_offset = (i - 1) * SHA1_BLOCK_SIZE;
            SHA1_Update(&ctx, (unsigned char *)(content + beg_offset), part.end_offset - beg_offset);

            if (i == total_block)
            {
                // last block
                part.cumulate_sha1 = SHA1Final(&ctx);
            }
            else
            {
                part.cumulate_sha1 = SHA1State(&ctx);
            }
        }

        return 0;
    }

} // namespace file_block_digest
