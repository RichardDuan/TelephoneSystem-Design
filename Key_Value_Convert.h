#pragma once
#define _CRT_SECURE_NO_WARNINGS
#include <cstdint>
#include <cstring>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <string>
#define HASHMAP_SIZE 100000
// 定义SHA-1的常量
constexpr uint32_t K[] = {
    0x5A827999, 0x6ED9EBA1, 0x8F1BBCDC, 0xCA62C1D6
};

// 左循环移位宏
#define SHA1_ROL(value, bits) (((value) << (bits)) | ((value) >> (32 - (bits))))

// SHA-1压缩函数
void sha1_compress(uint32_t state[5], const uint8_t block[64]) {
    uint32_t W[80];

    // 将块分成16个32比特的字
    for (int t = 0; t < 16; ++t) {
        W[t] = (block[t * 4] << 24) | (block[t * 4 + 1] << 16) | (block[t * 4 + 2] << 8) | (block[t * 4 + 3]);
    }

    // 扩展字
    for (int t = 16; t < 80; ++t) {
        W[t] = SHA1_ROL(W[t - 3] ^ W[t - 8] ^ W[t - 14] ^ W[t - 16], 1);
    }

    // 初始化工作变量
    uint32_t A = state[0];
    uint32_t B = state[1];
    uint32_t C = state[2];
    uint32_t D = state[3];
    uint32_t E = state[4];

    // 主循环
    for (int t = 0; t < 80; ++t) {
        uint32_t temp = SHA1_ROL(A, 5) + ((t < 20) ? ((B & C) | ((~B) & D)) : ((t < 40) ? (B ^ C ^ D) : ((t < 60) ? ((B & C) | (B & D) | (C & D)) : (B ^ C ^ D)))) + E + K[t / 20] + W[t];
        E = D;
        D = C;
        C = SHA1_ROL(B, 30);
        B = A;
        A = temp;
    }

    // 更新工作变量
    state[0] += A;
    state[1] += B;
    state[2] += C;
    state[3] += D;
    state[4] += E;
}

// SHA-1哈希函数
void sha1_hash(const uint8_t* input, size_t length, uint32_t hash[5]) {
    // 初始化哈希值
    hash[0] = 0x67452301;
    hash[1] = 0xEFCDAB89;
    hash[2] = 0x98BADCFE;
    hash[3] = 0x10325476;
    hash[4] = 0xC3D2E1F0;

    // 处理输入数据
    for (size_t i = 0; i < length; i += 64) {
        uint8_t block[64];
        size_t block_end = (i + 64 <= length) ? 64 : length - i;

        // 复制块
        std::memcpy(block, input + i, block_end);

        // 添加填充
        if (block_end < 64) {
            block[block_end] = 0x80; // 10000000
            std::memset(block + block_end + 1, 0, 64 - block_end - 1);
            if (block_end < 56) {
                // 在末尾添加消息长度，64位表示
                uint64_t bit_length = (length * 8);
                block[56] = (bit_length >> 56) & 0xFF;
                block[57] = (bit_length >> 48) & 0xFF;
                block[58] = (bit_length >> 40) & 0xFF;
                block[59] = (bit_length >> 32) & 0xFF;
                block[60] = (bit_length >> 24) & 0xFF;
                block[61] = (bit_length >> 16) & 0xFF;
                block[62] = (bit_length >> 8) & 0xFF;
                block[63] = bit_length & 0xFF;
            }
        }

        // 压缩块
        sha1_compress(hash, block);
    }
}

// 将SHA-1哈希值转为十六进制字符串
std::string sha1_hex_string(const uint32_t hash[5], int& length) {
    std::ostringstream oss;
    for (int i = 0; i < 5; ++i) {
        oss << std::hex << std::setw(8) << std::setfill('0') << hash[i];
    }
    std::string result = oss.str(); // 获取存储在ostringstream中的字符串内容
    //std::cout << "SHA-1 Hash: " << result << std::endl; // 输出字符串内容
    //std::cout << "Length: " << result.length() << std::endl; // 输出字符串长度
    return result;
}

size_t hash_function(const std::string& key, size_t table_size) {
    size_t hash = 0;
    for (char ch : key) {
        // 通过将当前字符的ASCII值累加到哈希值，生成一个简单的散列
        hash = hash * 31 + static_cast<size_t>(ch);
    }
    // 取余操作确保哈希值在表的范围内
    return hash % table_size;
}
int KEY_VALUE(const char* input) {   //输入电话号码，输出最终对应的按键值

    // 计算SHA-1哈希值
    uint32_t hash[5];
    sha1_hash(reinterpret_cast<const uint8_t*>(input), std::strlen(input), hash);

    // 输出加密后的结果
   // std::cout << "Input: " << input << std::endl;
    int length;
    int result_final;
    std::string hashed_string = sha1_hex_string(hash, length);
    return hash_function(hashed_string, 1000000);
}