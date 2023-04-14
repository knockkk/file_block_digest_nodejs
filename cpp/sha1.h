
#pragma once

#include <sys/types.h>

namespace file_block_digest
{
    typedef struct
    {
        union
        {
            u_int32_t h0; // 兼容openssl SHA_CTX结构
            u_int32_t state[5];
        };
        u_int32_t count[2];
        unsigned char buffer[64];
    } SHA_CTX;

    void SHA1_Init(SHA_CTX *context);
    void SHA1_Update(SHA_CTX *context, const unsigned char *data, u_int32_t len);
    void SHA1_Final(unsigned char digest[20], SHA_CTX *context);

} // namespace file_block_digest
